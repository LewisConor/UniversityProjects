#pragma once
#ifndef __BEE_H__
#define __BEE_H__

// Includes
#include "olcPixelGameEngine.h"

#include "Constants.h"
#include "Vector2.h"

//Bee Defines
#define BEE_SCORE 50
#define BEE_SPRITE_WIDTH 13
#define BEE_SPRITE_GAP 10
#define NUM_OF_BEE_SHIPS 16 * BEE_SPRITE_WIDTH
#define HALF_OF_BEE_SHIPS NUM_OF_BEE_SHIPS / 2

class Scene;

class Bee
{
public:
	//Constructor & Destructor
	Bee(float x, float y);
	~Bee() {}

	// Getters / Setters
	olc::Sprite* GetSprite() { return sprites[currentSprite]; }
	void SetSprite(olc::Sprite* a_sprite) { sprites[currentSprite] = a_sprite; }

	Vector2& GetOriginalPosition() { return originalPosition; }
	Vector2& GetPosition() { return position; }
	void SetPosition(Vector2 a_position) { position = a_position; }

	//Functions
	void Update(Scene* pScene);
	void Draw(Scene* pScene);

	void ShootMissile(Scene* pScene);
private:
	olc::Sprite* sprites[2];
	Vector2 position;
	Vector2 originalPosition;

	int frameCount;
	int currentSprite;
	int timesMoved;
	int cycle;

	bool moveLeft;
	bool moveCenter;
	bool moveRight;
	bool moveDown;
};

#endif // !__BEE_H__
