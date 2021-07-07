#include "DXUT.h"
#include "cMABullet.h"

cMABullet::cMABullet(Vec2 pos, Vec2 dir, float damage, float size, float speed, float dirtimer)
	:cBullet(pos, dir, size), m_speed(speed), dirtimer(dirtimer)
{
	m_Damage = damage;
	bulletType = "mob";
}

cMABullet::~cMABullet()
{
}

void cMABullet::Update()
{
	m_pos += m_Dir * 300 * Delta * float(m_speed / 500);
	m_angle = atan2(m_Dir.y, m_Dir.x);
	if (dirtimer >= 0) D3DXVec2Normalize(&m_Dir, &(SCENE->v_pos - m_pos));
	dirtimer -= Delta;
	timer += Delta;
	if (timer > 0.2)
	{
		count++;
		if (count >= m_ani.size())
			count = 0;
		timer = 0;
	}
}

void cMABullet::Render()
{
	RENDER->CenterRender(m_ani[count], m_pos, 1, m_angle);
}
