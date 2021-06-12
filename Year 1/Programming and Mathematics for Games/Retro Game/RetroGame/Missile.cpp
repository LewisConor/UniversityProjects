//Includes
#include "Entities.h"

#include "Scene.h"

//Name Space
using namespace olc;

//Player Constructor
Missile::Missile(Ship* playerShip) : enemyMissile(false)
{
	sprite = new Sprite("Resources/missile.png");

	position = { (playerShip->GetPosition().GetX() + sprite->width * 3), (playerShip->GetPosition().GetY() - sprite->height) };
}

//Commander Constructor
Missile::Missile(Commander* enemyShip)
{
	sprite = new Sprite("Resources/enemy_missile.png");

	position = { (enemyShip->GetPosition().GetX() + sprite->width * 3), (enemyShip->GetPosition().GetY() + sprite->height) };

	enemyMissile = true;
}

//Butterfly Constructor
Missile::Missile(Butterfly* enemyShip)
{
	sprite = new Sprite("Resources/enemy_missile.png");

	position = { (enemyShip->GetPosition().GetX() + sprite->width * 3), (enemyShip->GetPosition().GetY() + sprite->height) };

	enemyMissile = true;
}

//Bee Constructor
Missile::Missile(Bee* enemyShip)
{
	sprite = new Sprite("Resources/enemy_missile.png");

	position = { (enemyShip->GetPosition().GetX() + sprite->width * 3), (enemyShip->GetPosition().GetY() + sprite->height) };

	enemyMissile = true;
}

//Update Method
bool Missile::Update(Scene* pScene)
{
	//Checks if it is an Enemy Missile and Checks if the Missile goes out of Frame
	if (enemyMissile == false)
	{
		//Player Missile
		if (position.GetY() < 0)
		{
			return false;
		}
		else
		{
			position.SetY(position.GetY() - 1.5f);
		}
	}
	else
	{
		//Enemy Missile
		if (position.GetY() > WINDOW_HEIGHT)
		{
			return false;
		}
		else
		{
			position.SetY(position.GetY() + 1.5f);
		}
	}

	return true;
}

//Draw Method
void Missile::Draw(Scene* pScene)
{
	//Draws the Sprite
	pScene->DrawSprite((int32_t)position.GetX(), (int32_t)position.GetY(), sprite);
}