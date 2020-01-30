#include "StateMachine.h"

StateMachine::StateMachine()
{
	m_iCurrentStage = 1 ;
	m_iCurrentState = MENU;

	m_Field = new Field();

	ifreset = true;
}

void StateMachine::Update()
{
	m_tempState = m_iCurrentState;
	if(!(m_iCurrentState == PAUSE))
		m_beforepauseState = m_tempState;

	switch( m_iCurrentState )
	{
	case MENU:
		m_Menu.Update(m_iCurrentState, m_iCurrentStage);
		break;

	case FIELD:
		m_Field->Update(m_iCurrentState, m_iCurrentStage);
		break;

	case BATTLE:
		m_Battle.Update(m_iCurrentState, m_iCurrentStage);
		break;

	case PAUSE:
		m_Pause.Update(m_iCurrentState, m_iCurrentState, m_beforepauseState);
		break;

	case LVUP:
		m_LvUp.Update(m_iCurrentState);
		break;

	case GAMEOVER:
		m_GameOver.Update(m_iCurrentState, m_iCurrentStage);
		ifreset = false;
		break;

	case GAMEEND:
		m_Ending.Update();
		break;
	}

	if (!ifreset)
	{
		GameReset();
	}
}

void StateMachine::Render()
{
	switch( m_tempState )
	{
	case MENU:
		m_Menu.Render();
		break;

	case FIELD:
		m_Field->Render(m_iCurrentStage);
		break;

	case BATTLE:
		if(m_Battle.whilebattle==true)
			m_Battle.Render(m_iCurrentState, m_iCurrentStage);
		break;

	case PAUSE:
		if(m_beforepauseState==FIELD)
			m_Field->Render(m_iCurrentStage);
		else if(m_beforepauseState==BATTLE)
			m_Battle.Render(m_iCurrentState, m_iCurrentStage);
		m_Pause.Render();
		break;
		
	case LVUP:
		m_LvUp.Render();
		break;

	case GAMEOVER:
		m_GameOver.Render();
		break;

	case GAMEEND:
		m_Ending.Render();
		break;

	}
}

void StateMachine::init(HWND g_hWnd)
{
	m_Menu.init();
}

void StateMachine::GameReset()
{

	delete m_Field;
	m_Field = new Field();

	m_iCurrentStage = 1;

	HeroStat::star = 0;
	HeroStat::fullhp = 3;
	HeroStat::hp = 3;
	HeroStat::level = 1;
	HeroStat::attack = 1;

	ifreset = true;
}

