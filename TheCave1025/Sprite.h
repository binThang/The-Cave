#pragma once

#include <Windows.h>
#include "DirectX.h"

class Sprite
{
public:
	Sprite();
	void					Draw();
	void					Draw(int _alpha);
	void					CreateTextureFromFile( char* path, LPDIRECT3DTEXTURE9* pTexture );
	void					SetTransform(D3DXMATRIX* matrix);

	bool					m_bVisible;
	RECT					m_rSource;
	D3DXVECTOR3				m_vPosition;
	D3DXVECTOR3				m_vCenter;

	LPDIRECT3DTEXTURE9		m_Texture;
};