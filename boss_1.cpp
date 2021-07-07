#include "DXUT.h"
#include "boss_1.h"
#include "cMBullet.h"
#include "cMABullet.h"

boss_1::boss_1(vector<cBullet*>& bullet)
	:m_bullet(bullet)
{
	D3DXVec2Normalize(&dir, &(Vec2(rand() % 1920, rand() % 1080) - bpos));
}

boss_1::~boss_1()
{
}

void boss_1::Update(Vec2 m_pos, int cell[][CELLSIZEY])
{
	if (SCENE->colorper < 70) { Skill(m_pos); Move(cell); }

	if (SCENE->colorper >= 70)
	{
		b_die += Delta * 100;
		if (b_die >= die.size()) b_die = die.size() - 1;
	}
}

void boss_1::Move(int cell[][CELLSIZEY])
{
	POINT c = { trunc(bpos.x) - 0, trunc(bpos.y) - 0 };

	for (int y = -110; y <= 110; y++)
		for (int x = -110; x <= 110; x++)
			if (cell[int(c.x + x)][int(c.y + y)] == 2)
				dir = RANDOM->Vecc2(bpos);
	bpos += dir * 200 * Delta;
}

void boss_1::Skill(Vec2 m_pos)
{
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
	RENDER->CenterRender(IMAGE->FindImage("boss"), bpos, 1);
	if (SCENE->colorper >= 80)
	{
		RENDER->CenterRender(die[int(b_die)], bpos, 3);
	}
}

void boss_1::UIRender()
{
}
