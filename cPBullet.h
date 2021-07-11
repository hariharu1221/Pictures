#pragma once
#include "cBullet.h"
class cPBullet :
	public cBullet
{
public:
	cPBullet(Vec2 pos, Vec2 dir, float damage, float size = 10, float speed = 700);
	virtual ~cPBullet();
	// cBullet을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

