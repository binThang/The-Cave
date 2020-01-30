#pragma once

#include "AllManage.h"
#include "Sprite.h"

#define TERM 7

class Pause
{
private:

	int		timet;

	int select;
	int	ifinit;

	Sprite	m_pauseBG;

public:

			Pause();

	void	init();
	void	Update(int &m_iCurrentState, int &m_iCurrentStage, int &m_beforeState);
	void	Render();
};
