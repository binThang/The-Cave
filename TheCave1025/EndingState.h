#pragma once

#include "Sprite.h"
#include "AllManage.h"

#define TERM 7

class Ending
{
private:
	
	bool	ifinit;

	Sprite	EndBG[3];

	int		scene;
	int		timet;

public:

			Ending();
	void	Update();
	void	Render();
	void	init();

};