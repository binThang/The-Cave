#pragma once
#include "Monster.h"
#include "BattleState.h"
#include <time.h>

#define ZERO 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define SPACE 5

#define IDLE 1
#define MOVE 2
#define ATTACK 3
#define RAGE 5
#define FALLING 6


#define HITTED 8
#define DEAD 9


void Monster::SetState()
{
};

void Monster::AI(Hero hero)
{
	int attackrange = 0;
	if (hp <= 0)		// 죽음 처리
	{
  		state = DEAD;
	}
	else			//살아 있다면
	{

		switch (species)
		{
		case 0:
		case 1:
			attackrange = 150;
			break;
		case 2:
			attackrange = 200;
			break;
		case 3:
			attackrange = 150;
			break;
		case 11:
			attackrange = 250;
			break;
		case 12:
		case 13:
			attackrange = 250;
			break;
		case 14:
			attackrange = 400;
			break;
		}

		if(bodysquare.right >= hero.bodysquare.left - 1000 && bodysquare.right <= hero.bodysquare.left)	//주인공 왼쪽에 몹이 시야 범위 안, 공격 범위 밖에 있을 때 (조낸 들러붙긔)
		{
			state = MOVE;
			direction = RIGHT;
		}
		else if(bodysquare.right >= hero.bodysquare.left && bodysquare.right < hero.bodysquare.left + attackrange)		//주인공의 왼쪽에 몹이 시야범위 안, 공격 범위 안에 있을 때 (조낸 치긔)
		{
			state = ATTACK; 
			direction = RIGHT;
		}
		else if(bodysquare.left >= hero.bodysquare.right - attackrange && bodysquare.left <= hero.bodysquare.right)	// 주인공의 오른쪽에 몹이 시야범위 안, 공격범위 안에 있을 때 (조낸 때리긔)
		{
			state = ATTACK;
			direction = LEFT;
		}
		else if(bodysquare.left >= hero.bodysquare.right && bodysquare.left <= hero.bodysquare.right + 1000)	// 주인공의 시야 범위 안, 공격 범위 밖
		{
			state = MOVE;
			direction = LEFT;
		}
		else							// 시야 범위 밖에 있을 때
		{
			state = IDLE;
		}

	}
};

