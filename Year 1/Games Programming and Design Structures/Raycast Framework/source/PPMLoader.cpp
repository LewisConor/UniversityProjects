//Precompiled Header File
#include <stdafx.h>

//Header File
#include "PPMLoader.h"

void* PPMLoader::LoadFromFile(const void* a_stream, u32& a_w, u32& a_h, u8& a_bpp)
{
	std::fstream* file = (std::fstream*)a_stream;

	PPM image;
	//Read as text
	char buffer[512];
	memset(buffer, 0, 512);

	//Gets File Header
	file->getline(buffer, 512);
	memcpy(&image.id, buffer, 2);
	if (image.id != 13904)
	{
		return nullptr;
	}

	//Comment Line
	memset(buffer, 0, 512);
	file->getline(buffer, 512);
	if (buffer[0] == '#')
	{
		//File has Comment
		memcpy(image.comment, buffer, 512);
	}

	//Read Image Dimensions
	memset(buffer, 0, 512);
	*file >> image.width >> image.height;

	a_w = image.width;
	a_h = image.height;

	*file >> image.maxColours;

	file->ignore(1);

	unsigned int pixelSize = 0;

	//Create PPM Image Object for Storage
	if (image.maxColours > 255)
	{
		image.pixelData = new PPMPixel<unsigned short>[image.width * image.height];
		pixelSize = image.width * image.height * sizeof(PPMPixel<unsigned short>);
	}
	else
	{
		image.pixelData = new PPMPixel<unsigned char>[image.width * image.height];
		pixelSize = image.width * image.height * sizeof(PPMPixel<unsigned char>);
	}

	file->read((char*)image.pixelData, pixelSize);
	file->close();

	a_bpp = 24;

	//Converts the image into 32 bit BMP
	u8* imageData = new u8[image.width * image.height * 4];
	for (u32 pixel = 0, i = 0; pixel < pixelSize; pixel += 3, i += 4)
	{
		u8* ppmPixel = (u8*)(image.pixelData);
		imageData[i + 0] = ppmPixel[pixel+2];
		imageData[i + 1] = ppmPixel[pixel+1];
		imageData[i + 2] = ppmPixel[pixel+0];
		imageData[i + 3] = 0;
	}

	delete[] image.pixelData;
	image.pixelData = imageData;

	return image.pixelData;
}