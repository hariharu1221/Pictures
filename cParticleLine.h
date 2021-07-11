#pragma once
#include "cParticle.h"
class cParticleLine :
    public cParticle
{
public:
    cParticleLine(Vec2 pos, float size, const string& key);
    virtual ~cParticleLine();

    vector<cTexture*> m_images;
    cTimer* m_ani = nullptr;
    int m_frame = 0;
    bool m_bOnce = true;

    virtual void Update() override;
    virtual void Render() override;
};

