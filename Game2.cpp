#include "Defines.h"
#include "Game2.h"
// 먼저 두개의 콘솔 화면 핸들을 준비합니다.
HANDLE g_hScreen[2];

// 몇 번쨰 화면을 표시할 것인지 지정할 변수입니다.
int g_ScreenIndex = 0;

int g_Delay = 30;

// 화면에 출력할 문자열
const char Sel[4][4] = {
	{"▲"}
};


// 화면 가운데에 출력할 문자열

// 콘솔 화면에서 글자 색상을 변경합니다.
void SetColor(UINT color) {
	SetConsoleTextAttribute(g_hScreen[g_ScreenIndex], color);
}

// 핸들을 사용했다면 닫아주어야 합니다.
void ScreenRelease() {
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void ClearScreen() {

	// cls 대신에 사용합니다.
	// 지우기 시작할 좌표입니다.
	COORD coor = { 0,0 };

	// 버퍼에 실제 기록된 문자 수를 받는 변수 포인터
	DWORD dw;

	// FillConsoleOutputCharacter
	// 지정된 좌표부터 시작하여 지정된 횟수만큼
	// 콘솔화면 버퍼에 씁니다.
	// 1 : 사용될 화면 핸들
	// 2 : 채울 문자
	// 3 : 채울 횟수
	// 4 : 채우기 시작할 좌표
	// 5 : 콘솔 화면 버퍼에 실제로 기록될 문자수를 받는 변수에 대한 포인터
	FillConsoleOutputCharacter(
		g_hScreen[g_ScreenIndex], ' ', 120 * 60, coor, &dw);
}

// 커서를 숨깁니다.
void HideCursor() {
	CONSOLE_CURSOR_INFO cci;

	cci.dwSize = 1;

	cci.bVisible = FALSE;

	// 두 화면 모두 커서를 지웁니다.
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

// 화면을 교체합니다.
void ScreenFlipping() {
	Sleep(g_Delay);

	// 해당 화면으로 교체합니다.
	SetConsoleActiveScreenBuffer(g_hScreen[g_ScreenIndex]);

	// 다음에 띄울 화면 인덱스를 변경합니다.
	g_ScreenIndex = !g_ScreenIndex;
}

// 화면에 출력합니다.
void ScreenPrint(int x, int y, const char* text) {

	// 버퍼에 실제 기록된 문자수를 받는 변수 포인터
	DWORD dw;

	// 좌표
	COORD coor = { x,y };

	// 해당 화면의 커서 위치를 coor로 옮깁니다.
	SetConsoleCursorPosition(
		g_hScreen[g_ScreenIndex], coor);


	WriteFile(						// 해당 화면에 문자열을 출력합니다.
		g_hScreen[g_ScreenIndex],	// 사용될 화면 핸들
		text,						// 채울 문자열
		strlen(text),				// 채울 문자열의 길이
		&dw,						// 콘솔 화면 버퍼에 실제로 기록된 
									// 문자수를 받는 변수에 대한 포인터
		NULL);
}

void PrintMap(int x, int y) {
	ScreenPrint(x, y, "■■■■■■■");
	ScreenPrint(x, y + 1, "■          ■");
	ScreenPrint(x, y + 2, "■          ■");
	ScreenPrint(x, y + 3, "■          ■");
	ScreenPrint(x, y + 4, "■          ■");
	ScreenPrint(x, y + 5, "■          ■");
	ScreenPrint(x, y + 6, "■          ■");
	ScreenPrint(x, y + 7, "■          ■");
	ScreenPrint(x, y + 8, "■          ■");
	ScreenPrint(x, y + 9, "■■■■■■■");
}

map<string, int> maplist;

int g_selX = 56;
int g_selY = 10;
 void Select() { 

	 if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		 if (g_selY < 32) {
			 g_selY += 11;
		 }
	 }
	 else if (GetAsyncKeyState(VK_UP) & 0x0001) {
		 if (g_selY > 10) {
			 g_selY -= 11;
		 }
	 }
	 if (g_selY == 10) {
		 if (GetAsyncKeyState(VK_SPACE)) {
			
		 }
	 }
 }

 int obsX = 38;
 void Obstacle(int x) {
	srand(GetTickCount());
	int random = (rand() % 19) + 1;
	while (true) {
		ScreenPrint(x, random, "←");
		x--;
	}
 }

 int g_charX = 4;
 int g_charY = 2;
 void Map1() {
	 
	 ScreenPrint(2, 1, "■■■■■■■■■■■■■■■■■■■■");
	 for (int i = 2; i < 20; ++i) {
		 ScreenPrint(2, i, "■");
		 ScreenPrint(40, i, "■");
	 }
	 ScreenPrint(2, 20, "■■■■■■■■■■■■■■■■■■■■");

	 ScreenPrint(g_charX, g_charY, "⊙");
	 if (GetAsyncKeyState(VK_RIGHT) && g_charX < 38) g_charX++;
	 else if (GetAsyncKeyState(VK_LEFT) && g_charX > 4) g_charX--;
	 if (GetAsyncKeyState(VK_UP) && g_charY > 2) g_charY--;
	 else if (GetAsyncKeyState(VK_DOWN) && g_charY < 19) g_charY++;

	 Obstacle(obsX);
 }

 void Map2() {

 }

 void SelMap() {
	 if (GetAsyncKeyState(VK_RIGHT) & 0x0001) g_selX++;
	 Select();
	 ScreenPrint(g_selX, g_selY, "▶");
	 if (g_selY == 10) SetColor(14);
	 else SetColor(7);
	 PrintMap(60, 5);
	 if (g_selY == 21) SetColor(14);
	 else SetColor(7);
	 PrintMap(60, 16);
	 if (g_selY == 32) SetColor(14);
	 else SetColor(7);
	 PrintMap(60, 27);
 }



// 실행시 딱 한 번만 호출됩니다.
// 초기화 작업을 진행합니다.
void Init() {

	// 가상의 콘솔화면 2개를 만듭니다.
	g_hScreen[0] =
		CreateConsoleScreenBuffer(
			// 버퍼의 읽기 쓰기 모드에 대한 내용
			GENERIC_READ | GENERIC_WRITE,

			// 콘솔의 공유 모드
			0,

			// 보안 설명자
			NULL,

			// 콘솔의 타입
			CONSOLE_TEXTMODE_BUFFER,

			// 예약값 무조건 NULL
			NULL);

	g_hScreen[1] =
		CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL);

	// 커서를 숨깁니다.
	HideCursor();
	
}

void Render() {
	ClearScreen();

	switch (g_selY) {
	case 10:
		switch (g_selX) {
		case 56:
			if (GetAsyncKeyState(VK_RIGHT) & 0x0001) g_selX++;
			SelMap();
			break;
		case 57:
			if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) g_selX--;
			Map1();
			break;
		}
	case 21:
		switch (g_selX) {
		case 56:
			if (GetAsyncKeyState(VK_RIGHT) & 0x0001) g_selX++;
			SelMap();
			break;
		case 57:
			if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) g_selX--;
			if (GetAsyncKeyState(VK_SPACE)) {
				ScreenPrint(10, 10, "▼▼▼▼▼▼▼▼▼▼▼▼▼▼");
			}
			break;
		}
	case 32:
		switch (g_selX) {
		case 56:
			if (GetAsyncKeyState(VK_RIGHT) & 0x0001) g_selX++;
			SelMap();
			break;
		case 57:
			if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) g_selX--;
			if (GetAsyncKeyState(VK_SPACE)) {
				ScreenPrint(10, 10, "▼▼▼▼▼▼▼▼▼▼▼▼▼▼");
			}
			break;
		}
	}



}

void Loop() {
	while (true) {
		Render();
		ScreenFlipping();
	}
}

int main() {
	Init();
	Loop();
	ScreenRelease();
	return 0;
}

