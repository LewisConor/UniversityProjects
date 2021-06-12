//Precompiled Header File
#include <stdafx.h>

//Header File
#include "SplashState.h"

//Other Includes
#include "GamePlayState.h"
#include "GameState.h"
#include "Texture.h"

//Constructor
SplashState::SplashState() : GameState(), m_texManager(nullptr), m_tex(nullptr) {}

//Destructor
SplashState::~SplashState()
{
	if (m_texManager->TextureExists("resources/images/TITLEH.PCX"))
	{
		m_texManager->ReleaseTexture(m_tex);
	}
}

//Initaliser
void SplashState::Initialise(float a_fDT)
{
	UNREFERENCED_PARAMETER(a_fDT);

	//Gets the Texture Manager Instance
	m_texManager = TextureManager::GetInstance();

	m_isActive = true;
	m_fTimeInState = 0.0f;

	//Loads and Checks the Texture if its properly loaded
	if ((m_tex = m_texManager->LoadTexture("resources/images/TITLEH.PCX", 0)) != nullptr)
	{
		//Console Data
		GetConsole()->WriteToLocation((wchar_t*)"Current State: Splash Screen State", 20, 0, 3);

		//Changes Process to Update
		Process = &GameState::Update;
	}
	else
	{
		//Console Data
		GetConsole()->WriteToLocation((wchar_t*)"State Error: Error Loading Splash Screen...", 32, 0, 3);
	}
}

void SplashState::Update(float a_fDT)
{
	UNREFERENCED_PARAMETER(a_fDT);
	m_fTimeInState += a_fDT;

	//Waits for 5 Seconds
	if (m_fTimeInState > 5.0f)
	{
		m_fTimeInState = 0.0f;

		//Changes Process to Leave
		Process = &GameState::Leave;
	}
}

void SplashState::Draw()
{
	//Gets the Renderer Instance
	Renderer* renderer = Renderer::GetInstance();

	if (m_tex != nullptr)
	{
		u32 w = 0, h = 0;
		m_tex->GetDimensions(w, h);

		//Draws Image on Screen
		renderer->FillRenderBuffer(0, 0, w, h, m_tex->GetPixelData());
	}
}

void SplashState::Leave(float a_fDT)
{
	UNREFERENCED_PARAMETER(a_fDT);
	
	//Creates and Initalises Game Play State
	GamePlayState* gpState = new GamePlayState(1);
	gpState->SetStateName("GamePlayState_Level_1");
	gpState->SetManager(GetManager());
	gpState->SetConsole(GetConsole());
	GetManager()->SetGamePlayStatus(true);

	//Pushs to GSM
	GetManager()->PushState(gpState);

	//Removes this from GSM
	GetManager()->RemoveState(this);
}