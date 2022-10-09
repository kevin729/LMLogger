#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>

LRESULT CALLBACK windowProcedure(HWND, UINT, WPARAM, LPARAM);
void addMenus(HWND);
void addItems(HWND);

HMENU hMenu;
HWND button;
HWND searchField;
HWND dataField;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE preHInstance, LPSTR args, int ncmdshow)
{
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	wc.hInstance = hInstance;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = windowProcedure;

	if (!RegisterClassW(&wc)) {
		return -1;
	}

	CreateWindowW(
		L"myWindowClass",
		L"LukeMind Chat",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU,
		100, 100, 1000, 500,
		NULL,
		NULL,
		NULL,
		NULL
	);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

void search(HWND hWnd) {
	char* search;
	GetWindowTextA(searchField, search, GetWindowTextLength(searchField));
	size_t size = strlen(search) + 1;

	wchar_t wtext;
	mbstowcs_s(&size, &wtext, size, &search, size);//Plus nul


	dataField = CreateWindowW(L"STATIC",
		search,
		WS_VISIBLE | WS_CHILD,
		400, 130, 200, 100,
		hWnd,
		NULL,
		NULL,
		NULL
	);
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		addItems(hWnd);
		addMenus(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:

		switch (LOWORD(wp)) {
		case 1:
			search(hWnd);
			break;

		}

		break;
	}

	return DefWindowProcW(hWnd, msg, wp, lp);
}

void addMenus(HWND hWnd)
{
	hMenu = CreateMenu();
}

void addItems(HWND hWnd) {
	searchField = CreateWindowW(L"EDIT",
		L"Search...",
		WS_VISIBLE | WS_CHILD,
		400, 100, 80, 20,
		hWnd,
		NULL,
		NULL,
		NULL
	);

	CreateWindowW(L"BUTTON",
		L"Search",
		WS_VISIBLE | WS_CHILD,
		500, 100, 100, 20,
		hWnd,
		(HMENU)1,
		NULL,
		NULL
	);

	dataField = CreateWindowW(L"STATIC",
		L"Data...",
		WS_VISIBLE | WS_CHILD,
		400, 130, 200, 100,
		hWnd,
		NULL,
		NULL,
		NULL
	);


}

