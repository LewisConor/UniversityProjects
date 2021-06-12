//Precompiled Header File
#include <stdafx.h>

//Header File
#include "GameState.h"

//Other Includes
#include "GameStateManager.h"

//Constructor
GameState::GameState() : m_pManager(nullptr), m_Name(nullptr), m_fTimeInState(0.0f), m_isActive(false)
{
	//Sets Process to Initalise
	Process = &GameState::Initialise;
}

//Deconstructor
GameState::~GameState()
{
	if (m_Name != nullptr)
	{
		delete[] m_Name;
		m_Name = nullptr;
	}
}

//Sets the Current States Name
void GameState::SetStateName(const char* a_pStateName)
{
	if (m_Name == nullptr)
	{
		u64 l = (u64)strlen(a_pStateName);
		m_Name = new char[l + 1];
		strcpy(m_Name, a_pStateName);
	}
}

//Gets the State Name
const char* GameState::GetStateName()
{
	return m_Name;
}

//Sets the Manager
void GameState::SetManager(GameStateManager* a_pManager)
{
	m_pManager = a_pManager;
}

void GameState::Draw()
{
}