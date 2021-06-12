#pragma once

//C++ Includes
#include <Windows.h>
#include <time.h>
#include <chrono>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>

//Project Includes
#include "Raycaster_Types.h"
#include "Renderer.h"
#include "Console.h"
#include "TextureManager.h"
#include "Texture.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "Timer.h"

#pragma region Definitions
//Window Dimension
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

//Console Dimension and Position
#define CONSOLE_WIDTH 120
#define CONSOLE_HEIGHT 40
#define CONSOLE_X_POS 20
#define CONSOLE_Y_POS 180

//Player Properties
#define PI 3.1415926535
#define FOV 60
#define HALF_FOV (FOV>>1)

//Other Defined Data
#define BYTES_PER_PIXEL 4
#pragma endregion