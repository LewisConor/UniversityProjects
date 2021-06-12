#pragma once
//Includes
#include <string>
#include <cstdlib>

//Definitions
#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 350
#define WINDOW_PIXEL_WIDTH 2
#define WINDOW_PIXEL_HEIGHT 2

#ifdef GAME_TEXT

//Main Menu
const std::string titleOne = "SPACE INVADERS";
const std::string titleTwo = "MEETS GALAGA";

const std::string activePlayText = "-> PLAY";
const std::string playText = "PLAY";

const std::string activeMenuText = "-> Main Menu";
const std::string menuText = "Main Menu";

const std::string activeExitText = "-> EXIT";
const std::string exitText = "EXIT";

const std::string controlText = "CONTROLS";
const std::string menuControlText = "Up/Down - Menu Control";
const std::string movementText = "Left/Right - Movement";
const std::string shootText = "Z/X - Shoot Missile";
const std::string pauseText = "P - Pause";
const std::string interactText = "Enter - Interact/Confirm";


//In-Game
const std::string pausedText = "PAUSED";
const std::string scoreText = "Score: ";
const std::string lifeText = "Life: ";
const std::string enemyCountText = "Enemies Left: ";
const std::string enemyFireChanceText = "Enemy Fire Chance: ";
const std::string percentageText = "%";
const std::string stageText = "Stage ";
const std::string completedText = " Completed";

//Game Over
const std::string gameText = "GAME";
const std::string overText = "OVER";


#endif // !GAME_TEXT