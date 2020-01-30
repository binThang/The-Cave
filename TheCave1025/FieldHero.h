#pragma once

#include <Windows.h>
#include "HeroStat.h"
#include "DXSound.h"

class CDirectSound;

class FieldHero
{
private:

	HeroStat m_Stat;

	float 	movingx;
	float 	movingy;
	float 	movingt;

	enum	direction	{	UP, DOWN, LEFT, RIGHT	};
	bool	LeftKeyPress;
	bool	RightKeyPress;
	bool	UpKeyPress;
	bool	DownKeyPress;
	bool	ifinit;

	RECT	UP1, DOWN1, LEFT1, RIGHT1,
			UP2, DOWN2, LEFT2, RIGHT2;

	int star;			// 별
	int level;			// 레벨
	int fullhp;			// 풀 hp
	int hp;				// hp
	CDirectSound* CSound;


public:
			FieldHero();

	int		m_direct;

	int		minipos_x;
	int		minipos_y;

	void	init();
	void	Update(char a[14][21],RECT &r,float &x, float &y, float &fx, float &fy);
	void	Update(char a[8][7],RECT &r,float &x, float &y, float &fx, float &fy);
	void	KeyState(char a[14][21]);
	void	KeyState(char a[8][7]);
	//
	bool	m_LeftHitTest(char a[14][21]);
	bool	m_RightHitTest(char a[14][21]); 
	bool	m_UpHitTest(char a[14][21]);
	bool	m_DownHitTest(char a[14][21]);
	//stage5전용
	bool	m_LeftHitTest(char a[8][7]);
	bool	m_RightHitTest(char a[8][7]); 
	bool	m_UpHitTest(char a[8][7]);
	bool	m_DownHitTest(char a[8][7]);
	//
	void	StatInit();
	void	Moving(float &x, float &y);
	void	fogMoving(float &x, float &y, float &fx, float &fy);
	void	SpriteChanging(RECT &r);
	void	ChangeDirection();
	
	int key;
};