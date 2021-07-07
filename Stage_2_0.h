#pragma once
#include "DXUT.h"
#include "cPlayer.h"
#include "cBulletAdmin.h"
#include "TileMap.h"
#include "cCollison.h"
#include "boss_3.h"
#include "mob_3.h"

class Stage_2_0 :
	public cScene
{
	cPlayer* player = nullptr;
	cBulletAdmin* bullet = nullptr;
	TileMap* tile = nullptr;
	cCollison* coll = nullptr;
	boss_3* boss = nullptr;
	vector<mob_1*> mob;

	int stage = 2;
public:

	Stage_2_0();
	virtual ~Stage_2_0();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void UIRender();
	virtual void Release();
	virtual void M_Destroy();
};

