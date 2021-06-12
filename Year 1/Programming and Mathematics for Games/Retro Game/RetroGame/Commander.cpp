// Includes
#include "Commander.h"

#include "Missile.h"
#include "Scene.h"

// Namespaces
using namespace olc;

//Constructor
Commander::Commander(float x) : currentSprite(0), stage2(false), frameCount(0), moveLeft(true), moveCenter(false), moveRight(false), moveDown(false), timesMoved(0), cycle(0)
{
	// Load the Commander sprites
	sprites[0] = new Sprite("Resources/Enemies/Commander/stage1_frame1.png");
	sprites[1] = new Sprite("Resources/Enemies/Commander/stage1_frame2.png");
	sprites[2] = new Sprite("Resources/Enemies/Commander/stage2_frame1.png");
	sprites[3] = new Sprite("Resources/Enemies/Commander/stage2_frame2.png");

	// Set the position vector
	position = { x, 50 };
	originalPosition = position;
}

//Update Method
void Commander::Update(Scene *pScene)
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

	//Sprite Animation every 60 Frames
	if (stage2 != true)
	{
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
	else
	{
		if (currentSprite == 2)
		{
			if (frameCount > 60)
			{
				currentSprite = 3;
				frameCount = 0;
			}
			frameCount++;
		}
		else if (currentSprite == 3)
		{
			if (frameCount > 60)
			{
				currentSprite = 2;
				frameCount = 0;
			}
			frameCount++;
		}
	}
}

//Draw Method
void Commander::Draw(Scene* pScene)
{
	//Draws the Sprite
	pScene->DrawSprite((int32_t)position.GetX(), (int32_t)position.GetY(), sprites[currentSprite]);
}

//Shoot Missile from Commander
void Commander::ShootMissile(Scene* pScene)
{
	pScene->AddMissile(new Missile(this));
}