//Includes
#include "Bee.h"

#include "Missile.h"
#include "Scene.h"

//Namespace
using namespace olc;

//Constructor
Bee::Bee(float x, float y) : currentSprite(0), frameCount(0), moveLeft(true), moveCenter(false), moveRight(false), moveDown(false), timesMoved(0), cycle(0)
{
	//Assigns the Bee Sprites
	sprites[0] = new Sprite("Resources/Enemies/Bee/bee_frame1.png");
	sprites[1] = new Sprite("Resources/Enemies/Bee/bee_frame2.png");

	//Sets Position
	position = { x, y };
	originalPosition = position;
}

//Update Method
void Bee::Update(Scene* pScene)
{
	//Every 60 Frames
	if (frameCount > 60)
	{
		//Move Left and back to Center
		if (moveLeft == true && moveCenter == false && moveRight == false)
		{
			if (timesMoved < 2)
			{
				position.SetX(position.GetX() - 5.0f);
				timesMoved++;
			}
			else
			{
				moveCenter = true;
				timesMoved = 0;
			}
		}
		else if (moveLeft == true && moveCenter == true)
		{
			if (timesMoved < 2)
			{
				position.SetX(position.GetX() + 5.0f);
				timesMoved++;
			}
			else
			{
				moveLeft = false;
				moveCenter = false;
				moveRight = true;
				timesMoved = 0;
			}
		}

		//Move Right and back to Center
		if (moveRight == true && moveCenter == false && moveLeft == false)
		{
			if (timesMoved < 2)
			{
				position.SetX(position.GetX() + 5.0f);
				timesMoved++;
			}
			else
			{
				moveCenter = true;
				timesMoved = 0;
			}
		}
		else if (moveRight == true && moveCenter == true)
		{
			if (timesMoved < 2)
			{
				position.SetX(position.GetX() - 5.0f);
				timesMoved++;
			}
			else
			{
				moveLeft = true;
				moveCenter = false;
				moveRight = false;
				moveDown = true;

				timesMoved = 0;
				cycle++;
			}
		}

		//Move Down the Screen
		if (moveDown)
		{
			switch (cycle)
			{
				case 1:
				{
					position.SetY(position.GetY() + 10.0f);
					moveDown = false;
					break;
				}
				case 2:
				{
					position.SetY(position.GetY() + 15.0f);
					moveDown = false;
					break;
				}
				case 3:
				{
					position.SetY(position.GetY() + 20.0f);
					moveDown = false;
					break;
				}
				case 4:
				{
					position.SetY(position.GetY() + 25.0f);
					moveDown = false;
					break;
				}
				case 5:
				{
					position.SetY(position.GetY() + 30.0f);
					moveDown = false;
					break;
				}
				case 6:
				{
					position.SetY(position.GetY() + 35.0f);
					moveDown = false;
					break;
				}
				default:
				{
					position.SetY(position.GetY() + 40.0f);
					moveDown = false;
					break;
				}
			}
		}
	}

	//Changes between the 2 sprites every 60 frames
	if (currentSprite == 0)
	{
		if (frameCount > 60)
		{
			currentSprite = 1;
			frameCount = 0;
		}
		frameCount++;
	}
	else if (currentSprite == 1)
	{
		if (frameCount > 60)
		{
			currentSprite = 0;
			frameCount = 0;
		}
		frameCount++;
	}
}

//Draw Method
void Bee::Draw(Scene* pScene)
{
	//Draws Sprite
	pScene->DrawSprite((int32_t)position.GetX(), (int32_t)position.GetY(), sprites[currentSprite]);
}

//Shoots a Missile from Bee
void Bee::ShootMissile(Scene* pScene)
{
	pScene->AddMissile(new Missile(this));
}