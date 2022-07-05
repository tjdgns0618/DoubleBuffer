#include "Bullet.h"

Bullet::Bullet() {
}


Bullet::~Bullet() {
}

void Bullet::Init() {
	
}

void Bullet::Init(int x, int y) {
	srand(GetTickCount());
	int random = (rand() % 19) + 1;
	m_PosX = 38;
	m_PosY = random;
}

void Bullet::Progress() {
	if (m_PosX < 2) Release();
}

void Bullet::Render() {
	if (m_PosX > 2) {
		// ÃÑ¾Ë ±×¸®±â
		m_PosX--;
	}
}

void Bullet::Release() {
	isRemove = true;
}
