#include "DXUT.h"
#include "cPBullet.h"

cPBullet::cPBullet(Vec2 pos, Vec2 dir, float damage, float size, float speed)
	:cBullet(pos, dir, 10)
{
	bulletType = "player";
}

cPBullet::~cPBullet()
{
}

void cPBullet::Update()
{
	m_pos -= m_Dir * 900 * Delta;
}

void cPBullet::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("PBullet"), m_pos);
}
