#include "BattleState.h"
#include <iostream>
#include "HeroStat.h"
//#include <time.h>

using namespace std;

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


void Battle::Render(int m_iCurrentState, int m_iCurrentStage)
{
	D3DXMATRIX T, R, A, A2;

	////// 최종 위치로 스프라이트를 이동

	D3DXMatrixScaling(&T,1,1,1);
	//D3DXMatrixScaling(&A,1,1,1);

	// 뒷 배경 그리기
	m_b_BG.SetTransform(&T);
	m_b_BG_Road.SetTransform(&T);
	m_b_BG.m_vPosition.x = - (hero.screen_x) / 2;
	m_b_BG_Road.m_vPosition.x = - hero.screen_x;
	m_b_BG.Draw();
	m_b_BG_Road.Draw();
	// 몹 그리기
	for(int i=lowspecies;i<highspecies;i++)
	{
		m_b_monster[i]->SetTransform(&T);
		for(int j=0;j<monstercount;j++)
		{
			if(monster[j]->species == i)
			{
				if(monster[j]->state == DEAD)
				{
					m_b_monster[i]->m_bVisible = false;
					continue;
				}
				else
				{
					m_b_monster[i]->m_bVisible = true;
					m_b_monster[i]->m_vPosition.x = monster[j]->x - hero.screen_x;
					m_b_monster[i]->m_vPosition.y = monster[j]->y;

					m_b_monster[i]->m_rSource.left		=	(monster[j]->width * monster[j]->sprite_x) ;
					m_b_monster[i]->m_rSource.top		=	(monster[j]->height * monster[j]->sprite_y) ;
					m_b_monster[i]->m_rSource.right		=	monster[j]->width * (monster[j]->sprite_x+1);
					m_b_monster[i]->m_rSource.bottom		=	monster[j]->height * (monster[j]->sprite_y+1);
				}
			}
			else
			{
				m_b_monster[i]->m_bVisible = false;
			}
			m_b_monster[i]->Draw();
		}
	}

	if(whatboss != 10)
	{
			boss->m_b_effect.m_rSource.left	= (250 * boss->effect.sprite_x) + 1;
			boss->m_b_effect.m_rSource.top	= (250 * boss->effect.sprite_y) + 1;
			boss->m_b_effect.m_rSource.right	= 250 * (boss->effect.sprite_x+1);
			boss->m_b_effect.m_rSource.bottom	= 250 * (boss->effect.sprite_y+1);

			boss->m_b_effect.m_vPosition.x = ((boss->effect.x+125 - hero.screen_x) / boss->effect.size ) ;
			boss->m_b_effect.m_vPosition.y = (boss->effect.y+125) / boss->effect.size;

			boss->m_b_effect.m_vCenter.x = 125;
			boss->m_b_effect.m_vCenter.y = 125;
			boss->m_b_effect.m_vCenter.z = 0;
		
			D3DXMatrixScaling(&R, boss->effect.size, boss->effect.size, 1);
			if (boss->effect.valid == true)
			{
				boss->m_b_effect.SetTransform(&(T*R));
				boss->m_b_effect.Draw(255- 50*(boss->effect.sprite_y-1) );
				//boss->m_b_effect.Draw(255- 122.5*(monster[i]->effect.size-1) );
			}
			D3DXMatrixScaling(&R, 1/boss->effect.size, 1/boss->effect.size, 1);
	

		m_b_boss->SetTransform(&T);
		

		m_b_boss->m_vPosition.x = boss->x - hero.screen_x;
		m_b_boss->m_vPosition.y = boss->y;

		m_b_boss->m_rSource.left		=	(boss->width * boss->sprite_x) ;
		m_b_boss->m_rSource.top			=	(boss->height * boss->sprite_y) ;
		m_b_boss->m_rSource.right		=	boss->width * (boss->sprite_x+1);
		m_b_boss->m_rSource.bottom		=	boss->height * (boss->sprite_y+1);
		m_b_boss->Draw();

		if(boss->bosseffect.valid==true)
		{
			m_b_bosseffect->m_vPosition.z = 0;
			if(whatboss == 12)
			{
				m_b_bosseffect->m_rSource.left= 250*boss->bosseffect.sprite_x;
				m_b_bosseffect->m_rSource.top=  150*boss->bosseffect.sprite_y;
				m_b_bosseffect->m_rSource.right=250*(boss->bosseffect.sprite_x+1);
				m_b_bosseffect->m_rSource.bottom=150*(boss->bosseffect.sprite_y+1);
				if(boss->direction==LEFT) 
				{
					m_b_bosseffect->m_vPosition.x =  boss->x - 100 - hero.screen_x;
					m_b_bosseffect->m_vPosition.y =  boss->y + 150;
				}
				else
				{
					m_b_bosseffect->m_vPosition.x =  boss->x + 250 - hero.screen_x; 
					m_b_bosseffect->m_vPosition.y = boss->y + 150;
				}
			}
			else if(whatboss == 13)
			{
				m_b_bosseffect->m_rSource.left= 500*boss->bosseffect.sprite_x;
				m_b_bosseffect->m_rSource.top=  500*boss->bosseffect.sprite_y;
				m_b_bosseffect->m_rSource.right=500*(boss->bosseffect.sprite_x+1);
				m_b_bosseffect->m_rSource.bottom=500*(boss->bosseffect.sprite_y+1);
				if(boss->direction==LEFT) 
				{
					m_b_bosseffect->m_vPosition.x =  boss->x - 350 - hero.screen_x;
					m_b_bosseffect->m_vPosition.y =  boss->y-100;
				}
				else
				{
					m_b_bosseffect->m_vPosition.x =  boss->x + 250 - hero.screen_x; 
					m_b_bosseffect->m_vPosition.y = boss->y-100;
				}
			}
			else if(whatboss == 15)
			{
				m_b_bosseffect->m_rSource.left= 1000*boss->bosseffect.sprite_x;
				m_b_bosseffect->m_rSource.top=  200*boss->bosseffect.sprite_y;
				m_b_bosseffect->m_rSource.right=1000*(boss->bosseffect.sprite_x+1);
				m_b_bosseffect->m_rSource.bottom=200*(boss->bosseffect.sprite_y+1);

				if(boss->direction==LEFT) 
				{
					if(boss->phase == 6)
					{
						m_b_bosseffect->m_vPosition.x = boss->x - 250 - hero.screen_x;
						m_b_bosseffect->m_vPosition.y =  boss->y;
					}
				}
				else
				{
					if(boss->phase == 6)
					{
						m_b_bosseffect->m_vPosition.x = boss->x + 1000 - hero.screen_x;
						m_b_bosseffect->m_vPosition.y =  boss->y;
					}
				}

			}

				m_b_bosseffect->m_vPosition.z =  0;
				m_b_bosseffect->SetTransform(&T);
				m_b_bosseffect->Draw();
		}


		

	}


	// 주인공 그리기
	m_b_hero.SetTransform(&T);
	
	m_b_hero.m_rSource.left = (350 * hero.sprite_x) + 1;
	m_b_hero.m_rSource.top = (250 * hero.sprite_y) + 1;
	m_b_hero.m_rSource.right = 350 * (hero.sprite_x+1);
	m_b_hero.m_rSource.bottom = 250 * (hero.sprite_y+1);
	m_b_hero.m_vPosition.x = hero.x - hero.screen_x;//hero.x;
	m_b_hero.m_vPosition.y = hero.y;

	m_b_hero.Draw();	
	// 앞 바위 그리기
	m_b_BG_Rock.SetTransform(&T);
	m_b_BG_Rock.m_vPosition.x = - (hero.screen_x) * 5 / 4;
	m_b_BG_Rock.Draw();
	// 제일 앞 이펙트나 대사, 인터페이스 그리기

	for (int i=0;i<monstercount;i++)
	{
		monster[i]->m_b_effect.m_rSource.left	= (250 * monster[i]->effect.sprite_x) + 1;
		monster[i]->m_b_effect.m_rSource.top	= (250 * monster[i]->effect.sprite_y) + 1;
		monster[i]->m_b_effect.m_rSource.right	= 250 * (monster[i]->effect.sprite_x+1);
		monster[i]->m_b_effect.m_rSource.bottom	= 250 * (monster[i]->effect.sprite_y+1);

		monster[i]->m_b_effect.m_vPosition.x = ((monster[i]->effect.x+125 - hero.screen_x) / monster[i]->effect.size ) ;
		monster[i]->m_b_effect.m_vPosition.y = (monster[i]->effect.y+125) / monster[i]->effect.size;

		monster[i]->m_b_effect.m_vCenter.x = 125;
		monster[i]->m_b_effect.m_vCenter.y = 125;
		monster[i]->m_b_effect.m_vCenter.z = 0;
	}
	for(int i=0;i<monstercount;i++)
	{
		D3DXMatrixScaling(&R, monster[i]->effect.size, monster[i]->effect.size, 1);
		if (monster[i]->effect.valid == true)
		{
			monster[i]->m_b_effect.SetTransform(&(T*R));
			monster[i]->m_b_effect.Draw(255- 50*(monster[i]->effect.sprite_y-1) );
			//monster[i]->m_b_effect.Draw(255- 122.5*(monster[i]->effect.size-1) );
		}
		D3DXMatrixScaling(&R, 1/monster[i]->effect.size, 1/monster[i]->effect.size, 1);
	}

	/////bigeffect
	for (int i=0;i<monstercount;i++)
	{
		monster[i]->m_b_bigeffect.m_rSource.left	= (120 * monster[i]->bigeffect.sprite_x) + 1;
		monster[i]->m_b_bigeffect.m_rSource.top	= (120 * monster[i]->bigeffect.sprite_y) + 1;
		monster[i]->m_b_bigeffect.m_rSource.right	= 120 * (monster[i]->bigeffect.sprite_x+1);
		monster[i]->m_b_bigeffect.m_rSource.bottom	= 120 * (monster[i]->bigeffect.sprite_y+1);

		monster[i]->m_b_bigeffect.m_vPosition.x = ((monster[i]->bigeffect.x+60 - hero.screen_x) / monster[i]->bigeffect.size ) ;
		monster[i]->m_b_bigeffect.m_vPosition.y = (monster[i]->bigeffect.y+60) / monster[i]->bigeffect.size;

		monster[i]->m_b_bigeffect.m_vCenter.x = 60;
		monster[i]->m_b_bigeffect.m_vCenter.y = 60;
		monster[i]->m_b_bigeffect.m_vCenter.z = 0;
	}

	for(int i=0;i<monstercount;i++)
	{
		D3DXMatrixScaling(&R, monster[i]->bigeffect.size, monster[i]->bigeffect.size, 1);
		if (monster[i]->bigeffect.valid == true)
		{
			monster[i]->m_b_bigeffect.SetTransform(&(T*R));
			monster[i]->m_b_bigeffect.Draw(50 );
			//monster[i]->m_b_effect.Draw(255- 122.5*(monster[i]->effect.size-1) );
		}
		D3DXMatrixScaling(&R, 1/monster[i]->bigeffect.size, 1/monster[i]->bigeffect.size, 1);
	}


	for(int i=0;i<monstercount;i++)
	{
		/*
	D3DXMATRIX TT;
	D3DXMatrixTranslation(&TT, 400.f, 50.0f, 0.0f);
	monster[i]->m_b_star.SetTransform(&TT);*/

		for(int j=0;j<5;j++)
		{
			if (monster[i]->star[j].valid == true)
			{
				monster[i]->m_b_star.m_vCenter.x =12;
				monster[i]->m_b_star.m_vCenter.y =12;
				monster[i]->m_b_star.m_vCenter.z = 0;

				monster[i]->m_b_star.m_vPosition.x = 0;
				monster[i]->m_b_star.m_vPosition.y = 0;
				monster[i]->m_b_star.m_vPosition.z = 0;

				D3DXMatrixRotationZ(&A2, monster[i]->star[j].degree);

				D3DXMatrixTranslation(&A, monster[i]->star[j].x  - hero.screen_x, monster[i]->star[j].y, 0.0f);

				monster[i]->m_b_star.SetTransform(&(A2*A));

				monster[i]->m_b_star.Draw();
				
 				D3DXMatrixTranslation(&A, -monster[i]->star[j].x +  hero.screen_x, -monster[i]->star[j].y, 0.0f);
			}
		}
	}


	////hp바
	m_b_hpbar.SetTransform(&T);
	m_b_hpbar.m_vPosition.x=0;
	m_b_hpbar.m_vPosition.y=0;
	m_b_hpbar.m_vPosition.z=0;
	m_b_hpbar.Draw();


	m_b_hpball.SetTransform(&T);
	m_b_emptyball.SetTransform(&T);
	for(int i=0;i<HeroStat::hp;i++)
	{
		switch(i)
		{
		case 0:
			m_b_hpball.m_vPosition.x = 33;
			m_b_hpball.m_vPosition.y = 89;
			m_b_emptyball.m_vPosition.x = 33;
			m_b_emptyball.m_vPosition.y = 89;
			break;
		case 1:
			m_b_hpball.m_vPosition.x = 33;
			m_b_hpball.m_vPosition.y = 107;
			m_b_emptyball.m_vPosition.x = 33;
			m_b_emptyball.m_vPosition.y = 107;
			break;
		case 2:
			m_b_hpball.m_vPosition.x = 21;
			m_b_hpball.m_vPosition.y = 121;
			m_b_emptyball.m_vPosition.x = 21;
			m_b_emptyball.m_vPosition.y = 121;
			break;
		case 3:
			m_b_hpball.m_vPosition.x = 41;
			m_b_hpball.m_vPosition.y = 127;
			m_b_emptyball.m_vPosition.x = 41;
			m_b_emptyball.m_vPosition.y = 127;
			break;
		case 4:
			m_b_hpball.m_vPosition.x = 30;
			m_b_hpball.m_vPosition.y = 143;
			m_b_emptyball.m_vPosition.x = 30;
			m_b_emptyball.m_vPosition.y = 143;
			break;
		case 5:
			m_b_hpball.m_vPosition.x = 37;
			m_b_hpball.m_vPosition.y = 167;
			m_b_emptyball.m_vPosition.x = 37;
			m_b_emptyball.m_vPosition.y = 167;
			break;
		case 6:
			m_b_hpball.m_vPosition.x = 29;
			m_b_hpball.m_vPosition.y = 186;
			m_b_emptyball.m_vPosition.x = 29;
			m_b_emptyball.m_vPosition.y = 186;
			break;
		case 7:
			m_b_hpball.m_vPosition.x = 33;
			m_b_hpball.m_vPosition.y = 214;
			m_b_emptyball.m_vPosition.x = 33;
			m_b_emptyball.m_vPosition.y = 214;
			break;
		case 8:
			m_b_hpball.m_vPosition.x = 38;
			m_b_hpball.m_vPosition.y = 238;
			m_b_emptyball.m_vPosition.x = 38;
			m_b_emptyball.m_vPosition.y = 238;
			break;
		case 9:
			m_b_hpball.m_vPosition.x = 33;
			m_b_hpball.m_vPosition.y = 266;
			m_b_emptyball.m_vPosition.x = 33;
			m_b_emptyball.m_vPosition.y = 266;
			break;
		}
		m_b_hpball.Draw();
		m_b_emptyball.Draw(100);
	}

	for(int i=0; i<HeroStat::fullhp-HeroStat::hp; i++)
	{
		switch(10-(HeroStat::fullhp-i))		//남은 hp에 따라 그려주는 데...
		{
			case 0:
				m_b_emptyball.m_vPosition.x = 33;
				m_b_emptyball.m_vPosition.y = 266;
				break;
			case 1:
				m_b_emptyball.m_vPosition.x = 38;
				m_b_emptyball.m_vPosition.y = 238;
				break;
			case 2:
				m_b_emptyball.m_vPosition.x = 33;
				m_b_emptyball.m_vPosition.y = 214;
				break;
			case 3:
				m_b_emptyball.m_vPosition.x = 29;
				m_b_emptyball.m_vPosition.y = 186;
				break;
			case 4:
				m_b_emptyball.m_vPosition.x = 37;
				m_b_emptyball.m_vPosition.y = 167;
				break;
			case 5:
				m_b_emptyball.m_vPosition.x = 30;
				m_b_emptyball.m_vPosition.y = 143;
				break;
			case 6:
				m_b_emptyball.m_vPosition.x = 41;
				m_b_emptyball.m_vPosition.y = 127;
				break;
			case 7:
				m_b_emptyball.m_vPosition.x = 21;
				m_b_emptyball.m_vPosition.y = 121;
				break;
			case 8:
				m_b_emptyball.m_vPosition.x = 33;
				m_b_emptyball.m_vPosition.y = 107;
				break;
			case 9:
				m_b_emptyball.m_vPosition.x = 33;
				m_b_emptyball.m_vPosition.y = 89;
				break;
			}
			m_b_emptyball.Draw();
	}
	


}

void Battle::Update(int &m_iCurrentState, int m_iCurrentStage)
{

	if (mustinit==false)
	{
		initializing2();
	}
	//////////////선처리/////////////////////
	if(initialized==false)
	{
		//스테이지 경우에 따라, 몬스터 마리수에 따라 이니셜라이징 해준다.
		Initializing(m_iCurrentStage);
	}
	////////////////////////////////////


	//////////////행동결정////////////////
	if(hero.delayed == false)
	{
		hero.Key();
		hero.SetState();
	}
	for(int i=0;i<monstercount;i++)
	{
		if(monster[i]->delayed	==	false)
		{
			monster[i]->AI(hero);
			monster[i]->SetState();
		}
	}
	if(whatboss != 10)
	{
		if(boss->delayed == false)
		{
			boss->AI(hero);
			boss->SetState();

		}
	}
	////////////////////////////////////


	//////////////연산///////////////////
	CheckSituation();

	if(CheckCollision())
	{
		Collision();
	}

	Calculate();

	AfterCalculate();
	////////////////////////////////////




	/////////////후처리////////////////////
	if (whilebattle == false)
	{
		Ending(m_iCurrentState);
	}
	////////////////////////////////////
}

//////////////// Update 재료 함수 //////////////////
void Battle::Initializing(int m_iCurrentStage)
{
	endtime = 0 ;
	whilebattle = true;
	
	///// 속성 초기화 //////
	hero.Initialize(700,400);


	switch(m_iCurrentStage)			//난이도에 따라 결정될 것들.
	{
	case 1:
		monstercount = 40;
		species = 2;
		lowspecies = 0;
		highspecies = lowspecies + species;
		whatboss = 10 + rand()%2;// + rand()%5 ;
		break;
	case 2:
		monstercount = 50;
		species = 3;
		lowspecies = 0;
		highspecies = lowspecies + species;
		whatboss = 11 + rand()%2;
		break;
	case 3:
		monstercount = 60;
		species = 3;
		lowspecies = 1;
		highspecies = lowspecies + species;
		whatboss = 12;
		break;
	case 4:
		monstercount = 50;
		species = 2;
		lowspecies = 2;
		highspecies = lowspecies + species;
		whatboss = 12+rand()%2;
		break;
	case 5:
		monstercount = 40;
		species = 4;
		lowspecies = 0;
		highspecies = lowspecies + species;
		whatboss = 14;
		break;
	}

	monster = new Monster*[monstercount];
	for(int i=0;i<monstercount; i++)
	{
		monster[i] = new Monster;
		for(int j=0;j<5;j++)
		{
			monster[i]->star[j].Initialize();
		}
	}
	m_b_monster = new Sprite*[highspecies];

	for (int i=0;i<highspecies;i++)
	{
		m_b_monster[i] = new Sprite;
	}
	if(whatboss != 10)
	{
		boss = new Monster;
		boss->Initialize(rand()%1300,100,whatboss);
		boss->bosseffect.valid=false;
		boss->bosseffect.Initialize();
		m_b_boss = new Sprite;
		m_b_bosseffect = new Sprite;
		m_b_boss->m_bVisible = true;
		m_b_boss->m_rSource.top = 0;
		m_b_boss->m_rSource.left = 0;
		m_b_boss->m_rSource.right = 2250;
		m_b_boss->m_rSource.bottom = 2250;
		m_b_boss->m_vPosition.x = 0;
		m_b_boss->m_vPosition.y = 0;
		m_b_boss->m_vPosition.z = 0;
		switch(boss->species)
		{
		case 11:			m_b_boss->CreateTextureFromFile( "goblin_hammer.png", &(m_b_boss->m_Texture));
			m_b_bosseffect->CreateTextureFromFile("hpball.png",&(m_b_bosseffect->m_Texture));
			break;
		case 12:			m_b_boss->CreateTextureFromFile( "whisp_red.png", &(m_b_boss->m_Texture));
			m_b_bosseffect->CreateTextureFromFile("fire_effect.png",&(m_b_bosseffect->m_Texture));
			break;
		case 13:			m_b_boss->CreateTextureFromFile( "whisp_yellow.png", &(m_b_boss->m_Texture));
			m_b_bosseffect->CreateTextureFromFile("lightning_effect.png",&(m_b_bosseffect->m_Texture));
			break;
		case 14:			m_b_boss->CreateTextureFromFile( "lastboss.png", &(m_b_boss->m_Texture));
			m_b_bosseffect->CreateTextureFromFile("hpball.png",&(m_b_bosseffect->m_Texture));
			break;
		case 15:			m_b_boss->CreateTextureFromFile( "whisp_king.png", &(m_b_boss->m_Texture));
			m_b_bosseffect->CreateTextureFromFile("lazor_horizon.png",&(m_b_bosseffect->m_Texture));
			break;
		}
	}



	for(int i=0;i<monstercount;i++)
	{
		if(rand()%2)
		{
			monster[i]->Initialize(rand()%300,465,rand()%species+lowspecies);
		}
		else
		{
			monster[i]->Initialize(rand()%300 + 1000,465,rand()%species+lowspecies);
		}
		if(monster[i]->species==2)
		{
			monster[i]->y = 365;
		}
		monster[i]->effect.size = 2;
	}

	srand(time(NULL));

	//Monster
	for(int i=0;i<highspecies;i++)
	{
		m_b_monster[i]->m_bVisible = true;
		m_b_monster[i]->m_rSource.top = 0;
		m_b_monster[i]->m_rSource.left = 0;
		m_b_monster[i]->m_rSource.right = 2250;
		m_b_monster[i]->m_rSource.bottom = 2250;

		m_b_monster[i]->m_vPosition.x = 0;//monster[i]->screen_x;
		m_b_monster[i]->m_vPosition.y = 0;//monster[i]->screen_y;
		m_b_monster[i]->m_vPosition.z = 0;

		m_b_monster[i]->m_vCenter.x = 0;
		m_b_monster[i]->m_vCenter.y = 0;
		m_b_monster[i]->m_vCenter.z = 0;

		switch(i)	/// 이것은 임시로 해둔 것. 나중에 맵의 난이도와 함께 조정 지금은 그냥 여러 몹을 로딩할려는 것
		{
		case 0:			m_b_monster[i]->CreateTextureFromFile( "goblin_spear.png", &(m_b_monster[i]->m_Texture) );
			break;
		case 1:			m_b_monster[i]->CreateTextureFromFile( "goblin_axe.png", &(m_b_monster[i]->m_Texture) );
			break;
		case 2:			m_b_monster[i]->CreateTextureFromFile( "goblin_hammer.png", &(m_b_monster[i]->m_Texture) );
			break;
		case 3:			m_b_monster[i]->CreateTextureFromFile( "whisp_blue.png", &(m_b_monster[i]->m_Texture) );
			break;
		case 4:			m_b_monster[i]->CreateTextureFromFile( "whisp_yellow.png", &(m_b_monster[i]->m_Texture) );
			break;
		}
	}



	//effect
	for (int i=0;i<monstercount;i++)
	{
		monster[i]->effect.Initialize();
		
		monster[i]->m_b_effect.m_bVisible = true;
		monster[i]->m_b_effect.m_rSource.left = 0;
		monster[i]->m_b_effect.m_rSource.top = 0;
		monster[i]->m_b_effect.m_rSource.right = 2250;
		monster[i]->m_b_effect.m_rSource.bottom = 2250;

		monster[i]->m_b_effect.m_vPosition.x = 0;
		monster[i]->m_b_effect.m_vPosition.y = 0;
		monster[i]->m_b_effect.m_vPosition.z = 0;

		monster[i]->m_b_effect.CreateTextureFromFile( "attackeffect.png", &(monster[i]->m_b_effect.m_Texture) );

		monster[i]->bigeffect.Initialize();

		monster[i]->m_b_bigeffect.m_bVisible = true;
		monster[i]->m_b_bigeffect.m_rSource.left = 0;
		monster[i]->m_b_bigeffect.m_rSource.top = 0;
		monster[i]->m_b_bigeffect.m_rSource.right = 1024;
		monster[i]->m_b_bigeffect.m_rSource.bottom = 768;

		monster[i]->m_b_bigeffect.m_vPosition.x = 0;
		monster[i]->m_b_bigeffect.m_vPosition.y = 0;
		monster[i]->m_b_bigeffect.m_vPosition.z = 0;

		monster[i]->m_b_bigeffect.CreateTextureFromFile( "effect.png", &(monster[i]->m_b_bigeffect.m_Texture) );


	}

	//star
	for(int i=0;i<monstercount;i++)
	{
		monster[i]->m_b_star.m_rSource.left = 0;
		monster[i]->m_b_star.m_rSource.top = 0;
		monster[i]->m_b_star.m_rSource.right = 25;
		monster[i]->m_b_star.m_rSource.bottom = 25;

		monster[i]->m_b_star.m_vPosition.x = 0;
		monster[i]->m_b_star.m_vPosition.y = 0;
		monster[i]->m_b_star.m_vPosition.z = 0;
		monster[i]->m_b_star.CreateTextureFromFile("smallstar.png", &(monster[i]->m_b_star.m_Texture) );
	}



	initialized=true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Battle::CheckSituation()
{
	for(int i=0;i<monstercount;i++)
	{
		if((monster[i]->bodysquare.left + monster[i]->bodysquare.right) / 2 < (hero.bodysquare.left + hero.bodysquare.right) / 2)
		{
			monster[i]->herodirection = RIGHT;
		}
		else
		{
			monster[i]->herodirection = LEFT;
		}
	}

	if(whatboss!=10)
	{
		if((boss->bodysquare.left + boss->bodysquare.right) / 2 < (hero.bodysquare.left + hero.bodysquare.right) / 2)
		{
			boss->herodirection = RIGHT;
		}
		else
		{
			boss->herodirection = LEFT;
		}
	}
}

bool Battle::CheckCollision()
{
	bool collisioncheck = false;
	if(whatboss!=10)
	{
		if(boss->state == ATTACK)
		{
			collisioncheck = true;
		}
	}
	if(hero.combo[0] == SPACE)
	{
		collisioncheck	=	true;
	}
	for(int i=0;i<monstercount;i++)
	{
		if(monster[i]->state == ATTACK)
		{
			collisioncheck	=	true;
			break;
		}
	}

	return collisioncheck;

}

void Battle::Collision()
{
	RECT hit;
	RECT hit1;

	RECT hit2;
	RECT hit3;

	///// 주인공의 공격 범위안에 제일 근처 적이 있으면 /////
	for(int i=0;i<monstercount;i++)
	{
		if( (monster[i]->immune == false) && (IntersectRect( &hit , &hero.attacksquare, &monster[i]->bodysquare) != NULL) )
		{
			monster[i]->hp -= HeroStat::attack;
			monster[i]->state = HITTED;
			monster[i]->immune = true;
			monster[i]->phase = 0;
			monster[i]->effect.x = monster[i]->bodysquare.left-75;
			monster[i]->effect.y = monster[i]->bodysquare.top-50;
			monster[i]->effect.valid=true;
			monster[i]->effect.sprite_x = 0;
			monster[i]->effect.sprite_y = 0;
			switch(hero.state)
			{
			case 33235:
			case 44245:
				switch(hero.phase)
				{
				case 3:
				case 6:
					if(monster[i]->herodirection == LEFT)
					{
						monster[i]->moving_x += rand()%100;
					}
					else
					{
						monster[i]->moving_x -= rand()%100;
					}
					monster[i]->moving_y = -10;
					monster[i]->falltime =  -10;
					break;
				case 9:
				case 10:
					if(monster[i]->herodirection == LEFT)
					{
						monster[i]->moving_x += rand()%70;
					}
					else
					{
						monster[i]->moving_x -= rand()%70;
					}
					monster[i]->moving_y = -20;
					monster[i]->falltime =  -10;
					break;
				case 12:
					if(monster[i]->herodirection == LEFT)
					{
						monster[i]->moving_x += rand()%70;
					}
					else
					{
						monster[i]->moving_x -= rand()%70;
					}
					break;

				}
				if(hero.falling == true)
				{
					hero.moving_y = -20;
				}
				break;
			case 445:
			case 335:
				if(monster[i]->herodirection == LEFT)
				{
					monster[i]->moving_x += rand()%70;
				}
				else
				{
					monster[i]->moving_x -= rand()%70;
				}
				monster[i]->moving_y = -20;
				monster[i]->falltime =  -10;
				if(hero.falling == true)
				{
					hero.moving_y = -20;
				}

				break;
			case 345:
			case 435:
				if(monster[i]->herodirection == LEFT)
				{
					monster[i]->moving_x += 180;
				}
				else
				{
					monster[i]->moving_x -= 180;
				}
				monster[i]->moving_y = -20;
				monster[i]->falltime =  -10;
				if(hero.falling == true)
				{
					hero.moving_y = -20;
				}

				break;
			case 235:
			case 245:
				if(monster[i]->herodirection == LEFT)
				{
					monster[i]->moving_x += rand()%70;
				}
				else
				{
					monster[i]->moving_x -= rand()%70;
				}
				monster[i]->moving_y = -20;
				monster[i]->falltime = -15-rand()%10;
				if(hero.falling == true)
				{
					hero.moving_y = -20;
				}

				break;
			case 325:
			case 425:
				if(monster[i]->herodirection == LEFT)
				{
					monster[i]->moving_x += rand()%70;
				}
				else
				{
					monster[i]->moving_x -= rand()%70;
				}
				monster[i]->moving_y = 20;
				monster[i]->falltime = 15+rand()%10;
				if(hero.falling == true)
				{
					hero.moving_y = -20;
				}

				break;
			default:
				if(monster[i]->herodirection == LEFT)
				{
					monster[i]->moving_x += 50 + rand()%100;
				}
				else
				{
					monster[i]->moving_x -= 50 + rand()%100;
				}
				monster[i]->moving_y = -20;
				if(hero.falling == true)
				{
					hero.moving_y = -30;
				}
				break;
			}
				
		}
	}


	///// 주인공 범위내에 보스가 잇으면

	if(whatboss!=10)
	{
		if( (boss->immune == false) && (IntersectRect( &hit2 , &hero.attacksquare, &boss->bodysquare) != NULL) )
		{
			boss->hp -= HeroStat::attack;
		boss->state = HITTED;
		boss->immune = true;
		boss->phase = 0;
		boss->effect.x = boss->bodysquare.left-75;
		boss->effect.y = boss->bodysquare.top-50;
		boss->effect.valid=true;
		boss->effect.sprite_x = 0;
		boss->effect.sprite_y = 0;
		switch(hero.state)
		{
		case 33235:
		case 44245:
			switch(hero.phase)
			{
			case 3:
			case 6:
				if(boss->herodirection == LEFT)
				{
					boss->moving_x += rand()%80;
				}
				else
				{
					boss->moving_x -= rand()%80;
				}
				break;
			case 9:
			case 10:
				if(boss->herodirection == LEFT)
				{
					boss->moving_x += rand()%50;
				}
				else
				{
					boss->moving_x -= rand()%50;
				}
				break;
			case 12:
				if(boss->herodirection == LEFT)
				{
					boss->moving_x += rand()%50;
				}
				else
				{
					boss->moving_x -= rand()%50;
				}
				break;
			}
			if(hero.falling == true)
			{
				hero.moving_y = -20;
			}
			break;
		case 445:
		case 335:
			if(boss->herodirection == LEFT)
			{
				boss->moving_x += rand()%50;
			}
			else
			{
				boss->moving_x -= rand()%50;
			}
			if(hero.falling == true)
			{
				hero.moving_y = -20;
			}

			break;
		case 345:
		case 435:
			if(boss->herodirection == LEFT)
			{
				boss->moving_x += 150;
			}
			else
			{
				boss->moving_x -= 150;
			}
			boss->moving_y = -20;
			boss->falltime =  -10;
			if(hero.falling == true)
			{
				hero.moving_y = -20;
			}

			break;
		case 235:
		case 245:
			if(boss->herodirection == LEFT)
			{
				boss->moving_x += rand()%50;
			}
			else
			{
				boss->moving_x -= rand()%50;
			}
			if(hero.falling == true)
			{
				hero.moving_y = -20;
			}

			break;
		case 325:
		case 425:
			if(boss->herodirection == LEFT)
			{
				boss->moving_x += rand()%50;
			}
			else
			{
				boss->moving_x -= rand()%50;
			}
			if(hero.falling == true)
			{
				hero.moving_y = -20;
			}

			break;
		default:
			if(boss->herodirection == LEFT)
			{
				boss->moving_x += 50 + rand()%40;
			}
			else
			{
				boss->moving_x -= 50 + rand()%40;
			}
			if(hero.falling == true)
			{
				hero.moving_y = -30;
			}
			break;
		}
			
		}

	}


	///// 몹의 공격 범위 안에 적이 있으면 ////////
	for(int i=0;i<monstercount;i++)
	{
		if( (hero.immune == false) && ( IntersectRect( &hit1, &hero.bodysquare, &monster[i]->attacksquare) != NULL) )
		{
			HeroStat::hp -= monster[i]->damage;
			hero.state = HITTED;
			hero.immune = true;
			hero.phase = 0;
			if(monster[i]->herodirection == LEFT)
			{
				hero.direction = LEFT;
				hero.moving_x -= 10;
			}
			else
			{
				hero.direction = RIGHT;
				hero.moving_x += 10;
			}
		}
	}


	if(whatboss != 10)
	{
		if( (hero.immune ==false )  && (IntersectRect( &hit3, &hero.bodysquare, &boss->attacksquare) != NULL) )
		{
			HeroStat::hp -= boss->damage;
			hero.state = HITTED;
			hero.immune = true;
			hero.phase = 0;
			if(boss->herodirection == LEFT)
			{
				hero.direction = LEFT;
				hero.moving_x -= 10;
			}
			else
			{
				hero.direction = RIGHT;
				hero.moving_x += 10;
			}
		}
	}

}

void Battle::Calculate()
{
	
	if(hero.prestate!=hero.combo[0]) hero.time=0;

	hero.time++;
	for(int i=0;i<monstercount;i++)
	{
		monster[i]->time++;
		monster[i]->effect.time++;
		monster[i]->bigeffect.time++;
		for(int j=0;j<5;j++)
		{
			monster[i]->star[j].time++;
		}
	}
	if(whatboss!=10)
	{
		boss->time++;
	//boss->effect.time++;
	//boss->bigeffect.time++;
		boss->bosseffect.time++;
	}
	



	/////// 영웅 상태에 따른 연산

	if(hero.falling == true)
	{
		hero.falltime++;
		if(hero.y + 250 < hero.ground)			{hero.moving_y = hero.falltime;}
		else if(hero.y + 250 > hero.ground)		{hero.moving_y = -(hero.y +250 - hero.ground);}
		else if(hero.y + 250 == hero.ground)					{hero.falling = false; hero.whilejumpdown = false; hero.whilejumpup = false;}
	}

	


	if(hero.y + 250 != hero.ground)
	{
		hero.falling = true;
	}
	else
	{
		hero.falltime = 0;
		hero.falling = false;
	}

	switch(hero.state)
	{
	case HITTED:
		if(hero.direction==LEFT)		{hero.sprite_y=6;}
		else							{hero.sprite_y=7;}

		SetRect( &hero.attacksquare , 0, 0, 0, 0);
		hero.delayed = true;
		if(hero.time >= 5)
		{
			hero.time = 0;
			hero.phase++;
		}

		switch(hero.phase)
		{
		case 0:
			hero.sprite_x=0;
			break;
		case 1:
			hero.sprite_x=1;
			break;
		case 2:
			if(hero.direction==LEFT)		{hero.direction=RIGHT;}
			else							{hero.direction=LEFT;}
			hero.delayed = false;
			hero.sprite_x=1;
			hero.phase = 0;
			hero.immune = false;
			break;
		}
		break;

	case DEAD:
		if(hero.direction==LEFT)		{hero.sprite_y=6;}
		else							{hero.sprite_y=7;}

		hero.immune = true;
		hero.delayed = true;

		if(hero.time >= 5)
		{
			hero.time = 0;
			hero.phase++;
		}
		switch(hero.phase)
			{
			case 0:
			case 3:
			case 6:
			case 9:
			case 10:
			case 11:
				hero.sprite_x=0;
				break;
			case 1:
			case 4:
			case 7:
				hero.sprite_x=1;
				break;
			case 2:
			case 5:
			case 8:
				hero.sprite_y=20;
				hero.sprite_x=20;
				break;
			case 12:
				hero.immune = false;
				hero.delayed = false;
				hero.sprite_x=1;
				hero.phase = 0;
				whilebattle = false;
				break;

			}
		break;

	case 33235:
	case 44245:
		hero.immune = true;
		hero.delayed = true;
		if (hero.time > 2)
		{
			hero.phase++;
			hero.time=0;
		}

		switch(hero.phase)
		{
		case 0:
			if(hero.direction == LEFT)		{hero.sprite_y = 9;} 
			else							{hero.sprite_y = 8;}
			hero.sprite_x=3;
			break;
		case 1:
		case 4:
			if(hero.direction == LEFT)		{hero.moving_x = -15;} 
			else							{hero.moving_x = 15;}
			hero.sprite_x=4;
			break;
		case 2:
		case 5:
			if(hero.direction == LEFT)		{hero.moving_x = -20;} 
			else							{hero.moving_x = 20;}
			hero.sprite_x=5;
			break;
		case 3:
		case 6:
			if(hero.direction == LEFT)		{hero.moving_x = -5;} 
			else							{hero.moving_x = 5;}
			hero.sprite_x=6;
			if(hero.direction == LEFT)
			{
				SetRect( &hero.attacksquare, hero.x, hero.y + 180, hero.x + 300, hero.y + 250);
			}
			else
			{
				SetRect( &hero.attacksquare, hero.x + 50, hero.y, hero.x + 350, hero.y + 250);
			}
			break;
		case 7:
			if(hero.direction == LEFT)		{hero.sprite_y = 5;} 
			else							{hero.sprite_y = 4;}
			if(hero.direction == LEFT)		{hero.moving_x = -15; hero.moving_y = -15; hero.falltime = 0;} 
			else							{hero.moving_x = 15; hero.moving_y = -15; hero.falltime = 0;}
			hero.sprite_x=4;
			SetRect( &hero.attacksquare, 0, 0, 0, 0);
			break;
		case 8:
			if(hero.direction == LEFT)		{hero.moving_x = -15;} 
			else							{hero.moving_x = 15;}
			if(hero.direction == LEFT)		{hero.moving_y = -15; hero.falltime = 0;} 
			else							{hero.moving_y = -15; hero.falltime = 0;}
			hero.sprite_x=5;
			break;
		case 9:
			if(hero.direction == LEFT)		{hero.moving_x = -30;} 
			else							{hero.moving_x = 30;}
			if(hero.direction == LEFT)		{hero.moving_y = -15; hero.falltime = 0;} 
			else							{hero.moving_y = -15; hero.falltime = 0;}
			hero.sprite_x=6;
			if(hero.direction == LEFT)
			{
				SetRect( &hero.attacksquare, hero.x, hero.y + 100, hero.x + 250, hero.y + 200);
			}
			else
			{
				SetRect( &hero.attacksquare, hero.x + 100, hero.y + 100, hero.x + 350, hero.y + 200);
			}
			break;
		case 10:
			if(hero.direction == LEFT)		{hero.moving_x = -10;} 
			else							{hero.moving_x = 10;}
			hero.sprite_x=7;
			if(hero.direction == LEFT)
			{
				SetRect( &hero.attacksquare, hero.x, hero.y + 100, hero.x + 50, hero.y + 200);
			}
			else
			{
				SetRect( &hero.attacksquare, hero.x + 300, hero.y+ 100, hero.x + 350, hero.y + 200);
			}
			break;
		case 11:
			if(hero.direction == LEFT)		{hero.sprite_y = 7;} 
			else							{hero.sprite_y = 6;}
			hero.sprite_x=3;
			if(hero.direction == LEFT)		{hero.moving_x = -20;} 
			else							{hero.moving_x = 20;}
			SetRect( &hero.attacksquare, 0, 0, 0, 0);
			break;
		case 12:
			if(hero.direction == LEFT)		{hero.moving_y = 15; hero.falltime = 0;} 
			else							{hero.moving_y = 15; hero.falltime = 0;}
			hero.sprite_x=4;
			if(hero.direction == LEFT)		{hero.moving_x = -10;} 
			else							{hero.moving_x = 10;}
			if(hero.direction == LEFT)
			{
				SetRect( &hero.attacksquare, hero.x, hero.y, hero.x + 175, hero.y + 250);
			}
			else
			{
				SetRect( &hero.attacksquare, hero.x + 175, hero.y, hero.x + 350, hero.y + 250);
			}
			break;
		case 13:
			hero.sprite_x=5;
			SetRect( &hero.attacksquare, 0, 0, 0, 0);
			break;
		case 14:
			///// 공격 범위 초기화 해줌
			hero.immune = false;
			hero.delayed=false;
			if(hero.direction == LEFT)		{hero.sprite_y = 1;} 
			else							{hero.sprite_y = 0;}
			hero.sprite_x=5;
			hero.phase=0;
			break;
		}
		break;

	case 235:
	case 245:
			if(hero.direction == LEFT)		{hero.sprite_y = 7;} 
			else							{hero.sprite_y = 6;}
			hero.immune = true;
			hero.delayed = true;
			if (hero.time > 2)
			{
				hero.phase++;
				hero.time=0;
			}

			switch(hero.phase)
			{
			case 0:
				hero.sprite_x=5;
				break;
			case 1:
				hero.sprite_x=4;
				break;
			case 2:
				hero.sprite_x=3;
				if(hero.direction == LEFT)
				{
					SetRect( &hero.attacksquare, hero.x, hero.y, hero.x + 175, hero.y + 250);
				}
				else
				{
					SetRect( &hero.attacksquare, hero.x + 175, hero.y, hero.x + 350, hero.y + 250);
				}
				break;
			case 3:
				///// 공격 범위 초기화 해줌
				SetRect( &hero.attacksquare, 0, 0, 0, 0);
				hero.immune =false;
				hero.delayed=false;
				if(hero.direction == LEFT)		{hero.sprite_y = 1;} 
				else							{hero.sprite_y = 0;}
				hero.sprite_x=5;
				hero.phase=0;
				break;
			}
			break;

		
	case 325:
	case 425:
			if(hero.direction == LEFT)		{hero.sprite_y = 7;} 
			else							{hero.sprite_y = 6;}
			hero.immune = true;
			hero.delayed = true;
			if (hero.time > 2)
			{
				hero.phase++;
				hero.time=0;
			}

			switch(hero.phase)
			{
			case 0:
				hero.sprite_x=3;
				break;
			case 1:
				hero.sprite_x=4;
				break;
			case 2:
				hero.sprite_x=5;
				if(hero.direction == LEFT)
				{
					SetRect( &hero.attacksquare, hero.x, hero.y, hero.x + 175, hero.y + 250);
				}
				else
				{
					SetRect( &hero.attacksquare, hero.x + 175, hero.y, hero.x + 350, hero.y + 250);
				}
				break;
			case 3:
				///// 공격 범위 초기화 해줌
				SetRect( &hero.attacksquare, 0, 0, 0, 0);
				hero.immune =false;
				hero.delayed=false;
				if(hero.direction == LEFT)		{hero.sprite_y = 1;} 
				else							{hero.sprite_y = 0;}
				hero.sprite_x=3;
				hero.phase=0;
				break;
			}
			break;

		
	case 345:
	case 435:
			if(hero.direction == LEFT)		{hero.sprite_y = 5;} 
			else							{hero.sprite_y = 4;}
			hero.delayed = true;
			hero.immune = true;
			if (hero.time > 2)
			{
				hero.phase++;
				hero.time=0;
			}

			switch(hero.phase)
			{
			case 0:
				hero.sprite_x=3;
				break;
			case 1:
				if(hero.direction == LEFT)		{hero.moving_x=-20;} 
				else							{hero.moving_x=20;}
				hero.sprite_x=4;
				break;
			case 2:
				if(hero.direction == LEFT)		{hero.moving_x=-30;} 
				else							{hero.moving_x=30;}
				hero.sprite_x=5;
				break;
			case 3:
				if(hero.direction == LEFT)		{hero.moving_x=-40;} 
				else							{hero.moving_x=40;}
				hero.sprite_x=6;
				if(hero.direction == LEFT)
				{
					SetRect( &hero.attacksquare, hero.x, hero.y + 150, hero.x + 250, hero.y + 200);
				}
				else
				{
					SetRect( &hero.attacksquare, hero.x + 100, hero.y + 150, hero.x + 350, hero.y + 200);
				}
				break;
			case 4:
				if(hero.direction == LEFT)		{hero.moving_x=-10;} 
				else							{hero.moving_x=10;}
				hero.sprite_x=7;
				if(hero.direction == LEFT)
				{
					SetRect( &hero.attacksquare, hero.x, hero.y + 150, hero.x + 50, hero.y + 200);
				}
				else
				{
					SetRect( &hero.attacksquare, hero.x + 300, hero.y+ 150, hero.x + 350, hero.y + 200);
				}
				break;
			case 5:
				///// 공격 범위 초기화 해줌
				hero.delayed=false;
				hero.immune=false;
				if(hero.direction == LEFT)		{hero.sprite_y = 4;} 
				else							{hero.sprite_y = 5;}
				SetRect( &hero.attacksquare, 0, 0, 0, 0);
				hero.sprite_x=4;
				hero.phase=0;
				break;
			}
			break;


	case 335:
	case 445:
			if(hero.direction == LEFT)		{hero.sprite_y = 9;} 
			else							{hero.sprite_y = 8;}
			hero.immune = true;
			hero.delayed = true;
			if (hero.time > 2)
			{
				hero.phase++;
				hero.time=0;
			}

			switch(hero.phase)
			{
			case 0:
				if(hero.direction == LEFT)		{hero.moving_x=-10;} 
				else							{hero.moving_x=10;}
				hero.sprite_x=3;
				break;
			case 1:
				if(hero.direction == LEFT)		{hero.moving_x=-20;} 
				else							{hero.moving_x=20;}
				hero.sprite_x=4;
				break;
			case 2:
				if(hero.direction == LEFT)		{hero.moving_x=-30;} 
				else							{hero.moving_x=30;}
				hero.sprite_x=5;
				if(hero.direction == LEFT)
				{
					SetRect( &hero.attacksquare, hero.x, hero.y + 180, hero.x + 300, hero.y + 250);
				}
				else
				{
					SetRect( &hero.attacksquare, hero.x + 50, hero.y, hero.x + 350, hero.y + 250);
				}
				break;
			case 3:
				if(hero.direction == LEFT)		{hero.moving_x=-40;} 
				else							{hero.moving_x=40;}
				hero.sprite_x=6;
				SetRect( &hero.attacksquare, 0, 0, 0, 0);
				break;
			case 4:
				///// 공격 범위 초기화 해줌
				hero.immune=false;
				hero.delayed=false;
				if(hero.direction == LEFT)		{hero.sprite_y = 1;} 
				else							{hero.sprite_y = 0;}
				hero.sprite_x=3;
				hero.phase=0;
				break;
			}
		
		break;

	case 333:
	case 444:
		if(hero.falling==false)
		{
			if(hero.direction == LEFT)				{hero.sprite_y = 9;}
			else									{hero.sprite_y = 8;}
			hero.immune = true;
			hero.delayed = true;
			switch(hero.phase)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
				hero.sprite_x = 0;
			
				if(hero.direction == LEFT)				{hero.moving_x -= 10;}
				else									{hero.moving_x += 10;}
				
				hero.phase++;
				break;
			case 8:
				hero.delayed = false;
				hero.immune = false;
				hero.sprite_y = 3;
				hero.sprite_x = 1;

				if(hero.direction == LEFT)				{hero.moving_x -= 10;}
				else									{hero.moving_x += 10;}
				
				hero.phase = 0;
				hero.state = 0;
				break;
			}
		}
		break;
	default:
		switch(hero.combo[0])
		{
		case ZERO:
			if(hero.direction==LEFT)		{hero.sprite_y=1;}
			else							{hero.sprite_y=0;}
			if(hero.time >= 5)
			{
				hero.time = 0;
				hero.sprite_x++;
			}
			if(hero.sprite_x>8)
			{
				hero.sprite_x=0;
			}
			break;
		case UP:
			if(hero.y + 250 == hero.ground)
			{
				hero.falling = true;
				hero.whilejumpup = true;
				hero.whilejumpdown = false;
				hero.falltime = -25;
				hero.moving_y = hero.falltime;
			}
			break;
		case DOWN:
			break;
		case LEFT:
			hero.direction=LEFT;
			hero.sprite_y = 3;
			hero.moving_x = -15;
			if(hero.time >= 5)
			{
				hero.time = 0;
				hero.sprite_x++;
			}
			if(hero.sprite_x>2)
			{
				hero.sprite_x=0;
			}
			break;
		case RIGHT:
			hero.direction=RIGHT;
			hero.sprite_y = 2;
			hero.moving_x = 15;

			if(hero.time >= 5)
			{
				hero.time = 0;
				hero.sprite_x++;
			}
			if(hero.sprite_x>2)
			{
				hero.sprite_x=0;
			}
			break;
		case SPACE:
			if(hero.whilejumpup == true)
			{
				if(hero.direction==LEFT)				{hero.sprite_y=3; }
				else									{hero.sprite_y=2; }
				if(GetKeyState(VK_LEFT) & 0x8000)		{ hero.moving_x=-15;}
				else if(GetKeyState(VK_RIGHT) & 0x8000)		{ hero.moving_x=15;}

				hero.delayed = true;
				if (hero.time > 4)
				{
					hero.phase++;
					hero.time=0;
				}

				switch(hero.phase)
				{
				case 0:
					hero.sprite_x=5;
					break;
				case 1:
					hero.sprite_x=6;
					break;
				case 2:
					hero.sprite_x=7;
					if(hero.direction == LEFT)
					{
						SetRect( &hero.attacksquare, hero.x, hero.y, hero.x + 175, hero.y + 150);
					}
					else
					{
						SetRect( &hero.attacksquare, hero.x + 175, hero.y, hero.x + 350, hero.y + 150);
					}
					break;
				case 3:
					///// 공격 범위 초기화 해줌
					SetRect( &hero.attacksquare, 0, 0, 0, 0);
					hero.delayed=false;
					hero.sprite_x=5;
					hero.phase=0;
					break;
				}
				break;
			}
			else if(hero.whilejumpdown == true)
			{
				
				if(hero.direction==LEFT)				{hero.sprite_y=7;}
				else									{hero.sprite_y=6;}
				if(GetKeyState(VK_LEFT) & 0x8000)		{ hero.moving_x=-15;}
				else if(GetKeyState(VK_RIGHT) & 0x8000)		{ hero.moving_x=15;}

				hero.delayed = true;
				if (hero.time > 2)
				{
					hero.phase++;
					hero.time=0;
				}

				switch(hero.phase)
				{
				case 0:
					hero.sprite_x=6;
					break;
				case 1:
					hero.sprite_x=7;
					break;
				case 2:
					hero.sprite_x=8;
					if(hero.direction == LEFT)
					{
						SetRect( &hero.attacksquare, hero.x, hero.y, hero.x + 175, hero.y + 150);
					}
					else
					{
						SetRect( &hero.attacksquare, hero.x + 175, hero.y, hero.x + 350, hero.y + 150);
					}
					break;
				case 3:
					///// 공격 범위 초기화 해줌
					SetRect( &hero.attacksquare, 0, 0, 0, 0);
					hero.delayed=false;
					hero.sprite_x=6;
					hero.phase=0;
					break;
				}
				break;
			}
			else
			{
				if(hero.direction==LEFT)				{hero.sprite_y=5;}
				else									{hero.sprite_y=4;}

				hero.delayed = true;
				if (hero.time > 2)
				{
					hero.phase++;
					hero.time=0;
				}

				switch(hero.phase)
				{
				case 0:
					hero.sprite_x=0;
					break;
				case 1:
					hero.sprite_x=1;
					break;
				case 2:
					hero.sprite_x=2;
					if(hero.direction == LEFT)
					{
						SetRect( &hero.attacksquare, hero.x, hero.y, hero.x + 175, hero.y + 250);
					}
					else
					{
						SetRect( &hero.attacksquare, hero.x + 175, hero.y, hero.x + 350, hero.y + 250);
					}
					break;
				case 3:
					///// 공격 범위 초기화 해줌
					SetRect( &hero.attacksquare, 0, 0, 0, 0);
					hero.delayed=false;
					hero.sprite_x=0;
					hero.phase=0;
					break;
				}
				break;
			}
		}
		break;
	}

	/////////// 점프

	if(hero.falltime == 0 && hero.y + 250 < hero.ground)
	{
		hero.whilejumpup = false;
		hero.whilejumpdown = true;
	}
	if(hero.whilejumpup == true && (hero.combo[0] != SPACE))
	{
		hero.sprite_x = 3;
		if(hero.direction == LEFT)		hero.sprite_y = 3;
		else							hero.sprite_y = 2;
	}
	if(hero.whilejumpdown == true && (hero.combo[0] != SPACE))
	{
		hero.sprite_x = 4;
		if(hero.direction == LEFT)		hero.sprite_y = 3;
		else							hero.sprite_y = 2;
	}

	///// 스크롤 범위 넘어가면 원점

	if(hero.x < 0 && hero.moving_x < 0)
	{
		hero.moving_x = 0;
	}
	if(hero.x  > 1000 + 175 && hero.moving_x > 0)
	{
		hero.moving_x = 0;
	}


///////////////////////////////////////////////////////////////////////
	///////// 몬스터 상태에 따른 연산//////////////////
//////////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<monstercount;i++)
	{

		if(monster[i]->y + monster[i]->height != monster[i]->ground)
		{
			monster[i]->state = FALLING;
		}
		else
		{
			monster[i]->falltime = 0;
		}


		switch(monster[i]->state)
		{
		case IDLE:
			if(monster[i]->direction==LEFT)		{monster[i]->sprite_y=0;}
			else								{monster[i]->sprite_y=1;}

			if(monster[i]->time >= 5)
			{
				monster[i]->time = 0;
				monster[i]->sprite_x++;
			}
			if(monster[i]->sprite_x>3)
			{
				monster[i]->sprite_x=0;
			}
			break;
		case MOVE:
			switch(monster[i]->species)
			{
			case 0:
			case 1:
				if(monster[i]->direction==LEFT)
				{
					monster[i]->sprite_y=2;
					monster[i]->moving_x = -8 - rand()%4;
				}
				else
				{
					monster[i]->sprite_y=3;
					monster[i]->moving_x = 8 + rand()%4;
				}
				break;
			case 2:
				if(monster[i]->direction==LEFT)
				{
					monster[i]->sprite_y=4;
					monster[i]->moving_x = -8 - rand()%4;
				}
				else
				{
					monster[i]->sprite_y=5;
					monster[i]->moving_x = 8 + rand()%4;
				}
				break;
			case 3:
				if(monster[i]->direction==LEFT)
				{
					monster[i]->sprite_y=0;
					monster[i]->moving_x = -10 - rand()%4;
				}
				else
				{
					monster[i]->sprite_y=1;
					monster[i]->moving_x = 10 + rand()%4;
				}
				break;
			case 4:
				if(monster[i]->direction==LEFT)
				{
					monster[i]->sprite_y=0;
					monster[i]->moving_x = -10 - rand()%4;
				}
				else
				{
					monster[i]->sprite_y=1;
					monster[i]->moving_x = 10 + rand()%4;
				}
				break;
			}

			if(monster[i]->time > 4)
			{
				monster[i]->time = 0;
				monster[i]->sprite_x++;
			}
			if(monster[i]->sprite_x>2)
			{
				monster[i]->sprite_x=0;
			}
			break;
		case ATTACK:
			monster[i]->delayed=true;
			if(monster[i]->time > 3)
			{
				monster[i]->time = 0;
				monster[i]->phase++;
			}
			switch(monster[i]->species)
			{
			case 0:
			case 1:
				switch(monster[i]->phase)
				{
				case 0:
					if(monster[i]->direction==LEFT)		{monster[i]->sprite_y=8;}
					else								{monster[i]->sprite_y=9;}
					monster[i]->sprite_x = 0;
					break;
				case 1:
					monster[i]->sprite_x = 1;
					break;
				case 2:
					monster[i]->sprite_x = 2;
					break;
				case 3:
					monster[i]->sprite_x = 1;
					break;
				case 4:
					monster[i]->sprite_x = 2;
					break;
				case 5:
					if(monster[i]->direction==LEFT)		{monster[i]->sprite_y=4;}
					else								{monster[i]->sprite_y=5;}
					monster[i]->sprite_x = 0;
					break;
				case 6:
					monster[i]->sprite_x = 1;
					break;
				case 7:
					monster[i]->sprite_x = 2;
					if(monster[i]->direction == LEFT)
					{
						SetRect( &monster[i]->attacksquare, monster[i]->x, monster[i]->y + 80, monster[i]->x + 140, monster[i]->y + 250);
					}
					else
					{
						SetRect( &monster[i]->attacksquare, monster[i]->x + 210, monster[i]->y + 80, monster[i]->x + 350, monster[i]->y + 250);
					}
					break;
				case 8:
					SetRect( &monster[i]->attacksquare, 0, 0, 0, 0);
					monster[i]->delayed=false;
					monster[i]->sprite_x=0;
					monster[i]->phase=0;
					break;
				}
				break;
			case 2:
				switch(monster[i]->phase)
				{
				case 0:
				case 1:
				case 2:
					if(monster[i]->direction==LEFT)		{monster[i]->sprite_y=2;}
					else								{monster[i]->sprite_y=3;}
					monster[i]->sprite_x = 0;
					break;
				case 3:
					monster[i]->sprite_x = 1;
					break;
				case 4:
					monster[i]->sprite_x = 2;
					break;
				case 5:
					monster[i]->sprite_x = 3;
					if(monster[i]->direction == LEFT)
					{
						SetRect( &monster[i]->attacksquare, monster[i]->x+100, monster[i]->y + 200, monster[i]->x + 200, monster[i]->y + 350);
					}
					else
					{
						SetRect( &monster[i]->attacksquare, monster[i]->x + 300, monster[i]->y + 200, monster[i]->x + 400, monster[i]->y + 350);
					}
					break;
				case 6:
					SetRect( &monster[i]->attacksquare, 0, 0, 0, 0);
					monster[i]->delayed=false;
					monster[i]->sprite_x=0;
					monster[i]->phase=0;
					break;
				}
				break;
			case 3:				//일반 위습
				switch(monster[i]->phase)
				{
				case 0:
				case 1:
				case 2:
					if(monster[i]->direction==LEFT)		{monster[i]->sprite_y=2;}
					else								{monster[i]->sprite_y=3;}
					monster[i]->sprite_x = 0;
					break;
				case 3:
					monster[i]->sprite_x = 1;
					if(monster[i]->direction==LEFT)		{monster[i]->moving_x=-10;}
					else								{monster[i]->moving_x=10;}
					if(monster[i]->direction == LEFT)
					{
						SetRect( &monster[i]->attacksquare, monster[i]->x, monster[i]->y + 130, monster[i]->x + 300, monster[i]->y + 240);
					}
					else
					{
						SetRect( &monster[i]->attacksquare, monster[i]->x + 100, monster[i]->y + 130, monster[i]->x + 400, monster[i]->y + 240);
					}
					break;
				case 4:
					SetRect( &monster[i]->attacksquare, 0, 0, 0, 0);
					monster[i]->sprite_x = 2;
					if(monster[i]->direction==LEFT)		{monster[i]->moving_x=-20;}
					else								{monster[i]->moving_x=20;}
					break;
				case 5:
					monster[i]->sprite_x = 3;
					if(monster[i]->direction==LEFT)		{monster[i]->moving_x=-10;}
					else								{monster[i]->moving_x=10;}
					break;
				case 6:
					monster[i]->delayed=false;
					monster[i]->sprite_x=0;
					monster[i]->phase=0;
					break;
				}
				break;
			}
			break;

		case FALLING:
			monster[i]->delayed = true;
			monster[i]->immune = false;
			monster[i]->falltime++;
			if(monster[i]->y + monster[i]->height < monster[i]->ground)			{monster[i]->moving_y = monster[i]->falltime;}
			else if(monster[i]->y + monster[i]->height > monster[i]->ground)		{monster[i]->moving_y = -(monster[i]->y + monster[i]->height - monster[i]->ground);}
			else																											{monster[i]->falling = false; monster[i]->delayed = false;}
			break;

		case HITTED:
			switch(monster[i]->species)
			{
			case 0:
			case 1:
				if(monster[i]->herodirection==LEFT)	 {monster[i]->sprite_y=6;}
				else								 {monster[i]->sprite_y=7;}
				break;
			case 2:
				if(monster[i]->herodirection==LEFT)	 {monster[i]->sprite_y=6;}
				else								 {monster[i]->sprite_y=7;}
				break;
			case 3:
				if(monster[i]->herodirection==LEFT)	 {monster[i]->sprite_y=4;}
				else								 {monster[i]->sprite_y=5;}
				break;
			}

			SetRect( &monster[i]->attacksquare , 0, 0, 0, 0);
			monster[i]->delayed = true;
			if(monster[i]->time >= 3)
			{
				monster[i]->time = 0;
				monster[i]->phase++;
			}
			switch(monster[i]->phase)
			{
			case 0:
			case 2:
			case 4:
				monster[i]->sprite_x=0;
				break;
			case 1:
			case 3:
			case 5:
				monster[i]->sprite_x=1;
				break;
			case 6:
				monster[i]->immune = false;
				monster[i]->sprite_x=1;
				monster[i]->phase = 0;
				monster[i]->delayed = false;
				break;
			}
			break;


		case DEAD:
			if(monster[i]->herodirection==LEFT)	{monster[i]->sprite_y=6;}
			else								{monster[i]->sprite_y=7;}

			monster[i]->immune = true;
			monster[i]->delayed = true;
			

			if(monster[i]->time >= 3)
			{
				monster[i]->time = 0;
				monster[i]->phase++;
			}
			switch(monster[i]->phase)
			{
			case 1:
				for(int j=0;j<rand()%2+4;j++)
				{
					monster[i]->bigeffect.valid=true;
					monster[i]->m_b_bigeffect.m_bVisible=true;
					monster[i]->bigeffect.x = monster[i]->bodysquare.left-75;
					monster[i]->bigeffect.y = monster[i]->bodysquare.top-50;
					monster[i]->bigeffect.sprite_y = 0;
					monster[i]->bigeffect.sprite_x = rand()%6;

					monster[i]->star[j].valid=true;
					monster[i]->m_b_star.m_bVisible=true;
					monster[i]->star[j].ground = monster[i]->ground;
					monster[i]->star[j].x=(monster[i]->bodysquare.left + monster[i]->bodysquare.left) / 2;
					monster[i]->star[j].y=(monster[i]->bodysquare.top + monster[i]->bodysquare.bottom) / 2;
					monster[i]->star[j].moving_y = -20 - rand()%10;
					monster[i]->star[j].moving_x = -8 + rand()%16;
				}

			case 4:
			case 7:
			case 8:
			case 9:
				monster[i]->sprite_x=0;
				break;
			case 2:
			case 5:
				monster[i]->sprite_x=1;
				break;
			case 3:
			case 6:
				monster[i]->sprite_x=2;
				break;
			case 10:
				monster[i]->sprite_x=1;
				monster[i]->phase = 2;
				break;

			}
			break;
		}


	}


	for(int i=0;i<monstercount;i++)
	{
		if (monster[i]->effect.valid == true)
		{
			if (monster[i]->effect.time > 1)
			{
				//monster[i]->effect.sprite_y++;
				monster[i]->effect.phase++;
				monster[i]->effect.time=0;
			}
			switch(monster[i]->effect.phase)
			{
			case 0:
				monster[i]->effect.sprite_y = 0;
				break;
			case 1:
				monster[i]->effect.sprite_y = 1;
				break;
			case 2:
				monster[i]->effect.sprite_y = 2;
				break;
			case 3:
				monster[i]->effect.sprite_y = 3;
				break;
			case 4:
				monster[i]->effect.sprite_y = 4;
				break;
			case 5:
				monster[i]->effect.sprite_y = 5;
				break;
			case 6:
				monster[i]->effect.sprite_y = 0;
				monster[i]->effect.phase = 0;
				monster[i]->effect.valid = false;
				break;
			}
		}
		if (monster[i]->bigeffect.valid == true)
		{
			if (monster[i]->bigeffect.time > 0)
			{
				monster[i]->bigeffect.phase++;
				monster[i]->bigeffect.time=0;
			}
			switch(monster[i]->bigeffect.phase)
			{
			case 0:
				monster[i]->bigeffect.size = 1;
				break;
			case 1:
				monster[i]->bigeffect.size = 1.5;
				break;
			case 2:
				monster[i]->bigeffect.size = 2;
				break;
			case 3:
				monster[i]->bigeffect.size = 2.5;
				break;
			case 4:
				monster[i]->bigeffect.size = 3;
				break;
			case 5:
				monster[i]->bigeffect.size = 3.5;
				break;
			case 6:
				monster[i]->bigeffect.size = 1;
				monster[i]->bigeffect.phase = 0;
				monster[i]->bigeffect.valid = false;
				break;
			}
		}
		for(int j=0;j<5;j++)
		{			
			if(monster[i]->star[j].valid==true)
			{
				monster[i]->star[j].degree=rand()%100; //D3DXToRadian(rand()%100);
				//a=D3DXToRadian(e*1.f); // 90번=90도

				monster[i]->star[j].moving_y++;

				if(monster[i]->star[j].y > monster[i]->star[j].ground - 30)
				{
					monster[i]->star[j].moving_y = -monster[i]->star[j].moving_y * 4 / 5;
					monster[i]->star[j].moving_x = monster[i]->star[j].moving_x * 4 / 5;
				}

				if(hero.bodysquare.left <  monster[i]->star[j].x && hero.bodysquare.right >  monster[i]->star[j].x &&
					hero.bodysquare.bottom > monster[i]->star[j].y && hero.bodysquare.top <  monster[i]->star[j].y )
				{
					monster[i]->star[j].valid=false;
					HeroStat::star++;
				}


			}

			
		
		}


	}

	///////////////////////////////////////////////////////////
	//////////////보스몹////////////////////////////////
	////////////////////////////////////////////////////
	if(whatboss != 10)
	{
		if(boss->y + boss->height != boss->ground)
		{
			boss->state = FALLING;
		}
		else
	{
		boss->falltime = 0;
	}

		switch(boss->state)
		{
		case IDLE:
			if(boss->direction==LEFT)		{boss->sprite_y=0;}
			else							{boss->sprite_y=1;}

			if(boss->time >= 1)

			{
				boss->time = 0;
				boss->sprite_x++;
			}
			if(boss->sprite_x>3)
			{
				boss->sprite_x=0;
			}
			break;
		case MOVE:
			switch(boss->species)
			{
			case 11:
				if(boss->direction==LEFT)
				{
					boss->sprite_y=4;
					boss->moving_x = -8 - rand()%4;
				}
				else
				{
					boss->sprite_y=5;
					boss->moving_x = 8 + rand()%4;
				}
				break;
			case 12:
				if(boss->direction==LEFT)
				{
					boss->sprite_y=0;
					boss->moving_x = -10 - rand()%4;
				}
				else
				{
					boss->sprite_y=1;
					boss->moving_x = 10 + rand()%4;
				}
				break;
			case 13:
				if(boss->direction==LEFT)
				{
					boss->sprite_y=0;
					boss->moving_x = -10 - rand()%4;
				}
				else
				{
					boss->sprite_y=1;
					boss->moving_x = 10 + rand()%4;
				}
				break;
			case 14:
				if(boss->direction==LEFT)
				{
					boss->sprite_y=0;
					boss->moving_x = -10 - rand()%4;
				}
				else
				{
					boss->sprite_y=1;
					boss->moving_x = 10 + rand()%4;
				}
				break;
			}

			if(boss->time > 4)
			{
				boss->time = 0;
				boss->sprite_x++;
			}
			if(boss->sprite_x>2)
			{
				boss->sprite_x=0;
			}
			break;
		case ATTACK:
			boss->delayed=true;
			if(boss->time > 3)
			{
				boss->time = 0;
				boss->phase++;
			}
			switch(boss->species)
			{
			case 11:						/// 해머 고블린
				switch(boss->phase)
				{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
					if(boss->direction==LEFT)		{boss->sprite_y=2;}
					else								{boss->sprite_y=3;}
					boss->sprite_x = 0;
					break;
				case 5:
				case 6:
					boss->sprite_x = 1;
					break;
				case 7:
					boss->sprite_x = 2;
					break;
				case 8:
					boss->sprite_x = 3;
					if(boss->direction == LEFT)
					{
						SetRect( &boss->attacksquare, boss->x+100, boss->y + 200, boss->x + 200, boss->y + 350);
					}
					else
					{
						SetRect( &boss->attacksquare, boss->x + 300, boss->y + 200, boss->x + 400, boss->y + 350);
					}
					break;
				case 9:
					SetRect( &boss->attacksquare, 0, 0, 0, 0);
					boss->delayed=false;
					boss->sprite_x=0;
					boss->phase=0;
					break;
				}
				break;
			case 12:						///불쏘시기 위습
					switch(boss->phase)
					{
					case 0:
					case 1:
					case 2:
						if(boss->direction==LEFT)			{boss->sprite_y=6;}
						else								{boss->sprite_y=7;}
						boss->sprite_x = 0;
						break;
					case 3:
						boss->sprite_x = 1;
						break;
					case 4:
						boss->sprite_x = 2;
						break;
					case 5:
						boss->sprite_x = 3;
						break;
					case 6:
						boss->sprite_x = 4;
						if(boss->direction == LEFT)
						{
							SetRect( &boss->attacksquare, boss->x, boss->y, boss->x + 200, boss->y + 250);
						}
						else
						{
							SetRect( &boss->attacksquare, boss->x + 200, boss->y, boss->x + 400, boss->y + 250);
						}
						break;
					case 7:
						if(boss->direction==LEFT)			{boss->sprite_y=8;}
						else								{boss->sprite_y=9;}
						boss->sprite_x = 0;
						SetRect( &boss->attacksquare, 0, 0, 0, 0);
						break;
					case 8:
						boss->sprite_x = 1;
						break;
					case 9:
						boss->sprite_x = 2;
						break;
					case 10:
						boss->bosseffect.valid=true;
						m_b_bosseffect->m_bVisible=true;
						if(boss->direction == LEFT)
						{
							SetRect( &boss->attacksquare, boss->x-100, boss->y + 150, boss->x + 150, boss->y + 300);
						}
						else
						{
							SetRect( &boss->attacksquare, boss->x + 250, boss->y + 150, boss->x + 500, boss->y + 300);
						}
						boss->sprite_x = 3;
						break;
					case 11:
						SetRect( &boss->attacksquare, 0, 0, 0, 0);
						boss->sprite_x = 0;
						break;
					case 12:
						boss->sprite_x = 0;
						boss->delayed = false;
						boss->phase = 0;
						break;
					}
					break;
			case 13:					//// 초사이언 위습
					switch(boss->phase)
					{
					case 0:
					case 1:
					case 2:
						if(boss->direction==LEFT)			{boss->sprite_y=4;}
						else								{boss->sprite_y=5;}
						boss->sprite_x = 0;
						break;
					case 3:
						boss->sprite_x = 1;
						break;
					case 4:
						boss->sprite_x = 2;
						break;
					case 5:
						boss->sprite_x = 3;
						break;
					case 6:
						boss->bosseffect.valid=true;
						m_b_bosseffect->m_bVisible=true;
						boss->sprite_x = 4;
						if(boss->direction == LEFT)
						{
							SetRect( &boss->attacksquare, boss->x-350, boss->y + 150, boss->x + 150, boss->y + 300);
						}
						else
						{
							SetRect( &boss->attacksquare, boss->x + 250, boss->y + 150, boss->x + 750, boss->y + 300);
						}
						break;
					case 7:
						boss->sprite_x = 5;
						SetRect( &boss->attacksquare, 0, 0, 0, 0);
						break;
					case 8:
						boss->sprite_x = 0;
						boss->delayed = false;
						boss->phase = 0;
						break;
					}
					break;
			case 14:
				switch(boss->phase)
				{
				case 0:
				case 1:
					if(boss->direction==LEFT)		{boss->sprite_y=2;}
					else							{boss->sprite_y=3;}
					boss->sprite_x = 0;
					break;
				case 2:
					if(boss->direction==LEFT)		{boss->moving_x=-5;}
					else							{boss->moving_x=5;}
					boss->sprite_x = 1;
					break;
				case 3:
					if(boss->direction==LEFT)		{boss->moving_x=-10;}
					else							{boss->moving_x=10;}
					boss->sprite_x = 2;
					break;
				case 4:
					if(boss->direction==LEFT)		{boss->moving_x=-15;}
					else							{boss->moving_x=15;}
					boss->sprite_x = 3;
					break;
				case 5:
					if(boss->direction==LEFT)		{boss->moving_x=-5;}
					else							{boss->moving_x=5;}
					boss->sprite_x = 4;
					if(boss->direction == LEFT)
					{
						SetRect( &boss->attacksquare, boss->x + 200, boss->y + 200, boss->x + 600, boss->y + 600);
					}
					else
					{
						SetRect( &boss->attacksquare, boss->x + 600, boss->y + 200, boss->x + 1000, boss->y + 600);
					}
					break;
				case 6:
				case 7:
					boss->sprite_x=4;
					break;
				case 8:
					if(boss->direction==LEFT)		{boss->sprite_y=4;}
					else							{boss->sprite_y=5;}
					SetRect( &boss->attacksquare, 0, 0, 0, 0);
					boss->sprite_x=0;
					break;
				case 9:
					if(boss->direction==LEFT)		{boss->moving_x=-5;}
					else							{boss->moving_x=5;}
					boss->sprite_x=1;
					break;
				case 10:
					if(boss->direction==LEFT)		{boss->moving_x=-10;}
					else							{boss->moving_x=10;}
					boss->sprite_x=2;
					break;
				case 11:
					if(boss->direction==LEFT)		{boss->moving_x=-15;}
					else							{boss->moving_x=15;}
					boss->sprite_x=3;
					break;
				case 12:
					if(boss->direction==LEFT)		{boss->moving_x=-5;}
					else							{boss->moving_x=5;}
					boss->sprite_x=4;
					if(boss->direction == LEFT)
					{
						SetRect( &boss->attacksquare, boss->x + 200, boss->y + 400, boss->x + 600, boss->y + 600);
					}
					else
					{
						SetRect( &boss->attacksquare, boss->x + 600, boss->y + 400, boss->x + 1000, boss->y + 600);
					}
					break;
				case 13:
				case 14:
					boss->sprite_x=4;
					break;
				case 15:
					if(boss->direction==LEFT)		{boss->sprite_y=6;}
					else							{boss->sprite_y=7;}
					SetRect( &boss->attacksquare, 0, 0, 0, 0);
					if(boss->direction==LEFT)		{boss->moving_x=-5;}
					else							{boss->moving_x=5;}
					boss->sprite_x=0;
				case 16:
					boss->sprite_x=1;
					if(boss->direction==LEFT)		{boss->moving_x=-10;}
					else							{boss->moving_x=10;}
					break;
				case 17:
					boss->sprite_x=2;
					if(boss->direction == LEFT)
					{
						SetRect( &boss->attacksquare, boss->x + 0, boss->y + 400, boss->x + 500, boss->y + 550);
					}
					else
					{
						SetRect( &boss->attacksquare, boss->x + 700, boss->y + 400, boss->x + 1200, boss->y + 550);					}
					break;
				case 18:
					boss->sprite_x=2;					
					break;
				case 19:
					SetRect( &boss->attacksquare, 0, 0, 0, 0);
					boss->delayed=false;
					boss->sprite_x=0;
					boss->phase=0;
					break;
				}
				break;
			}
			break;

		case HITTED:
			SetRect( &boss->attacksquare , 0, 0, 0, 0);
			boss->delayed = false;
			break;
		case FALLING:
			boss->delayed = true;
			boss->immune = false;
			boss->falltime++;

			if(boss->time > 4)
			{
				boss->time = 0;
				boss->sprite_x++;
			}
			if(boss->y + boss->height < boss->ground)									{boss->moving_y = boss->falltime;}
			else if(boss->y + boss->height > boss->ground)								{boss->moving_y = -(boss->y + boss->height - boss->ground);}
			else																		{boss->falling = false; boss->delayed = false;}
			break;

		case DEAD:
			if(boss->herodirection==LEFT)		{boss->sprite_y=6;}
			else								{boss->sprite_y=7;}

			boss->immune = true;
			boss->delayed = true;


			if(boss->time >= 4)
			{
				boss->time = 0;
				boss->phase++;
			}
			switch(boss->phase)
			{
			case 1:
				for(int j=3;j<rand()%2+4;j++)
				{
					boss->bigeffect.valid=true;
					boss->m_b_bigeffect.m_bVisible=true;
					boss->bigeffect.x = boss->bodysquare.left-75;
					boss->bigeffect.y = boss->bodysquare.top-50;
					boss->bigeffect.sprite_y = 0;
					boss->bigeffect.sprite_x = rand()%6;

					boss->star[j].valid=true;
					boss->m_b_star.m_bVisible=true;
					boss->star[j].ground = boss->ground;
					boss->star[j].x=(boss->bodysquare.left + boss->bodysquare.left) / 2;
					boss->star[j].y=(boss->bodysquare.top + boss->bodysquare.bottom) / 2;
					boss->star[j].moving_y = -20 - rand()%10;
					boss->star[j].moving_x = -8 + rand()%16;
				}

			case 2:
			case 6:
			case 10:
			case 11:
				boss->sprite_x=0;
				break;
			case 3:
			case 7:
				boss->sprite_x=1;
				break;
			case 4:
			case 8:
				boss->sprite_x=2;
				break;
			case 5:
			case 9:
				boss->sprite_x=200;
				break;
			case 12:
				boss->sprite_x= 200;
				boss->phase = 100;
				break;

			}
			break;
		}

		if(boss->bosseffect.valid==true)
		{
			boss->bosseffect.sprite_x = 0;
			if (whatboss==12)
			{
				if(boss->direction == LEFT)					
				{boss->bosseffect.sprite_y = 1;}
				else										
				{boss->bosseffect.sprite_y = 0;}
				switch(boss->bosseffect.phase)
				{
				case 0:
					boss->bosseffect.sprite_x = 0;
					break;
				case 1:
					boss->bosseffect.sprite_x = 1;
					break;
				case 2:
					boss->bosseffect.sprite_x = 2;
					break;
				case 3:
					boss->bosseffect.sprite_x = 3;
					break;
				case 4:
					boss->bosseffect.sprite_x = 4;
					break;
				case 5:
					boss->bosseffect.sprite_x = 5;
					break;
				case 6:
					boss->bosseffect.sprite_x = 6;
					break;
				case 7:
					boss->bosseffect.sprite_x = 7;
					break;
				case 8:
					boss->bosseffect.sprite_x = 8;
					break;
				case 9:
					boss->bosseffect.sprite_x =9;
					boss->bosseffect.phase = 0;
					boss->bosseffect.valid = false;
					break;
				}
			}
			else if(whatboss==13)
			{		
				if(boss->direction == LEFT)					
				{
					boss->bosseffect.sprite_y = 0;
					switch(boss->bosseffect.phase)
					{
					case 0:
						boss->bosseffect.sprite_x = 0;
						break;
					case 1:
						boss->bosseffect.sprite_x = 1;
						break;
					case 2:
						boss->bosseffect.sprite_x = 2;
						break;
					case 3:
						boss->bosseffect.sprite_x = 3;
						break;
					case 4:
						boss->bosseffect.sprite_x = 4;
						break;
					case 5:
						boss->bosseffect.sprite_x = 5;
						break;
					case 6:
						boss->bosseffect.sprite_x = 6;
						break;
					case 7:
						boss->bosseffect.sprite_x = 7;
						break;
					case 8:
						boss->bosseffect.sprite_x = 8;
						break;
					case 9:
						boss->bosseffect.sprite_x =9;
						boss->bosseffect.phase = 0;
						boss->bosseffect.valid = false;
						break;
					}
				}
				else										
				{
					boss->bosseffect.sprite_y = 1;
					switch(boss->bosseffect.phase)
					{
					case 0:
						boss->bosseffect.sprite_x = 9;
						break;
					case 1:
						boss->bosseffect.sprite_x = 8;
						break;
					case 2:
						boss->bosseffect.sprite_x = 7;
						break;
					case 3:
						boss->bosseffect.sprite_x = 6;
						break;
					case 4:
						boss->bosseffect.sprite_x = 5;
						break;
					case 5:
						boss->bosseffect.sprite_x = 4;
						break;
					case 6:
						boss->bosseffect.sprite_x = 3;
						break;
					case 7:
						boss->bosseffect.sprite_x = 2;
						break;
					case 8:
						boss->bosseffect.sprite_x = 1;
						break;
					case 9:
						boss->bosseffect.sprite_x =0;
						boss->bosseffect.phase = 0;
						boss->bosseffect.valid = false;
						break;
					}
				}

			}
			else if(whatboss==15)
			{
				if(boss->direction == LEFT)					
				{
					boss->bosseffect.sprite_x = 0;
					switch(boss->bosseffect.phase)
					{
					case 0:
						boss->bosseffect.sprite_y = 0;
						break;
					case 1:
						boss->bosseffect.sprite_y = 1;
						break;
					case 2:
						boss->bosseffect.sprite_y = 2;
						boss->bosseffect.phase = 0;
						boss->bosseffect.valid = false;
						break;
					}
				}
				else										
				{
					boss->bosseffect.sprite_x = 0;
					switch(boss->bosseffect.phase)
					{
					case 0:
						boss->bosseffect.sprite_y = 0;
						break;
					case 1:
						boss->bosseffect.sprite_y = 1;
						break;
					case 2:
						boss->bosseffect.sprite_y = 2;
						boss->bosseffect.phase = 0;
						boss->bosseffect.valid = false;
						break;
					}
				}

			}
			if(boss->bosseffect.time >1)
			{
				boss->bosseffect.phase++;
				boss->bosseffect.time=0;
			}
		}

		////보스 이펙트
		if(boss->effect.valid == true)
		{
			if (boss->effect.time > 1)
			{
				//monster[i]->effect.sprite_y++;
				boss->effect.phase++;
				boss->effect.time=0;
			}
			switch(boss->effect.phase)
			{
			case 0:
				boss->effect.sprite_y = 0;
				break;
			case 1:
				boss->effect.sprite_y = 1;
				break;
			case 2:
				boss->effect.sprite_y = 2;
				break;
			case 3:
				boss->effect.sprite_y = 3;
				break;
			case 4:
				boss->effect.sprite_y = 4;
				break;
			case 5:
				boss->effect.sprite_y = 5;
				break;
			case 6:
				boss->effect.sprite_y = 0;
				boss->effect.phase = 0;
				boss->effect.valid = false;
				break;
			}
		}
		if (boss->bigeffect.valid == true)
		{
			if (boss->bigeffect.time > 0)
			{
				boss->bigeffect.phase++;
				boss->bigeffect.time=0;
			}
			switch(boss->bigeffect.phase)
			{
			case 0:
				boss->bigeffect.size = 1;
				break;
			case 1:
				boss->bigeffect.size = 1.5;
				break;
			case 2:
				boss->bigeffect.size = 2;
				break;
			case 3:
				boss->bigeffect.size = 2.5;
				break;
			case 4:
				boss->bigeffect.size = 3;
				break;
			case 5:
				boss->bigeffect.size = 3.5;
				break;
			case 6:
				boss->bigeffect.size = 1;
				boss->bigeffect.phase = 0;
				boss->bigeffect.valid = false;
				break;
			}
		}
		for(int j=0;j<5;j++)
		{			
			if(boss->star[j].valid==true)
			{
				boss->star[j].degree=rand()%100; //D3DXToRadian(rand()%100);
				//a=D3DXToRadian(e*1.f); // 90번=90도

				boss->star[j].moving_y++;

				if(boss->star[j].y > boss->star[j].ground - 30)
				{
					boss->star[j].moving_y = -boss->star[j].moving_y * 4 / 5;
					boss->star[j].moving_x = boss->star[j].moving_x * 4 / 5;
				}

				if(hero.bodysquare.left <  boss->star[j].x && hero.bodysquare.right >  boss->star[j].x &&
					hero.bodysquare.bottom > boss->star[j].y && hero.bodysquare.top <  boss->star[j].y )
				{
					boss->star[j].valid=false;
					HeroStat::star++;
				}


			}

			
		
		}


}




	///// 이전 행동을 지금의 행동으로 바꿔줌//
	hero.prestate=hero.combo[0];


	///////////////////////
	///// 마지막 연산 //////
	///////////////////////

	///// 최종 위치 확정

	for(int i=0;i<monstercount;i++)
	{
		monster[i]->x += monster[i]->moving_x;
		monster[i]->y += monster[i]->moving_y;
		for(int j=0;j<5;j++)
		{
			monster[i]->star[j].x += monster[i]->star[j].moving_x;
			monster[i]->star[j].y += monster[i]->star[j].moving_y;
		}

	}
	if(whatboss != 10)
	{
		boss->x += boss->moving_x;
		boss->y += boss->moving_y;
		for(int j=0;j<5;j++)
		{
			boss->star[j].x += boss->star[j].moving_x;
			boss->star[j].y += boss->star[j].moving_y;
		}
	}
	hero.x += hero.moving_x;
	hero.y += hero.moving_y;

	///// 변화값만큼 몸사각형을 이동 시켜줌

	for (int i=0;i<monstercount;i++)
	{
		OffsetRect(&monster[i]->bodysquare, monster[i]->moving_x, monster[i]->moving_y);
	}
	if(boss != NULL)  OffsetRect(&boss->bodysquare, boss->moving_x, boss->moving_y);
	OffsetRect(&hero.bodysquare, hero.moving_x, hero.moving_y);


	///////  스크롤
	if(hero.x > 500 && hero.x < 1000)
	{
		hero.screen_x = hero.x - 500;
	}
	else if(hero.x < 500)
	{
		hero.screen_x = 0;
	}
	else if(hero.x > 1000)
	{
		hero.screen_x = 500;
	}
	
	hero.screen_y = hero.y - 465;


	// 이것은 임시로 해둔 것. 이거땜에 버그가 생길 수도 잇음.
	for (int i=0;i<monstercount;i++)
	{
		monster[i]->moving_x = 0;
		monster[i]->moving_y = 0;
	}
	if(boss!=NULL)
	{
		boss->moving_x = 0;
		boss->moving_y = 0;
	} 
	if(hero.delayed==false)
	{	
		hero.moving_x = 0;
		hero.moving_y = 0;
	}
}

void Battle::AfterCalculate()
{
	int i;
	if(HeroStat::hp <= 0)	hero.state = DEAD;
	if(whatboss!=10)
	{
		for(i=0;i<monstercount;i++)
		{
			if(boss->state != DEAD || (monster[i]->state != DEAD && monster[i]->phase != 10) )	break;
		}
	}
	else
	{
		for(i=0;i<monstercount;i++)
		{
			if((monster[i]->state != DEAD && monster[i]->phase != 10) )	break;
		}
	}
	if(i==monstercount)
		endtime++;
	if(endtime==150)
		whilebattle = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Battle::Ending(int &m_iCurrentState)
{

	initialized = false;

	
	for(int i=0;i<monstercount; i++)
	{
		monster[i]->m_b_bigeffect.m_Texture->Release();
		monster[i]->m_b_effect.m_Texture->Release();
		monster[i]->m_b_star.m_Texture->Release();

 		delete monster[i];
	}
 	delete monster;

	if(whatboss != 10)
	{
		m_b_boss->m_Texture->Release();
		delete m_b_boss;
		m_b_bosseffect->m_Texture->Release();
		delete m_b_bosseffect;
		delete boss;
	}


	for(int i=0;i<highspecies; i++)
	{
		m_b_monster[i]->m_Texture->Release();
		delete m_b_monster[i];
	}
 	delete m_b_monster;

	if(hero.state==DEAD)
	{
		m_iCurrentState = 4;
	}
	else
	{
		m_iCurrentState = 1;
	}
}

void Battle::initializing2()
{
	//BG1
	m_b_BG.m_bVisible = true;
	m_b_BG.m_rSource.right = 2250;
	m_b_BG.m_rSource.bottom = 2250;

	m_b_BG.m_vPosition.x = 0;
	m_b_BG.m_vPosition.y = 0;
	m_b_BG.m_vPosition.z = 0;

	m_b_BG.CreateTextureFromFile( "bb.jpg", &(m_b_BG.m_Texture) );

	//BG_Road
	m_b_BG_Road.m_bVisible = true;
	m_b_BG_Road.m_rSource.right = 2250;
	m_b_BG_Road.m_rSource.bottom = 2250;

	m_b_BG_Road.m_vPosition.x = 0;
	m_b_BG_Road.m_vPosition.y = 0;
	m_b_BG_Road.m_vPosition.z = 0;

	m_b_BG_Road.CreateTextureFromFile( "fb.png", &(m_b_BG_Road.m_Texture) );

	//HERO
	m_b_hero.m_bVisible = true;
	m_b_hero.m_rSource.left = 0;
	m_b_hero.m_rSource.top = 0;
	m_b_hero.m_rSource.right = 2250;
	m_b_hero.m_rSource.bottom = 2250;

	m_b_hero.m_vPosition.x = 0;//hero.screen_x;
	m_b_hero.m_vPosition.y = 0;//hero.screen_y;
	m_b_hero.m_vPosition.z = 0;

	m_b_hero.CreateTextureFromFile( "hero.png", &(m_b_hero.m_Texture) );

	//BG_Rock
	m_b_BG_Rock.m_bVisible = true;
	m_b_BG_Rock.m_rSource.right = 2250;
	m_b_BG_Rock.m_rSource.bottom = 2250;

	m_b_BG_Rock.m_vPosition.x = 0;
	m_b_BG_Rock.m_vPosition.y = 0;
	m_b_BG_Rock.m_vPosition.z = 0;


	m_b_BG_Rock.CreateTextureFromFile( "fb_rock.png", &(m_b_BG_Rock.m_Texture) );

	//hpball

	hpball.Initialize();
	emptyball.Initialize();

	m_b_hpball.m_bVisible = true;
	m_b_hpball.m_rSource.left = 0;
	m_b_hpball.m_rSource.top = 0;
	m_b_hpball.m_rSource.right = 30;
	m_b_hpball.m_rSource.bottom = 29;

	m_b_emptyball.m_bVisible = true;
	m_b_emptyball.m_rSource.left = 0;
	m_b_emptyball.m_rSource.top = 0;
	m_b_emptyball.m_rSource.right = 30;
	m_b_emptyball.m_rSource.bottom = 29;

	m_b_hpball.m_vPosition.x = 0;
	m_b_hpball.m_vPosition.y = 0;
	m_b_hpball.m_vPosition.z = 0;

	m_b_emptyball.m_vPosition.x = 0;
	m_b_emptyball.m_vPosition.y = 0;
	m_b_emptyball.m_vPosition.z = 0;

	m_b_hpball.CreateTextureFromFile( "hpball.png", &(m_b_hpball.m_Texture) );

	m_b_emptyball.CreateTextureFromFile( "emptyball.png", &(m_b_emptyball.m_Texture) );


	m_b_hpbar.m_bVisible = true;
	m_b_hpbar.m_rSource.left = 0;
	m_b_hpbar.m_rSource.top = 0;
	m_b_hpbar.m_rSource.right = 500;
	m_b_hpbar.m_rSource.bottom = 500;
	m_b_hpbar.CreateTextureFromFile( "hpbar.png", &(m_b_hpbar.m_Texture) );

	mustinit = true;
}

Battle::Battle()
{
	mustinit = false;
}

