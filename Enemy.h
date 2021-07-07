#pragma once
#include "cBullet.h"
class Enemy
{
public:
	float m_Hp;
	Vec2 mob_p;

	Enemy();
	~Enemy();

	virtual void Update(Vec2 m_pos);
	virtual void Skill(Vec2 m_pos);
	virtual void Render();
	virtual void UIRender();
};
