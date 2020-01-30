#include "MenuState.h"

void Menu::Update(int &m_iCurrentState, int &m_iCurrentStage)
{
	//첫화면에서 키를 누르면
	if (GetKeyState(VK_SPACE) & 0x8000 && timet==0)
		BBG.m_bVisible = false;

	//두번째 메뉴화면에서
	if (!BBG.m_bVisible)
	{
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && !(select==2) && !RIGHTKEYPRESS && timet==0){
			select++;
			RIGHTKEYPRESS = true;
			timet = TERM;
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000 && !(select==0) && !LEFTKEYPRESS && timet==0){
			select--;
			LEFTKEYPRESS = true;
			timet = TERM;
		}

		//선택
		if (GetAsyncKeyState(VK_SPACE) & 0x8000){
			if(select==1)
				m_iCurrentState = 1;
			if(select==2)
				AllManager::GameON = false;
		}

	}
	if (select == 0)
	{
		Button.m_rSource.top = 150;
		Button.m_rSource.bottom = 300;
	}
	if (select == 1)
	{
		Button.m_rSource.top = 0;
		Button.m_rSource.bottom = 150;
	}
	if (select == 2)
	{
		Button.m_rSource.top = 300;
		Button.m_rSource.bottom = 450;
	}

	RIGHTKEYPRESS = false;
	LEFTKEYPRESS = false;

	timet--;
	if (timet <= 0)
		timet = 0;
}

void Menu::Render()
{

	BG.Draw();
	Button.Draw();
	BBG.Draw();
}

void Menu::init()
{
	select = 0;
	timet = TERM;

	//BG
	BG.m_bVisible = true;

	BG.m_rSource.left = 0;
	BG.m_rSource.top = 0;
	BG.m_rSource.right = 1024;
	BG.m_rSource.bottom = 768;

	BG.m_vPosition.x = 0;
	BG.m_vPosition.y = 0;
	BG.m_vPosition.z = 0;
	BG.CreateTextureFromFile( "Menu.png", &(BG.m_Texture) );

	//Button
	Button.m_bVisible = true;

	Button.m_rSource.left = 0;
	Button.m_rSource.top = 0;
	Button.m_rSource.right = 500;
	Button.m_rSource.bottom = 150;

	Button.m_vPosition.x = 450;
	Button.m_vPosition.y = 465;
	Button.m_vPosition.z = 0;
	Button.CreateTextureFromFile( "MenuButton.png", &(Button.m_Texture) );

	//BBG
	BBG.m_bVisible = true;

	BBG.m_rSource.left = 0;
	BBG.m_rSource.top = 0;
	BBG.m_rSource.right = 1024;
	BBG.m_rSource.bottom = 768;

	BBG.m_vPosition.x = 0;
	BBG.m_vPosition.y = 0;
	BBG.m_vPosition.z = 0;
	BBG.CreateTextureFromFile( "BeforeMenu.png", &(BBG.m_Texture) );

}
