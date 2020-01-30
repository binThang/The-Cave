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

	/// �ӽ� ����
	bool		initialized;
	bool		mustinit;
	int			monstercount;
	int			species;
	int			lowspecies;
	int			highspecies;
	int			whatboss;

	int			endtime;
	/////// ���� �Լ� ///////////
				Battle();
	void		Render(int m_iCurrentState, int m_iCurrentStage);
	void		Update(int &m_iCurrentState, int m_iCurrentStage);
	void		init(HWND g_hWnd);

	/////// Render ��� �Լ� ///////////
	void		SetSprite();
	/////// Update ��� �Լ� ///////////
	void		Initializing(int m_iCurrentStage);
	void		initializing2();
	void		CheckSituation();
	bool		CheckCollision();
	void		Collision();
	void		Calculate();		//������ �ο�� ��	//state�� ó����	//���� ���� ����
	void		AfterCalculate();
	void		Ending(int &m_iCurrentState);

	//////// �ɸ��� ���� ///////////
	Hero			hero;
	Monster			**monster;
	Monster			*boss;

	Gimmick			hpball;
	Gimmick			emptyball;
	Gimmick			hpbar;


	//////// ��������Ʈ /////////
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