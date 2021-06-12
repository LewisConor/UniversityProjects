#include <stdafx.h>

#pragma once
#ifndef __PCX_LOADER_H__
#define __PCX_LOADER_H__

#define PCX_VALID_HEADER 10
#define PCX_RLE_ENCODING 1
#define PCX_VGA_PALETTE_OFFSET -769
#define PCX_RLE_MASK 0xC0 //0x1100 0000
#define PCX_RLE_FREQ_MASK 0x3F //0x0011 1111

//Default VGA Palette V3.0
const u8 PCX_defaultPalette[48] =
{
	0x00, 0x00, 0x00,	0x00, 0x00, 0x80,	0x00, 0x80, 0x00,
	0x00, 0x80, 0x80,	0x80, 0x00, 0x00,	0x80, 0x00, 0x80,
	0x80, 0x80, 0x00,	0x80, 0x80, 0x80,	0xC0, 0xC0, 0xC0,
	0x00, 0x00, 0xFF,	0x00, 0xFF, 0x00,	0x00, 0xFF, 0xFF,
	0xFF, 0x00, 0x00,	0xFF, 0x00, 0xFF,	0xFF, 0xFF, 0x00,
	0xFF, 0xFF, 0xFF
};

typedef struct PCXHeader
{
	u8 identifier;
	u8 version;
	u8 encoding;
	u8 bitsPerPixel;

	struct PCXDimensions { u16 left; u16 top; u16 right; u16 bottom; } dimensions;

	u16 hRes;
	u16 vRes;

	struct PCXPaletteColour { u8 R; u8 G; u8 B; } colourPalette[16];

	u8 reservedByte;
	u8 numColourPlanes;
	u16 bytesPerScanLine;
	u16 paletteInfo;
	u16 hScreenRes;
	u16 vScreenRes;
	u8 padding[54];
}PCXHeader;

class PCXLoader
{
public:
	PCXLoader() {};
	~PCXLoader() {};

	static void* LoadFromFile(std::fstream* a_stream, u32& a_w, u32& a_h, u8& a_bpp, void*& a_imgPalette);
	static void* ConvertTo32BPP(void* a_imageData, void* a_imgPalette, u32& a_w, u32& a_h, u8& a_bpp);
};

#endif //__PCX_LOADER_H__