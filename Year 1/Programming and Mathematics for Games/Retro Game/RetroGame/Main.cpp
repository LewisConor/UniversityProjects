//Pre-File Definition
#define OLC_PGE_APPLICATION

//Includes
#include "olcPixelGameEngine.h"
#include "olcPGEX_Sound.h"
#include "Scene.h"
#include "Constants.h"

//Main Entry Point for Program
int main()
{
	//Starts Random Seed Generation
	srand((unsigned int)time(NULL));

	// Entry point for our game
	Scene retroGameScene;
	if (retroGameScene.Construct(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_PIXEL_WIDTH, WINDOW_PIXEL_HEIGHT, false, true))
	{
		//Starts the Game Scene
		retroGameScene.Start();
	}

	//Destoys the Audio
	SOUND::DestroyAudio();

	//Exit Point for Program
	return 0;
}