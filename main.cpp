#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){
	
	WNDCLASSW wc = {};
	
	wc.lpszClassName = L"My Window Class";
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcedure;
	wc.hInstance = hInst;
	
	RegisterClassW(&wc);
	
	CreateWindowW(
		wc.lpszClassName,
		L"My GUI App",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 800, 600,
		NULL, NULL, NULL, NULL
	);
	
	MSG msg = {};
	
	while(GetMessage(&msg, NULL, NULL, NULL)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	
	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
	
	switch (msg){
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			
	}
	return DefWindowProcW(hWnd, msg, wp, lp);
}
