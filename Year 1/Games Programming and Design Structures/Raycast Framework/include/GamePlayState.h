#include <stdafx.h>
#include "GameState.h"
#pragma once

#ifndef __GAMEPLAY_STATE_H__
#define __GAMEPLAY_STATE_H__

class Player;
class Level;

class GamePlayState : public GameState
{
public:
	GamePlayState(int levelNumber);
	virtual ~GamePlayState() { }

	virtual void Initialise(float a_fDT);
	virtual void Update(float a_fDT);
	virtual void Leave(float a_fDT);

	virtual void Draw();

	Player* GetPlayer() { return m_pPlayer; }
	int GetLevelID() { return m_levelID; }

private:
	Level* m_pLevel;
	int m_levelID;
	bool m_levelLoaded;
	Player* m_pPlayer;
};
#endif // !__GAMEPLAY_STATE_H__
