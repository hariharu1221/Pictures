#include "DXUT.h"
#include "Stage_3_0.h"

Stage_3_0::Stage_3_0()
{
}

Stage_3_0::~Stage_3_0()
{
}

void Stage_3_0::Init()
{
	srand(time(NULL));
	bullet = new cBulletAdmin();
	player = new cPlayer(bullet->m_bullets);
	boss = new boss_4(bullet->m_bullets);
	tile = new TileMap(bullet->m_bullets, "Stage_3_0");
	tile->Init(stage);
	mob.push_back(new mob_4(bullet->m_bullets, { 400, 300 }));
	mob.push_back(new mob_4(bullet->m_bullets, { 1700, 200 }));
	mob.push_back(new mob_4(bullet->m_bullets, { 500, 700 }));
	mob.push_back(new mob_4(bullet->m_bullets, { 1600, 800 }));
	coll = new cCollison(bullet->m_bullets, mob, tile, 200);
}

void Stage_3_0::Update()
{
	player->Update(tile->pos);
	boss->Update(tile->pos, tile->cell);
	for (auto iter = mob.begin(); iter != mob.end(); iter++)	(*iter)->Update(tile->pos, tile->cell);
	bullet->Update();
	coll->Update(0, boss->bpos);
	tile->Update();
	M_Destroy();
}

void Stage_3_0::Render()
{
	tile->Render();
	for (auto iter : mob) iter->Render();
	player->Render(tile->pos);
	boss->Render();
	bullet->Render();
}

void Stage_3_0::UIRender()
{
	tile->UIRender();
	tile->SUI();
}

void Stage_3_0::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(tile);
	SAFE_DELETE(boss);
	SAFE_DELETE(coll);
	for (auto iter : mob)	SAFE_DELETE(iter);
}

void Stage_3_0::M_Destroy() //몬스터 파괴 및 조건
{
	size_t size = mob.size();
	for (size_t i = 0; i < size; i++)
	{
		auto& iter = mob[i];
		if (tile->cell[int(iter->mob_p.x)][int(iter->mob_p.y)] == 3)
		{
			SAFE_DELETE(iter);
			mob.erase(mob.begin() + i);
			i--; size--;
		}
	}
}