#pragma once

class Object {
public:
	virtual void Init() = 0;		// �ʱ�ȭ
	virtual void Progress() = 0;	// ���� ���� ������Ʈ
	virtual void Render() = 0;		// ������
	virtual void Release() = 0;		// �޸� ����
};