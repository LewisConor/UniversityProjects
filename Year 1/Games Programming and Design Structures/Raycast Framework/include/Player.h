#include <stdafx.h>
#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

class GamePlayState;

class Player
{
public:
	Player(GamePlayState* gamePlayState);
	~Player() { }

	void Update(float a_fDT);
	void Draw();

	void SetPosition(float a_x, float a_y);
	void SetRotation(float a_degrees);

	void GetPosition(float& a_x, float& a_y) const;
	void GetRotation(float& a_x, float& a_y) const;
	float GetNearPlaneLength() const { return m_nearPlaneLength; }

private:
	float m_posX;
	float m_posY;

	float m_dirX;
	float m_dirY;

	float m_nearPlaneDist;
	float m_nearPlaneLength;

	float m_movSpeed;

	InputManager* m_inputManager;

	GameStateManager* m_gSManager;
	GamePlayState* m_gamePlayState;

	//HUD
	TextureManager* m_texManager;
	Texture* m_tex;
};

#endif // !__PLAYER_H__
