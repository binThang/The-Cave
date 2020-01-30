#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "StateMachine.h"
#include "DirectX.h"
#include "AllManage.h"

class CDirectSound;

#define APP_NAME  "The Cave"

#define	HEIGHT 768
#define WIDTH 1024

class Main
{
private:
	HWND					g_hWnd;
	DWORD					frame;
	DWORD					timet;
	
	CDirectSound			*pDSnd;

public:
							Main()		{	g_hWnd = NULL;	}
	static Main&			GetInstance();
	HWND					getHWND()	{	return g_hWnd;	}
	CDirectX*				GetDX()		{	return &m_dx;	}
	int WINAPI				WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	static LRESULT CALLBACK	WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	StateMachine			m_StateMachine;
	CDirectX				m_dx;

	void					Render();
	void					Update();
	void					init();

	CDirectSound* Get_DSound(){return pDSnd;}
};
