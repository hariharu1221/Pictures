#pragma once
#include "DXUT.h"
class SelectScene
	:public cScene
{
public:
	int select = 1;
	int optionS = 1;
	bool option = 0;
	bool bop = false;
	bool set = false;

	bool s1ready = false;
	bool s2ready = false;
	bool s3ready = false;
	bool s4ready = false;
	float timer = 0;

	SelectScene();
	virtual ~SelectScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void UIRender();
	virtual void Release();

};

