//Precompiled Header File
#include <stdafx.h>

//Header File
#include "Texture.h"

//Other Includes
#include "ImageLoader.h"

#pragma region Constructor and Destructor
Texture::Texture() : m_fileName(""), m_width(0), m_height(0), m_bpp(0), m_paletteSize(0), m_palette(nullptr), m_pixelData(nullptr) { }

Texture::~Texture()
{
	if (m_palette)
	{
		delete[] m_palette;
		m_palette = nullptr;
	}

	if (m_pixelData)
	{
		delete[] m_pixelData;
		m_pixelData = nullptr;
	}
}
#pragma endregion

#pragma region Getter Functions
void Texture::GetDimensions(u32& a_width, u32& a_height) const
{
	a_width = m_width;
	a_height = m_height;
}

u16 Texture::GetPalette(void* a_palette)
{
	a_palette = m_palette;
	return m_paletteSize;
}
#pragma endregion

#pragma region Other Functions
bool Texture::Load(const char* a_fileName, u32 a_format)
{
	m_pixelData = ImageLoader::LoadFromFile(a_fileName, a_format, m_width, m_height, m_bpp, m_palette);

	if (m_pixelData)
	{
		m_fileName = a_fileName;
		return true;
	}

	m_width = m_height = 0;
	m_bpp = 0;
	m_paletteSize = 0;

	return false;
}
#pragma endregion