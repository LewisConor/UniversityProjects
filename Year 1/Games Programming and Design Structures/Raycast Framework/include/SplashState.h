#include <stdafx.h>
#include "GameState.h"
#pragma once

#ifndef __SPLASH_STATE_H__
#define __SPLASH_STATE_H__

class SplashState : public GameState
{
public:
	SplashState();
	virtual ~SplashState();

	virtual void Initialise(float a_fDT);
	virtual void Update(float a_fDT);
	virtual void Leave(float a_fDT);

	virtual void Draw();

private:
	TextureManager* m_texManager;
	Texture* m_tex;
};
#endif // !__SPLASH_STATE_H__
