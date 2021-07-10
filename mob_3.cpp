#include "DXUT.h"
#include "mob_3.h"
#include "cMABullet.h"

mob_3::mob_3(vector<cBullet*>& bullet, Vec2 mob_p)
	: mob_1(bullet, mob_p)
{
	if (rand() % 2)
		m_tex = IMAGE->FindImage("mob5");
	else
		m_tex = IMAGE->FindImage("mob6");
	size = 70;
}

mob_3::~mob_3()
{
}

void mob_3::Update(Vec2 m_pos, int cell[][CELLSIZEY])
{
	Skill(m_pos);
	Move(cell);
}

void mob_3::Skill(Vec2 m_pos)
{
	if (bultime > 1) //1�ʸ��� �⺻ �ҷ�
	{
		Vec2 pos;
		D3DXVec2Normalize(&pos, &(m_pos - mob_p));
		m_bullet.push_back(new cMABullet(Vec2(mob_p.x + 70, mob_p.y), pos, 1, 10, 700, 1));
		bultime = 0;
	}

	bultime += Delta;
}