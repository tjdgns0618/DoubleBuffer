#pragma once
#include "Defines.h"
#include "Object.h"

class Bullet :
	public Object {
public:
	Bullet();
	~Bullet();

public:
	virtual void Init();
	void Init(int x, int y);
	virtual void Progress();
	virtual void Render();
	virtual void Release();

	void SetBulletList(list<Bullet>* pBulletList) { m_pBulletList = pBulletList; }
	bool isDestroy() { return isRemove; }

private:
	bool isRemove = false;
	int m_PosX = 0;
	int m_PosY = 0;
	list<Bullet>* m_pBulletList;
};

