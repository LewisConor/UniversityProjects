#pragma once
#ifndef __COMMANDER_H__
#define __COMMANDER_H__

// Includes
#include "olcPixelGameEngine.h"

#include "Constants.h"
#include "Vector2.h"

//Defines
#define COMMANDER_SCORE 150
#define COMMANDER_SPRITE_WIDTH 15
#define COMMANDER_SPRITE_GAP 11
#define NUM_OF_COMMANDER_SHIPS 7 * COMMANDER_SPRITE_WIDTH

// Forward declarations
class Scene;
class Missile;

class Commander
{
public:
	//Constructor & Destructor
	Commander(float x);
	~Commander() {}

	// Getters / Setters
	olc::Sprite* GetSprite() { return sprites[currentSprite]; }
	void SetSprite(olc::Sprite* a_sprite) { sprites[currentSprite] = a_sprite; }
	void SetCurrentSprite(int a_spriteNumber) { currentSprite = a_spriteNumber; }

	Vector2& GetOriginalPosition() { return originalPosition; }
	Vector2& GetPosition() { return position; }
	void SetPosition(Vector2 a_position) { position = a_position; }

	//Functions
	void Update(Scene* pScene);
	void Draw(Scene* pScene);
	
	void ShootMissile(Scene* pScene);

	bool GetCommanderStage() { return stage2; }
	void SetCommanderStage() { stage2 = true; }
private:
	olc::Sprite* sprites[4];
	Vector2 position;
	Vector2 originalPosition;

	int frameCount;
	int currentSprite;
	int timesMoved;
	int cycle;

	bool stage2;
	bool moveLeft;
	bool moveCenter;
	bool moveRight;
	bool moveDown;
};
#endif //!SHIP_H
