#include "Main.h"
#include "DXSound.h"

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------


Main& Main::GetInstance()
{
	static Main instance;
	return instance;
}

int WINAPI Main::WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow )
{
	WNDCLASSEX winClass; 
	MSG        uMsg;

	memset(&uMsg,0,sizeof(uMsg));

	winClass.lpszClassName = APP_NAME;
	winClass.cbSize        = sizeof(WNDCLASSEX);
	winClass.style         = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc   = WindowProc;
	winClass.hInstance     = hInstance;
	winClass.hIcon	       = NULL;
	winClass.hIconSm	   = NULL;
	winClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName  = NULL;
	winClass.cbClsExtra    = 0;
	winClass.cbWndExtra    = 0;

	if( !RegisterClassEx(&winClass) )
		return E_FAIL;

	g_hWnd = CreateWindowEx(NULL, APP_NAME, 
							APP_NAME,
							WS_OVERLAPPEDWINDOW,//WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
							CW_USEDEFAULT, 0, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

	if( g_hWnd == NULL )
		return E_FAIL;


	ShowWindow( g_hWnd, nCmdShow );
	UpdateWindow( g_hWnd );
	//sound
	pDSnd = new CDirectSound(g_hWnd);
	pDSnd->SetWavSize(14);	//0은 사용 안한다.사용하는 WAV파일 갯수 등록
	pDSnd->LoadWav(SOUND_N_F_WALK1_FILE,SOUND_N_F_WALK1);
	pDSnd->LoadWav(SOUND_N_F_WALK2_FILE,SOUND_N_F_WALK2);
	pDSnd->LoadWav(SOUND_CAVE1_FILE,SOUND_CAVE1);
	pDSnd->LoadWav(SOUND_CAVE2_FILE,SOUND_CAVE2);
	//
	pDSnd->LoadWav(SOUND_RED_WS_FILE,SOUND_RED_WS);
	pDSnd->LoadWav(SOUND_BLUE_WS_FILE,SOUND_BLUE_WS);
	pDSnd->LoadWav(SOUND_BOSS_EL_ATK_FILE,SOUND_BOSS_EL_ATK);
	pDSnd->LoadWav(SOUND_BOSS_BGM_FILE,SOUND_BOSS_BGM);
	pDSnd->LoadWav(SOUND_DASH_FILE,SOUND_DASH);
// 	pDSnd->LoadWav(SOUND_CH_BOSS_ATK_FILE,SOUND_CH_BOSS_ATK);
// 	
// 
// 	pDSnd->LoadWav(SOUND_CH_RGBL_ATK_FILE,SOUND_CH_RGBL_ATK);
// 	pDSnd->LoadWav(SOUND_CH_SPEARGBL_ATK_FILE,SOUND_CH_SPEARGBL_ATK);
// 	pDSnd->LoadWav(SOUND_CH_WS_ATK_FILE,SOUND_CH_WS_ATK);
	pDSnd->LoadWav(SOUND_YELLOW_WS_FILE,SOUND_YELLOW_WS);


	m_dx.InitD3D( g_hWnd );

	m_StateMachine.init( g_hWnd );

	while( uMsg.message != WM_QUIT )
	{
		if( PeekMessage( &uMsg, NULL, 0, 0, PM_REMOVE ) )
		{ 
			TranslateMessage( &uMsg );
			DispatchMessage( &uMsg );
		}
		else
		{
			timet = timeGetTime();
			Update();
			Render();
			frame = timeGetTime() - timet;
			if (frame < 1000 / 45)
			{
				Sleep( (1000 / 45) - frame);
			}
		}
	}
	UnregisterClass( APP_NAME, winClass.hInstance );

	return uMsg.wParam;
}
//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------

LRESULT CALLBACK Main::WindowProc( HWND hWnd,UINT iMessage, WPARAM wParam, LPARAM lParam )
{
	static POINT ptLastMousePosit;
	static POINT ptCurrentMousePosit;
	static bool bMousing;
	
	if (!AllManager::GameON)
		PostQuitMessage(0);

    switch( iMessage )
	{	
		case WM_CLOSE:
		{
			PostQuitMessage(0);
		}
		break;
        case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
        break;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}

void Main::Render()
{
	// Clear the backbuffer to a blue color
	GetDX()->GetD3DDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 1.0f, 0 );

	// Begin the scene
	if( SUCCEEDED( GetDX()->GetD3DDevice()->BeginScene() ) )
	{
		GetDX()->GetD3DXSprite()->Begin(D3DXSPRITE_ALPHABLEND);

		//////////////////////////////////////////////////////
		m_StateMachine.Render();				/**********///
		//////////////////////////////////////////////////////
		GetDX()->GetD3DXSprite()->End();

		// End the scene
		GetDX()->GetD3DDevice()->EndScene();
	}

	// Present the backbuffer contents to the display
	GetDX()->GetD3DDevice()->Present( NULL, NULL, NULL, NULL );
}

void Main::Update()
{
	m_StateMachine.Update();
}