#pragma once
#include "cBullet.h"
class boss_2
{
public:
	vector<cBullet*>& m_bullet;
	cTimer* playerAS = nullptr;
	Vec2 bpos = CENTER;
	Vec2 dir;
	vector<cTexture*> die = IMAGE->MakeVecImg("bdie");
	float b_die = 0;

	bool b_fire = true;

	float m_Hp;
	float bultime = 0;
	float skilltime = 0;
	float busttime = 0;
	float razortime = 0;
	float b_count = 4;
	float b_time = 0;
	float beam = 0;
	int acttime = 0;
	int alphaacttime = 0;

	boss_2(vector<cBullet*>& bullet);
	~boss_2();

	void Update(Vec2 m_pos, int cell[][CELLSIZEY]);
	void Skill(Vec2 m_pos);
	void Move(int cell[][CELLSIZEY]);
	void Render();
	void UIRender();
};

