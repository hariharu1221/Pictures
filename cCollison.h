#pragma once
#include "cBullet.h"
#include "mob_1.h"
#include "TileMap.h"
class cCollison
{
public:
	cCollison(vector<cBullet*>& bullet, vector<mob_1*>& mob, TileMap* m_player, int centerboss = 0);
	~cCollison();

	vector<cBullet*>& m_bullet;
	vector<mob_1*>& m_mob;
	TileMap* m_player;

	Vec2 bpos;
	LPD3DXLINE line;

	RECT MP;
	RECT MBP;
	RECT BMP;
	RECT BPT;

	bool b_PMcoll = true;
	int centerboss;
	int colsize;

	void Update(int bosspatern = 0, Vec2 bpos = CENTER);

	void MPColl();
	void MBPColl();
	void BMPColl();
	void BPTColl(int bosspatern);
	void Rtdraw(RECT rt);
	void Render();
};

