#include "DXUT.h"
#include "mob_1.h"
#include "cMBullet.h"
#include "cMABullet.h"

mob_1::mob_1(vector<cBullet*>& bullet, Vec2 mob_p)
	:m_bullet(bullet)
{
	if (rand() % 2)
		m_tex = IMAGE->FindImage("mob1");
	else 
		m_tex = IMAGE->FindImage("mob2");
	this->mob_p = mob_p;
	D3DXVec2Normalize(&dir, &(Vec2(rand() % 1920, rand() % 1080) - this->mob_p));
}

mob_1::~mob_1()
{

}

void mob_1::Update(Vec2 m_pos, int cell [][CELLSIZEY])
{
	Skill(m_pos);
	Move(cell);
}

void mob_1::Move(int cell[][CELLSIZEY])
{
	POINT c = { trunc(mob_p.x) - 0, trunc(mob_p.y) - 0 };

	for (int y = -40; y <= 40; y++)
		for (int x = -40; x <= 40; x++)
			if (cell[int(c.x + x)][int(c.y + y)] == 2)
				dir = RANDOM->Vecc2(mob_p);
	mob_p += dir * 200 * Delta;
}

void mob_1::Skill(Vec2 m_pos)
{
	//if (bultime > 1) //1초마다 기본 불렛
	//{
	//	Vec2 pos;
	//	D3DXVec2Normalize(&pos, &(m_pos - mob_p));
	//	m_bullet.push_back(new cMABullet(Vec2(mob_p.x + 70, mob_p.y), pos, 1, 10, 700, 1));
	//	bultime = 0;
	//}
	//
	//bultime += Delta;
}
void mob_1::Render()
{
	RENDER->CenterRender(m_tex ,mob_p, 2);
}
void mob_1::UIRender()
{
}