#include <windows.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_EXIT 2
#define BUTTON_CLIQUE_AQUI 3

HWND hEdit;

void loadImage();
void addMenu(HWND hWnd);
void addElements(HWND hWnd);

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){
	
	WNDCLASS wc = {};
	
	wc.lpszClassName = "My Window Class";
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcedure;
	wc.hInstance = hInst;
	
	RegisterClass(&wc);
	
	CreateWindow(
		wc.lpszClassName,
		"My GUI App",
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
		
		case WM_CREATE:
			addMenu(hWnd);
			addElements(hWnd);
			break;
			
		case WM_COMMAND:
			switch(wp){
				case FILE_MENU_NEW:
					MessageBox(NULL, "Menu New cliked!", "Message", MB_OK);
					break;
				case FILE_MENU_EXIT:
					DestroyWindow(hWnd);
					break;
				case BUTTON_CLIQUE_AQUI:
					char editText[100];
					GetWindowText(hEdit, editText, 100);
					MessageBox(NULL, editText, "Message", MB_OK);
					break;
			}
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	
	return DefWindowProc(hWnd, msg, wp, lp);
}

void addMenu(HWND hWnd){

	HMENU hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");
		
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");

	SetMenu(hWnd, hMenu);
}

void addElements(HWND hWnd){
	
	CreateWindow(
		"Static",
		"Entre com um valor",
		WS_VISIBLE | WS_CHILD | SS_CENTER,
		100, 100, 600, 20,
		hWnd,
		NULL, NULL, NULL
	);
	
	hEdit = CreateWindow(
		"Edit",
		"",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		100, 130, 600, 20,
		hWnd,
		NULL, NULL, NULL
	);
	
	CreateWindow(
		"Button",
		"Clique aqui",
		WS_VISIBLE | WS_CHILD,
		100, 160, 600, 50,
		hWnd,
		(HMENU)BUTTON_CLIQUE_AQUI, NULL, NULL
	);
	
	HWND hLogoStatic = CreateWindow(
		"Static",
		NULL,
		WS_VISIBLE | WS_CHILD | SS_BITMAP,
		250, 220, 0, 0,
		hWnd,
		NULL, NULL, NULL
	);
	
	HBITMAP hLogoImage = (HBITMAP)LoadImage(NULL, "img\\logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	
	
	SendMessage(hLogoStatic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);
}
