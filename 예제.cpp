#include "Defines.h"









// 더블버퍼 예제문제 내주기

// 만들어 보세요!















// 먼저 두 개의 콘솔 화면 핸들을 준비합니다.

HANDLE g_hScreen[2];



// 몇 번째 화면을 표시할 지 정할 변수입니다.

int g_ScreenIndex = 0;



int g_Delay = 200;



// 화면에 출력할 

char background1[] = "★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★";

char background2[] = "☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆";







// 콘솔창에서 1~15까지 색상을 설정 가능

void SetColor(unsigned int color) {

	SetConsoleTextAttribute(g_hScreen[g_ScreenIndex], color);

}



// 화면 가운데에 출력할 문자열

char Text1[] = "　HelloWorld　";



// 핸들을 사용했다면 닫아주어야 합니다.

void ScreenRelease() {

	CloseHandle(g_hScreen[0]);

	CloseHandle(g_hScreen[1]);

}



void ClearScreen() {

	// cls 대신 사용합니다.



	// 화면의 좌표값을 갖는 구조체 (지우기 시작할 좌표를설정합니다.)

	COORD coor = { 0,0 };



	// 버퍼에 실제 기록된 문자수를 받는 변수포인터입니다.

	// (unsigned long 형)

	DWORD dw;

	// FillConsoleOutputCharacter() : 지정된 좌표부터 시작하여 지정한 횟수만큼 콘솔화면 버퍼에 씁니다.

	// 1 : 사용될 화면핸들

	// 2 : 채울 문자열

	// 3 : 채울 횟수

	// 4 : 채우기 시작할 좌표

	// 5 : 콘솔 화면 버퍼에 실제로 기록 된 문자 수를받는 변수에 대한 포인터

	FillConsoleOutputCharacter(g_hScreen[g_ScreenIndex], ' ', 80 * 25, coor, &dw);

}



void HideCursor() {



	CONSOLE_CURSOR_INFO cci;



	cci.dwSize = 1;

	cci.bVisible = FALSE;



	// 두 화면 모두 커서를 제거합니다.

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



void ScreenPrint(int x, int y, const char* str) {

	// 버퍼에 실제 기록된 문자수를 받는 변수포인터

	DWORD dw;



	// 좌표

	COORD l_coor = { x, y };



	// 해당 화면의 커서 위치를 l_coor로 옮김

	SetConsoleCursorPosition(g_hScreen[g_ScreenIndex], l_coor);



	// 해당 화면에 문자열을 출력합니다.

	// 1 : 사용될 화면핸들

	// 2 : 채울 문자열

	// 3 : 채울 문자열의 길이

	// 4 : 콘솔 화면 버퍼에 실제로 기록 된 문자 수를받는 변수에 대한 포인터

	WriteFile(g_hScreen[g_ScreenIndex], str, strlen(str), &dw, NULL);



}



// 실행시 딱 한번만 호출됩니다.

// 초기화 작업을 진행합니다.

void Init() {



	// 가상의 콘솔화면 2개를 만듭니다.

	g_hScreen[0] = CreateConsoleScreenBuffer(

		GENERIC_READ | GENERIC_WRITE,			// 버퍼의 읽기 쓰기모드에 대한 내용

		0,										// 콘솔의 공유 모드. 공유하지 않을때는 0.

		NULL,									// 보안 설명자. 그냥 NULL.

		CONSOLE_TEXTMODE_BUFFER,				// 콘솔의 타입인데 설정 가능 타입은 현재 CONSOLE_TEXTMODE_BUFFER 만 있음.

		NULL);									// 예약 값. 무조건 NULL.



	g_hScreen[1] = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);
	HideCursor();
}



void Render() {

	ClearScreen();

	for (int i = 0; i < 30; i++) {
		if (g_ScreenIndex) {
			if (i % 2 == 0) ScreenPrint(0, i, background1);
			else  ScreenPrint(0, i, background2);
		}

		else {
			if (i % 2 == 0) ScreenPrint(0, i, background2);

			else  ScreenPrint(0, i, background1);
		}
	}

	//(g_ScreenIndex) ? SetColor(2) : SetColor(5);
	ScreenPrint(32, 15, "　　　　　　　");
	ScreenPrint(32, 16, Text1);
	ScreenPrint(32, 17, "　　　　　　　");
}



void Loop() {
	while (true) {
		Render();
		ScreenFlipping();
	}
}





void main() {
	Init();
	Loop();
}