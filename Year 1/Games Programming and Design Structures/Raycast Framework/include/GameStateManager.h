#include <stdafx.h>
#pragma once

#ifndef __GAME_STATE_MANAGER_H__
#define __GAME_STATE_MANAGER_H__

class GameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	static GameStateManager* GetInstance() { return m_instance; }

	void Update(float a_fDT);
	void Draw();

	bool RemoveState(GameState* a_pState);
	bool PopToState(GameState* a_pState);
	void PushState(GameState* a_pState);
	void PopState();

	GameState* StateExists(const char* a_pStateName);

	GameState* GetState() { return m_currentState; }

	void LoadGamePlayState(GameState* currentGameState, int newGamePlayStateID);

	bool GetGamePlayStatus() { return m_gamePlayActive; }
	void SetGamePlayStatus(bool a_bool) { m_gamePlayActive = a_bool; }

private:
	static GameStateManager* m_instance;

	std::vector<GameState*> m_pStates;
	std::vector<GameState*> m_pStatesToFree;

	GameState* m_currentState;
	bool m_gamePlayActive;
};
#endif // !__GAME_STATE_MANAGER_H__
