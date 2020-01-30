#pragma once

#include "AllManage.h"
#include "Sprite.h"

class LvUp
{
private:
	Sprite		LvUpBG[7];
	bool		SPACEKEYPRESS;
	bool		ifinit;

public:

	LvUp()	{ifinit = false;}
	void	init();
	void	release();
	void	Update(int &m_iCurrentState);
	void	Render();

};