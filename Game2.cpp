#include "Defines.h"
#include "Game2.h"
// ���� �ΰ��� �ܼ� ȭ�� �ڵ��� �غ��մϴ�.
HANDLE g_hScreen[2];

// �� ���� ȭ���� ǥ���� ������ ������ �����Դϴ�.
int g_ScreenIndex = 0;

int g_Delay = 30;

// ȭ�鿡 ����� ���ڿ�
const char Sel[4][4] = {
	{"��"}
};


// ȭ�� ����� ����� ���ڿ�

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
		g_hScreen[g_ScreenIndex], ' ', 120 * 60, coor, &dw);
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

void PrintMap(int x, int y) {
	ScreenPrint(x, y, "��������");
	ScreenPrint(x, y + 1, "��          ��");
	ScreenPrint(x, y + 2, "��          ��");
	ScreenPrint(x, y + 3, "��          ��");
	ScreenPrint(x, y + 4, "��          ��");
	ScreenPrint(x, y + 5, "��          ��");
	ScreenPrint(x, y + 6, "��          ��");
	ScreenPrint(x, y + 7, "��          ��");
	ScreenPrint(x, y + 8, "��          ��");
	ScreenPrint(x, y + 9, "��������");
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
		ScreenPrint(x, random, "��");
		x--;
	}
 }

 int g_charX = 4;
 int g_charY = 2;
 void Map1() {
	 
	 ScreenPrint(2, 1, "���������������������");
	 for (int i = 2; i < 20; ++i) {
		 ScreenPrint(2, i, "��");
		 ScreenPrint(40, i, "��");
	 }
	 ScreenPrint(2, 20, "���������������������");

	 ScreenPrint(g_charX, g_charY, "��");
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
	 ScreenPrint(g_selX, g_selY, "��");
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
				ScreenPrint(10, 10, "���������������");
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
				ScreenPrint(10, 10, "���������������");
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

