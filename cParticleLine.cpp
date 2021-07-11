#include "DXUT.h"
#include "cParticleLine.h"

cParticleLine::cParticleLine(Vec2 pos, float size, const string& key)
	:cParticle(pos, size)
{
	m_images = IMAGE->MakeVecImg(key);
	isDestroy = false;

}

cParticleLine::~cParticleLine()
{
	SAFE_DELETE(m_ani);
}

void cParticleLine::Update()
{
	if (m_ani != nullptr) m_ani->Update();
	if (m_bOnce)
	{
		m_ani = new cTimer(0.02, [&]()->void {
			m_frame++;
			if (m_frame == m_images.size() - 1)
				m_frame = 0;
			}, 1);
		m_bOnce = false;
	}
}

void cParticleLine::Render()
{
	RENDER->CenterRender(m_images[m_frame], m_pos, RenderSize);
}
