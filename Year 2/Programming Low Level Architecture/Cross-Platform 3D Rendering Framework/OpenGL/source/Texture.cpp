//Includes - In-App > External > Windows
#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>
#include <vector>
#include <string>

Texture::Texture() : m_filename(), m_width(0), m_height(0), m_textureID(0) {}
Texture::~Texture() { Unload(); }

bool Texture::Load(std::string a_filepath)
{
	int width = 0, height = 0, channels = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imageData = stbi_load(a_filepath.c_str(), &width, &height, &channels, 4);

	if (imageData != nullptr)
	{
		m_filename = a_filepath;
		m_width = width;
		m_height = height;

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(imageData);
		stbi_set_flip_vertically_on_load(false);

		std::cout << "Image File Loaded: " << a_filepath << std::endl;

		return true;
	}
	
	std::cout << "Failed to Load Image File: " << a_filepath << std::endl;
	return false;
}

unsigned int Texture::LoadSkyboxFaces(std::vector<std::string> a_filenames, unsigned int* a_skyboxFaces)
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

	int width, height, nrChannels;
	
	for (int i = 0; i < 6; i++)
	{
		unsigned char* imageData;
		stbi_set_flip_vertically_on_load(false);

		imageData = stbi_load(a_filenames[i].c_str(), &width, &height, &nrChannels, 0);

		if (imageData != nullptr)
		{
			m_filename = a_filenames[i];
			m_width = width;
			m_height = height;

			glTexImage2D(a_skyboxFaces[i], 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

			stbi_image_free(imageData);

			std::cout << "Image File Loaded: " << a_filenames[i] << std::endl;
		}
		else
		{
			std::cout << "Failed to Load Image File: " << a_filenames[i] << std::endl;
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return m_textureID;
}

void Texture::Unload() { glDeleteTextures(1, &m_textureID); }