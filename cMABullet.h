#pragma once
#include "cBullet.h"
class cMABullet :
	public cBullet
{
public:
	cMABullet(Vec2 pos, Vec2 dir, float damage, float size = 10, float speed = 700, float dirtimer = 1);
	virtual ~cMABullet();
	float m_speed;
	float timer = 0;
	int count = 0;
	float dirtimer = 0;
	vector<cTexture*> m_ani = IMAGE->MakeVecImg("bulletblue");

	// cBullet을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

