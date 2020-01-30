#include "FieldMonster.h"
#include <time.h>


void FieldMonster::init(int x, int y, DWORD z)
{

	minipos_x = x;
	minipos_y = y;

	TimeCount = z;
	srand(time(NULL)*TimeCount);
}

void FieldMonster::Update( char a[14][21], RECT &r, float &x, float &y )
{	
	SpriteChanging(r);
	Moving(x, y);
	TimeCount++;
	if(TimeCount == 45)
	{
		
		switch(rand()%4){
			case 0:
				if(!m_UpHitTest(a))
					UpMoving(a);
				else
					TimeCount = 0;
				break;

			case 1:
				if(!m_RightHitTest(a))
					RightMoving(a);
				else
					TimeCount = 0;			
				break;

			case 2:
				if(!m_LeftHitTest(a))
					LeftMoving(a);
				else
					TimeCount = 0;
				break;

			case 3:
				if(!m_DownHitTest(a))
					DownMoving(a);
				else
					TimeCount = 0;
				break;
		}
	}
	a[minipos_y][minipos_x] = '2';
}

FieldMonster::FieldMonster()
{
	LeftMove=FALSE;
	RightMove=FALSE;
	UpMove=FALSE;
	DownMove=FALSE;

	movingt = 16;
	TimeCount = 0;

	m_direct = LEFT;

	RIGHT1.left = 0, RIGHT1.top = 50, RIGHT1.right = 50, RIGHT1.bottom = 100;
	RIGHT2.left = 50, RIGHT2.top = 50, RIGHT2.right = 100, RIGHT2.bottom = 100;

	LEFT1.left = 0, LEFT1.top = 100, LEFT1.right = 50, LEFT1.bottom = 150;
	LEFT2.left = 50, LEFT2.top = 100, LEFT2.right = 100, LEFT2.bottom = 150;

	UP1.left = 0, UP1.top = 150, UP1.right = 50, UP1.bottom = 200;
	UP2.left = 50, UP2.top = 150, UP2.right = 100, UP2.bottom = 200;

	DOWN1.left = 0, DOWN1.top = 0, DOWN1.right = 50, DOWN1.bottom = 50;
	DOWN2.left = 50, DOWN2.top = 0, DOWN2.right = 100, DOWN2.bottom = 50;

}

void FieldMonster::Moving( float &x, float &y )
{
	if(LeftMove && !movingt==0){
		x += movingx;
		movingt--;
	}
	if(RightMove && !movingt==0){
		x += movingx;
		movingt--;
	}
	if(DownMove && !movingt==0){
		y += movingy;
		movingt--;
	}
	if(UpMove && (!movingt==0) ){
		y += movingy;
		movingt--;
	}
	if(movingt==0){
		LeftMove=FALSE;
		RightMove=FALSE;
		UpMove=FALSE;
		DownMove=FALSE;
	}
}
////////////////충돌체크/////////////////////////
bool FieldMonster::m_LeftHitTest(char a[14][21])
{
	m_direct = LEFT;
	if(!(a[minipos_y][minipos_x-1] == '0'))
		return true;
	else
		return false;
}

bool FieldMonster::m_RightHitTest(char a[14][21])
{
	m_direct = RIGHT;
	if(!(a[minipos_y][minipos_x+1] == '0'))
		return true;
	else
		return false;
}

bool FieldMonster::m_UpHitTest(char a[14][21])
{
	m_direct = UP;
	if(!(a[minipos_y-1][minipos_x] == '0' ))
		return true;
	else
		return false;
}

bool FieldMonster::m_DownHitTest(char a[14][21])
{
	m_direct = DOWN;
	if(!(a[minipos_y+1][minipos_x] == '0'))
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////
///////////////////이동초기화////////////////////////
void FieldMonster::UpMoving( char a[14][21] )
{
	UpMove = true;
	a[minipos_y][minipos_x] ='0';
	minipos_y -= 1;
	movingy = -3.125;
	movingt = 16;
	TimeCount = 0;
}

void FieldMonster::LeftMoving( char a[14][21] )
{
	LeftMove = true;
	a[minipos_y][minipos_x] ='0';
	minipos_x -= 1;
	movingx = -3.125;
	movingt = 16;
	TimeCount = 0;
}

void FieldMonster::RightMoving( char a[14][21] )
{
	RightMove = true;
	a[minipos_y][minipos_x] ='0';
	minipos_x += 1;
	movingx = +3.125;
	movingt = 16;
	TimeCount = 0;
}

void FieldMonster::DownMoving( char a[14][21] )
{
	DownMove = true;
	a[minipos_y][minipos_x] ='0';
	minipos_y += 1;
	movingy = +3.125;
	movingt = 16;
	TimeCount = 0;
}
///////////////////////////////////////////////////
void FieldMonster::SpriteChanging( RECT &r )
{
	if(m_direct == LEFT)
	{
		if(movingt == 0 || movingt == 16)
			r = LEFT1;
		else if (movingt == 8)
			r = LEFT2;
	}
	else if(m_direct == RIGHT)
	{
		if(movingt == 0 || movingt == 16)
			r = RIGHT1;
		else if (movingt == 8)
			r = RIGHT2;
	}
	else if(m_direct == UP)
	{
		if(movingt == 16)
			r = UP1;
		else if (movingt == 8)

			r = UP2;
	}
	else if(m_direct == DOWN)
	{
		if(movingt == 0 || movingt == 16)
			r = DOWN1;
		else if (movingt == 8)
			r = DOWN2;
	}
}