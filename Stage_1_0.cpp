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
	mciSendString(L"play ./Resource/sound/stage_1.mp3 repeat", NULL, 0, NULL);
	srand(time(NULL));
	bullet = new cBulletAdmin();
	player = new cPlayer(bullet->m_bullets);
	boss = new boss_1(bullet->m_bullets);
	tile = new TileMap(bullet->m_bullets, "Stage_1_0");
	tile->Init(stage);
	mob.push_back(new mob_1(bullet->m_bullets, { 400, 300 }));
	mob.push_back(new mob_1(bullet->m_bullets, { 1700, 200 }));
	mob.push_back(new mob_1(bullet->m_bullets, { 500, 700 }));
	mob.push_back(new mob_1(bullet->m_bullets, { 1600, 800 }));
	coll = new cCollison(bullet->m_bullets, mob, tile, 200);
}

void Stage_1_0::Update()
{
	player->Update(tile->pos);
	if (SCENE->theworld == false) {
		boss->Update(tile->pos, tile->cell);
		for (auto iter = mob.begin(); iter != mob.end(); iter++)	(*iter)->Update(tile->pos, tile->cell);
		bullet->Update();
	}
	coll->Update(0, boss->bpos);
	tile->Update();
	M_Destroy();
}

void Stage_1_0::Render()
{
	tile->Render();
	bullet->Render();
}

void Stage_1_0::ObRender()
{
	for (auto iter : mob) iter->Render();
	boss->Render();
	player->Render(tile->pos);
}

void Stage_1_0::UIRender()
{
	tile->SUI();
	player->UIRender();
}

void Stage_1_0::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(tile);
	SAFE_DELETE(boss);
	SAFE_DELETE(coll);
	for (auto iter : mob)	SAFE_DELETE(iter);
	mciSendString(L"stop ./Resource/sound/stage_1.mp3", NULL, 0, NULL);
}

void Stage_1_0::M_Destroy() //몬스터 파괴 및 조건
{
	size_t size = mob.size();
	for (size_t i = 0; i < size; i++)
	{
		auto& iter = mob[i];
		if (tile->cell[int(iter->mob_p.x)][int(iter->mob_p.y)] == 3)
		{
			mciSendString(L"stop ./Resource/sound/mdie.mp3", NULL, 0, NULL);
			mciSendString(L"play ./Resource/sound/mdie.mp3", NULL, 0, NULL);
			PART->AddParticle(iter->mob_p, 1, "mdie");
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