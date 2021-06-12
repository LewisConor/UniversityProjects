//Precompiled Header File
#include <stdafx.h>

//Header File
#include "PCXLoader.h"

int PCXGetEncodedByte(u8& a_value, u8& a_frequency, std::fstream* a_stream)
{
	if (a_stream->peek() == EOF)
	{
		return EOF;
	}

	a_frequency = 1;
	a_stream->read((char*)(&a_value), 1);

	if ((a_value & PCX_RLE_MASK) == PCX_RLE_MASK)
	{
		a_frequency = a_value & PCX_RLE_FREQ_MASK;

		if (a_stream->peek() == EOF)
		{
			return EOF;
		}

		a_stream->read((char*)(&a_value), 1);
	}

	return 0;
}

void* PCXLoader::LoadFromFile(std::fstream* a_stream, u32& a_w, u32& a_h, u8& a_bpp, void*& a_imgPalette)
{
	std::fstream* file = a_stream;
	PCXHeader header;

	//Read all 128 Bytes
	file->read((char*)(&header), sizeof(PCXHeader));

	//Check if it is Valid if not Bail
	if (header.identifier != PCX_VALID_HEADER || header.encoding != PCX_RLE_ENCODING)
	{
		file->close();
		return nullptr;
	}
	
	//Get Palette Info if available 
	if (header.version == 3)
	{
		//V3.0 has no Palette, use Default
		u8* egaPalette = (u8*)(header.colourPalette);
		for (int i = 0; i < 16; ++i)
		{
			egaPalette[i] = PCX_defaultPalette[i];
		}
	}

	if (header.bitsPerPixel == 8)
	{
		file->seekg(PCX_VGA_PALETTE_OFFSET, std::ios_base::end);
		char paletteIndicator = 0;
		file->read(&paletteIndicator, 1);

		if (paletteIndicator == 0xc)
		{
			a_imgPalette = new PCXHeader::PCXPaletteColour[256];
			file->read((char*)(a_imgPalette), 256 * sizeof(PCXHeader::PCXPaletteColour));
		}

		file->clear();
		file->seekg(0, std::ios_base::beg);
		file->seekg(sizeof(PCXHeader), std::ios_base::beg);
	}

	if (!a_imgPalette && (header.numColourPlanes * header.bitsPerPixel) < 24)
	{
		a_imgPalette = new PCXHeader::PCXPaletteColour[16];
		memcpy(a_imgPalette, header.colourPalette, 48);
	}

	//Get Pixel Size of Image
	a_w = header.dimensions.right - header.dimensions.left + 1;
	a_h = header.dimensions.bottom - header.dimensions.top + 1;
	a_bpp = header.bitsPerPixel * header.numColourPlanes;

	//Size of Decompressed Image
	u32 bytesInRow = (u32)(a_w * (float)(a_bpp / 8.f));
	u32 decompImageSize = a_h * bytesInRow;

	//Size of Decompressed Image Scanline
	u32 decompScanLine = header.bytesPerScanLine * header.numColourPlanes;

	//Calculate Line Padding
	u32 scanlinePadding = decompScanLine - bytesInRow;
	u32 actualBytesPerImageRow = decompScanLine - scanlinePadding;

	//Create Data Buffer for Decompressed Image
	u8* imageData = new u8[decompImageSize];
	memset(imageData, 0, decompImageSize);

	u8* scanlineData = new u8[decompScanLine];
	memset(scanlineData, 0, decompScanLine);

	//Stack Variables
	u8 value = 0;
	u8 frequency = 0;

	u32 bytesProcessed = 0;
	std::streamsize streamLocation;
	u32 row = 0;

	while (row < a_h - 1)
	{
		streamLocation = file->tellg();

		//Decode each Row of Image Data
		for (u8* slp = scanlineData; slp < (scanlineData + decompScanLine);)
		{
			if (EOF == PCXGetEncodedByte(value, frequency, file))
			{
				//Null the Data and Close File
				delete[] imageData;
				imageData = nullptr;
				
				if (!a_imgPalette)
				{
					delete[] a_imgPalette;
					a_imgPalette = nullptr;
				}

				return imageData;
			}

			for (u8 i = 0; i < frequency; ++i)
			{
				*slp++ = value;
			}
		}

		++row;

		//Copy based off Num of Colour Planes
		if (header.numColourPlanes != 1)
		{
			//Scanline Colour Data Variables
			u8* red = scanlineData;
			u8* green = scanlineData + header.bytesPerScanLine;
			u8* blue = scanlineData + (header.bytesPerScanLine * 2);
			u8* alpha = header.numColourPlanes == 4 ? scanlineData + (header.bytesPerScanLine * 3) : nullptr;

			for (u32 processedBytes = bytesProcessed; processedBytes < (bytesProcessed + actualBytesPerImageRow);)
			{
				if (header.bitsPerPixel == 8)
				{
					imageData[processedBytes + 0] = *red++;
					imageData[processedBytes + 1] = *green++;
					imageData[processedBytes + 2] = *blue++;

					if (alpha != nullptr)
					{
						imageData[processedBytes + 3] = *alpha++;
					}

					processedBytes += header.numColourPlanes;
				}
			}
		}
		else
		{
			memcpy(&imageData[bytesProcessed], scanlineData, actualBytesPerImageRow);
		}

		bytesProcessed += actualBytesPerImageRow;
	}

	return imageData;
}

void* PCXLoader::ConvertTo32BPP(void* a_imageData, void* a_imgPalette, u32& a_w, u32& a_h, u8& a_bpp)
{
	//Allocated Mem for Image Data in RGBA
	u8* rawImage = new u8[a_w * a_h * 4];
	u32 currentDataSize = a_w * (u32)(a_h * ((float)a_bpp / 8.f));
	u8* currentImage = (u8*)a_imageData;

	if (a_imgPalette != nullptr)
	{
		PCXHeader::PCXPaletteColour* palette = (PCXHeader::PCXPaletteColour*)a_imgPalette;

		for (u32 pixel = 0, i = 0; pixel < currentDataSize; ++pixel, i += 4)
		{
			u32 pix = currentImage[pixel];

			if (a_bpp == 8)
			{
				rawImage[i + 0] = palette[pix].B;
				rawImage[i + 1] = palette[pix].G;
				rawImage[i + 2] = palette[pix].R;
				rawImage[i + 3] = 0;
			}
			else if (a_bpp == 4)
			{
				rawImage[i + 0] = palette[(pix >> 4) & 0xf].B;
				rawImage[i + 1] = palette[(pix >> 4) & 0xf].G;
				rawImage[i + 2] = palette[(pix >> 4) & 0xf].R;
				rawImage[i + 3] = 0;

				i += 4;

				rawImage[i + 0] = palette[pix & 0xf].B;
				rawImage[i + 1] = palette[pix & 0xf].G;
				rawImage[i + 2] = palette[pix & 0xf].R;
				rawImage[i + 3] = 0;
			}
		}
	}
	else
	{
		for (u32 pixel = 0, i = 0; pixel < currentDataSize; pixel += 3, i += 3)
		{
			rawImage[i + 0] = currentImage[pixel + 2];
			rawImage[i + 1] = currentImage[pixel + 1];
			rawImage[i + 2] = currentImage[pixel];
			rawImage[i + 3] = 0;
		}
	}

	delete[] a_imageData, a_imgPalette;
	a_imageData = nullptr, a_imgPalette = nullptr;

	return rawImage;
}