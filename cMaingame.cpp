#include "DXUT.h"
#include "cMaingame.h"
#include "TitleScene.h"
#include "EndScene.h"
#include "SelectScene.h"

cMaingame::cMaingame()
{
}

cMaingame::~cMaingame()
{
}

void cMaingame::Init()
{
    AddResource();
    SCENE->AddScene("TitleScene", new TitleScene);
    SCENE->AddScene("EndScene", new EndScene);
    SCENE->AddScene("SelectScene", new SelectScene);
    SCENE->AddScene("nullScene", new nullScene);
    SCENE->AddScene("Stage_1_0", new Stage_1_0);
    SCENE->AddScene("Stage_2_0", new Stage_2_0);
    SCENE->AddScene("Stage_3_0", new Stage_3_0);
    SCENE->ChangeScene("TitleScene");
    //CAMERA->Init();
}

void cMaingame::Update()
{
    RENDER->Update();
    SCENE->Update();
    INPUT->Update();
    PART->Update();
    //CAMERA->Update();
}

void cMaingame::Render()
{
    SCENE->Render();
    PART->Render();
    SCENE->ObRender();
    UI->Begin();
    SCENE->UIRender();
    UI->End();
}

void cMaingame::Release()
{
    cImageManger::ReleaseInstance();
    cInputManager::ReleaseInstance();
    cUIManager::ReleaseInstance();
    cSceneManager::ReleaseInstance();
    cRenderManager::ReleaseInstance();
    cParticleManager::ReleaseInstance();
}

void cMaingame::LostDevice()
{
    UI->Lost();
}

void cMaingame::ResetDevice()
{
    UI->Reset();
}

void cMaingame::AddResource()
{
    IMAGE->AddImage("stage_f", "stage_f");
    IMAGE->AddImage("stage_c", "stage_c");
    IMAGE->AddImage("tbasic", "title/basic");
    IMAGE->AddImage("start_b", "title/start_b");
    IMAGE->AddImage("start_d", "title/start_d");
    IMAGE->AddImage("2-0stage_f", "2-0stage_f");
    IMAGE->AddImage("2-0stage_c", "2-0stage_c");
    IMAGE->AddImage("3-0stage_f", "3-0stage_f");
    IMAGE->AddImage("3-0stage_c", "3-0stage_c");
    IMAGE->AddImage("exit_b", "title/exit_b");
    IMAGE->AddImage("exit_d", "title/exit_d");
    IMAGE->AddImage("credit_b", "title/credit_b");
    IMAGE->AddImage("credit_d", "title/credit_d");
    IMAGE->AddImage("hp", "hp");
    IMAGE->AddImage("camera", "camera");
    IMAGE->AddImage("boss", "boss");
    IMAGE->AddImage("boss2", "boss2");
    IMAGE->AddImage("boss3", "boss3");
    IMAGE->AddImage("mob1", "mob1");
    IMAGE->AddImage("mob2", "mob2");
    IMAGE->AddImage("mob3", "mob3");
    IMAGE->AddImage("mob4", "mob4");
    IMAGE->AddImage("mob5", "mob5");
    IMAGE->AddImage("mob6", "mob6");
    IMAGE->AddImage("back", "back");
    IMAGE->AddImage("z", "z");

    IMAGE->AddImage("start", "start/startgame", 26);
    IMAGE->AddImage("timebar", "timebar/timebar", 6);
    IMAGE->AddImage("bdie", "bdie/bdie", 30);
    IMAGE->AddImage("mdie", "mdie/mdie", 30);
    IMAGE->AddImage("player", "player/player", 9);
    IMAGE->AddImage("gve", "gv/gve/gve", 32);
    IMAGE->AddImage("gc", "gc/gc", 18);
    IMAGE->AddImage("2gve", "gv2/gve/gve", 31);
    IMAGE->AddImage("2gc", "gc2/gc", 23);
    IMAGE->AddImage("3gve", "gv3/gve/gve", 28);
    IMAGE->AddImage("3gc", "gc3/gc", 29);
    IMAGE->AddImage("part", "part/part", 12);
    IMAGE->AddImage("bdash", "bdash/dash", 9);
    IMAGE->AddImage("worldpart", "theworld/part", 8);

    IMAGE->AddImage("PBullet", "PBullet");
    IMAGE->AddImage("AB", "AlphaBlack");
    IMAGE->AddImage("credit", "credit");
    IMAGE->AddImage("selectS", "selectS");
    IMAGE->AddImage("ping", "ping");

    IMAGE->AddImage("bulletwhite", "bullet/bulletwhite");
    IMAGE->AddImage("bullet", "bullet/bullet", 4);
    IMAGE->AddImage("bulletworld", "bullet/bulletworld", 2);
    IMAGE->AddImage("bulletblue", "bullet/b_bullet", 8);
    IMAGE->AddImage("damage", "bullet/damage", 28);
}

