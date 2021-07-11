#pragma once
#include "cBullet.h"
class cPlayer
{
public:
	vector<cBullet*>& m_bullet;
	cTimer* playerAS = nullptr;

	bool b_fire = true;

	float m_Hp;
	float m_MaxHp;
	int m_Score;
	float ztimer = 0;

	string ItemName;
	vector<cTexture*> m_ani = IMAGE->MakeVecImg("player");

	float b_ani = 0;
	float partcycle = 0;

	cPlayer(vector<cBullet*>& bullet);
	~cPlayer();

	void Update(Vec2 m_pos);
	void Render(Vec2 m_pos);
	void UIRender();

	void Move();
	void FireBullet(Vec2 m_pos);
	void ItemUpdate();
	void Skill(Vec2 m_pos);
};

