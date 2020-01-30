#pragma once

#include "Sprite.h"
#include "AllManage.h"

#define TERM 7

class GameOver
{
private:
	Sprite		GameOverBG;
	
	bool		ifinit;
	bool		UPKEYPRESS;
	bool		DOWNKEYPRESS;

	int			select;
	int			timet;

public:
			GameOver();
	void	Update(int &m_iCurrentState, int &m_iCurrentStage);
	void	Render();
	void	init();
};