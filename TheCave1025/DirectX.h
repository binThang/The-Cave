#pragma once

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>


class CDirectX
{
protected:
	LPDIRECT3D9             g_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9       g_pd3dDevice; // Our rendering device
	LPD3DXSPRITE			m_pd3dxSprite; // 스프라이트 변수. (전체를 총괄하는 느낌의.)

public:
	LPDIRECT3D9				GetD3D() { return g_pD3D; };
	LPDIRECT3DDEVICE9		GetD3DDevice() { return g_pd3dDevice; };
	LPD3DXSPRITE			GetD3DXSprite() { return m_pd3dxSprite; };
	HRESULT 				InitD3D( HWND hWnd );
	HRESULT 				BeginScene();
	void 					EndScene();
	void 					CleanUp();
};