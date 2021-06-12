//Precompiled Header File
#include <stdafx.h>

//Header File
#include "Player.h"

//Other Includes
#include "ImageLoader.h"
#include "GamePlayState.h"

//Constructor
Player::Player(GamePlayState* gamePlayState) : m_dirX(1.0f), m_dirY(0.0f), m_posX(2.0f), m_posY(3.0f), m_movSpeed(2.0f)
{
	m_gSManager = GameStateManager::GetInstance();
	m_gamePlayState = gamePlayState;

	m_nearPlaneDist = 1.f;
	m_nearPlaneLength = tanf(HALF_FOV * (float)(PI / 180.0f)) * m_nearPlaneDist;
	m_inputManager = InputManager::GetInstance();

	m_texManager = TextureManager::GetInstance();
	m_tex = m_texManager->LoadTexture("resources/images/hud.pcx", 0);
}

//Set Player Pos
void Player::SetPosition(float a_x, float a_y)
{
	m_posX = a_x;
	m_posY = a_y;
}

//Set Player Rotation 
void Player::SetRotation(float a_degrees)
{
	float radians = a_degrees * (float)(PI / 180.0f);
	m_dirX = 1.0f * cosf(radians);
	m_dirY = 1.0f * sin(radians);
}

//Get Player Position
void Player::GetPosition(float& a_x, float& a_y) const
{
	a_x = m_posX;
	a_y = m_posY;
}

//Get Player Roation
void Player::GetRotation(float& a_x, float& a_y) const
{
	a_x = m_dirX;
	a_y = m_dirY;
}

//Update Function
void Player::Update(float a_fDT)
{
	//Input Checks

	//Up
	if (m_inputManager->GetKeyDown('W'))
	{
		m_posX += m_movSpeed * m_dirX * a_fDT;
		m_posY += m_movSpeed * m_dirY * a_fDT;
	}

	//Down
	if (m_inputManager->GetKeyDown('S'))
	{
		m_posX -= m_movSpeed * m_dirX * a_fDT;
		m_posY -= m_movSpeed * m_dirY * a_fDT;
	}

	//Left
	if (m_inputManager->GetKeyDown('A'))
	{
		float playerRotSpeed = -3.0f * a_fDT;
		float oldDirX = m_dirX;
		m_dirX = oldDirX * cosf(playerRotSpeed) - m_dirY * sin(playerRotSpeed);
		m_dirY = oldDirX * sin(playerRotSpeed) + m_dirY * cos(playerRotSpeed);
	}

	//Right
	if (m_inputManager->GetKeyDown('D'))
	{
		float playerRotSpeed = 3.0f * a_fDT;
		float oldDirX = m_dirX;
		m_dirX = oldDirX * cosf(playerRotSpeed) - m_dirY * sin(playerRotSpeed);
		m_dirY = oldDirX * sin(playerRotSpeed) + m_dirY * cos(playerRotSpeed);
	}
}

//Draw Function
void Player::Draw()
{
	//Gets Renderer Instance
	Renderer* renderer = Renderer::GetInstance();

	u32 w = 0, h = 0;
	m_tex->GetDimensions(w, h);

	if (m_tex != nullptr)
	{
		//Draws HUD
		renderer->FillRenderBuffer(25, WINDOW_HEIGHT - h - 35, w, h, m_tex->GetPixelData());
	}
}