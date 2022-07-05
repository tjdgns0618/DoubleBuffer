#include "Defines.h"


// GetAsyncKeyState()
// 현재 어떤 키가 눌렸는지 체크하는 함수
// VK_키코드를 사용합니다.

int main() {
	int test = VK_SPACE;
	int test1 = VK_RETURN;
	int esc = VK_ESCAPE;
	int q = 0x51;

	while (true) {
		if (GetAsyncKeyState(q) & 0x0001) {
			cout << "Q키가 눌렸습니다." << endl;
		}
	}

	return 0;
}