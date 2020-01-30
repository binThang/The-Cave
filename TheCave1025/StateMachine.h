#pragma once

#include "MenuState.h"
#include "Field1State.h"
#include "BattleState.h"
#include "PauseState.h"
#include "LvUpState.h"
#include "GameOverState.h"
#include "EndingState.h"

#include "HeroStat.h"
#include "AllManage.h"


class StateMachine
{
private:
	Battle		m_Battle;	
	Field*		m_Field;
	Menu		m_Menu;
	Pause		m_Pause;
	LvUp		m_LvUp;
	GameOver	m_GameOver;
	Ending		m_Ending;

	void		GameReset();

	bool		ifreset;

public:
				StateMachine();
	enum		State				{MENU, FIELD, BATTLE, PAUSE, GAMEOVER, LVUP, GAMEEND};
	void		Render();
	void		Update();
	void		init(HWND g_hWnd);

	int			m_iCurrentState;
	int			m_tempState;
	int			m_beforepauseState;

	int			m_iCurrentStage;
	int			m_tempStage;

};