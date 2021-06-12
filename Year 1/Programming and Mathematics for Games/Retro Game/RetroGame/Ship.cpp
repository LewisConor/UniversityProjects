// Includes
#include "Ship.h"

#include "Missile.h"
#include "Scene.h"

//Namespace
using namespace olc;

//Constructor
Ship::Ship() : frameCount(0), currentExplosionSprite(0), explode(false)
{
	// Load our sprite
	shipSprite = new Sprite("Resources/galaga.png");
	explosionSprite[0] = new Sprite("Resources/Player/explosion_1.png");
	explosionSprite[1] = new Sprite("Resources/Player/explosion_2.png");
	explosionSprite[2] = new Sprite("Resources/Player/explosion_3.png");
	explosionSprite[3] = new Sprite("Resources/Player/explosion_4.png");

	// Set the position vector
	position = { (WINDOW_WIDTH / 2), (WINDOW_HEIGHT - 40) };

	//Sets the Missile Sound
	missileClipID = SOUND::LoadAudioSample("Resources\\Sound\\missile.wav");
}

//Update Method
void Ship::Update(Scene* pScene)
{
	//Checks if the Player is Exploding
	if (!explode)
	{
		//Handle Left and Right Input
		if (pScene->GetKey(Key::A).bHeld || pScene->GetKey(Key::LEFT).bHeld)
		{
			if (position.GetX() > 0)
			{
				position.SetX(position.GetX() - 1.0f);
			}
		}
		else if (pScene->GetKey(Key::D).bHeld || pScene->GetKey(Key::RIGHT).bHeld)
		{
			if (position.GetX() < (WINDOW_WIDTH - GetSprite()->width))
			{
				position.SetX(position.GetX() + 1.0f);
			}
		}

		//Handle Shooting Input
		if (frameCount >= 30)
		{
			if (pScene->GetKey(Key::Z).bHeld || pScene->GetKey(Key::Z).bPressed || pScene->GetKey(Key::X).bHeld || pScene->GetKey(Key::X).bPressed)
			{
				pScene->AddMissile(new Missile(this));
				SOUND::PlaySample(missileClipID, false);
				frameCount = 0;
			}
		}
	}

	frameCount++;
}

//Draw Method
void Ship::Draw(Scene* pScene)
{
	//Checks if the Player is Exploding
	if (!explode)
	{
		//Draw the Ship Sprite
		pScene->DrawSprite((int32_t)position.GetX(), (int32_t)position.GetY(), shipSprite);
	}
	else
	{
		//Draw the Exploding Sprites
		pScene->DrawSprite((int32_t)position.GetX(), (int32_t)position.GetY(), explosionSprite[currentExplosionSprite]);
	}
}