#include "DXUT.h"
#include "cMBullet.h"

cMBullet::cMBullet(Vec2 pos, Vec2 dir, float damage, float size, float speed, int color)
	:cBullet(pos, dir, size), m_speed(speed), color(color)
{
	m_Damage = damage;
	bulletType = "mob";

	if (color == 1) { m_ani = IMAGE->MakeVecImg("bullet"); isize = 1; }
	if (color == 2)	{ m_ani = IMAGE->MakeVecImg("bulletblue"); isize = 0.5; }
}

cMBullet::~cMBullet()
{
}

void cMBullet::Update()
{
	m_pos += m_Dir * 300 * Delta * float(m_speed / 500);
	m_angle = atan2(m_Dir.y, m_Dir.x);
	timer += Delta;
	if (timer > 0.2)
	{
		count++;
		if (count >= m_ani.size() - 1)
			count = 0;
		timer = 0;
	}
}

void cMBullet::Render()
{
	RENDER->CenterRender(m_ani[count], m_pos, isize, m_angle);
}
