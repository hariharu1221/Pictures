#include "DXUT.h"
#include "mob_1.h"
#include "cMBullet.h"
#include "cMABullet.h"

mob_1::mob_1(vector<cBullet*>& bullet, Vec2 mob_p)
	:m_bullet(bullet)
{
	this->mob_p = mob_p;
}

mob_1::~mob_1()
{

}

void mob_1::Update(Vec2 m_pos, int cell [][CELLSIZEY])
{
	Skill(m_pos);
}

void mob_1::Skill(Vec2 m_pos)
{
	frame += Delta * 5;
	if (frame >= m_ani.size())
		frame = 0;

	if (bultime > 1) //1초마다 기본 불렛
	{
		Vec2 pos;
		D3DXVec2Normalize(&pos, &(m_pos - mob_p));
		m_bullet.push_back(new cMABullet(Vec2(mob_p.x + 70, mob_p.y), pos, 1, 10, 700, 1));
		bultime = 0;
	}

	bultime += Delta;
}
void mob_1::Render()
{
	RENDER->CenterRender(m_ani[int(frame)], mob_p, 2);
}
void mob_1::UIRender()
{
}