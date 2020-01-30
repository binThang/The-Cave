#include "Main.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE prevInst, LPSTR pCmdLine, INT nCmdShow )
{
	return Main::GetInstance().WinMain(hInst, prevInst, pCmdLine, nCmdShow );
}