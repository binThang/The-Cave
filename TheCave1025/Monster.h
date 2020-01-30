#pragma once
#include <windows.h>
#include <time.h>
#include "Hero.h"
#include "Gimmick.h"
#include "Sprite.h"

class Monster
{
public:
	//////// 위치 정보 ////////////
	int x;
	int y;
	int moving_x;
	int moving_y;
	int screen_x;
	int screen_y;
	int sprite_x;
	int sprite_y;

	///////// 속성	////////////////
	int species;		// 이 케릭터의 종류. 몬스터들
	int prestate;
	int state;			// 현재 상태
	int phase;			// 현재 상태의 단계
	int time;			// 단위 시간
	int direction;		// 방향
	int herodirection;	// 주인공의 방향
	bool delayed;			// 딜레이
	bool immune;			// 공격 이뮨

	int ground;
	bool falling;
	int falltime;

	int width;
	int height;


	RECT bodysquare;	// 몸범위
	float damage;			// 공격치
	RECT attacksquare;	// 공격범위
	int fullhp;			// 풀 hp
	int hp;				// hp

	Gimmick		bosseffect;
	Gimmick		effect;
	Gimmick		bigeffect;
	Gimmick		speech;
	Gimmick		star[5];

	Sprite		m_b_effect;
	Sprite		m_b_bigeffect;
	Sprite		m_b_speech;
	Sprite		m_b_star;


	void Initialize(int _x, int _y, int _species)
	{
		for(int i=0;i<5;i++)
		{
			star[i].x=0;
			star[i].y=0;
			star[i].moving_x=0;
			star[i].moving_y=0;
		}
		falltime = 0;
		x	=	_x;
		y	=	_y;
		sprite_x = 0;
		sprite_y = 0;
		moving_x = 0;
		moving_y = 0;
		time = 0;
		state = 0;
		phase = 0;
		prestate = 0;
		species	=	_species;
		immune = false;
		delayed = false;
		switch(species)		//몹 종류에 따라 초기화시켜줌
		{
		case 0:					// 창고블린
			damage = 0.1;
			fullhp	=	20;
			hp		=	20;
			direction = rand()%2+3;
			
			width = 350;
			height = 250;
			ground = 715;

			SetRect(&bodysquare, x+130, y+70, x+250, y+250);
			break;
		case 1:					// 도끼고블린
			damage = 0.1;
			fullhp = 35;
			hp = 35;
			direction = rand()%2+3;
			width = 350;
			height = 250;
			ground = 715;
			SetRect(&bodysquare, x+130, y+70, x+250, y+250);
			break;
		case 2:					// 해머고블린
			damage = 0.3;
			fullhp = 40;
			hp = 40;
			direction = rand()%2+3;
			width = 500;
			height = 350;
			ground = 715;
			SetRect(&bodysquare, x+250, y+100, x+370, y+320);
			break;
		case 3:					// 일반적인 퍼랭이 위스프
			damage = 0.2;
			fullhp = 60;
			hp = 60;
			direction = rand()%2+3;
			width = 255;
			height = 200;
			ground = 700;
			SetRect(&bodysquare, x+80, y+80, x+160, y+160);
			break; 
		case 11:					// 고블린 해머 대장
			damage = 0.3;
			fullhp = 50;
			hp = 50;
			direction = rand()%2+3;
			width = 500;
			height = 350;
			ground = 715;
			SetRect(&bodysquare, x+250, y+100, x+320, y+320);
			break; 
		case 12:				//불위습
			damage = 0.5;
			fullhp = 150;
			hp = 150;
			direction = rand()%2+3;
			width = 400;
			height = 300;
			ground = 715;
			SetRect(&bodysquare, x+120, y+120, x+280, y+240);
			break;
		case 13:				//초사이어 위습
			damage = 0.5;
			fullhp = 200;
			hp = 200;
			direction = rand()%2+3;
			width = 400;
			height = 300;
			ground = 715;
			SetRect(&bodysquare, x+120, y+120, x+280, y+240);
			break;
		case 14:				//끝판 대장
			damage = 1;
			fullhp = 500;
			hp = 500;
			direction = rand()%2+3;
			width = 1200;
			height = 600;
			ground = 700;
			SetRect(&bodysquare, x+450, y+270, x+750, y+600);
			break;

		}
	}

	void AI(Hero hero);
	void SetState();
	Monster(){}

};