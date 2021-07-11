#include "DXUT.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	SCENE->PlayerInit();
	set = true;
	option = false;
	mciSendString(L"play ./Resource/sound/title.mp3 repeat", NULL, 0, NULL);
}

void TitleScene::Update()
{
	if (set)
	{
		SCENE->ResetScnee("Stage_1_0", new Stage_1_0);
		SCENE->ResetScnee("Stage_2_0", new Stage_2_0);
		SCENE->ResetScnee("Stage_3_0", new Stage_3_0);
	}
	if (option == false)
	{
		if (INPUT->PointUp(VK_LBUTTON, { 380,810,670,940 })) { option = true; mciSendString(L"play ./Resource/sound/button.mp3", NULL, 0, NULL);
		}
		if (INPUT->PointUp(VK_LBUTTON, { 790,810,1080,940 })) {  mciSendString(L"play ./Resource/sound/button.mp3", NULL, 0, NULL); SCENE->ChangeScene("Stage_1_0");
		}
		if (INPUT->PointUp(VK_LBUTTON, { 1200,810,1490,940 })) { mciSendString(L"play ./Resource/sound/button.mp3", NULL, 0, NULL) ; exit(0);
		}
	}

}

void TitleScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("tbasic"), CENTER, 1.2);
	if (INPUT->PointOn(VK_LBUTTON, { 380,810,670,940 }))	RENDER->CenterRender(IMAGE->FindImage("credit_b"), CENTER, 1.2);
	if (INPUT->PointOn(VK_LBUTTON, { 790,810,1080,940 }))	RENDER->CenterRender(IMAGE->FindImage("start_b"), CENTER, 1.2);
	if (INPUT->PointOn(VK_LBUTTON, { 1200,810,1490,940 }))	RENDER->CenterRender(IMAGE->FindImage("exit_b"), CENTER, 1.2);

	if (INPUT->PointPress(VK_LBUTTON, { 380,810,670,940 }))	RENDER->CenterRender(IMAGE->FindImage("credit_d"), Vec2(966, 540), 1.2);
	if (INPUT->PointPress(VK_LBUTTON, { 790,810,1080,940 }))	RENDER->CenterRender(IMAGE->FindImage("start_d") , CENTER, 1.2);
	if (INPUT->PointPress(VK_LBUTTON, { 1200,810,1490,940 }))	RENDER->CenterRender(IMAGE->FindImage("exit_d"), CENTER, 1.2);
	if (option) {
		RENDER->CenterRender(IMAGE->FindImage("credit"), CENTER, 1.2);
		if (INPUT->KeyDown(VK_ESCAPE)) { option = false; }
	}
}

void TitleScene::ObRender()
{
}

void TitleScene::UIRender()
{
}

void TitleScene::Release()
{
	mciSendString(L"stop ./Resource/sound/title.mp3", NULL, 0, NULL);
}
