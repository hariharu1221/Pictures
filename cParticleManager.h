#pragma once
#include "singleton.h"
class cParticleManager :
    public singleton<cParticleManager>
{
    vector<cParticle*> m_particles;
    vector<cParticle*> m_particlelines;
public:
    cParticleManager();
    ~cParticleManager();

    void AddParticle(Vec2 pos, float size, const string& key);
    void AddParticleLine(Vec2 pos, float size, const string& key);
    void Update();
    void Render();
    void Release();
};

#define PART cParticleManager::GetInstance()