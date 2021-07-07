#include "DXUT.h"
#include "T_BG.h"

T_BG::T_BG()
{
}

T_BG::~T_BG()
{
}

void T_BG::Init(IDirect3DDevice9* pdDevice)
{
	D3DXCreateTextureFromFileEx(
		pdDevice
		, L"./Texture/Title_bg.jpg"
		, 0
		, 0
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, 0x00000001
		, 0x00000001
		, 0xf0000001
		, &m_Img
		, NULL
		, &m_Tex
	);

	D3DXMatrixTransformation2D(&mat, &m_pos, 0, &size, &m_pos, 0, &m_pos);
}

void T_BG::Update()
{

}

void T_BG::Render(ID3DXSprite* pdSprite)
{
	pdSprite->SetTransform(&mat);
	pdSprite->Draw(
		m_Tex
		, nullptr
		, nullptr
		, &v_pos
		, D3DXCOLOR(1, 1, 1, 1)
	);
}

void T_BG::Release()
{
	SAFE_RELEASE(m_Tex);
}
