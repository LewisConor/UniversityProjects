#pragma once
#ifndef SHIP_H
#define SHIP_H

// Includes
#include "olcPixelGameEngine.h"
#include "olcPGEX_Sound.h"

#include "Constants.h"
#include "Vector2.h"

// Forward declarations
class Scene;

// Namespaces
using namespace olc;

class Ship
{
public:
	//Constructor & Destructor
	Ship();
	~Ship() {}

	// Getters / Setters
	Sprite* GetSprite() { return shipSprite; }
	void SetSprite(Sprite* a_sprite) { shipSprite = a_sprite; }
	int GetCurrentSprite() { return currentExplosionSprite; }
	void AddToCurrentSprite() { currentExplosionSprite++; }

	Vector2& GetPosition() { return position; }
	void SetPosition(Vector2 a_position) { position = a_position; }

	//Functions
	void Update(Scene* pScene);
	void Draw(Scene* pScene);

	void TriggerExplosion() { explode = !explode; frameCount = 0; currentExplosionSprite = 0; }
	bool CheckExplosion() { return explode; }
private:
	Sprite* shipSprite;
	Sprite* explosionSprite[4];

	Vector2 position;
	int frameCount;
	int missileClipID;

	bool explode;
	int currentExplosionSprite;
};

#endif //!SHIP_H
