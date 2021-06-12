#include <stdafx.h>

#pragma once
#ifndef __IMAGE_LOADER_H__
#define __IMAGE_LOADER_H__

typedef enum Image_Type
{
	IM_PCX,
	IM_PPM,
	IM_BITMAP,

	IM_MAX
}Image_Type;

class ImageLoader
{
public:
	ImageLoader() {};
	~ImageLoader() {};

	static void* LoadFromFile(const char* a_fileName, u32 a_type, u32& a_w, u32& a_h, u8& a_bpp, void*& a_imgPalette);
};

#endif // __IMAGE_LOADER_H__
