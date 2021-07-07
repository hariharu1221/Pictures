#include "DXUT.h"
#include "boss_2.h"

boss_2::boss_2()
{
}

boss_2::~boss_2()
{
}

void boss_2::Update(Vec2 m_pos)
{
	if (SCENE->colorper < 70) Skill(m_pos);

	if (SCENE->colorper >= 70)
	{
		b_die += Delta * 10;
		if (b_die >= die.size()) b_die = die.size() - 1;
	}
}

void boss_2::Skill(Vec2 m_pos)
{
	if (m_pos.x <= 810 && m_pos.x >= 560 && m_pos.y >= 520 && m_pos.y <= 700 && sk != 2) sk = 1;
	if (m_pos.x >= 1110 && m_pos.x <= 1360 && m_pos.y >= 520 && m_pos.y <= 700 && sk != 1) sk = 2;
}


void boss_2::Render()
{
	if (sk == 1)
	{
		m_ani = IMAGE->MakeVecImg("boss2l");
		frame += Delta * 7;
		if (frame >= m_ani.size()) { frame = 0; sk = 0; }
		RENDER->CenterRender(m_ani[int(frame)], CENTER, 3);
	}
	else if (sk == 2)
	{
		m_ani = IMAGE->MakeVecImg("boss2r");
		frame += Delta * 7;
		if (frame >= m_ani.size()) { frame = 0; sk = 0; }
		RENDER->CenterRender(m_ani[int(frame)], CENTER, 3);
	}
	else RENDER->CenterRender(IMAGE->FindImage("bos2"), CENTER, 3);
	if (SCENE->colorper >= 80)
	{
		RENDER->CenterRender(die[int(b_die)], bpos, 3);
	}
}

void boss_2::UIRender()
{
}
