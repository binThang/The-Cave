#pragma once
#include <windows.h>
#include "HeroStat.h"

class Hero
{
public:
	//////// 위치 정보 ////////////////
	int x;
	int y;
	int moving_x;
	int moving_y;
	int screen_x;
	int screen_y;
	int sprite_x;
	int sprite_y;

	//////// 키 정보 /////////////////
	bool up;
	bool down;
	bool left;
	bool right;
	bool space;

	int combo[20];

	DWORD up_A;
	DWORD up_B;
	DWORD down_A;
	DWORD down_B;
	DWORD left_A;
	DWORD left_B;
	DWORD right_A;
	DWORD right_B;
	DWORD space_A;
	DWORD space_B;

	DWORD combo_A;
	DWORD combo_B;


	//////// 속성 //////////
	int prestate;
	int state;			// 현재 상태
	int phase;			// 현재 상태의 단계
	int time;			// 단위 시간
	int direction;		// 방향
	bool delayed;			// 딜레이
	bool immune;			// 공격 이뮨
	
	int ground;
	bool falling;
	int falltime;
	bool whilejumpup;		//위로 점프 중
	bool whilejumpdown;		//아래로 점프 중
	int jumptime;


	RECT bodysquare;	// 몸범위
	float damage;			// 공격치
	RECT attacksquare;	// 공격범위
	int level;			// 레벨
	int exp;			// 경험치
	int fullhp;			// 풀 hp
	float hp;				// hp 
     
	Hero()
	{
		HeroStat::level = 1;
		HeroStat::star = 0;
		HeroStat::fullhp = 3;
		HeroStat::hp = 3;
		HeroStat::attack = 1;
		immune = false;
		delayed = false;
		time = 0;
		state = 0;
		phase = 0;
		ground = 715;

	}

	void Initialize(int _x, int _y)
	{
		x	=	_x;
		y	=	_y;
		time = 0;
		state = 0;
		phase = 0;
		immune = false;
		delayed = false;
		falling = false;
		falltime = 0;
		SetRect(&bodysquare, x + 120, y + 90, x+250, y+250);
		SetRect(&attacksquare, 0, 0, 0, 0);

	}

	void Key();
	void SetState();


};