#include "DXUT.h"
#include "mob_4.h"
#include "cMABullet.h"

mob_4::mob_4(vector<cBullet*>& bullet, Vec2 mob_p)
	: mob_1(bullet, mob_p)
{
	size = 80;
	m_ani = IMAGE->MakeVecImg("mob4l");

	b_skill = rand() % 10;
	speed = 70;
}

mob_4::~mob_4()
{
}

void mob_4::Update(Vec2 m_pos, int cell[][CELLSIZEY])
{
	Move(cell);
	Skill(m_pos);
}

void mob_4::Move(int cell[][CELLSIZEY])
{
	if (b_move > 6) b_move = 0;
	if (b_move == 0)
		dir = rand() % 4;

	char str[256];
	if (dir == 0 && mob_p.x > 0)
	{
		mob_p.x -= Delta * speed;
		sprintf(str, "mob4l");
		m_ani = IMAGE->MakeVecImg(str);
	}
	if (dir == 1 && mob_p.x < 1920)
	{
		mob_p.x += Delta * speed;
		sprintf(str, "mob4r");
		m_ani = IMAGE->MakeVecImg(str);
	}
	if (dir == 2 && mob_p.y > 0)
	{
		mob_p.y -= Delta * speed;
		sprintf(str, "mob4t");
		m_ani = IMAGE->MakeVecImg(str);
	}
	if (dir == 3 && mob_p.y < 1080)
	{
		mob_p.y += Delta * speed;
		sprintf(str, "mob4b");
		m_ani = IMAGE->MakeVecImg(str);
	}
	if (mob_p.x < 0) mob_p.x = 1;
	if (mob_p.x > 1920) mob_p.x = 1919;
	if (mob_p.y < 0) mob_p.y = 1;
	if (mob_p.y > 1080) mob_p.y = 1079;

	if (dir == 0 && cell[int(mob_p.x)][int(mob_p.y)] == 3)
		while (cell[int(mob_p.x)][int(mob_p.y)] == 3)
			mob_p.x++;

	if (dir == 1 && cell[int(mob_p.x)][int(mob_p.y)] == 3)
		while (cell[int(mob_p.x)][int(mob_p.y)] == 3)
			mob_p.x--;

	if (dir == 2 && cell[int(mob_p.x)][int(mob_p.y)] == 3)
		while (cell[int(mob_p.x)][int(mob_p.y)] == 3)
			mob_p.y++;

	if (dir == 3 && cell[int(mob_p.x)][int(mob_p.y)] == 3)
		while (cell[int(mob_p.x)][int(mob_p.y)] == 3)
			mob_p.y--;

	b_move += 0.1;
}

void mob_4::Skill(Vec2 m_pos)
{
	frame += Delta * 5;
	if (frame >= m_ani.size()) { frame = 0; }

	xgap = fabs(mob_p.x - m_pos.x);
	ygap = fabs(mob_p.y - m_pos.y);
	b_skill += Delta;
	if (b_skill >= 6)
	{
		speed = 160;
		if (xgap > ygap) {
			if (mob_p.x >= m_pos.x)
				dir = 0;
			if (mob_p.x <= m_pos.x)
				dir = 1;
		}
		else {
			if (mob_p.y >= m_pos.y)
				dir = 2;
			if (mob_p.y <= m_pos.y)
				dir = 3;
		}
	}

	if (b_skill >= 10) { speed = 80; b_skill = 0; }

	if (bultime > 1) //1초마다 기본 불렛
	{
		Vec2 pos;
		D3DXVec2Normalize(&pos, &(m_pos - mob_p));
		m_bullet.push_back(new cMABullet(Vec2(mob_p.x + 70, mob_p.y), pos, 1, 10, 700, 1));
		bultime = 0;
	}

	bultime += Delta;
}