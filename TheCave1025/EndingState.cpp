#include "EndingState.h"

Ending::Ending()
{
	scene = 0;
	ifinit = false;
}

void Ending::init()
{
	for(int i=0; i<3; i++){
		EndBG[i].m_bVisible = true;
	
		EndBG[i].m_rSource.left = 0;
		EndBG[i].m_rSource.top = 0;
		EndBG[i].m_rSource.right = 1024;
		EndBG[i].m_rSource.bottom = 768;

		EndBG[i].m_vPosition.x = 0;
		EndBG[i].m_vPosition.y = 0;
		EndBG[i].m_vPosition.z = 0;
	}
	EndBG[0].CreateTextureFromFile( "엔딩1.png", &(EndBG[0].m_Texture) );
	EndBG[1].CreateTextureFromFile( "엔딩2.png", &(EndBG[1].m_Texture) );
	EndBG[2].CreateTextureFromFile( "엔딩3.png", &(EndBG[2].m_Texture) );
}

void Ending::Update()
{
	if(!ifinit)
	{
		init();
		ifinit = true;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && timet==0){
		if(scene==2)
			AllManager::GameON = false;
		scene++;
		timet = TERM + 3;
	}

	timet--;
	if (timet <= 0)
		timet = 0;
}

void Ending::Render()
{
	if (scene == 0)
		EndBG[0].Draw();
	else if(scene == 1)
		EndBG[1].Draw();
	else if(scene == 2)
		EndBG[2].Draw();
		
	
}