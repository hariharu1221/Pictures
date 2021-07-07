#pragma once
#include "DXUT.h"

class cMaingame
{
public:
	cMaingame();
	~cMaingame();

	void Init();
	void Update();
	void Render();
	void Release();
	void LostDevice();
	void ResetDevice();
	void AddResource();
};

