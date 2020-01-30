#pragma once

#include <Windows.h>
#include "Sprite.h"
#include "FieldHero.h"
#include "FieldMonster.h"
#include "AllManage.h"

class CDirectSound;

class Field
{
private:
	FieldHero		hero;
	FieldMonster*	monster1[6];
	FieldMonster*	monster2[6];
	FieldMonster*	monster3[7];
	FieldMonster*	monster4[8];
	FieldMonster*	monster5;
	//////////스프라이트//////////////////
	Sprite*		m_f_Stage1;
	Sprite*		m_f_Stage2;
	Sprite*		m_f_Stage3;
	Sprite*		m_f_Stage4;
	Sprite*		m_f_Stage5;

	Sprite		m_f_Char;
	Sprite		m_f_Fog;
	Sprite		m_f_UI;
	Sprite*		m_f_HP[10];
	Sprite*		m_f_Font[6];

	Sprite*		m_f_Mop1[6];
	Sprite*		m_f_Mop2[6];
	Sprite*		m_f_Mop3[7];
	Sprite*		m_f_Mop4[8];
	Sprite*		m_f_Mop5;


	Sprite*		m_f_key1;
	Sprite*		m_f_key2;
	Sprite*		m_f_key3[2];
	Sprite*		m_f_key4[2];
	Sprite*		m_f_cage1;
	Sprite*		m_f_cage2;
	Sprite*		m_f_cage3[2];
	Sprite*		m_f_cage4[3];
	Sprite*		m_f_potion1;

	//////////////////////////////////////
	bool		ifinit;

	bool		be_monster1[6];
	bool		be_monster2[6];
	bool		be_monster3[7];
	bool		be_monster4[8];
	bool		be_monster5;
	bool		be_key1;
	bool		be_key2;
	bool		be_key3[2];
	bool		be_key4[2];
	bool		be_cage1;
	bool		be_cage2;
	bool		be_cage3[2];
	bool		be_cage4[3];
	bool		be_potion1;

	CDirectSound* CSound;

public:
 
				Field();
				~Field();
	void		Render(int &CurrentStage);
	void		Update(int &CurrentState, int &CurrentStage);
	void		UIUpdate();
	void		StarUpdate(int &CurrentState);

	void		Stage1process(int &CurrentState, int &CurrentStage);
	void		Stage2process(int &CurrentState, int &CurrentStage);
	void		Stage3process(int &CurrentState, int &CurrentStage);
	void		Stage4process(int &CurrentState, int &CurrentStage);
	void		Stage5process(int &CurrentState, int &CurrentStage);

	void		Stage1init();
	void		Stage2init();
	void		Stage3init();
	void		Stage4init();
	void		Stage5init();

	void		Stage1release();
	void		Stage2release();
	void		Stage3release();
	void		Stage4release();
	void		Stage5release();

};