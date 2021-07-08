#include "DXUT.h"
#include "mob_2.h"
#include "cMABullet.h"

mob_2::mob_2(vector<cBullet*>& bullet, Vec2 mob_p)
	: mob_1(bullet, mob_p)
{
	if (rand() % 2)
		m_tex = IMAGE->FindImage("mob3");
	else
		m_tex = IMAGE->FindImage("mob4");
	size = 70;
}

mob_2::~mob_2()
{
}

void mob_2::Update(Vec2 m_pos, int cell[][CELLSIZEY])
{
	Skill(m_pos);  
	Move(cell);
}

void mob_2::Skill(Vec2 m_pos)
{
	if (bultime > 1) //1초마다 기본 불렛
	{
		Vec2 pos;
		D3DXVec2Normalize(&pos, &(m_pos - mob_p));
		m_bullet.push_back(new cMABullet(Vec2(mob_p.x + 70, mob_p.y), pos, 1, 10, 700, 1));
		bultime = 0;
	}

	bultime += Delta;
}