#pragma once
#include "Enemy.h"
class mob_1 
	: public Enemy
{
public:
	cTexture* m_tex;
	vector<cBullet*>& m_bullet;
	Vec2 dir;

	float frame = 1;
	float bultime = 0;
	float b_count = 4;
	float size = 40;

	mob_1(vector<cBullet*>& bullet, Vec2 mob_p);
	virtual ~mob_1();

	virtual void Update(Vec2 m_pos, int cell[][CELLSIZEY]);
	void Move(int cell[][CELLSIZEY]);
	virtual void Skill(Vec2 m_pos);
	virtual void Render();
	virtual void UIRender();
};

