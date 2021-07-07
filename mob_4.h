#pragma once
#include "mob_1.h"

class mob_4
	:public mob_1
{
public:
	mob_4(vector<cBullet*>& bullet, Vec2 mob_p);
	~mob_4();

	char color;
	float b_move = 0;
	float b_skill = 0;
	float speed = 70;
	float xgap;
	float ygap;
	int dir = 0;

	void Update(Vec2 m_pos, int cell[][CELLSIZEY]);
	void Move(int cell[][CELLSIZEY]);
	void Skill(Vec2 m_pos);
};

