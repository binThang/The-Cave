#pragma once

#include "AllManage.h"
#include "Sprite.h"
#define TERM 7

class Menu
{
private:

	Sprite	BBG;
	Sprite	BG;
	Sprite	Button;

	int		select;

	bool	LEFTKEYPRESS;
	bool	RIGHTKEYPRESS;

	int		timet;

public:
	void	Update(int &m_iCurrentState, int &m_iCurrentStage);
	void	Render();
	void	init();
};