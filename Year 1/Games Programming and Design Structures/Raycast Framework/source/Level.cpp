//Precompiled Header File
#include <stdafx.h>

//Header File
#include "Level.h"

//Other Includes
#include "Player.h"
#include "ImageLoader.h"

//Constructor
Level::Level() : m_width(0), m_height(0), m_map(nullptr)
{
	m_texManager = TextureManager::GetInstance();
	m_tex = m_texManager->LoadTexture("resources/images/black.pcx", 0);
}

//Loads a Level from File
bool Level::LoadLevel(const char* a_filename)
{
	//Checks if a Map is already Loaded
	if (m_map != nullptr)
	{
		delete[] m_map;
		m_map = nullptr;
	}

	//Opens the Map File and Reads the Values in File
	std::fstream file;
	file.open(a_filename, std::ios_base::in | std::ios_base::binary);

	if (file.is_open())
	{
		file.ignore(std::numeric_limits<std::streamsize>::max());
		std::streamsize fileSize = file.gcount();
		file.clear();
		file.seekg(0, std::ios_base::beg);
		
		if (fileSize == 0)
		{
			file.close();
			return false;
		}

		file >> m_width >> m_height;
		file.ignore(1);
		
		m_map = new u8[m_height * m_width];
		u32 index = 0;

		for (std::string currentMapLine; std::getline(file, currentMapLine);)
		{
			std::stringstream ss{ currentMapLine };
			int value = 0;
			while (ss >> value)
			{
				m_map[index] = (u8)(value);
				++index;

				if ((ss >> std::ws).peek() == ',')
				{
					ss.ignore();
				}
			}
		}

		file.close();

		u64 l = (u64)strlen(a_filename);
		m_levelName = new char[l + 1];
		strcpy(m_levelName, a_filename);

		return true;
	}

	return false;
}

//Draws the Level to Renderer
void Level::Draw(const Player* a_player)
{
	Renderer* renderer = Renderer::GetInstance();

	float playerPosX = 0.0f, playerPosY = 0.0f;
	a_player->GetPosition(playerPosX, playerPosY);

	float playerDirX = 0.0f, playerDirY = 0.0f;
	a_player->GetRotation(playerDirX, playerDirY);

	float camPlaneX = -playerDirY * a_player->GetNearPlaneLength();
	float camPlaneY = playerDirX * a_player->GetNearPlaneLength();

	for (u32 c = 0; c < WINDOW_WIDTH; c++)
	{
		float cameraX = ((2.0f * c) / (float)WINDOW_WIDTH - 1.0f);
		float rayDirX = playerDirX + (camPlaneX * cameraX);
		float rayDirY = playerDirY + (camPlaneY * cameraX);

		float deltaDistX = (rayDirX != 0.0f) ? std::abs(1.0f / rayDirX) : 0;
		float deltaDistY = (rayDirY != 0.0f) ? std::abs(1.0f / rayDirY) : 0;

		int mapX = (int)(playerPosX);
		int mapY = (int)(playerPosY);

		float sideDistX = 0.0f;
		float sideDistY = 0.0f;

		float perpWallDist = 0.0f;

		int stepX = 0;
		int stepY = 0;

		int collision = 0;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (playerPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0f - playerPosX) * deltaDistX;
		}

		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (playerPosY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0f - playerPosY) * deltaDistY;
		}

		int yIntersection = 0;
		while (collision == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				yIntersection = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				yIntersection = 1;
			}

			collision = m_map[(mapX + (mapY * m_width))];
		}

		perpWallDist = (!yIntersection) ? (mapX - playerPosX + (1 - stepX) / 2.0f) / rayDirX : (mapY - playerPosY + (1 - stepY) / 2.0f) / rayDirY;

		s32 lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);
		s32 yPos = (WINDOW_HEIGHT >> 1) - (lineHeight >> 1);

		renderer->FillRenderBuffer(c, yPos, 1, lineHeight, (!yIntersection) ? 0x00113B51 : 0x0055008C);

		/*if (m_tex != nullptr)
		{
			u32 w = 0, h = 0;
			m_tex->GetDimensions(w, h);

			renderer->FillRenderBuffer(c, yPos, 1, lineHeight, (!yIntersection) ? m_tex->GetPixelData() : m_tex->GetPixelData());
		}
		else
		{
			renderer->FillRenderBuffer(c, yPos, 1, lineHeight, (!yIntersection) ? 0x00FF0FF0 : 0x00880880);
		}*/
	}
}

//Gets the Level Size
void Level::GetSize(u32& a_w, u32& a_h)
{
	a_w = m_width;
	a_h = m_height;
}

//Gets the Values from the Level File
u8 Level::GetGridValue(u32& a_x, u32& a_y)
{
	u32 index = a_x + (a_y * m_width);
	
	if (index < (m_width * m_height))
	{
		return m_map[index];
	}

	return 255;
}