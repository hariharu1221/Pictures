#include "DXUT.h"
#include "cParticleAni.h"

cParticleAni::cParticleAni(Vec2 pos, float size, const string& key)
	:cParticle(pos, size)
{
	m_images = IMAGE->MakeVecImg(key);
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
			if (m_frame == m_images.size() - 1)
				isDestroy = true;
		}, 1);
		m_bOnce = false;
	}
}

void cParticleAni::Render()
{
	RENDER->CenterRender(m_images[m_frame], m_pos, RenderSize);
}
