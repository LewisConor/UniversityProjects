//Include Precompiled Header File
#include <stdafx.h>

//Includes
#include "SplashState.h"
#include "GamePlayState.h"
#include "Player.h"
#include "Level.h"

//Main Function
int main(int argc, char* argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	//Creates Console Window
	Console* console = new Console();
	console->Initaialise("Raycaster Framework - Data Console Window");

	//Creates the Renderer Window
	Renderer mainRenderer;
	if (!mainRenderer.Initialise(console->GetConsoleWindowHandle(), "Raycaster Framework - Render Window", WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		//Creates Game State Manager
		GameStateManager* gsManager = new GameStateManager();

		//Creates the Texture Manager
		TextureManager texManager;

		//Creates the Input Manager
		InputManager* inputManager = InputManager::CreateInstance();

		//Random Seed
		srand((unsigned int)time(nullptr));

		MSG msg = { 0 };

		//Creates timer to get Delta Time each frame;
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto previousTime = currentTime;
		double timer = 0.0f;

		std::chrono::duration<double> elapsedTime;
		unsigned int frame = 0;

		//Initalises Splash Screen
		SplashState* splashState = new SplashState();
		splashState->SetStateName("SplashState");
		splashState->SetManager(gsManager);
		splashState->SetConsole(console);

		//Push Splash Screen to GSM
		gsManager->PushState(splashState);

		//Main Loop
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//Calculates Delta Time
				previousTime = currentTime;
				currentTime = std::chrono::high_resolution_clock::now();
				elapsedTime = currentTime - previousTime;
				double fElapsedTime = elapsedTime.count();
				timer += fElapsedTime;

				#pragma region Update Method
				gsManager->Update((float)(fElapsedTime));

				//Input Control

				//Level 1
				if (inputManager->GetKeyDown('1'))
				{
					if (((GamePlayState*)gsManager->GetState())->GetLevelID() != 1)
					{
						gsManager->SetGamePlayStatus(false);
						gsManager->LoadGamePlayState(gsManager->GetState(), 1);
					}
				}

				//Level 2
				if (inputManager->GetKeyDown('2'))
				{
					if (((GamePlayState*)gsManager->GetState())->GetLevelID() != 2)
					{
						gsManager->SetGamePlayStatus(false);
						gsManager->LoadGamePlayState(gsManager->GetState(), 2);
					}
				}

				//Level 3
				if (inputManager->GetKeyDown('3'))
				{
					if (((GamePlayState*)gsManager->GetState())->GetLevelID() != 3)
					{
						gsManager->SetGamePlayStatus(false);
						gsManager->LoadGamePlayState(gsManager->GetState(), 3);
					}
				}

				//Exit Program
				if (inputManager->GetKeyDown(27))
				{
					msg.message = WM_QUIT;
				}
				#pragma endregion

				#pragma region Draw Method
				mainRenderer.ClearRenderBuffer();

				gsManager->Draw();
				mainRenderer.Draw();

				if (frame % 30 == 0)
				{
					//FPS Data
					wchar_t fpsBuffer[8];
					unsigned int fps = (unsigned int)(1.0f / fElapsedTime);
					swprintf(fpsBuffer, 8, L"FPS:%3u", fps > 999 ? 999 : fps);
					console->WriteToLocation(fpsBuffer, 8, 0, 0);

					//Time Since Boot
					wchar_t timerBuffer[16];					
					swprintf(timerBuffer, 16, L"Timer:%.2Lf", timer);					
					console->WriteToLocation(timerBuffer, 10, 0, 1);

					//Player X and Y
					if (gsManager->GetGamePlayStatus())
					{
						GamePlayState* gamePlayState = (GamePlayState*)gsManager->GetState();
						float playerX;
						float playerY;
						gamePlayState->GetPlayer()->GetPosition(playerX, playerY);

						wchar_t playerXBuffer[16];
						wchar_t playerYBuffer[16];

						swprintf(playerXBuffer, 16, L"Player X:%.2Lf", playerX);
						swprintf(playerYBuffer, 16, L"Player Y:%.2Lf", playerY);

						console->WriteToLocation(playerXBuffer, 16, 0, 8);
						console->WriteToLocation(playerYBuffer, 16, 0, 9);
					}

					console->WriteToLocation((wchar_t*)"Press Number for Levels.", 16, 0, 11);
					console->WriteToLocation((wchar_t*)"1 for Level 1", 8, 0, 12);
					console->WriteToLocation((wchar_t*)"2 for Level 2", 8, 0, 13);
					console->WriteToLocation((wchar_t*)"3 for Level 3", 8, 0, 14);
				}
				#pragma endregion

				++frame;
			}
		}

		delete gsManager;
		return 0;
	}

	return 1;
}