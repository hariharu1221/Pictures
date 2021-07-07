#include "DXUT.h"
#include "cCameraManager.h"

cCameraManager::cCameraManager()
{
}

cCameraManager::~cCameraManager()
{
}

DWORD cCameraManager::dwOldTime;

void cCameraManager::Init()
{
	isClip = true;
	//GetClientRect(m_hWnd, &rect);

	// 화면 밖으로 못 나가게 한다.
	POINT p1, p2;
	p1.x = rect.left;
	p1.y = rect.top;
	p2.x = rect.right;
	p2.y = rect.bottom;

	//ClientToScreen(m_hWnd, &p1);
	//ClientToScreen(m_hWnd, &p2);

	rect.left = p1.x;
	rect.top = p1.y;
	rect.right = p2.x;
	rect.bottom = p2.y;

	//ClipCursor(&rect);
	centerPt.x = (p1.x + p2.x) / 2;
	centerPt.y = (p1.y + p2.y) / 2;
	// 마우스를 중앙으로 고정시킨다.
	SetCursorPos(centerPt.x, centerPt.y);


	vp.X = 0;
	vp.Y = 0;
	vp.Width = rect.right - rect.left;
	vp.Height = rect.bottom - rect.top;
	vp.MinZ = 0.f;
	vp.MaxZ = 1.0;

	m_Eye.x = 20.f;
	m_Eye.y = 20.f;
	m_Eye.z = -30.f;

	m_At.x = 0.f;
	m_At.y = 0.f;
	m_At.z = 0.f;

	m_Up.x = 0.f;
	m_Up.y = 1.f;
	m_Up.z = 0.f;

	D3DXMatrixLookAtLH(&m_matView, &m_Eye, &m_At, &m_Up);
	g_device->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4, 1.f, 1.f, 100.f);
	g_device->SetTransform(D3DTS_PROJECTION, &m_matProj);
	g_device->SetViewport(&vp);
}

void cCameraManager::Update()
{
    dwCurTime = GetTickCount64();
    dwOldTime = GetTickCount64();
    m_dwElapsedTime = dwCurTime - dwOldTime;
    dwOldTime = dwCurTime;

    SetPos();
    SetRot();

    D3DXMatrixLookAtLH(&m_matView, &m_Eye, &m_At, &m_Up);
    g_device->SetTransform(D3DTS_VIEW, &m_matView);

    D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
    g_device->SetTransform(D3DTS_PROJECTION, &m_matProj);
    g_device->SetViewport(&vp);
}

void cCameraManager::SetPos()
{
    if (GetAsyncKeyState(0x57)) // 'W' key, front move
    {
        D3DXVECTOR3 Direction;
        D3DXVec3Normalize(&Direction, &(m_At - m_Eye));
        m_Eye += m_dwElapsedTime * Direction * moveSpeed;
        m_At += m_dwElapsedTime * Direction * moveSpeed;
    }

    if (GetAsyncKeyState(0x53)) // 'S' key, back move
    {
        D3DXVECTOR3 Direction;
        D3DXVec3Normalize(&Direction, &(m_At - m_Eye));
        m_Eye -= m_dwElapsedTime * Direction * moveSpeed;
        m_At -= m_dwElapsedTime * Direction * moveSpeed;
    }

    if (GetAsyncKeyState(0x41)) // 'A' key, left move
    {
        D3DXVECTOR3 UpNormal, ForwardNormal, Direction;
        D3DXVec3Normalize(&UpNormal, &m_Up);
        D3DXVec3Normalize(&ForwardNormal, &(m_At - m_Eye));
        D3DXVec3Cross(&Direction, &ForwardNormal, &UpNormal);
        D3DXVec3Normalize(&Direction, &Direction);
        m_Eye += m_dwElapsedTime * Direction * moveSpeed;
        m_At += m_dwElapsedTime * Direction * moveSpeed;
    }

    if (GetAsyncKeyState(0x44)) // 'D' key, right move
    {
        D3DXVECTOR3 UpNormal, ForwardNormal, Direction;
        D3DXVec3Normalize(&UpNormal, &m_Up);
        D3DXVec3Normalize(&ForwardNormal, &(m_At - m_Eye));
        D3DXVec3Cross(&Direction, &ForwardNormal, &UpNormal);
        D3DXVec3Normalize(&Direction, &Direction);
        m_Eye -= m_dwElapsedTime * Direction * moveSpeed;
        m_At -= m_dwElapsedTime * Direction * moveSpeed;
    }

    if (GetAsyncKeyState(0x51)) // 'Q' key, up move
    {
        m_Eye.y += m_dwElapsedTime * moveSpeed;
        m_At.y += m_dwElapsedTime * moveSpeed;
    }
    if (GetAsyncKeyState(0x45)) // 'E' key, down move
    {
        m_Eye.y -= m_dwElapsedTime * moveSpeed;
        m_At.y -= m_dwElapsedTime * moveSpeed;
    }
}

void cCameraManager::SetRot()
{
    POINT curPt;
    GetCursorPos(&curPt);
    DWORD _CurTime = GetTickCount();
    static DWORD _OldTime = GetTickCount();
    if (_CurTime - _OldTime > 500.f)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            if (isClip)
                isClip = false;
            else
                isClip = true;
            _OldTime = _CurTime;
        }
    }
    if (isClip)
    {
        SetCursorPos(centerPt.x, centerPt.y);

        if (curPt.y < centerPt.y) // mouse up look
        {
            D3DXVECTOR3 UpNormal;
            D3DXVec3Normalize(&UpNormal, &m_Up);
            m_At += m_dwElapsedTime * UpNormal * rotSpeed;
        }

        if (curPt.y > centerPt.y) // mouse down look
        {
            D3DXVECTOR3 UpNormal;
            D3DXVec3Normalize(&UpNormal, &m_Up);
            m_At -= m_dwElapsedTime * UpNormal * rotSpeed;
        }

        if (curPt.x < centerPt.x) // mouse left look
        {
            D3DXVECTOR3 UpNormal, ForwardNormal, Left;
            D3DXVec3Normalize(&UpNormal, &m_Up);
            D3DXVec3Normalize(&ForwardNormal, &(m_At - m_Eye));
            D3DXVec3Cross(&Left, &ForwardNormal, &UpNormal);
            D3DXVec3Normalize(&Left, &Left);
            m_At += m_dwElapsedTime * Left * rotSpeed;
        }

        if (curPt.x > centerPt.x) // mouse right look
        {
            D3DXVECTOR3 UpNormal, ForwardNormal, Right;
            D3DXVec3Normalize(&UpNormal, &m_Up);
            D3DXVec3Normalize(&ForwardNormal, &(m_At - m_Eye));
            D3DXVec3Cross(&Right, &ForwardNormal, &UpNormal);
            D3DXVec3Normalize(&Right, &Right);
            m_At -= m_dwElapsedTime * Right * rotSpeed;
        }
    }
}
