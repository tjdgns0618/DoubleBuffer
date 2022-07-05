#include "Defines.h"

// 먼저 두개의 콘솔 화면 핸들을 준비합니다.
HANDLE g_hScreen[2];

// 몇 번쨰 화면을 표시할 것인지 지정할 변수입니다.
int g_ScreenIndex = 0;

int g_Delay = 300;

// 화면에 출력할 문자열
char background[] =
"☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆";

char background2[] =
"★★★★★★★★★★★★★★★★★★★★★★";

// 화면 가운데에 출력할 문자열
char Text1[] = "　　Hello 　　";
char Text2[] = "　　World!　　";

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
		g_hScreen[g_ScreenIndex],' ', 40 * 40,coor,&dw);
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
	for (int i = 0; i < 30; i++) {
		if (g_ScreenIndex) {
			if (i % 2 == 0) ScreenPrint(0, i, background);
			else ScreenPrint(0, i, background2);
		}
		else {
			if (i % 2 == 0) ScreenPrint(0, i, background2);
			else ScreenPrint(0, i, background);
		}
	}
	// 0번 버퍼라면 초록색,
	// 1번 버퍼라면 분혹색으로 설정합니다.
	(g_ScreenIndex) ? SetColor(2) : SetColor(5);

	// 14 /

	ScreenPrint(13, 9, "　　　　　　   ");
	ScreenPrint(13, 10, (g_ScreenIndex) ? Text1 : Text2);
	ScreenPrint(13, 11, "　　　　　　   ");

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