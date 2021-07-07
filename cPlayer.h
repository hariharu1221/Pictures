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

	string ItemName;

	cPlayer(vector<cBullet*>& bullet);
	~cPlayer();

	void Update(Vec2 m_pos);
	void Render(Vec2 m_pos);
	void UIRender();

	void Move();
	void FireBullet(Vec2 m_pos);
	void ItemUpdate();
};

