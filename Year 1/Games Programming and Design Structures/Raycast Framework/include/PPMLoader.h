#include <stdafx.h>
#pragma once

#ifndef __PPM_IMAGE_H__
#define __PPM_IMAGE_H__

//PPM Image Def
//Text/ASCII File
//Magic Number
//Possible Comments
//Width & Height
//MAX_COLOUR
//Image Data - RGB

template <typename T>
struct PPMPixel
{
	T r;
	T g;
	T b;
};

struct PPM
{
	unsigned short id;
	char comment[512];
	unsigned int width;
	unsigned int height;
	unsigned int maxColours;
	
	void* pixelData;
};

class PPMLoader
{
public:
	PPMLoader() {};
	~PPMLoader() {};

	static void* LoadFromFile(const void* a_stream, u32& a_w, u32& a_h, u8& a_bpp);
};

#endif //__PPM_IMAGE_H__