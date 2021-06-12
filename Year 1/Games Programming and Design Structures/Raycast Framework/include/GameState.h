#include <stdafx.h>
#pragma once

#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

//Foward Declare Class
class GameStateManager;

class GameState
{
public:
	GameState();
	virtual ~GameState();

	virtual void Initialise(float a_fDT) = 0;
	virtual void Update(float a_fDT) = 0;
	virtual void Leave(float a_fDT) = 0;

	virtual void Draw();

	void SetStateName(const char* a_name);
	const char* GetStateName();

	void SetManager(GameStateManager* a_pManager);
	GameStateManager* GetManager() { return m_pManager; }

	void SetConsole(Console* a_pConsole) { m_pConsole = a_pConsole; }
	Console* GetConsole() { return m_pConsole; }

	bool IsActive() { return m_isActive; }

	void (GameState::* Process)(float);
private:
	char* m_Name;
	GameStateManager* m_pManager;
	Console* m_pConsole;
protected:
	float m_fTimeInState;
	bool m_isActive;
};
#endif // !__GAME_STATE_H__
