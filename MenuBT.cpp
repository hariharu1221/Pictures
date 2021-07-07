#include "DXUT.h"
#include "MenuBT.h"

MenuBT::MenuBT()
{
}

MenuBT::~MenuBT()
{
}

void MenuBT::Init(IDirect3DDevice9* pdDevice)
{
	TCHAR* Address[]{
		L"./Texture/main_ui_start.png"
		, L"./Texture/main_ui_start_d.png"
		, L"./Texture/main_ui_option.png"
		, L"./Texture/main_ui_option_d.png"
		, L"./Texture/main_ui_exit.png"
		, L"./Texture/main_ui_exit_d.png"
	};
	for (int i = 0; i < 6; i++) {
		D3DXCreateTextureFromFileEx(
			pdDevice
			, Address[i]
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
			, &m_Tex[i]
		);
	}
	m_cen = Vector2(m_Img.Width / 2, m_Img.Height / 2);
	D3DXMatrixTransformation2D(&mat, &m_cen, 0, &size, &m_cen, 0, nullptr);
}

void MenuBT::Update()
{
	if (INPUT->KeyDown(VK_ESCAPE)) exit(0);
	if (INPUT->KeyDown(VK_UP) && select > 1) select--;
	if (INPUT->KeyDown(VK_DOWN) && select < 3) select++;

	switch (select)
	{
	case 1:
		if(INPUT->KeyDown(VK_RETURN)) {
			SCENE->Title = false;
			SCENE->Stage_01 = true;
		}
		break;
	case 2:
		INPUT->KeyDown(VK_RETURN);
		break;
	case 3:
		if (INPUT->KeyDown(VK_RETURN)) {
			exit(0);
		}
		break;
	}
}

void MenuBT::Render(ID3DXSprite* pdSprite)
{
	pdSprite->SetTransform(&mat);
	if (select == 1)
		pdSprite->Draw(
			m_Tex[1]
			, nullptr
			, nullptr
			, &Vector3(600, -500, 0)
			, D3DXCOLOR(1, 1, 1, 1)
		);
	else
		pdSprite->Draw(
			m_Tex[0]
			, nullptr
			, nullptr
			, &Vector3(600, -500, 0)
			, D3DXCOLOR(1, 1, 1, 1)
		);
	if (select == 2)
		pdSprite->Draw(
			m_Tex[3]
			, nullptr
			, nullptr
			, &Vector3(600, -100, 0)
			, D3DXCOLOR(1, 1, 1, 1)
		);
	else
		pdSprite->Draw(
			m_Tex[2]
			, nullptr
			, nullptr
			, &Vector3(600, -100, 0)
			, D3DXCOLOR(1, 1, 1, 1)
		);
	if(select == 3)
		pdSprite->Draw(
			m_Tex[5]
			, nullptr
			, nullptr
			, &Vector3(600, 300, 0)
			, D3DXCOLOR(1, 1, 1, 1)
		);
	else
		pdSprite->Draw(
			m_Tex[4]
			, nullptr
			, nullptr
			, &Vector3(600, 300, 0)
			, D3DXCOLOR(1, 1, 1, 1)
		);
}

void MenuBT::Release()
{
	for (int i = 0; i < 6; i++) SAFE_RELEASE(m_Tex[i]);
}
