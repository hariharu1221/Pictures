#include "DXUT.h"
#include "cPlayer.h"
#include "cPBullet.h"

cPlayer::cPlayer(vector<cBullet*>& bullet)
	:m_bullet(bullet)
{
	m_Hp = SCENE->m_Hp;
	m_MaxHp = SCENE->m_MaxHp;
	m_Score = SCENE->m_Score;
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(playerAS);
	SCENE->m_Hp = m_Hp;
	SCENE->m_MaxHp = m_MaxHp;
	SCENE->m_Score = m_Score;
}

void cPlayer::Update(Vec2 m_pos)
{
	if (m_Hp <= 0)
		SCENE->ChangeScene("EndScene");
	if (playerAS) playerAS->Update();
	Move();
	FireBullet(m_pos);
	ItemUpdate();
	SCENE->v_pos = m_pos;

	b_ani += Delta * 5;
	if (b_ani > m_ani.size()) b_ani = 0;
}

void cPlayer::Render(Vec2 m_pos)
{
	RENDER->CenterRender(m_ani[int(b_ani)], Vec2(m_pos.x, m_pos.y - 30), 0.7);
}

void cPlayer::UIRender()
{
}

void cPlayer::Move()
{
	
}

void cPlayer::FireBullet(Vec2 m_pos)
{
	if (INPUT->KeyPress(90) && b_fire)
	{
		m_bullet.push_back(new cPBullet(m_pos));
		playerAS = new cTimer(0.1, [&]()->void { b_fire = true; playerAS = nullptr; });
		b_fire = false;
	}
}

void cPlayer::ItemUpdate()
{
	if (m_Hp >= 6) m_Hp = 6;
	if (ItemName == "Heal")
	{
		m_Hp += 2;
		ItemName = "none";
	}
}
