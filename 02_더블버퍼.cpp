#include "Defines.h"

// ���� �ΰ��� �ܼ� ȭ�� �ڵ��� �غ��մϴ�.
HANDLE g_hScreen[2];

// �� ���� ȭ���� ǥ���� ������ ������ �����Դϴ�.
int g_ScreenIndex = 0;

int g_Delay = 300;

// ȭ�鿡 ����� ���ڿ�
char background[] =
"�١١١١١١١١١١١١١١١١١١١١١�";

char background2[] =
"�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�";

// ȭ�� ����� ����� ���ڿ�
char Text1[] = "����Hello ����";
char Text2[] = "����World!����";

// �ܼ� ȭ�鿡�� ���� ������ �����մϴ�.
void SetColor(UINT color) {
	SetConsoleTextAttribute(g_hScreen[g_ScreenIndex], color);
}

// �ڵ��� ����ߴٸ� �ݾ��־�� �մϴ�.
void ScreenRelease() {
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void ClearScreen() {

	// cls ��ſ� ����մϴ�.
	// ����� ������ ��ǥ�Դϴ�.
	COORD coor = { 0,0 };

	// ���ۿ� ���� ��ϵ� ���� ���� �޴� ���� ������
	DWORD dw;

	// FillConsoleOutputCharacter
	// ������ ��ǥ���� �����Ͽ� ������ Ƚ����ŭ
	// �ܼ�ȭ�� ���ۿ� ���ϴ�.
	// 1 : ���� ȭ�� �ڵ�
	// 2 : ä�� ����
	// 3 : ä�� Ƚ��
	// 4 : ä��� ������ ��ǥ
	// 5 : �ܼ� ȭ�� ���ۿ� ������ ��ϵ� ���ڼ��� �޴� ������ ���� ������
	FillConsoleOutputCharacter(
		g_hScreen[g_ScreenIndex],' ', 40 * 40,coor,&dw);
}

// Ŀ���� ����ϴ�.
void HideCursor() {
	CONSOLE_CURSOR_INFO cci;

	cci.dwSize = 1;

	cci.bVisible = FALSE;

	// �� ȭ�� ��� Ŀ���� ����ϴ�.
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

// ȭ���� ��ü�մϴ�.
void ScreenFlipping() {
	Sleep(g_Delay);

	// �ش� ȭ������ ��ü�մϴ�.
	SetConsoleActiveScreenBuffer(g_hScreen[g_ScreenIndex]);

	// ������ ��� ȭ�� �ε����� �����մϴ�.
	g_ScreenIndex = !g_ScreenIndex;
}

// ȭ�鿡 ����մϴ�.
void ScreenPrint(int x, int y, const char* text) {

	// ���ۿ� ���� ��ϵ� ���ڼ��� �޴� ���� ������
	DWORD dw;

	// ��ǥ
	COORD coor = { x,y };

	// �ش� ȭ���� Ŀ�� ��ġ�� coor�� �ű�ϴ�.
	SetConsoleCursorPosition(
		g_hScreen[g_ScreenIndex], coor);

	
	WriteFile(						// �ش� ȭ�鿡 ���ڿ��� ����մϴ�.
		g_hScreen[g_ScreenIndex],	// ���� ȭ�� �ڵ�
		text,						// ä�� ���ڿ�
		strlen(text),				// ä�� ���ڿ��� ����
		&dw,						// �ܼ� ȭ�� ���ۿ� ������ ��ϵ� 
									// ���ڼ��� �޴� ������ ���� ������
		NULL);
}

// ����� �� �� ���� ȣ��˴ϴ�.
// �ʱ�ȭ �۾��� �����մϴ�.
void Init() {
	// ������ �ܼ�ȭ�� 2���� ����ϴ�.
	g_hScreen[0] =
		CreateConsoleScreenBuffer(
			// ������ �б� ���� ��忡 ���� ����
			GENERIC_READ | GENERIC_WRITE,
			
			// �ܼ��� ���� ���
			0,

			// ���� ������
			NULL,

			// �ܼ��� Ÿ��
			CONSOLE_TEXTMODE_BUFFER,

			// ���ప ������ NULL
			NULL);

	g_hScreen[1] =
		CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL);

	// Ŀ���� ����ϴ�.
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
	// 0�� ���۶�� �ʷϻ�,
	// 1�� ���۶�� ��Ȥ������ �����մϴ�.
	(g_ScreenIndex) ? SetColor(2) : SetColor(5);

	// 14 /

	ScreenPrint(13, 9, "������������   ");
	ScreenPrint(13, 10, (g_ScreenIndex) ? Text1 : Text2);
	ScreenPrint(13, 11, "������������   ");

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