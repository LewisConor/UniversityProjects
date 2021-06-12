#include <stdafx.h>
#pragma once
#ifndef __LEVEL_H__
#define __LEVEL_H__

class Player;

class Level
{
public:
	Level();
	~Level() { }

	void GetSize(u32& a_w, u32& a_h);
	u8 GetGridValue(u32& a_x, u32& a_y);

	bool LoadLevel(const char* a_filename);

	char* GetLevelName() const { return m_levelName; }

	void Draw(const Player* a_player);

private:
	char* m_levelName;

	u32 m_width;
	u32 m_height;

	u8* m_map;
	void* m_backgroundData;

	TextureManager* m_texManager;
	Texture* m_tex;
};

#endif // !__LEVEL_H__
