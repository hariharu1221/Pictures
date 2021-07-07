#pragma once
#include "singleton.h"
class cInputManager :
	public singleton<cInputManager>
{
	bool nowkey[256];
	bool oldkey[256];
	POINT mouse;
public:
	cInputManager();
	~cInputManager();

	LPD3DXLINE line;

	void Update();
	bool KeyPress(int key);
	bool KeyDown(int key);
	bool KeyUp(int key);
	bool PointPress(int key, RECT rt);
	bool PointDown(int key, RECT rt);
	bool PointUp(int key, RECT rt);
	void Rtdraw(RECT rt);
};

#define INPUT cInputManager::GetInstance()