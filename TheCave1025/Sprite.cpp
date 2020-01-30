#include "Sprite.h"
#include "Main.h"

Sprite::Sprite()
{
	m_vCenter.x = 0;
	m_vCenter.y = 0;
	m_vCenter.z = 0;
	m_bVisible=false;
}

void Sprite::Draw()
{	
	if( m_bVisible == true )
		Main::GetInstance().GetDX()->GetD3DXSprite()->Draw( m_Texture, &m_rSource, &m_vCenter, &m_vPosition, 0xffffffff );

	
}

void Sprite::Draw(int _alpha)
{	
	if( m_bVisible == true )
		Main::GetInstance().GetDX()->GetD3DXSprite()->Draw( m_Texture, &m_rSource, &m_vCenter, &m_vPosition, D3DCOLOR_RGBA(255,255,255,_alpha) );
}


void Sprite::CreateTextureFromFile( char* path, LPDIRECT3DTEXTURE9* pTexture )
{
	D3DXCreateTextureFromFileEx( Main::GetInstance().GetDX()->GetD3DDevice(), path, 
		D3DX_DEFAULT_NONPOW2 , D3DX_DEFAULT_NONPOW2 ,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, pTexture);
}

void Sprite::SetTransform(D3DXMATRIX* matrix)
{
	Main::GetInstance().GetDX()->GetD3DXSprite()->SetTransform(matrix);
}
