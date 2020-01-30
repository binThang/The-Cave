#pragma once
#include <windows.h>
#include <time.h>
#include "Hero.h"
#include "Gimmick.h"
#include "Sprite.h"

class Monster
{
public:
	//////// ��ġ ���� ////////////
	int x;
	int y;
	int moving_x;
	int moving_y;
	int screen_x;
	int screen_y;
	int sprite_x;
	int sprite_y;

	///////// �Ӽ�	////////////////
	int species;		// �� �ɸ����� ����. ���͵�
	int prestate;
	int state;			// ���� ����
	int phase;			// ���� ������ �ܰ�
	int time;			// ���� �ð�
	int direction;		// ����
	int herodirection;	// ���ΰ��� ����
	bool delayed;			// ������
	bool immune;			// ���� �̹�

	int ground;
	bool falling;
	int falltime;

	int width;
	int height;


	RECT bodysquare;	// ������
	float damage;			// ����ġ
	RECT attacksquare;	// ���ݹ���
	int fullhp;			// Ǯ hp
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
		switch(species)		//�� ������ ���� �ʱ�ȭ������
		{
		case 0:					// â���
			damage = 0.1;
			fullhp	=	20;
			hp		=	20;
			direction = rand()%2+3;
			
			width = 350;
			height = 250;
			ground = 715;

			SetRect(&bodysquare, x+130, y+70, x+250, y+250);
			break;
		case 1:					// �������
			damage = 0.1;
			fullhp = 35;
			hp = 35;
			direction = rand()%2+3;
			width = 350;
			height = 250;
			ground = 715;
			SetRect(&bodysquare, x+130, y+70, x+250, y+250);
			break;
		case 2:					// �ظӰ��
			damage = 0.3;
			fullhp = 40;
			hp = 40;
			direction = rand()%2+3;
			width = 500;
			height = 350;
			ground = 715;
			SetRect(&bodysquare, x+250, y+100, x+370, y+320);
			break;
		case 3:					// �Ϲ����� �۷��� ������
			damage = 0.2;
			fullhp = 60;
			hp = 60;
			direction = rand()%2+3;
			width = 255;
			height = 200;
			ground = 700;
			SetRect(&bodysquare, x+80, y+80, x+160, y+160);
			break; 
		case 11:					// ��� �ظ� ����
			damage = 0.3;
			fullhp = 50;
			hp = 50;
			direction = rand()%2+3;
			width = 500;
			height = 350;
			ground = 715;
			SetRect(&bodysquare, x+250, y+100, x+320, y+320);
			break; 
		case 12:				//������
			damage = 0.5;
			fullhp = 150;
			hp = 150;
			direction = rand()%2+3;
			width = 400;
			height = 300;
			ground = 715;
			SetRect(&bodysquare, x+120, y+120, x+280, y+240);
			break;
		case 13:				//�ʻ��̾� ����
			damage = 0.5;
			fullhp = 200;
			hp = 200;
			direction = rand()%2+3;
			width = 400;
			height = 300;
			ground = 715;
			SetRect(&bodysquare, x+120, y+120, x+280, y+240);
			break;
		case 14:				//���� ����
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