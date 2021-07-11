#include "DXUT.h"
#include "cParticleAni.h"
#include "cParticleLine.h"
#include "cParticleManager.h"

cParticleManager::cParticleManager()
{
}

cParticleManager::~cParticleManager()
{
	Release();
}

void cParticleManager::AddParticle(Vec2 pos, float size, const string& key)
{
	cParticle* par = new cParticleAni(pos, size, key);
	m_particles.push_back(par);
}

void cParticleManager::AddParticleLine(Vec2 pos, float size, const string& key)
{
	cParticle* par = new cParticleLine(pos, size, key);
	m_particlelines.push_back(par);
}

void cParticleManager::Update()
{
	for (auto iter : m_particles) iter->Update();

	for (auto iter = m_particles.begin(); iter != m_particles.end();)
	{
		if ((*iter)->isDestroy)
		{
			SAFE_DELETE((*iter));
			iter = m_particles.erase(iter);
		}
		else
			iter++;
	}

	for (auto iter : m_particlelines) iter->Update();

	for (auto iter = m_particlelines.begin(); iter != m_particlelines.end();)
	{
		if (SCENE->line == true || SCENE->damage == true)
		{
			SAFE_DELETE((*iter));
			iter = m_particlelines.erase(iter);
		}
		else
			iter++;
	}
}

void cParticleManager::Render()
{
	for (auto iter : m_particles) iter->Render();
	for (auto iter : m_particlelines) iter->Render();
}

void cParticleManager::Release()
{
	for (auto iter : m_particles) SAFE_DELETE(iter);
	m_particles.clear();
	for (auto iter : m_particlelines) SAFE_DELETE(iter);
	m_particlelines.clear();
}
