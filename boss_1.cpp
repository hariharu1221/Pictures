#include "DXUT.h"
#include "boss_1.h"
#include "cMBullet.h"
#include "cMABullet.h"

boss_1::boss_1(vector<cBullet*>& bullet)
	:m_bullet(bullet)
{
	
}

boss_1::~boss_1()
{
}

void boss_1::Update(Vec2 m_pos)
{
	if (SCENE->colorper < 70) Skill(m_pos);

	if (SCENE->colorper >= 70)
	{
		b_die += Delta * 10;
		if (b_die >= die.size()) b_die = die.size() - 1;
	}
}

void boss_1::Skill(Vec2 m_pos)
{
	frame += Delta * 4;
	if (frame >= m_ani.size())
		frame = 0;

	if (bultime > 0.5) //0.5초마다 기본 불렛
	{
		Vec2 pos;
		D3DXVec2Normalize(&pos, &(m_pos - bpos));
		m_bullet.push_back(new cMBullet(bpos, pos, 1, 10, 700, 1));
		bultime = 0;
	}

	if (skilltime > 2.5 )//5초마다 원형 불렛
	{
		float  angle = 0;

		float  rad = D3DX_PI * 2 / 30;
		for (float i = acttime; i < 15.5 + acttime; i += 0.01, angle = rad * i)
		{
			Vec2 Direction = Vec2(bpos.x + (cosf(angle) * 5), bpos.y + (sinf(angle) * 5));
			Direction = Direction - bpos;
			D3DXVec2Normalize(&Direction, &Direction);
			m_bullet.push_back(new cMBullet(bpos, Direction, 1, 10, 700, 2));
		}
		skilltime = 0;
		acttime++;
		if (acttime == 23) { acttime = 0; skilltime = -1; }
	}

	else if (busttime > 0.2 && SCENE->colorper > 30) //7초마다 360도 불렛
	{
		float  angle = 0;

		float  rad = D3DX_PI * 2 / 45;
		for (float i = acttime; i < 15.5 + acttime; i++, angle = rad * i)
		{
			Vec2 Direction = Vec2(bpos.x + (cosf(angle) * 5), bpos.y + (sinf(angle) * 5));
			Direction = Direction - bpos;
			D3DXVec2Normalize(&Direction, &Direction);
			m_bullet.push_back(new cMBullet(bpos, Direction, 1, 10, 700, 1));
		}
		busttime = 0;
		acttime++;
		if (acttime == 30) { acttime = 0; busttime = -7; }
	}

	beam += Delta;
	bultime += Delta;
	skilltime += Delta;
	b_time += Delta;
	busttime += Delta;
}

void boss_1::Render()
{
	RENDER->CenterRender(m_ani[int(frame)], CENTER, 2);
	if (SCENE->colorper >= 80)
	{
		RENDER->CenterRender(die[int(b_die)], bpos, 3);
	}
}

void boss_1::UIRender()
{
}
