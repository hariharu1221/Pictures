#include "DXUT.h"
#include "boss_3.h"
#include "cMBullet.h"

boss_3::boss_3(vector<cBullet*>& bullet)
	:m_bullet(bullet)
{
	m_ani = IMAGE->MakeVecImg("boss3b");
	speed = 80;
}

boss_3::~boss_3()
{
}

void boss_3::Update(Vec2 m_pos, int cell[][CELLSIZEY])
{
	if (bulskill == false && SCENE->colorper < 70) Move();
	if (SCENE->colorper < 80) Skill(m_pos);
	Limit(cell);

	if (SCENE->colorper >= 70)
	{
		b_die += Delta * 10;
		if (b_die >= die.size()) b_die = die.size() - 1;
	}
}

void boss_3::Move()
{
	if (dir == 0 && bpos.x > 0)
	{
		bpos.x -= Delta * speed;
		m_ani = IMAGE->MakeVecImg("boss3l");
	}
	if (dir == 1 && bpos.x < 1920)
	{
		bpos.x += Delta * speed;
		m_ani = IMAGE->MakeVecImg("boss3r");
	}
	if (dir == 2 && bpos.y > 0)
	{
		bpos.y -= Delta * speed;
		m_ani = IMAGE->MakeVecImg("boss3t");
	}
	if (dir == 3 && bpos.y < 1080)
	{
		bpos.y += Delta * speed;
		m_ani = IMAGE->MakeVecImg("boss3b");
	}
}

void boss_3::Limit(int cell[][CELLSIZEY])
{
	if (bulskill == false) {
		if (bpos.x < 10) while (cell[int(bpos.x)][int(bpos.y)] == 3) bpos.x++;
		if (bpos.x > 1910) while (cell[int(bpos.x)][int(bpos.y)] == 3) bpos.x--;
		if (bpos.y < 10) while(cell[int(bpos.x)][int(bpos.y)] == 3) bpos.y++;
		if (bpos.y > 1070) while (cell[int(bpos.x)][int(bpos.y)] == 3) bpos.y--;
	}

	if (dir == 0 && cell[int(bpos.x)][int(bpos.y)] == 3)	//따먹은 땅으로 들어가지 않도록
		while (cell[int(bpos.x)][int(bpos.y)] == 3)
			bpos.x++;

	if (dir == 1 && cell[int(bpos.x)][int(bpos.y)] == 3)
		while (cell[int(bpos.x)][int(bpos.y)] == 3)
			bpos.x--;

	if (dir == 2 && cell[int(bpos.x)][int(bpos.y)] == 3)
		while (cell[int(bpos.x)][int(bpos.y)] == 3)
			bpos.y++;

	if (dir == 3 && cell[int(bpos.x)][int(bpos.y)] == 3)
		while (cell[int(bpos.x)][int(bpos.y)] == 3)
			bpos.y--;
}

void boss_3::Skill(Vec2 m_pos)
{
	frame += Delta * 5;							//프레임
	

	xgap = fabs(bpos.x - m_pos.x);				//보스와 플레이어 거리
	ygap = fabs(bpos.y - m_pos.y);

	if (xgap > ygap) {							//방향 조절
		if (bpos.x >= m_pos.x)
			dir = 0;
		if (bpos.x <= m_pos.x)
			dir = 1;
	}
	else {
		if (bpos.y >= m_pos.y)
			dir = 2;
		if (bpos.y <= m_pos.y)
			dir = 3;
	}

	b_skill += Delta;
	if (b_skill >= 4 && b_skill < 5) ready = true;
	if (b_skill > 5)							//스킬
	{
		speed = 160;
		bulskill = true;

		if (bpos.x >= m_pos.x)
			bpos.x -= Delta * speed;
		else if (bpos.x <= m_pos.x)
			bpos.x += Delta * speed;
		if (bpos.y >= m_pos.y)
			bpos.y -= Delta * speed;
		else if (bpos.y <= m_pos.y)
			bpos.y += Delta * speed;
	}

	if (b_skill >= 10) { speed = 80; b_skill = 0; bulskill = false; }

	if (beam > 0.05 && SCENE->colorper > 30)//5초마다 원형 불렛
	{
		float  angle = 0;

		float  rad = D3DX_PI * 2 / 20;
		for (float i = alphaacttime; i < 15.5 + alphaacttime; i += 0.02, angle = rad * i)
		{
			Vec2 Direction = Vec2(bpos.x + (cosf(angle) * 5), bpos.y + (sinf(angle) * 5));
			Direction = Direction - bpos;
			D3DXVec2Normalize(&Direction, &Direction);
			m_bullet.push_back(new cMBullet(bpos, Direction, 1, 10, 700, 2));
		}
		beam = 0;
		alphaacttime++;
		if (alphaacttime == 10) { alphaacttime = 0; beam = -4; }
	}

	beam += Delta;
}

void boss_3::Render()
{
	if (b_skill > 5.2) {
		if (ready)
		{
			frame = 0;
			m_ani = IMAGE->MakeVecImg("boss3sk1");
			ready = false;
		}
		if (frame >= m_ani.size()) { frame = 0; m_ani = IMAGE->MakeVecImg("boss3sk2"); }
		RENDER->CenterRender(m_ani[int(frame)], bpos, 3);
	}
	else
	{
		if (frame >= m_ani.size()) { frame = 0; }
		RENDER->CenterRender(m_ani[int(frame)], bpos, 3);
	}
	if (SCENE->colorper >= 80)
	{
		RENDER->CenterRender(die[int(b_die)], bpos, 3);
	}
}

void boss_3::UIRender()
{
}