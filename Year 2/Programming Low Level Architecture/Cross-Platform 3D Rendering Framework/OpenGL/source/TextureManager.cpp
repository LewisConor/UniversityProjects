#include "TextureManager.h"
#include "Texture.h"

TextureManager* TextureManager::m_instance = nullptr;

TextureManager* TextureManager::CreateInstance()
{
	if (nullptr == m_instance) { m_instance = new TextureManager(); }

	return m_instance;
}

TextureManager* TextureManager::GetInstance()
{
	if (nullptr == m_instance) { return CreateInstance(); }

	return m_instance;
}

void TextureManager::DestoryInstance()
{
	if (nullptr != m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

TextureManager::TextureManager() : m_TextureMap() {}
TextureManager::~TextureManager() {}

unsigned int TextureManager::LoadTexture(const char* a_filename)
{
	if (a_filename != nullptr)
	{
		auto dictionaryIter = m_TextureMap.find(a_filename);
		if (dictionaryIter != m_TextureMap.end())
		{
			TextureRef& texRef = (TextureRef&)(dictionaryIter->second);
			++texRef.refCount;
			
			return texRef.pTexture->GetTextureID();
		}
		else
		{
			Texture* pTexture = new Texture();

			if (pTexture->Load(a_filename))
			{
				TextureRef texRef = { pTexture, 1 };
				m_TextureMap[a_filename] = texRef;
				
				return pTexture->GetTextureID();
			}
			else
			{
				delete pTexture;

				return 0;
			}
		}
	}

	return 0;
}

void TextureManager::ReleaseTexture(unsigned int a_texture)
{
	for (auto dictionaryIter = m_TextureMap.begin(); dictionaryIter != m_TextureMap.end(); ++dictionaryIter)
	{
		TextureRef& texRef = (TextureRef&)(dictionaryIter->second);

		if (a_texture == texRef.pTexture->GetTextureID())
		{
			if (--texRef.refCount == 0)
			{
				delete texRef.pTexture;
				texRef.pTexture = nullptr;
				m_TextureMap.erase(dictionaryIter);

				break;
			}
		}
	}
}

bool TextureManager::TextureExists(const char* a_filename)
{
	auto dictionaryIter = m_TextureMap.find(a_filename);
	return (dictionaryIter != m_TextureMap.end());
}

unsigned int TextureManager::GetTexture(const char* a_filename)
{
	auto dictionaryIter = m_TextureMap.find(a_filename);

	if (dictionaryIter != m_TextureMap.end())
	{
		TextureRef& texRef = (TextureRef&)(dictionaryIter->second);
		texRef.refCount++;

		return texRef.pTexture->GetTextureID();
	}

	return 0;
}