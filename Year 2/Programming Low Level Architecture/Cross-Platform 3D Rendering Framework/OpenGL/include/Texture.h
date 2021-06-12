#pragma once

#include <string>
#include <vector>

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(std::string a_filepath);
	unsigned int LoadSkyboxFaces(std::vector<std::string> a_filenames, unsigned int* a_skyboxFace);
	void Unload();
	const std::string& GetFileName() const { return m_filename; }
	unsigned int GetTextureID() const { return m_textureID; }
	void GetDimensions(unsigned int& a_w, unsigned int& a_h) const;

private:
	std::string m_filename;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_textureID;
};

inline void Texture::GetDimensions(unsigned int& a_w, unsigned int& a_h) const { a_w = m_width; a_h = m_height; }