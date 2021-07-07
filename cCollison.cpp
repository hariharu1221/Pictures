#include "DXUT.h"
#include "cCollison.h"

cCollison::cCollison(vector<cBullet*>& bullet, vector<mob_1*>& mob, TileMap* player, int centerboss)
	:m_bullet(bullet), m_mob(mob), m_player(player), centerboss(centerboss)
{
	D3DXCreateLine(g_device, &line);
	line->SetAntialias(true);
	line->SetWidth(1);
}

cCollison::~cCollison()
{
	line->Release();
}

void cCollison::Update(int bosspatern, Vec2 bpos)
{
	this->bpos = bpos;
	if (m_player->damage == false)
	{
		MPColl();
		MBPColl();
		if (centerboss != 0) BMPColl();
		BPTColl(bosspatern);
	}
}

void cCollison::MPColl()
{
	for (auto iter = m_mob.begin(); iter != m_mob.end();)
	{
		if (7 + (*iter)->size >= D3DXVec2Length(&(m_player->pos - (*iter)->mob_p)) && m_player->cell[m_player->cc.x][m_player->cc.y] == 1)
		{
			MP = { long((*iter)->mob_p.x - (*iter)->mob_p.x), long((*iter)->mob_p.y - (*iter)->mob_p.y),
			long((*iter)->mob_p.x + (*iter)->mob_p.x), long((*iter)->mob_p.y + (*iter)->mob_p.y) };
			Rtdraw(MP);
			m_player->stop_pos = m_player->pos;
			m_player->hp -= 1;
			m_player->damage = true;
			m_player->pos = m_player->first;
			m_player->IsDrawing = true;
			m_player->DrawArea(3);
			break;
		}
		iter++;
	}
}

void cCollison::MBPColl()
{
	for (auto iter = m_bullet.begin(); iter != m_bullet.end();)
	{
		if ((*iter)->bulletType == "mob")
		{
			if (7 + (*iter)->size >= D3DXVec2Length(&(m_player->pos - (*iter)->m_pos)) && m_player->cell[m_player->cc.x][m_player->cc.y] == 1)
			{
				m_player->stop_pos = m_player->pos;
				m_player->hp -= 1;
				m_player->damage = true;
				m_player->pos = m_player->first;
				m_player->IsDrawing = true;
				m_player->DrawArea(3);
				//PART->AddParticle((*iter)->m_pos, 0.3);
				(*iter)->isDestroy = true;
			}
		}
		iter++;
	}
}

void cCollison::BMPColl()
{
	if (7 + centerboss >= D3DXVec2Length(&(m_player->pos - bpos)) && m_player->cell[m_player->cc.x][m_player->cc.y] == 1)
	{
		m_player->stop_pos = m_player->pos;
		m_player->hp -= 1;
		m_player->damage = true;
		m_player->pos = m_player->first;
		m_player->IsDrawing = true;
		m_player->DrawArea(3);
	}
}

void cCollison::BPTColl(int bosspatern)
{
	if (bosspatern == 0)
	{
		colsize = 1;
	}
	if (bosspatern == 1)
	{
		colsize += Delta * 20;
		if (7 + colsize >= D3DXVec2Length(&(m_player->pos - Vec2(855, 610))) && m_player->cell[m_player->cc.x][m_player->cc.y] == 1)
		{
			m_player->stop_pos = m_player->pos;
			m_player->hp -= 1;
			m_player->damage = true;
			m_player->pos = m_player->first;
			m_player->IsDrawing = true;
			m_player->DrawArea(3);
		}
	}
	if (bosspatern == 2)
	{
		colsize += Delta * 250;
		if (7 + colsize >= D3DXVec2Length(&(m_player->pos - Vec2(1085, 610))) && m_player->cell[m_player->cc.x][m_player->cc.y] == 1)
		{
			m_player->stop_pos = m_player->pos;
			m_player->hp -= 1;
			m_player->damage = true;
			m_player->pos = m_player->first;
			m_player->IsDrawing = true;
			m_player->DrawArea(3);
		}
	}
}

void cCollison::Rtdraw(RECT rt)
{
	if (coldraw)
	{
		Vec2* vs = new Vec2[5];
		vs[0] = { float(rt.left),float(rt.top) };
		vs[1] = { float(rt.right),float(rt.top) };
		vs[2] = { float(rt.right),float(rt.bottom) };
		vs[3] = { float(rt.left),float(rt.bottom) };
		vs[4] = { float(rt.left),float(rt.top) };

		line->Draw(vs, 5, D3DCOLOR_RGBA(0, 255, 0, 255));
		SAFE_DELETE_ARRAY(vs);
	}
}