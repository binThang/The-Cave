#include "LvUpState.h"
#include "HeroStat.h"

void LvUp::init()
{
	for (int i=0; i<7; i++)
	{
		LvUpBG[i].m_bVisible = true;

		LvUpBG[i].m_rSource.left = 0;
		LvUpBG[i].m_rSource.top = 0;
		LvUpBG[i].m_rSource.right = 1024;
		LvUpBG[i].m_rSource.bottom = 768;
	
		LvUpBG[i].m_vPosition.x = 0;
		LvUpBG[i].m_vPosition.y = 0;
		LvUpBG[i].m_vPosition.z = 0;
	}
	LvUpBG[0].CreateTextureFromFile( "12.png", &(LvUpBG[0].m_Texture) );
	LvUpBG[1].CreateTextureFromFile( "23.png", &(LvUpBG[1].m_Texture) );
	LvUpBG[2].CreateTextureFromFile( "34.png", &(LvUpBG[2].m_Texture) );
	LvUpBG[3].CreateTextureFromFile( "45.png", &(LvUpBG[3].m_Texture) );
	LvUpBG[4].CreateTextureFromFile( "56.png", &(LvUpBG[4].m_Texture) );
	LvUpBG[5].CreateTextureFromFile( "67.png", &(LvUpBG[5].m_Texture) );
	LvUpBG[6].CreateTextureFromFile( "78.png", &(LvUpBG[6].m_Texture) );

}

void LvUp::Update(int &m_iCurrentState)
{
	if (!ifinit)
	{
		init();
		ifinit = true;
	}
	if (GetKeyState(VK_SPACE) & 0x8000){
		m_iCurrentState = 1;
		HeroStat::hp += 1;
		HeroStat::attack += 0.5;
	}
}

void LvUp::Render()
{
	switch(HeroStat::level)
	{
	case 2:
		LvUpBG[0].Draw();
		break;
	case 3:
		LvUpBG[1].Draw();
		break;
	case 4:
		LvUpBG[2].Draw();
		break;
	case 5:
		LvUpBG[3].Draw();
		break;
	case 6:
		LvUpBG[4].Draw();
		break;
	case 7:
		LvUpBG[5].Draw();
		break;
	case 8:
		LvUpBG[6].Draw();
		break;
 	}
}

void LvUp::release()
{
}
