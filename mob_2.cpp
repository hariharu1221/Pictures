#include "DXUT.h"
#include "mob_2.h"

mob_2::mob_2(vector<cBullet*>& bullet, Vec2 mob_p)
	: mob_1(bullet, mob_p)
{
	m_ani = IMAGE->MakeVecImg("mob2");
	size = 70;
}

mob_2::~mob_2()
{
}

void mob_2::Update(Vec2 m_pos, int cell[][CELLSIZEY])
{
	Skill();  
}

void mob_2::Skill()
{
	frame += Delta * 5;
	if (frame >= m_ani.size())	{ frame = 0; size = 70; }
	if (frame >= 4)				  size = 110;
}
