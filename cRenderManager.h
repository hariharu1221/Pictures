#pragma once
#include "singleton.h"
class cRenderManager :
	public singleton<cRenderManager>
{
	struct VertexType
	{
		Vec3 m_pos;
		Vec2 m_uv;
		inline static constexpr DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	};

public:
	cRenderManager();
	~cRenderManager();

	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DINDEXBUFFER9 m_ib;

	Vec3 camPos, camLook, camUp, projPos;
	D3DXMATRIXA16 matView, matProj;
	float speed;

	Vec3 ncamPos, ncamLook, ncamUp, nprojPos;
	bool jsize = false;
	bool campos = false;
	bool camrot = false;
	bool size[3];
	float timer = 0;

	float tospeed[3] = { 1,1,1 };
	float acc[3] = { 1,1,1 };

	void Update();
	void ToCamPos(Vec3 pos, float speed, float acc);
	void ToCamRot(Vec3 rot, float speed, float acc);
	void TojSize(float size, float speed, float acc);
	void PlusCamPos(Vec3 pos);
	void PlusCamRot(Vec3 rot);
	void PlusjSize(float size);
	void SetCam();
	void Set();
	void CamTo();
	void CenterRender(cTexture* ptr, Vec2 pos, float size = 1, float rot = 0);
};

#define RENDER cRenderManager::GetInstance()