#pragma once
#include "cBullet.h"
class cPBullet :
	public cBullet
{
public:
	cPBullet(Vec2 pos, Vec2 dir = Vec2(0, 1));
	virtual ~cPBullet();
	// cBullet��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

