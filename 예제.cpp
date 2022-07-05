#include "Defines.h"









// ������� �������� ���ֱ�

// ����� ������!















// ���� �� ���� �ܼ� ȭ�� �ڵ��� �غ��մϴ�.

HANDLE g_hScreen[2];



// �� ��° ȭ���� ǥ���� �� ���� �����Դϴ�.

int g_ScreenIndex = 0;



int g_Delay = 200;



// ȭ�鿡 ����� 

char background1[] = "�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�";

char background2[] = "�١١١١١١١١١١١١١١١١١١١١١١١١١١١١١١١١١١١١١١١�";







// �ܼ�â���� 1~15���� ������ ���� ����

void SetColor(unsigned int color) {

	SetConsoleTextAttribute(g_hScreen[g_ScreenIndex], color);

}



// ȭ�� ����� ����� ���ڿ�

char Text1[] = "��HelloWorld��";



// �ڵ��� ����ߴٸ� �ݾ��־�� �մϴ�.

void ScreenRelease() {

	CloseHandle(g_hScreen[0]);

	CloseHandle(g_hScreen[1]);

}



void ClearScreen() {

	// cls ��� ����մϴ�.



	// ȭ���� ��ǥ���� ���� ����ü (����� ������ ��ǥ�������մϴ�.)

	COORD coor = { 0,0 };



	// ���ۿ� ���� ��ϵ� ���ڼ��� �޴� �����������Դϴ�.

	// (unsigned long ��)

	DWORD dw;

	// FillConsoleOutputCharacter() : ������ ��ǥ���� �����Ͽ� ������ Ƚ����ŭ �ܼ�ȭ�� ���ۿ� ���ϴ�.

	// 1 : ���� ȭ���ڵ�

	// 2 : ä�� ���ڿ�

	// 3 : ä�� Ƚ��

	// 4 : ä��� ������ ��ǥ

	// 5 : �ܼ� ȭ�� ���ۿ� ������ ��� �� ���� �����޴� ������ ���� ������

	FillConsoleOutputCharacter(g_hScreen[g_ScreenIndex], ' ', 80 * 25, coor, &dw);

}



void HideCursor() {



	CONSOLE_CURSOR_INFO cci;



	cci.dwSize = 1;

	cci.bVisible = FALSE;



	// �� ȭ�� ��� Ŀ���� �����մϴ�.

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



void ScreenPrint(int x, int y, const char* str) {

	// ���ۿ� ���� ��ϵ� ���ڼ��� �޴� ����������

	DWORD dw;



	// ��ǥ

	COORD l_coor = { x, y };



	// �ش� ȭ���� Ŀ�� ��ġ�� l_coor�� �ű�

	SetConsoleCursorPosition(g_hScreen[g_ScreenIndex], l_coor);



	// �ش� ȭ�鿡 ���ڿ��� ����մϴ�.

	// 1 : ���� ȭ���ڵ�

	// 2 : ä�� ���ڿ�

	// 3 : ä�� ���ڿ��� ����

	// 4 : �ܼ� ȭ�� ���ۿ� ������ ��� �� ���� �����޴� ������ ���� ������

	WriteFile(g_hScreen[g_ScreenIndex], str, strlen(str), &dw, NULL);



}



// ����� �� �ѹ��� ȣ��˴ϴ�.

// �ʱ�ȭ �۾��� �����մϴ�.

void Init() {



	// ������ �ܼ�ȭ�� 2���� ����ϴ�.

	g_hScreen[0] = CreateConsoleScreenBuffer(

		GENERIC_READ | GENERIC_WRITE,			// ������ �б� �����忡 ���� ����

		0,										// �ܼ��� ���� ���. �������� �������� 0.

		NULL,									// ���� ������. �׳� NULL.

		CONSOLE_TEXTMODE_BUFFER,				// �ܼ��� Ÿ���ε� ���� ���� Ÿ���� ���� CONSOLE_TEXTMODE_BUFFER �� ����.

		NULL);									// ���� ��. ������ NULL.



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
	ScreenPrint(32, 15, "��������������");
	ScreenPrint(32, 16, Text1);
	ScreenPrint(32, 17, "��������������");
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