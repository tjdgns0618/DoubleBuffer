#include "Defines.h"


// GetAsyncKeyState()
// ���� � Ű�� ���ȴ��� üũ�ϴ� �Լ�
// VK_Ű�ڵ带 ����մϴ�.

int main() {
	int test = VK_SPACE;
	int test1 = VK_RETURN;
	int esc = VK_ESCAPE;
	int q = 0x51;

	while (true) {
		if (GetAsyncKeyState(q) & 0x0001) {
			cout << "QŰ�� ���Ƚ��ϴ�." << endl;
		}
	}

	return 0;
}