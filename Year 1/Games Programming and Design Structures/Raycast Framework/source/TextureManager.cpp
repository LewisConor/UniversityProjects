//Precompiled Header File
#include <stdafx.h>

//Header File
#include "TextureManager.h"

//Other Includes
#include "Texture.h"

TextureManager* TextureManager::m_instance = nullptr;

#pragma region Constructor and Destructor
TextureManager::TextureManager() : m_textureMap() 
{ 
	m_instance = this;
}

TextureManager::~TextureManager()
{
	m_textureMap.clear();
}
#pragma endregion

#pragma region Texture Functions
Texture* TextureManager::LoadTexture(const char* a_fileName, u32 a_format)
{
	Texture* pTexture = nullptr;
	if (a_fileName != nullptr)
	{
		std::map<std::string, TextureRef>::iterator dictionaryIter = m_textureMap.find(a_fileName);

		if (dictionaryIter != m_textureMap.end())
		{
			TextureRef& texRef = (TextureRef&)(dictionaryIter->second);
			pTexture = texRef.pTexture;
			++texRef.refCount;
		}
		else
		{
			pTexture = new Texture();
			if (pTexture->Load(a_fileName, a_format))
			{
				TextureRef texRef = { pTexture, 1 };
				m_textureMap[a_fileName] = texRef;
			}
			else
			{
				delete pTexture;
				pTexture = nullptr;
			}
		}
	}

	return pTexture;
}

void TextureManager::ReleaseTexture(Texture* a_texturePointer)
{
	for (auto dictionaryIter = m_textureMap.begin(); dictionaryIter != m_textureMap.end(); ++dictionaryIter)
	{
		TextureRef& texRef = (TextureRef&)(dictionaryIter->second);
		if (a_texturePointer == texRef.pTexture)
		{
			if (--texRef.refCount == 0)
			{
				delete texRef.pTexture;
				texRef.pTexture = nullptr;
				m_textureMap.erase(dictionaryIter);
				break;
			}
		}
	}
}

bool TextureManager::TextureExists(const char* a_fileName)
{
	auto dictionaryIter = m_textureMap.find(a_fileName);
	
	if (dictionaryIter != m_textureMap.end())
	{
		return true;
	}
	
	return false;
}

Texture* TextureManager::GetTexture(const char* a_fileName)
{
	Texture* pTexture = nullptr;
	auto dictionaryIter = m_textureMap.find(a_fileName);

	if (dictionaryIter != m_textureMap.end())
	{
		TextureRef& texRef = (TextureRef&)(dictionaryIter->second);
		texRef.refCount++;
		pTexture = texRef.pTexture;
	}

	return pTexture;
}