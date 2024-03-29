#include "MainMenuState.h"

#include "GameStateMachine.h"

const std::string MainMenuState::s_menuID = "MENU";

bool MainMenuState::onEnter()
{
	GameState::onEnter();

	if (m_callbacks.empty())
	{
		m_callbacks.push_back(0); //pushback 0 callbackID start from 1
		m_callbacks.push_back(s_menuToPlay);
		m_callbacks.push_back(s_exitFromMenu);

		//set the callbacks for menu items
		setCallbacks(m_callbacks);
	}

	m_loadingComplete = true;
	
	return true;
}

void MainMenuState::s_menuToPlay()
{
	TheGameStateMachine::Instance().changeState(PLAY);
}

void MainMenuState::s_exitFromMenu()
{
	TheGameStateMachine::Instance().quit();
}
