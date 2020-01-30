#pragma once
#include <windows.h>
#include "HeroStat.h"

class Hero
{
public:
	//////// ��ġ ���� ////////////////
	int x;
	int y;
	int moving_x;
	int moving_y;
	int screen_x;
	int screen_y;
	int sprite_x;
	int sprite_y;

	//////// Ű ���� /////////////////
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


	//////// �Ӽ� //////////
	int prestate;
	int state;			// ���� ����
	int phase;			// ���� ������ �ܰ�
	int time;			// ���� �ð�
	int direction;		// ����
	bool delayed;			// ������
	bool immune;			// ���� �̹�
	
	int ground;
	bool falling;
	int falltime;
	bool whilejumpup;		//���� ���� ��
	bool whilejumpdown;		//�Ʒ��� ���� ��
	int jumptime;


	RECT bodysquare;	// ������
	float damage;			// ����ġ
	RECT attacksquare;	// ���ݹ���
	int level;			// ����
	int exp;			// ����ġ
	int fullhp;			// Ǯ hp
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