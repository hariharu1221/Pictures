#pragma once
class cCameraManager
	: public singleton<cCameraManager>
{
public:
	RECT rect;
	POINT centerPt;
	D3DVIEWPORT9 vp;

	D3DXMATRIX m_matView, m_matProj;
	D3DXVECTOR3 m_Eye, m_At, m_Up;
	DWORD m_dwElapsedTime;
	LPD3DXFONT m_pFont;

	DWORD dwCurTime;
	static DWORD dwOldTime;

	float moveSpeed = 0.02f;
	float rotSpeed = 0.1f;

	bool isClip;

public:

	cCameraManager();
	~cCameraManager();

	void Init();
	void Update();
	void SetPos();
	void SetRot();
};

#define CAMERA cCameraManager::GetInstance()