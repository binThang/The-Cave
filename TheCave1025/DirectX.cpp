#include "DirectX.h"

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT CDirectX::InitD3D( HWND hWnd )
{
	// Create the D3D object, which is needed to create the D3DDevice.
	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	// Set up the structure used to create the D3DDevice. Most parameters are
	// zeroed out. We set Windowed to TRUE, since we want to do D3D in a
	// window, and then set the SwapEffect to "discard", which is the most
	// efficient method of presenting the back buffer to the display.  And 
	// we request a back buffer format that matches the current desktop display 
	// format.

	D3DDISPLAYMODE d3ddm;
	if( FAILED( g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT,
		&d3ddm )))
		return E_FAIL;

	// Parameters for the D3DDevice. Most parameters are zero'd out.
	// This sets the video format to match the current desktop display.
	// Check docs for other options you can set here, such as
	// 'Windowed' which would create a window-based app (not full screen)

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferWidth = 1024;
	d3dpp.BackBufferHeight = 768;
	//d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	// Create the Direct3D device. Here we are using the default adapter (most
	// systems only have one, unless they have multiple graphics hardware cards
	// installed) and requesting the HAL (which is saying we want the hardware
	// device rather than a software one). Software vertex processing is 
	// specified since we know it will work on all cards. On cards that support 
	// hardware vertex processing, though, we would see a big performance gain 
	// by specifying hardware vertex processing.
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		return E_FAIL;
	}

	if( FAILED( D3DXCreateSprite( g_pd3dDevice, &m_pd3dxSprite ) ) )
		return false;

	// Device state would normally be set here

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID CDirectX::CleanUp()
{
	if( g_pd3dDevice != NULL) 
	{
		g_pd3dDevice->Release();
		g_pd3dDevice=NULL;
	}

	if( g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D=NULL;
	}

	if( m_pd3dxSprite != NULL)
	{
		m_pd3dxSprite->Release();
		m_pd3dxSprite=NULL;
	}
}


HRESULT CDirectX::BeginScene()
{
	HRESULT r;

	if( NULL == g_pd3dDevice || m_pd3dxSprite == NULL )
		return FALSE;

	// Clear the backbuffer to a blue color
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

	if ( SUCCEEDED( r=g_pd3dDevice->BeginScene() ) )
		m_pd3dxSprite->Begin(D3DXSPRITE_ALPHABLEND);

	return r;
}

void CDirectX::EndScene()
{
	if( NULL == g_pd3dDevice || m_pd3dxSprite == NULL )
		return;

	m_pd3dxSprite->End();
	g_pd3dDevice->EndScene();

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}



