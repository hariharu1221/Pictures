#pragma once
#include "cBullet.h"
class boss_1
{
public:
	vector<cBullet*>& m_bullet;
	cTimer* playerAS = nullptr;
	vector<cTexture*> m_ani = IMAGE->MakeVecImg("boss");
	Vec2 bpos = CENTER;
	vector<cTexture*> die = IMAGE->MakeVecImg("bdie");
	float b_die = 0;

	bool b_fire = true;

	float m_Hp;
	float frame = 0;
	float bultime = 0;
	float skilltime = 0;
	float busttime = 0;
	float razortime = 0;
	float b_count = 4;
	float b_time = 0;
	float beam = 0;
	int acttime = 0;
	int alphaacttime = 0;

	boss_1(vector<cBullet*>& bullet);
	~boss_1();

	void Update(Vec2 m_pos);
	void Skill(Vec2 m_pos);
	void Render();
	void UIRender();
};

