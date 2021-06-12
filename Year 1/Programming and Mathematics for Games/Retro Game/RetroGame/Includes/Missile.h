#pragma once
#ifndef __MISSILE_H__
#define __MISSILE_H__

// Includes
#include "olcPixelGameEngine.h"

#include "Constants.h"
#include "Vector2.h"

// Forward declarations
class Scene;
class Ship;
class Commander;
class Butterfly;
class Bee;

class Missile
{
public:
	//Constructor & Destructor
	Missile(Ship* playerShip);
	Missile(Commander* enemyShip);
	Missile(Butterfly* enemyShip);
	Missile(Bee* enemyShip);
	~Missile() {}

	// Getters / Setters
	olc::Sprite* GetSprite() { return sprite; }
	void SetSprite(olc::Sprite* a_sprite) { sprite = a_sprite; }

	Vector2& GetPosition() { return position; }
	void SetPosition(Vector2 a_position) { position = a_position; }

	//Functions
	bool Update(Scene* pScene);
	void Draw(Scene* pScene);
	bool IsEnemyMissile() { return enemyMissile; }

private:
	olc::Sprite* sprite;
	Vector2 position;

	bool enemyMissile;
};

#endif //!SHIP_H
