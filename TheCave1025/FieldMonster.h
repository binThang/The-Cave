#pragma once

#include <Windows.h>

class FieldMonster
{
private:

	float 	movingx;
	float 	movingy;
	int 	movingt;

	enum	direction	{	UP, DOWN, LEFT, RIGHT	};

	RECT	UP1, DOWN1, LEFT1, RIGHT1,
			UP2, DOWN2, LEFT2, RIGHT2;

	int		m_direct;

	bool	LeftMove;
	bool	RightMove;
	bool	DownMove;
	bool	UpMove;

	DWORD	TimeCount;

public:
			FieldMonster();
	void	init(int x, int y, DWORD z);
	void	Update( char a[14][21], RECT &r, float &x, float &y );
	void	Moving( float &x, float &y );
	//
	bool	m_LeftHitTest(char a[14][21]);
	bool	m_RightHitTest(char a[14][21]); 
	bool	m_UpHitTest(char a[14][21]);
	bool	m_DownHitTest(char a[14][21]);
	//
	void	LeftMoving( char a[14][21] );
	void	RightMoving( char a[14][21] );
	void	UpMoving( char a[14][21] );
	void	DownMoving( char a[14][21] );
	//
	void	SpriteChanging(RECT &r);

	int		minipos_x;
	int		minipos_y;


};