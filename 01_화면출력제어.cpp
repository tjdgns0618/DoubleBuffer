#include "Defines.h"

// ������ ������
int g_Delay = 1000;

// Ŀ�� ��ġ
int g_PosX = 0;
int g_PosY = 0;

// ȭ���� ����ϴ�.
void ClearScreen();

// Ŀ���� ����ϴ�.
void HideCursor();

// Ŀ���� ��ġ�� �����մϴ�.
void Gotoxy(int x, int y);

// �� �����Ӹ��� ȣ��˴ϴ�.
// �ð����� ó���� ������ ������ ó���� �۾��մϴ�.
void Update();

// �� �����Ӹ��� ȣ��˴ϴ�.
// �ð����� ó���� �۾��մϴ�.
void Render();

// �ý����� ������ �ʵ��� �ݺ����� ���� ��.
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
	// �ܼ��� Ŀ���� ���� ������ ������ �ִ� ����ü
	CONSOLE_CURSOR_INFO cci;

	// Ŀ���� ����� �����մϴ�.
	// 1 ~ 100 ���� ���� ����
	cci.dwSize = 1;

	// Ŀ���� ����ϴ�.
	// �� ������ ����� �� �һ� Ŀ���� ����� �������־�� �մϴ�.
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void Gotoxy(int x, int y) {
	// COORD : ȭ����� ��ǥ���� ������ ����ü
	COORD coor = { x,y };

	// SetConsoleCursorPosition() : Ŀ�� ��ġ�� �����մϴ�.
	// 1. ��ġ�� ������ Ŀ���� �ִ� ��ũ���� �ڵ�
	// 2. ������ ��ǥ���� ������ ����ü
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), coor);

	cout << "�ܼ�â�� Ŀ�� ��ġ�� �����Ѵ�.";
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
