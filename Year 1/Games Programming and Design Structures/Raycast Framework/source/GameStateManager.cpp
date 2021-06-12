//Precompiled Header File
#include <stdafx.h>

//Header File
#include "GameStateManager.h"

//Other Includes
#include "GameState.h"
#include "GamePlayState.h"

GameStateManager* GameStateManager::m_instance = nullptr;

//Constructor
GameStateManager::GameStateManager() : m_gamePlayActive(false)
{
	m_instance = this;

	//Clears both arrays
	m_pStates.clear();
	m_pStatesToFree.clear();
}

//Destructor
GameStateManager::~GameStateManager()
{
	//Deletes any remaining States
	for (auto iter = m_pStatesToFree.begin(); iter != m_pStatesToFree.end(); ++iter)
	{
		GameState* pState = *iter;
		delete pState;
		pState = nullptr;
	}
	m_pStatesToFree.clear();

	for (auto iter = m_pStates.begin(); iter != m_pStates.end(); ++iter)
	{
		GameState* pState = *iter;
		delete pState;
		pState = nullptr;
	}
	m_pStates.clear();
}

void GameStateManager::Draw()
{
	//Does all Draw Requests
	for (auto iter = m_pStates.begin(); iter != m_pStates.end(); ++iter)
	{
		if ((*iter)->IsActive())
		{
			(*iter)->Draw();
		}
	}
}

void GameStateManager::Update(float a_fDT)
{
	//Does alll Update Requests
	if (m_pStatesToFree.size() > 0)
	{
		for (auto iter = m_pStatesToFree.begin(); iter != m_pStatesToFree.end(); ++iter)
		{
			GameState* pState = *iter;
			delete pState;
			pState = nullptr;
		}
		m_pStatesToFree.clear();
	}

	for (auto iter = m_pStates.rbegin(); iter != m_pStates.rend(); ++iter)
	{
		u32 popStates = (u32)(m_pStatesToFree.size());
		void (GameState:: * func)(float) = (*iter)->Process;
		((*iter)->*func)(a_fDT);
		if (m_pStatesToFree.size() != popStates)
		{
			break;
		}
	}
}

//Checks if a State Exists
GameState* GameStateManager::StateExists(const char* a_pStateName)
{
	for (auto iter = m_pStates.begin(); iter != m_pStates.end(); ++iter)
	{
		GameState* pState = (*iter);
		const char* pName = pState->GetStateName();
		if (pName != nullptr && strcmp(pName, a_pStateName) == 0)
		{
			return pState;
		}
	}

	return nullptr;
}

//Pushs State to the GSM Array
void GameStateManager::PushState(GameState* a_pState)
{
	if (a_pState)
	{
		m_pStates.push_back(a_pState);
	}

	m_currentState = a_pState;
}

//Removes State from GSM Array
void GameStateManager::PopState()
{
	if (m_pStates.size() > 0)
	{
		GameState* pLastState = m_pStates.back();
		m_pStatesToFree.push_back(pLastState);

		m_pStates.pop_back();
	}
}

//Checks of State Exists and then Removes it
bool GameStateManager::PopToState(GameState* a_pState)
{
	int i = 0;
	bool stateFound = false;
	for (std::vector<GameState*>::reverse_iterator iter = m_pStates.rbegin(); iter != m_pStates.rend(); ++iter, ++i)
	{
		if ((*iter) == a_pState)
		{
			stateFound = true;
			break;
		}
	}

	if (stateFound)
	{
		for (int j = i; j > 0; --j)
		{
			GameState* pLastState = m_pStates.back();
			m_pStatesToFree.push_back(pLastState);
			m_pStates.pop_back();
		}
	}	

	return stateFound;
}

//Removes State
bool GameStateManager::RemoveState(GameState* a_pState)
{
	for (auto iter = m_pStates.begin(); iter != m_pStates.end(); ++iter)
	{
		GameState* pState = (*iter);
		if (pState == a_pState)
		{
			m_pStatesToFree.push_back(pState);
			m_pStates.erase(iter);
			return true;
		}
	}
	return false;
}

void GameStateManager::LoadGamePlayState(GameState* currentState, int newGamePlayStateID)
{
	GamePlayState* newGamePlayState = new GamePlayState(newGamePlayStateID);
	
	newGamePlayState->SetManager(this);
	newGamePlayState->SetConsole(currentState->GetConsole());

	char buffer[32];
	strncpy(buffer, "GamePlayState_Level_", sizeof(buffer));
	strncat(buffer, std::to_string(newGamePlayStateID).c_str(), sizeof(buffer));

	newGamePlayState->SetStateName(buffer);

	PushState(newGamePlayState);

	RemoveState(currentState);
}