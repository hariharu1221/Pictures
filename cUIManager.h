#pragma once
#include "singleton.h"
class cUIManager :
	public singleton<cUIManager>
{
	LPD3DXSPRITE m_sprite;
	LPD3DXFONT m_font;
public:
	cUIManager();
	~cUIManager();

	void Begin();
	void End();
	void Reset();
	void Lost();

	void CenterRender(cTexture* ptr, Vec2 pos, float size = 1, float rot = 0);
	void CenRender(cTexture* ptr, Vec2 pos, float size = 1, float rot = 0);
	void CenterRender2(cTexture* ptr, Vec2 pos, float size = 1, int alpha = 255, int r = 255, int g = 255, int b = 255);
	void CropRender(cTexture* ptr, Vec2 pos, RECT& rc, float size = 1);
	void CropRender2(cTexture* ptr, Vec2 pos, RECT& rc, float size = 1, int alpha = 255, int r = 255, int g = 255, int b = 255);
	void PrintText(string str, Vec2 pos, float size, int alpha = 255, int r = 0, int g = 0, int b = 0);
};

#define UI cUIManager::GetInstance()