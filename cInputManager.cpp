#include "DXUT.h"
#include "cInputManager.h"

cInputManager::cInputManager()
{
	D3DXCreateLine(g_device, &line);
	line->SetAntialias(true);
	line->SetWidth(1);
}

cInputManager::~cInputManager()
{
	line->Release();
}

void cInputManager::Update()
{
	for (int i = 0; i < 256; i++) oldkey[i] = nowkey[i];
	for (int i = 0; i < 256; i++)
	{
		if (GetAsyncKeyState(i)) nowkey[i] = true;
		else nowkey[i] = false;
	}
	GetCursorPos(&mouse);
}

bool cInputManager::KeyPress(int key)
{
	return nowkey[key] == true && oldkey[key] == true;
}

bool cInputManager::KeyDown(int key)
{
	return nowkey[key] == true && oldkey[key] == false;
}

bool cInputManager::KeyUp(int key)
{
	return nowkey[key] == false && oldkey[key] == true;
}

bool cInputManager::PointPress(int key, RECT rt)
{
	Rtdraw(rt);
	if (mouse.x >= rt.left && mouse.x <= rt.right
		&& mouse.y >= rt.top && mouse.y <= rt.bottom)
		return nowkey[key] == true && oldkey[key] == true;
	return false;
}

bool cInputManager::PointDown(int key, RECT rt)
{
	Rtdraw(rt);
	if (mouse.x >= rt.left && mouse.x <= rt.right
		&& mouse.y >= rt.top && mouse.y <= rt.bottom)
		return nowkey[key] == true && oldkey[key] == false;
	return false;
}

bool cInputManager::PointUp(int key, RECT rt)
{
	Rtdraw(rt);
	if (mouse.x >= rt.left && mouse.x <= rt.right
		&& mouse.y >= rt.top && mouse.y <= rt.bottom)
		return nowkey[key] == false && oldkey[key] == true;
	return false;
}

void cInputManager::Rtdraw(RECT rt)
{
	if (coldraw)
	{
		Vec2* vs = new Vec2[5];
		vs[0] = { float(rt.left),float(rt.top) };
		vs[1] = { float(rt.right),float(rt.top) };
		vs[2] = { float(rt.right),float(rt.bottom) };
		vs[3] = { float(rt.left),float(rt.bottom) };
		vs[4] = { float(rt.left),float(rt.top) };

		line->Draw(vs, 5, D3DCOLOR_RGBA(0, 255, 0, 255));
		SAFE_DELETE_ARRAY(vs);
	}
}
