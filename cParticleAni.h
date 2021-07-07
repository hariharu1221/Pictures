#pragma once
#include "cParticle.h"
class cParticleAni :
    public cParticle
{
public:
    cParticleAni(Vec2 pos, float size);
    virtual ~cParticleAni();

    vector<cTexture*> m_images;
    cTimer* m_ani = nullptr;
    int m_frame = 0;
    bool m_bOnce = true;

    virtual void Update() override;
    virtual void Render() override;
};

