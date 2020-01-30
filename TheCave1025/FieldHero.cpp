#include "FieldHero.h"
#include "Main.h"

void FieldHero::Update(char a[14][21],RECT &r,float &x, float &y, float &fx, float &fy)
{
	if (!ifinit)
	{
		init();
	}
	KeyState(a);
	SpriteChanging(r);
	Moving(x, y);
	fogMoving(x, y, fx, fy);
}

void FieldHero::Update( char a[8][7],RECT &r,float &x, float &y, float &fx, float &fy )
{
	KeyState(a);
	SpriteChanging(r);
	Moving(x, y);
	fogMoving(x, y, fx, fy);
}

FieldHero::FieldHero()
{
	ifinit = false;

	movingt = 16;

	LeftKeyPress = false;
	RightKeyPress = false;
	UpKeyPress = false;
	DownKeyPress = false;

	m_direct = RIGHT;

	LEFT1.left = 0, LEFT1.top = 50, LEFT1.right = 50, LEFT1.bottom = 100;
	LEFT2.left = 50, LEFT2.top = 50, LEFT2.right = 100, LEFT2.bottom = 100;

	RIGHT1.left = 0, RIGHT1.top = 100, RIGHT1.right = 50, RIGHT1.bottom = 150;
	RIGHT2.left = 50, RIGHT2.top = 100, RIGHT2.right = 100, RIGHT2.bottom = 150;

	UP1.left = 0, UP1.top = 150, UP1.right = 50, UP1.bottom = 200;
	UP2.left = 50, UP2.top = 150, UP2.right = 100, UP2.bottom = 200;

	DOWN1.left = 0, DOWN1.top = 0, DOWN1.right = 50, DOWN1.bottom = 50;
	DOWN2.left = 50, DOWN2.top = 0, DOWN2.right = 100, DOWN2.bottom = 50;

	minipos_x = 0;
	minipos_y = 12;

	key = 0;

}

void FieldHero::KeyState(char a[14][21])
{
	if( (GetAsyncKeyState(VK_LEFT) & 0x8000) && 
		(LeftKeyPress==FALSE) && 
		(RightKeyPress==FALSE) && 
		(UpKeyPress==FALSE) && 
		(DownKeyPress==FALSE) &&
		m_LeftHitTest(a)==false &&
		( !(minipos_x == 0)) )
	{
		minipos_x -= 1;
		movingx = -3.125;
		movingt = 16;
		LeftKeyPress=TRUE;
	}
	if( (GetAsyncKeyState(VK_RIGHT) & 0x8000) && 
		(LeftKeyPress==FALSE) && 
		(RightKeyPress==FALSE) && 
		(UpKeyPress==FALSE) && 
		(DownKeyPress==FALSE)&&
		m_RightHitTest(a)==false &&
		( !(minipos_x == 19)) )
	{
		minipos_x += 1;
		movingx = +3.125;
		movingt = 16;
		RightKeyPress=TRUE;
	}
	if( (GetAsyncKeyState(VK_UP) & 0x8000) && 
		(LeftKeyPress==FALSE) && 
		(RightKeyPress==FALSE) && 
		(UpKeyPress==FALSE) && 
		(DownKeyPress==FALSE) &&
		m_UpHitTest(a) == false &&
		( !(minipos_y == 0)) )
	{
		minipos_y -= 1;
		movingy = -3.125;
		movingt = 16;
		UpKeyPress=TRUE;
	}
	if((GetAsyncKeyState(VK_DOWN) & 0x8000) && 
		(LeftKeyPress==FALSE) && 
		(RightKeyPress==FALSE) && 
		(UpKeyPress==FALSE) && 
		(DownKeyPress==FALSE)&&
		m_DownHitTest(a)==false &&
		( !(minipos_y == 13)) )
	{
		minipos_y += 1;
		movingy = +3.125;
		movingt = 16;
		DownKeyPress=TRUE;
	}
}

void FieldHero::KeyState( char a[8][7] )
{
	if( (GetAsyncKeyState(VK_LEFT) & 0x8000) && 
		(LeftKeyPress==FALSE) && 
		(RightKeyPress==FALSE) && 
		(UpKeyPress==FALSE) && 
		(DownKeyPress==FALSE) &&
		m_LeftHitTest(a)==false &&
		( !(minipos_x == 0)) )
	{
		minipos_x -= 1;
		movingx = -3.125;
		movingt = 16;
		LeftKeyPress=TRUE;
	}
	if( (GetAsyncKeyState(VK_RIGHT) & 0x8000) && 
		(LeftKeyPress==FALSE) && 
		(RightKeyPress==FALSE) && 
		(UpKeyPress==FALSE) && 
		(DownKeyPress==FALSE)&&
		m_RightHitTest(a)==false &&
		( !(minipos_x == 5)) )
	{
		minipos_x += 1;
		movingx = +3.125;
		movingt = 16;
		RightKeyPress=TRUE;
	}
	if( (GetAsyncKeyState(VK_UP) & 0x8000) && 
		(LeftKeyPress==FALSE) && 
		(RightKeyPress==FALSE) && 
		(UpKeyPress==FALSE) && 
		(DownKeyPress==FALSE) &&
		m_UpHitTest(a) == false &&
		( !(minipos_y == 0)) )
	{
		minipos_y -= 1;
		movingy = -3.125;
		movingt = 16;
		UpKeyPress=TRUE;
	}
	if((GetAsyncKeyState(VK_DOWN) & 0x8000) && 
		(LeftKeyPress==FALSE) && 
		(RightKeyPress==FALSE) && 
		(UpKeyPress==FALSE) && 
		(DownKeyPress==FALSE)&&
		m_DownHitTest(a)==false &&
		( !(minipos_y == 7)) )
	{
		minipos_y += 1;
		movingy = +3.125;
		movingt = 16;
		DownKeyPress=TRUE;
	}
}

void FieldHero::Moving(float &x, float &y)
{
	if(LeftKeyPress && !movingt==0){
		x += movingx;
		movingt--;
	}
	if(RightKeyPress && !movingt==0){
		x += movingx;
		movingt--;
	}
	if(DownKeyPress && !movingt==0){
		y += movingy;
		movingt--;
	}
	if(UpKeyPress && !movingt==0){
		y += movingy;
		movingt--;
	}
	if(movingt==0){
		LeftKeyPress=FALSE;
		RightKeyPress=FALSE;
		UpKeyPress=FALSE;
		DownKeyPress=FALSE;
	}
}

void FieldHero::SpriteChanging(RECT &r)
{
	
	//CDirectSound *CSound = Main::GetInstance().Get_DSound();

	if(LeftKeyPress == true || m_direct == LEFT)
	{
		if(movingt == 0 || movingt == 16){
			r = LEFT1;

		}
		else if (movingt == 8){
			CSound->Play(SOUND_N_F_WALK1);
			r = LEFT2;
		}
	}
	else if(RightKeyPress == true || m_direct == RIGHT)
	{
		if(movingt == 0 || movingt == 16){
			r = RIGHT1;
		}
		else if (movingt == 8){
			CSound->Play(SOUND_N_F_WALK1);
			r = RIGHT2;
		}
	}
	else if(UpKeyPress == true || m_direct == UP)
	{
		if(movingt == 0 || movingt == 16){
			r = UP1;
		}
		else if (movingt == 8){
			CSound->Play(SOUND_N_F_WALK1);
			r = UP2;
		}
	}
	else if(DownKeyPress == true || m_direct == DOWN)
	{
		if(movingt == 0 || movingt == 16){
			r = DOWN1;
		}
		else if (movingt == 8){
			CSound->Play(SOUND_N_F_WALK1);
			r = DOWN2;
		}
	}
}

bool FieldHero::m_LeftHitTest(char a[14][21])
{
	m_direct = LEFT;
	if(a[minipos_y][minipos_x-1] == '1' || a[minipos_y][minipos_x-1] == '4')
		return true;
	else
		return false;
}

bool FieldHero::m_LeftHitTest( char a[8][7] )
{
	m_direct = LEFT;
	if(a[minipos_y][minipos_x-1] == '1' || a[minipos_y][minipos_x-1] == '4')
		return true;
	else
		return false;
}

bool FieldHero::m_RightHitTest(char a[14][21])
{
	m_direct = RIGHT;
	if(a[minipos_y][minipos_x+1] == '1' || a[minipos_y][minipos_x+1] == '4')
		return true;
	else
		return false;
}

bool FieldHero::m_RightHitTest( char a[8][7] )
{
	m_direct = RIGHT;
	if(a[minipos_y][minipos_x+1] == '1' || a[minipos_y][minipos_x+1] == '4')
		return true;
	else
		return false;
}

bool FieldHero::m_UpHitTest(char a[14][21])
{
	m_direct = UP;
	if(a[minipos_y-1][minipos_x] == '1' || a[minipos_y-1][minipos_x] == '4')
		return true;
	else
		return false;
}

bool FieldHero::m_UpHitTest( char a[8][7] )
{
	m_direct = UP;
	if(a[minipos_y-1][minipos_x] == '1' || a[minipos_y-1][minipos_x] == '4')
		return true;
	else
		return false;
}

bool FieldHero::m_DownHitTest(char a[14][21])
{
	m_direct = DOWN;
	if(a[minipos_y+1][minipos_x] == '1' || a[minipos_y+1][minipos_x] == '4')
		return true;
	else
		return false;
}

bool FieldHero::m_DownHitTest( char a[8][7] )
{
	m_direct = DOWN;
	if(a[minipos_y+1][minipos_x] == '1' || a[minipos_y+1][minipos_x] == '4')
		return true;
	else
		return false;
}

void FieldHero::fogMoving( float &x, float &y, float &fx, float &fy )
{
	fx = x - 975;
	fy = y - 675;
}

void FieldHero::StatInit()
{
	star = HeroStat::star;
	fullhp = HeroStat::fullhp;
	hp = HeroStat::hp;
	level = HeroStat::level;
}

void FieldHero::init()
{
	CSound = Main::GetInstance().Get_DSound();
}