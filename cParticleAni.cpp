#include "DXUT.h"
#include "cParticleAni.h"

cParticleAni::cParticleAni(Vec2 pos, float size)
	:cParticle(pos, size)
{
	m_images = IMAGE->MakeVecImg("expl");
	//SOUND->Play("explosion-2")->SetVolume(-1800);
	isDestroy = false;
}

cParticleAni::~cParticleAni()
{
	SAFE_DELETE(m_ani);
}

void cParticleAni::Update()
{
	if (m_ani != nullptr) m_ani->Update();
	if (m_bOnce)
	{
		m_ani = new cTimer(0.02, [&]()->void {
			m_frame++;
			if (m_frame == m_images.size())
				isDestroy = true;
		}, 1);
		m_bOnce = false;
	}
}

void cParticleAni::Render()
{
	RENDER->CenterRender(m_images[m_frame], m_pos, RenderSize);
}
