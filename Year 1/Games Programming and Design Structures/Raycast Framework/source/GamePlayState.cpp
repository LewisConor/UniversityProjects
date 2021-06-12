//Precompiled Header File
#include <stdafx.h>

//Header File
#include "GamePlayState.h"

//Other Includes
#include "GameStateManager.h"
#include "GameState.h"
#include "Player.h"
#include "Level.h"

//Constructor
GamePlayState::GamePlayState(int levelNumber) : GameState(), m_pLevel(nullptr), m_pPlayer(nullptr), m_levelLoaded(false)
{
	m_levelID = levelNumber;
	Process = &GameState::Initialise;
}

//Initialiser
void GamePlayState::Initialise(float a_fDT)
{
	UNREFERENCED_PARAMETER(a_fDT);

	//Creates new Level
	m_pLevel = new Level();

	switch (m_levelID)
	{
		case 1: 
		{
			m_levelLoaded = m_pLevel->LoadLevel("resources/levels/testMap_1.map");
			break;
		}
		case 2:
		{
			m_levelLoaded = m_pLevel->LoadLevel("resources/levels/testMap_2.map");
			break;
		}
		case 3:
		{
			m_levelLoaded = m_pLevel->LoadLevel("resources/levels/testMap_3.map");
			break;
		}
	}

	//Loads the Level
	if (m_levelLoaded)
	{
		//Creates and Initalises the Player
		m_pPlayer = new Player(this);

		m_isActive = true;

		wchar_t gameStateBuffer[40];
		const char* gameStateName = GetStateName();
		swprintf(gameStateBuffer, 40, L"Current State: %S", gameStateName);

		//Console Data
		GetConsole()->WriteToLocation(gameStateBuffer, 40, 0, 3);

		wchar_t levelNameBuffer[64];
		wchar_t levelWidthBuffer[16];
		wchar_t levelHeightBuffer[20];
		u32 w = 0, h = 0;

		m_pLevel->GetSize(w, h);

		swprintf(levelNameBuffer, 64, L"Level Name: %S", m_pLevel->GetLevelName());
		swprintf(levelWidthBuffer, 16, L"Level Width: %d", w);
		swprintf(levelHeightBuffer, 20, L"Level Height: %d", h);

		GetConsole()->WriteToLocation(levelNameBuffer, 64, 0, 4);
		GetConsole()->WriteToLocation(levelWidthBuffer, 16, 0, 5);
		GetConsole()->WriteToLocation(levelHeightBuffer, 20, 0, 6);

		GetManager()->SetGamePlayStatus(true);

		//Set Process to Update
		Process = &GameState::Update;
	}
	else
	{
		//Console Update
		GetConsole()->WriteToLocation((wchar_t*)"State Error: Error Loading Map...", 16, 0, 3);
	}
}

//Update Method
void GamePlayState::Update(float a_fDT)
{
	UNREFERENCED_PARAMETER(a_fDT);

	//Update Method on Player
	m_pPlayer->Update(a_fDT);
}

//Draw Method
void GamePlayState::Draw()
{
	//Gets Renderer Instance
	Renderer* renderer = Renderer::GetInstance();

	//Draws Background
	renderer->DrawBackground();

	//Draw Method on Level
	m_pLevel->Draw(m_pPlayer);

	//Draw Method on Player
	m_pPlayer->Draw();
}

//Leave Method
void GamePlayState::Leave(float a_fDT)
{
	UNREFERENCED_PARAMETER(a_fDT);

	//Removes current State
	GetManager()->RemoveState(this);
}