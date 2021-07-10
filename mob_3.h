#pragma once
#include "mob_1.h"
class mob_3
	:public mob_1
{
public:
	mob_3(vector<cBullet*>& bullet, Vec2 mob_p);
	~mob_3();

	void Update(Vec2 m_pos, int cell[][CELLSIZEY]);
	void Skill(Vec2 m_pos);
};

