#include "DXUT.h"
#include "Stage_1_0.h"

Stage_1_0::Stage_1_0()
{
}

Stage_1_0::~Stage_1_0()
{
}

void Stage_1_0::Init()
{
	srand(time(NULL));
	bullet = new cBulletAdmin();
	player = new cPlayer(bullet->m_bullets);
	boss = new boss_2();
	tile = new TileMap(bullet->m_bullets, "Stage_1_0");
	tile->Init(stage);
	mob.push_back(new mob_2(bullet->m_bullets, { 400, 300 }));
	mob.push_back(new mob_2(bullet->m_bullets, { 1700, 200 }));
	mob.push_back(new mob_2(bullet->m_bullets, { 500, 700 }));
	mob.push_back(new mob_2(bullet->m_bullets, { 1600, 800 }));
	coll = new cCollison(bullet->m_bullets, mob, tile, 200);
}

void Stage_1_0::Update()
{
	player->Update(tile->pos);
	boss->Update(tile->pos);
	for (auto iter = mob.begin(); iter != mob.end(); iter++)	(*iter)->Update(tile->pos, tile->cell);
	M_Destroy();
	bullet->Update();
	coll->Update(boss->sk);
	tile->Update();
}

void Stage_1_0::Render()
{
	tile->Render();
	for (auto iter : mob) iter->Render();
	boss->Render();
	player->Render(tile->pos);
	bullet->Render();
}

void Stage_1_0::UIRender()
{
	tile->UIRender();
	tile->SUI();
}

void Stage_1_0::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(tile);
	SAFE_DELETE(boss);
	SAFE_DELETE(coll);
	for (auto iter : mob)	SAFE_DELETE(iter);
}

void Stage_1_0::M_Destroy() //몬스터 파괴 및 조건
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
	//for (auto iter = mob.begin(); iter != mob.end();)
	//{
	//	if (tile->cell[int((*iter)->mob_p.x)][int((*iter)->mob_p.y)] == 3)
	//	{
	//		SAFE_DELETE((*iter));
	//		mob.erase(iter);
	//		iter--;
	//	}
	//	else ++iter;
	//}