#pragma once
#ifndef SCENE_H
#define SCENE_H

// Includes
#include "olcPixelGameEngine.h"
#include "olcPGEX_Sound.h"

#include "Constants.h"
#include "Vector2.h"

//Enums
enum class ENTITY_TYPE
{
	SHIP,
	MISSILE,
	COMMANDER,
	BUTTERFLY,
	BEE
};

enum class GAME_STATE
{
	MENU,
	PLAY,
	GAME_OVER
};

//Foward Declarations
class Vector2;

class Missile;
class Ship;
class Commander;
class Butterfly;
class Bee;

using namespace olc;

class Scene : public olc::PixelGameEngine
{
public:
	//Constructor
	Scene();

	//OLC PGE Functions
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	//Functions
	void SpawnEnemies();

	void AllUpdate();
	void AllDraw();

	void AddMissile(Missile* missile);
	void AddCommander(Commander* commander);
	void AddButterfly(Butterfly* butterfly);
	void AddBee(Bee* bee);

	template <class T> 
	void RemoveElement(T* objectToRemove, ENTITY_TYPE entityType);
	
	bool EntityHit(Vector2 &missilePos, Vector2 &objectHit, Sprite* objectSprite);

	void ResetGame();

private:
	GAME_STATE currentGameState;

	//Integers
	int commanderShipCount;
	int butterflyShipCount;
	int beeShipCount;
	int enemyCount;
	int score;
	int life;
	int updateFrameCount;
	int drawFrameCount;
	int stageNumber;
	int fireChance;

	//Floats
	float timer;
	float animationTimer;
	float animationFrameTimer;

	//Bools
	bool playTextActive;
	bool menuTextActive;
	bool exitTextActive;
	bool menuTextSwitch;
	bool paused;
	bool textSwitch;
	bool yTrigger;

	//Entities
	Ship* playerShip;
	std::list<Missile*> missiles;
	std::list<Commander*> commanderShips;
	std::list<Butterfly*> butterflyShips;
	std::list<Bee*> beeShips;
};

#endif //!SCENE_H
