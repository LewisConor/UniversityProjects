//Pre-File Definition
#define OLC_PGEX_SOUND
#define GAME_TEXT

// Includes
#include "Scene.h"

#include "Entities.h"

//Constructor
Scene::Scene() : currentGameState(GAME_STATE::MENU), yTrigger(false), playTextActive(true), menuTextActive(true), exitTextActive(false), menuTextSwitch(false), paused(false), textSwitch(false), playerShip(nullptr), commanderShipCount(0), butterflyShipCount(0), beeShipCount(0), score(0), life(1), enemyCount(0), updateFrameCount(0), drawFrameCount(0), animationFrameTimer(0), animationTimer(0), timer(0), stageNumber(1), fireChance(0){ }

// Called once at the start, so create things here
bool Scene::OnUserCreate()
{
	//Sets App Name
	sAppName = "Space Invaders meets Galaga";

	//Initalises Audio
	SOUND::InitialiseAudio();

	// Enables alpha blending
	SetPixelMode(Pixel::ALPHA);

	return true;
}

// Main Update Method using State Machines
bool Scene::OnUserUpdate(float fElapsedTime)
{
	// Should we quit?
	if (GetKey(Key::ESCAPE).bPressed)
	{
		return false;
	}

	//State Control
	switch (currentGameState)
	{
		case GAME_STATE::MENU: 
		{
			//Update

			//Menu Controls
			if (GetKey(Key::UP).bPressed)
			{
				if (playTextActive != true)
				{
					exitTextActive = false;
					playTextActive = true;
				}
			}
			else if (GetKey(Key::DOWN).bPressed)
			{
				if (exitTextActive != true)
				{
					playTextActive = false;
					exitTextActive = true;
				}
			}
			else if (GetKey(Key::ENTER).bPressed)
			{
				if (playTextActive)
				{
					ResetGame();
					playerShip = new Ship();
					SpawnEnemies();

					currentGameState = GAME_STATE::PLAY;
				}
				else if (exitTextActive)
				{
					return false;
				}
			}

			//Clear Screen
			Clear(Pixel());

			//Draw

			//Title Text
			DrawString((WINDOW_WIDTH / 2) - ((int32_t)(titleOne.length() * 4)), 50, titleOne, olc::WHITE, 1);
			DrawString((WINDOW_WIDTH / 2) - ((int32_t)(titleTwo.length() * 4)), 70, titleTwo, olc::WHITE, 1);

			//Play and Exit Text 
			if (playTextActive)
			{
				DrawString((WINDOW_WIDTH / 2) - ((int32_t)(playText.length() * 4)), 100, activePlayText, olc::WHITE, 1);
				DrawString((WINDOW_WIDTH / 2) - ((int32_t)(exitText.length() * 4)), 120, exitText, olc::WHITE, 1);
			}
			else if (exitTextActive)
			{
				std::string playText = "PLAY";
				std::string exitText = "-> EXIT";
				DrawString((WINDOW_WIDTH / 2) - ((int32_t)(playText.length() * 4)), 100, playText, olc::WHITE, 1);
				DrawString((WINDOW_WIDTH / 2) - ((int32_t)(exitText.length() * 4)), 120, activeExitText, olc::WHITE, 1);
			}

			//Controls
			DrawString((WINDOW_WIDTH / 2) - ((int32_t)(controlText.length() * 4)), 190, controlText, olc::WHITE, 1);
			DrawString((WINDOW_WIDTH / 2) - ((int32_t)(menuControlText.length() * 4)), 200, menuControlText, olc::WHITE, 1);
			DrawString((WINDOW_WIDTH / 2) - ((int32_t)(movementText.length() * 4)), 210, movementText, olc::WHITE, 1);
			DrawString((WINDOW_WIDTH / 2) - ((int32_t)(shootText.length() * 4)), 220, shootText, olc::WHITE, 1);
			DrawString((WINDOW_WIDTH / 2) - ((int32_t)(pauseText.length() * 4)), 230, pauseText, olc::WHITE, 1);
			DrawString((WINDOW_WIDTH / 2) - ((int32_t)(interactText.length() * 4)), 240, interactText, olc::WHITE, 1);

			//Space Paritcles
			Pixel pixel = Pixel(rand() % 255, rand() % 255, rand() % 255);
			for (int i = 0; i < 100; i++)
			{
				Draw(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT, pixel);
			}

			break;
		}
		case GAME_STATE::PLAY: 
		{
			//Checks the Enemy Count, Continue if Enemies > 0
			if (enemyCount > 0)
			{
				//Pause Control
				if (GetKey(Key::P).bPressed && !playerShip->CheckExplosion())
				{
					if (paused)
					{
						paused = false;
					}
					else
					{
						paused = true;
					}
				}

				//If Paused or not
				if (!paused)
				{
					//Checks if the player is exploding
					if (!playerShip->CheckExplosion())
					{
						//Update All Entites
						AllUpdate();

						// Clear the previous frame
						Clear(Pixel());

						// Draw all Entites
						AllDraw();
					}
					else
					{
						//Sets the Player Explosion in Motion
						if (animationTimer > 2)
						{
							//Continue if Life is more than 0
							if (life > 0)
							{
								//Turns the Explsion off on Player
								playerShip->TriggerExplosion();

								//Removes Life
								life--;

								//Resets Animation Timers
								animationFrameTimer = 0;
								animationTimer = 0;
							}
							else
							{
								//Switches to Game Over State
								currentGameState = GAME_STATE::GAME_OVER;
							}
						}
						else
						{
							if (animationFrameTimer > 0.5)
							{
								playerShip->AddToCurrentSprite();
								animationFrameTimer = 0;
							}
							else
							{
								animationFrameTimer += fElapsedTime;
							}

							animationTimer += fElapsedTime;
						}

						playerShip->Draw(this);
					}
				}
				else
				{
					//Pause Text
					if (updateFrameCount >= 60)
					{
						if (textSwitch == false)
						{
							DrawString(50, 150, pausedText, olc::WHITE, 2U);
							textSwitch = true;
						}
						else
						{
							DrawString(50, 150, pausedText, olc::BLACK, 2U);
							textSwitch = false;
						}

						updateFrameCount = 0;
					}
				}
			}
			else
			{
				//Shows Stage Completed for 5 Seconds
				if (timer < 5)
				{
					DrawString(30, 150, stageText + std::to_string(stageNumber) + completedText, olc::WHITE, 1);
					timer += fElapsedTime;
				}
				else
				{
					//Clears Timer and Missiles
					timer = 0;
					missiles.clear();

					//Adds one to each
					life++;
					stageNumber++;

					//Respawns the Enemies
					SpawnEnemies();
				}
			}
			
			break;
		}
		case GAME_STATE::GAME_OVER: 
		{
			//Game Over Menu Control
			if (GetKey(Key::DOWN).bPressed)
			{
				//Switches Active Text
				if (!exitTextActive)
				{
					exitTextActive = true;
					menuTextActive = false;
				}
			}
			else if (GetKey(Key::UP).bPressed)
			{
				//Switches Active Text
				if (!menuTextActive)
				{
					menuTextActive = true;
					exitTextActive = false;
				}
			}
			else if (GetKey(Key::ENTER).bPressed)
			{
				if (menuTextActive)
				{
					//Changes to Menu Game State
					currentGameState = GAME_STATE::MENU;
				}
				else if (exitTextActive)
				{
					//Exits Game
					return false;
				}
			}

			//Draw

			//Clear Screen
			Clear(Pixel());

			//Game Over Text
			DrawString(55, 75, gameText, olc::WHITE, 3);
			DrawString(55, 125, overText, olc::WHITE, 3);
			
			//Score Text
			std::string scoreText = "Score: " + std::to_string(score);
			DrawString((WINDOW_WIDTH / 2) - ((int32_t)(scoreText.length() * 4)), 175, scoreText, olc::WHITE, 1);
			
			//Switch text based on what is Active
			if (menuTextActive)
			{
				DrawString(((WINDOW_WIDTH / 2) - ((int32_t)(activeMenuText.length() * 4))), 200, activeMenuText, olc::WHITE, 1);
			}
			else
			{
				DrawString(((WINDOW_WIDTH / 2) - ((int32_t)(menuText.length() * 4))), 200, menuText, olc::WHITE, 1);
			}

			if (exitTextActive)
			{
				DrawString(((WINDOW_WIDTH / 2) - ((int32_t)(activeExitText.length() * 4))), 220, activeExitText, olc::WHITE, 1);
			}
			else
			{
				DrawString(((WINDOW_WIDTH / 2) - ((int32_t)(exitText.length() * 4))), 220, exitText, olc::WHITE, 1);
			}

			//Space Paritcles
			Pixel pixel = Pixel(rand() % 255, rand() % 255, rand() % 255);
			for (int i = 0; i < 100; i++)
			{
				Draw(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT, pixel);
			}

			break;
		}
	}

	//Update Frame Count
	updateFrameCount++;

	//Continues the Frame
	return true;
}

//Collection of Update and Drawing Logic
#pragma region Update & Draw

//Collection of Updates
void Scene::AllUpdate()
{
	//Player
	playerShip->Update(this);

	//Compile a Access Vector for all Entity Classes
	std::vector<Missile*> missileAccess(missiles.begin(), missiles.end());
	std::vector<Commander*> commanderAccess(commanderShips.begin(), commanderShips.end());
	std::vector<Butterfly*> butterflyAccess(butterflyShips.begin(), butterflyShips.end());
	std::vector<Bee*> beeAccess(beeShips.begin(), beeShips.end());

	//If the Enemy has Dropped to Player Position, reset all Enemy Positions
	if (yTrigger)
	{
		for (int i = 0; i < beeAccess.size(); i++)
		{
			beeAccess[i]->SetPosition(beeAccess[i]->GetOriginalPosition());
		}

		for (int i = 0; i < butterflyAccess.size(); i++)
		{
			butterflyAccess[i]->SetPosition(butterflyAccess[i]->GetOriginalPosition());
		}

		for (int i = 0; i < commanderAccess.size(); i++)
		{
			commanderAccess[i]->SetPosition(commanderAccess[i]->GetOriginalPosition());
		}

		yTrigger = false;
	}

	//Missile Logic Check
	for (int i = 0; i < missileAccess.size(); i++)
	{
		//Checks if the Missile is Out of Bounds while Updating
		if (missileAccess[i]->Update(this) == false)
		{
			RemoveElement(missileAccess[i], ENTITY_TYPE::MISSILE);
		}

		//Checks if the Player gets hit
		if (missileAccess[i]->IsEnemyMissile())
		{
			if (EntityHit(missileAccess[i]->GetPosition(), playerShip->GetPosition(), playerShip->GetSprite()))
			{
				RemoveElement(missileAccess[i], ENTITY_TYPE::MISSILE);
				playerShip->TriggerExplosion();
				missiles.clear();
			}
		}
		
		//Stops the Next Update if the Player has Exploded this Frame
		if (!playerShip->CheckExplosion())
		{
			//Checks if all Commander Ships and see if they got hit
			for (int j = 0; j < commanderAccess.size(); j++)
			{
				//Checks Which Stage the Commander is On
				if (commanderAccess[j]->GetCommanderStage() == false)
				{
					//Checks if the Missile belongs to an Enemy or Player
					if (!missileAccess[i]->IsEnemyMissile())
					{
						if (EntityHit(missileAccess[i]->GetPosition(), commanderAccess[j]->GetPosition(), commanderAccess[j]->GetSprite()))
						{
							RemoveElement(missileAccess[i], ENTITY_TYPE::MISSILE);
							commanderAccess[j]->SetCommanderStage();
							commanderAccess[j]->SetCurrentSprite(2);
						}
					}
				}
				else
				{
					if (!missileAccess[i]->IsEnemyMissile())
					{
						if (EntityHit(missileAccess[i]->GetPosition(), commanderAccess[j]->GetPosition(), commanderAccess[j]->GetSprite()))
						{
							RemoveElement(missileAccess[i], ENTITY_TYPE::MISSILE);
							RemoveElement(commanderAccess[j], ENTITY_TYPE::COMMANDER);

							score += COMMANDER_SCORE;
							enemyCount--;
							commanderShipCount--;
						}
					}
				}
			}

			//Checks if all Butterfly Ships and see if they got hit
			for (int j = 0; j < butterflyAccess.size(); j++)
			{
				if (!missileAccess[i]->IsEnemyMissile())
				{
					if (EntityHit(missileAccess[i]->GetPosition(), butterflyAccess[j]->GetPosition(), butterflyAccess[j]->GetSprite()))
					{
						RemoveElement(butterflyAccess[j], ENTITY_TYPE::BUTTERFLY);
						RemoveElement(missileAccess[i], ENTITY_TYPE::MISSILE);

						score += BUTTERFLY_SCORE;
						enemyCount--;
						butterflyShipCount--;
					}
				}
			}

			//Checks if all Bee Ships and see if they got hit
			for (int j = 0; j < beeAccess.size(); j++)
			{
				if (!missileAccess[i]->IsEnemyMissile())
				{
					if (EntityHit(missileAccess[i]->GetPosition(), beeAccess[j]->GetPosition(), beeAccess[j]->GetSprite()))
					{
						RemoveElement(beeAccess[j], ENTITY_TYPE::BEE);
						RemoveElement(missileAccess[i], ENTITY_TYPE::MISSILE);

						score += BEE_SCORE;
						enemyCount--;
						beeShipCount--;
					}
				}
			}
		}
	}

	//Second Stop Check of Next Update this Frame
	if (!playerShip->CheckExplosion())
	{
		//Enemy Updates after Missile Checks
		for (int i = 0; i < commanderAccess.size(); i++)
		{
			commanderAccess[i]->Update(this);
		}

		for (int i = 0; i < butterflyAccess.size(); i++)
		{
			butterflyAccess[i]->Update(this);
		}

		for (int i = 0; i < beeAccess.size(); i++)
		{
			beeAccess[i]->Update(this);
		}

		//Rolls a chance of a Enemy Shooting a Missile
		if (drawFrameCount >= 30)
		{
			int chance = rand() % 100;

			switch (stageNumber)
			{
				case 1:
				{
					fireChance = 5;
					if (chance > 95)
					{
						int pickedShip = 0;
						if (commanderShipCount > 0)
						{
							pickedShip = rand() % commanderShipCount;
							commanderAccess[pickedShip]->ShootMissile(this);
						}

						if (butterflyShipCount > 0)
						{
							pickedShip = rand() % butterflyShipCount;
							butterflyAccess[pickedShip]->ShootMissile(this);
						}

						if (beeShipCount > 0)
						{
							pickedShip = rand() % beeShipCount;
							beeAccess[pickedShip]->ShootMissile(this);
						}
					}

					break;
				}
				case 2:
				{
					fireChance = 15;
					if (chance > 85)
					{
						int pickedShip = 0;
						if (commanderShipCount > 0)
						{
							pickedShip = rand() % commanderShipCount;
							commanderAccess[pickedShip]->ShootMissile(this);
						}

						if (butterflyShipCount > 0)
						{
							pickedShip = rand() % butterflyShipCount;
							butterflyAccess[pickedShip]->ShootMissile(this);
						}

						if (beeShipCount > 0)
						{
							pickedShip = rand() % beeShipCount;
							beeAccess[pickedShip]->ShootMissile(this);
						}
					}

					break;
				}
				case 3:
				{
					fireChance = 25;
					if (chance > 75)
					{
						int pickedShip = 0;
						if (commanderShipCount > 0)
						{
							pickedShip = rand() % commanderShipCount;
							commanderAccess[pickedShip]->ShootMissile(this);
						}

						if (butterflyShipCount > 0)
						{
							pickedShip = rand() % butterflyShipCount;
							butterflyAccess[pickedShip]->ShootMissile(this);
						}

						if (beeShipCount > 0)
						{
							pickedShip = rand() % beeShipCount;
							beeAccess[pickedShip]->ShootMissile(this);
						}
					}

					break;
				}
				case 4:
				{
					fireChance = 35;
					if (chance > 65)
					{
						int pickedShip = 0;
						if (commanderShipCount > 0)
						{
							pickedShip = rand() % commanderShipCount;
							commanderAccess[pickedShip]->ShootMissile(this);
						}

						if (butterflyShipCount > 0)
						{
							pickedShip = rand() % butterflyShipCount;
							butterflyAccess[pickedShip]->ShootMissile(this);
						}

						if (beeShipCount > 0)
						{
							pickedShip = rand() % beeShipCount;
							beeAccess[pickedShip]->ShootMissile(this);
						}
					}

					break;
				}
				case 5:
				{
					fireChance = 45;
					if (chance > 55)
					{
						int pickedShip = 0;
						if (commanderShipCount > 0)
						{
							pickedShip = rand() % commanderShipCount;
							commanderAccess[pickedShip]->ShootMissile(this);
						}

						if (butterflyShipCount > 0)
						{
							pickedShip = rand() % butterflyShipCount;
							butterflyAccess[pickedShip]->ShootMissile(this);
						}

						if (beeShipCount > 0)
						{
							pickedShip = rand() % beeShipCount;
							beeAccess[pickedShip]->ShootMissile(this);
						}
					}

					break;
				}
				case 6:
				{
					fireChance = 55;
					if (chance > 45)
					{
						int pickedShip = 0;
						if (commanderShipCount > 0)
						{
							pickedShip = rand() % commanderShipCount;
							commanderAccess[pickedShip]->ShootMissile(this);
						}

						if (butterflyShipCount > 0)
						{
							pickedShip = rand() % butterflyShipCount;
							butterflyAccess[pickedShip]->ShootMissile(this);
						}

						if (beeShipCount > 0)
						{
							pickedShip = rand() % beeShipCount;
							beeAccess[pickedShip]->ShootMissile(this);
						}
					}

					break;
				}
				case 7:
				{
					fireChance = 65;
					if (chance > 35)
					{
						int pickedShip = 0;
						if (commanderShipCount > 0)
						{
							pickedShip = rand() % commanderShipCount;
							commanderAccess[pickedShip]->ShootMissile(this);
						}

						if (butterflyShipCount > 0)
						{
							pickedShip = rand() % butterflyShipCount;
							butterflyAccess[pickedShip]->ShootMissile(this);
						}

						if (beeShipCount > 0)
						{
							pickedShip = rand() % beeShipCount;
							beeAccess[pickedShip]->ShootMissile(this);
						}
					}

					break;
				}
				case 8:
				{
					fireChance = 75;
					if (chance > 25)
					{
						int pickedShip = 0;
						if (commanderShipCount > 0)
						{
							pickedShip = rand() % commanderShipCount;
							commanderAccess[pickedShip]->ShootMissile(this);
						}

						if (butterflyShipCount > 0)
						{
							pickedShip = rand() % butterflyShipCount;
							butterflyAccess[pickedShip]->ShootMissile(this);
						}

						if (beeShipCount > 0)
						{
							pickedShip = rand() % beeShipCount;
							beeAccess[pickedShip]->ShootMissile(this);
						}
					}

					break;
				}
				case 9:
				{
					fireChance = 85;
					if (chance > 15)
					{
						int pickedShip = 0;
						if (commanderShipCount > 0)
						{
							pickedShip = rand() % commanderShipCount;
							commanderAccess[pickedShip]->ShootMissile(this);
						}

						if (butterflyShipCount > 0)
						{
							pickedShip = rand() % butterflyShipCount;
							butterflyAccess[pickedShip]->ShootMissile(this);
						}

						if (beeShipCount > 0)
						{
							pickedShip = rand() % beeShipCount;
							beeAccess[pickedShip]->ShootMissile(this);
						}
					}

					break;
				}
				default:
				{
					fireChance = 95;
					if (chance > 5)
					{
						int pickedShip = 0;
						if (commanderShipCount > 0)
						{
							pickedShip = rand() % commanderShipCount;
							commanderAccess[pickedShip]->ShootMissile(this);
						}

						if (butterflyShipCount > 0)
						{
							pickedShip = rand() % butterflyShipCount;
							butterflyAccess[pickedShip]->ShootMissile(this);
						}

						if (beeShipCount > 0)
						{
							pickedShip = rand() % beeShipCount;
							beeAccess[pickedShip]->ShootMissile(this);
						}
					}

					break;
				}
			}

			drawFrameCount = 0;
		}

		//Checks if Enenmy has drops to Player Position
		for (int i = 0; i < beeAccess.size(); i++)
		{
			if (beeAccess[i]->GetPosition().GetY() >= playerShip->GetPosition().GetY())
			{
				yTrigger = true;
				break;
			}
		}

		for (int i = 0; i < butterflyAccess.size(); i++)
		{
			if (butterflyAccess[i]->GetPosition().GetY() >= playerShip->GetPosition().GetY())
			{
				yTrigger = true;
				break;
			}
		}

		for (int i = 0; i < commanderAccess.size(); i++)
		{
			if (commanderAccess[i]->GetPosition().GetY() >= playerShip->GetPosition().GetY())
			{
				yTrigger = true;
				break;
			}
		}

		//If they have, Trigger Explosion
		if (yTrigger)
		{
			playerShip->TriggerExplosion();
		}
	}

	drawFrameCount++;
}

//Collection of Draws
void Scene::AllDraw()
{
	//Player
	playerShip->Draw(this);

	//Compile a Access Vector for all Entity Classes
	std::vector<Missile*> missileAccess(missiles.begin(), missiles.end());
	std::vector<Commander*> commanderAccess(commanderShips.begin(), commanderShips.end());
	std::vector<Butterfly*> butterflyAccess(butterflyShips.begin(), butterflyShips.end());
	std::vector<Bee*> beeAccess(beeShips.begin(), beeShips.end());

	//All Entites Draws
	for (int i = 0; i < missiles.size(); i++)
	{
		missileAccess[i]->Draw(this);
	}

	for (int i = 0; i < commanderShips.size(); i++)
	{
		commanderAccess[i]->Draw(this);
	}

	for (int i = 0; i < butterflyAccess.size(); i++)
	{
		butterflyAccess[i]->Draw(this);
	}

	for (int i = 0; i < beeShips.size(); i++)
	{
		beeAccess[i]->Draw(this);
	}

	//Space Paritcles
	Pixel pixel = Pixel(rand() % 255, rand() % 255, rand() % 255);
	for (int i = 0; i < 100; i++)
	{
		Draw(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT, pixel);
	}

	//UI Text
	DrawString(0, 0, scoreText + std::to_string(score));
	DrawString(0, 10, lifeText + std::to_string(life));
	DrawString(0, 20, enemyCountText + std::to_string(enemyCount));

	DrawString(0, 30, enemyFireChanceText + std::to_string(fireChance) + percentageText);
}

#pragma endregion

//Collection of all Functions Adding and Removing Elements from their Arrays
#pragma region Add and Remove Elements
//Add Missile
void Scene::AddMissile(Missile* missile)
{
	missiles.push_back(missile);
}

//Add Commander
void Scene::AddCommander(Commander* commander)
{
	commanderShips.push_back(commander);
}

//Add Butterfly
void Scene::AddButterfly(Butterfly* butterfly)
{
	butterflyShips.push_back(butterfly);
}

//Add Bee
void Scene::AddBee(Bee* bee)
{
	beeShips.push_back(bee);
}

//Remove Entity
template <class T> 
void Scene::RemoveElement(T* objectToRemove, ENTITY_TYPE entityType)
{
	if (entityType == ENTITY_TYPE::MISSILE)
	{
	missiles.remove((Missile*)objectToRemove);
	}
	else if (entityType == ENTITY_TYPE::COMMANDER)
	{
		commanderShips.remove((Commander*)objectToRemove);
	}
	else if (entityType == ENTITY_TYPE::BUTTERFLY)
	{
		butterflyShips.remove((Butterfly*)objectToRemove);
	}
	else if (entityType == ENTITY_TYPE::BEE)
	{
		beeShips.remove((Bee*)objectToRemove);
	}
}
#pragma endregion

//Enemy Hit Detetction
bool Scene::EntityHit(Vector2 &missilePos, Vector2 &objectHit, Sprite* objectSprite)
{
	//Checks around the Entity and sees if the Missile has hit
	if ((missilePos.GetX() >= objectHit.GetX() && missilePos.GetX() <= (objectHit.GetX() + objectSprite->width)) && (missilePos.GetY() >= objectHit.GetY() && missilePos.GetY() <= (objectHit.GetY() + objectSprite->height)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Spawn all Enemies
void Scene::SpawnEnemies()
{
	//Commander
	for (int i = 0, j = COMMANDER_SPRITE_WIDTH; i < NUM_OF_COMMANDER_SHIPS; i += COMMANDER_SPRITE_WIDTH)
	{
		AddCommander(new Commander((float)(i + j)));
		enemyCount++;
		commanderShipCount++;
		j += COMMANDER_SPRITE_GAP;
	}

	//Butterfly
	bool turnOver = false;
	for (int i = 0, j = BUTTERFLY_SPRITE_WIDTH, k = 0; i < NUM_OF_BUTTERFLY_SHIPS; i += BUTTERFLY_SPRITE_WIDTH)
	{
		if (i <= HALF_OF_BUTTERFLY_SHIPS - BUTTERFLY_SPRITE_WIDTH && turnOver == false)
		{
			AddButterfly(new Butterfly((float)(i + j), 70));
			enemyCount++;
			butterflyShipCount++;
			j += BUTTERFLY_SPRITE_GAP;
		}
		else
		{
			if (turnOver == false)
			{
				i -= BUTTERFLY_SPRITE_WIDTH;
				j = BUTTERFLY_SPRITE_WIDTH;
				turnOver = true;
			}
			else
			{
				AddButterfly(new Butterfly((float)(k + j), 100));
				enemyCount++;
				butterflyShipCount++;
				j += BUTTERFLY_SPRITE_GAP;
				k += BUTTERFLY_SPRITE_WIDTH;
			}
		}
	}

	//Bee
	turnOver = false;
	for (int i = 0, j = BEE_SPRITE_WIDTH, k = 0; i < NUM_OF_BEE_SHIPS; i += BEE_SPRITE_WIDTH)
	{
		if (i <= HALF_OF_BEE_SHIPS - BEE_SPRITE_WIDTH && turnOver == false)
		{
			AddBee(new Bee((float)(i + j), 130));
			enemyCount++;
			beeShipCount++;
			j += BEE_SPRITE_GAP;
		}
		else
		{
			if (turnOver == false)
			{
				i -= BEE_SPRITE_WIDTH;
				j = BEE_SPRITE_WIDTH;
				turnOver = true;
			}
			else
			{
				AddBee(new Bee((float)(k + j), 160));
				enemyCount++;
				beeShipCount++;
				j += BEE_SPRITE_GAP;
				k += BEE_SPRITE_WIDTH;
			}
		}
	}
}

//Resets all Varaiables to Default
void Scene::ResetGame()
{
	//All Intergers
	score = 0;
	life = 3;
	stageNumber = 1;
	enemyCount = 0;
	drawFrameCount = 0;
	updateFrameCount = 0;
	commanderShipCount = 0;
	butterflyShipCount = 0;
	beeShipCount = 0;

	//All Floats
	animationTimer = 0.0f;
	animationFrameTimer = 0.0f;

	//All Arrays
	commanderShips.clear();
	butterflyShips.clear();
	beeShips.clear();

	//All Others
	delete playerShip;
	playerShip = nullptr;
}