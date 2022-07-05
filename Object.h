#pragma once

class Object {
public:
	virtual void Init() = 0;		// 초기화
	virtual void Progress() = 0;	// 게임 로직 업데이트
	virtual void Render() = 0;		// 렌더링
	virtual void Release() = 0;		// 메모리 해제
};