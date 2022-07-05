#include "Defines.h"

// 프레임 딜레이
int g_Delay = 1000;

// 커서 위치
int g_PosX = 0;
int g_PosY = 0;

// 화면을 지웁니다.
void ClearScreen();

// 커서를 숨깁니다.
void HideCursor();

// 커서의 위치를 변경합니다.
void Gotoxy(int x, int y);

// 매 프레임마다 호출됩니다.
// 시각적인 처리를 제외한 나머지 처리를 작업합니다.
void Update();

// 매 프레임마다 호출됩니다.
// 시가적인 처리를 작업합니다.
void Render();

// 시스템이 끝나지 않도록 반복문을 돌릴 곳.
void Loop();

int main() {
	HideCursor();
	Loop();


	return 0;
}

void ClearScreen() {
	system("cls");
}

void HideCursor() {
	// 콘솔의 커서에 대한 정보를 가지고 있는 구조체
	CONSOLE_CURSOR_INFO cci;

	// 커서의 사이즈를 지정합니다.
	// 1 ~ 100 까지 지정 가능
	cci.dwSize = 1;

	// 커서를 숨깁니다.
	// 이 설정을 사용할 때 할상 커서의 사이즈를 지정해주어야 합니다.
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void Gotoxy(int x, int y) {
	// COORD : 화면상의 좌표값을 가지는 구조체
	COORD coor = { x,y };

	// SetConsoleCursorPosition() : 커서 위치를 지정합니다.
	// 1. 위치를 변경할 커서가 있는 스크린의 핸들
	// 2. 변경할 좌표값을 가지는 구조체
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), coor);

	cout << "콘솔창의 커서 위치를 변경한다.";
}

void Update() {
	g_PosX = (g_PosX > 20) ? 0 : ++g_PosX;
	g_PosY = (g_PosY > 20) ? 0 : ++g_PosY;
}

void Render() {
	ClearScreen();
	Gotoxy(g_PosX, g_PosX);
}

void Loop() {
	while (true) {
		Update();
		Render();
		Sleep(g_Delay);
	}
}
