//Precompiled Header File
#include <stdafx.h>

//Header File
#include "ImageLoader.h"

//Other Includes
#include "PCXLoader.h"
#include "PPMLoader.h"

//Load Image from File
void* ImageLoader::LoadFromFile(const char* a_fileName, u32 a_type, u32& a_w, u32& a_h, u8& a_bpp, void*& a_imgPalette)
{
	//Get File from Stream
	std::fstream file;
	file.open(a_fileName, std::ios_base::in | std::ios_base::binary);

	//If File is Open else Return Nullptr
	if (file.is_open())
	{
		file.ignore(std::numeric_limits<std::streamsize>::max());
		std::streamsize fileLength = file.gcount();
		file.clear();
		file.seekg(0, std::ios_base::beg);
		if (fileLength == 0)
		{
			file.close();
			return nullptr;
		}

		void* imageData = nullptr;

		switch (a_type)
		{
			case IM_PCX: 
			{
				imageData = PCXLoader::LoadFromFile(&file, a_w, a_h, a_bpp, a_imgPalette);

				if (a_bpp != 32)
				{
					imageData = PCXLoader::ConvertTo32BPP(imageData, a_imgPalette, a_w, a_h, a_bpp);
				}
				break;
			}
			case IM_PPM:
			{
				imageData = PPMLoader::LoadFromFile(&file, a_w, a_h, a_bpp);
				a_bpp = 24;
				
				break;
			}
			case IM_BITMAP: 
			{
				break;
			}
			default: 
			{
				file.close();
				return nullptr;
			}
		}

		file.close();
		return imageData;
	}
	return nullptr;
}