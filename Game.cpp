#include "Defines.h"

// ���� �ΰ��� �ܼ� ȭ�� �ڵ��� �غ��մϴ�.
HANDLE g_hScreen[2];

// �� ���� ȭ���� ǥ���� ������ ������ �����Դϴ�.
int g_ScreenIndex = 0;

int g_Delay = 10;

// ȭ�鿡 ����� ���ڿ�
const char Character[2][200] = {
	{ "���" }, 
	{ "���" }
};

int g_CharX = 4;
int g_CharY = 4;

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

int g_X = 0;
int g_Y = 0;

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
		g_hScreen[g_ScreenIndex], ' ', g_X * g_Y, coor, &dw);
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

void CharacterMove() {
	if (GetAsyncKeyState(VK_RIGHT)) {
		if (g_CharX > 119) {
			g_CharX = 1;
		}
		g_CharX++;
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		if (g_CharX < 2) {
			g_CharX = 120;
		}
		g_CharX--;
	}
	if (GetAsyncKeyState(VK_UP)) {
		g_CharY--;
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
		g_CharY++;
	}
	if (GetAsyncKeyState(VK_SPACE)) {
		g_X = 200;
		g_Y = 200;
	}
	if (GetAsyncKeyState(VK_ESCAPE)) {
		g_X = 0;
		g_Y = 0;
	}
	if (GetAsyncKeyState(0x55) & 0x0001) {
		g_CharY -= 10;
	}
	if (GetAsyncKeyState(0x4A) & 0x0001) {
		g_CharY += 10;
	}
	if (GetAsyncKeyState(0x48) & 0x0001) {
		g_CharX -= 10;
	}
	if (GetAsyncKeyState(0x4B) & 0x0001) {
		g_CharX += 10;
	}

	if (GetAsyncKeyState(0x51)) SetColor(0);
	if (GetAsyncKeyState(0x57)) SetColor(3);
	if (GetAsyncKeyState(0x45)) SetColor(4);
	if (GetAsyncKeyState(0x52)) SetColor(5);
	if (GetAsyncKeyState(0x41)) SetColor(6);
	if (GetAsyncKeyState(0x53)) SetColor(7);
	if (GetAsyncKeyState(0x44)) SetColor(8);
	if (GetAsyncKeyState(0x46)) SetColor(9);
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

	ScreenPrint(g_CharX, g_CharY, *Character);
	CharacterMove();

	
	// 0�� ���۶�� �ʷϻ�,
	// 1�� ���۶�� ��Ȥ������ �����մϴ�.
	// (g_ScreenIndex) ? SetColor(2) : SetColor(5);


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