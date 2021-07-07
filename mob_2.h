#pragma once
#include "mob_1.h"
class mob_2
	:public mob_1
{
public:
	mob_2(vector<cBullet*>& bullet, Vec2 mob_p);
	~mob_2();

	void Update(Vec2 m_pos, int cell[][CELLSIZEY]);
	void Skill();
};

