#include <stdafx.h>
#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

class Texture
{
public:
	#pragma region Constructor and Destructor
	Texture();
	~Texture();
	#pragma endregion

	#pragma region Getter Functions
	const std::string& GetFileName() const { return m_fileName; }
	void GetDimensions(u32& a_width, u32& a_height) const;
	u8 GetBPP() { return m_bpp; }
	u16 GetPalette(void* a_palette);
	void* GetPixelData() { return m_pixelData; }
	#pragma endregion

	#pragma region Other Functions
	bool Load(const char* a_fileName, u32 a_format);
	#pragma endregion

private:
	#pragma region Variables
	std::string m_fileName;
	u32 m_width;
	u32 m_height;
	u16 m_paletteSize;
	u8 m_bpp;
	void* m_palette;
	void* m_pixelData;
	#pragma endregion
};

#endif //__TEXTURE_H__
