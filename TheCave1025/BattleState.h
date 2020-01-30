#pragma once

#include <Windows.h>
#include "Sprite.h"
#include "Hero.h"
#include "Gimmick.h"
#include "Monster.h"

class Battle
{
public:
	bool		whilebattle;

	/// 임시 변수
	bool		initialized;
	bool		mustinit;
	int			monstercount;
	int			species;
	int			lowspecies;
	int			highspecies;
	int			whatboss;

	int			endtime;
	/////// 최종 함수 ///////////
				Battle();
	void		Render(int m_iCurrentState, int m_iCurrentStage);
	void		Update(int &m_iCurrentState, int m_iCurrentStage);
	void		init(HWND g_hWnd);

	/////// Render 재료 함수 ///////////
	void		SetSprite();
	/////// Update 재료 함수 ///////////
	void		Initializing(int m_iCurrentStage);
	void		initializing2();
	void		CheckSituation();
	bool		CheckCollision();
	void		Collision();
	void		Calculate();		//실제로 싸우는 곳	//state를 처리함	//각종 스텟 조절
	void		AfterCalculate();
	void		Ending(int &m_iCurrentState);

	//////// 케릭터 정보 ///////////
	Hero			hero;
	Monster			**monster;
	Monster			*boss;

	Gimmick			hpball;
	Gimmick			emptyball;
	Gimmick			hpbar;


	//////// 스프라이트 /////////
	Sprite		m_b_BG;
	Sprite		m_b_BG_Road;
	Sprite		m_b_BG_Rock;

	Sprite		m_b_hero;
	Sprite		**m_b_monster;
	Sprite		*m_b_boss;
	Sprite		*m_b_bosseffect;


	Sprite		m_b_hpball;
	Sprite		m_b_emptyball;
	Sprite		m_b_hpbar;

};