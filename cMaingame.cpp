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
    PART->Render();
    SCENE->Render();
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
    IMAGE->AddImage("exit_b", "title/exit_b");
    IMAGE->AddImage("exit_d", "title/exit_d");
    IMAGE->AddImage("credit_b", "title/credit_b");
    IMAGE->AddImage("credit_d", "title/credit_d");

    IMAGE->AddImage("start", "start/startgame", 26);

    IMAGE->AddImage("hp", "hp");
    IMAGE->AddImage("player", "player");
    IMAGE->AddImage("PBullet", "PBullet");
    IMAGE->AddImage("2-0stage_f", "2-0stage_f");
    IMAGE->AddImage("2-0stage_c", "2-0stage_c");
    IMAGE->AddImage("3-0stage_f", "3-0stage_f");
    IMAGE->AddImage("3-0stage_c", "3-0stage_c");
    IMAGE->AddImage("timebar", "timebar");
    IMAGE->AddImage("ui_bg", "ui_bg");
    IMAGE->AddImage("AB", "AlphaBlack");
    IMAGE->AddImage("gvtext", "gv/gvb/gve");
    IMAGE->AddImage("gctext", "gc/gcb");
    IMAGE->AddImage("credit", "credit");
    IMAGE->AddImage("selectS", "selectS");
    IMAGE->AddImage("ping", "ping");


    IMAGE->AddImage("boss", "boss/1-2boss_file", 14);
    IMAGE->AddImage("bos2", "boss2/stop");
    IMAGE->AddImage("boss2r", "boss2/boss2l", 10);
    IMAGE->AddImage("boss2l", "boss2/boss2r", 10);
    IMAGE->AddImage("bullet", "bullet/bullet", 4);
    IMAGE->AddImage("bulletblue", "bullet/b_bullet", 8);
    IMAGE->AddImage("damage", "bullet/damage", 4);
    IMAGE->AddImage("mob1", "mob1/mob1", 5);
    IMAGE->AddImage("mob2", "mob2/mob2", 9);
    IMAGE->AddImage("mob2_skill", "mob2/mob2_skill", 9);
    IMAGE->AddImage("mob3rl", "mob3r/left/mob3", 3);
    IMAGE->AddImage("mob3rr", "mob3r/right/mob3", 3);
    IMAGE->AddImage("mob3rt", "mob3r/up/mob3", 3);
    IMAGE->AddImage("mob3rb", "mob3r/down/mob3", 3);
    IMAGE->AddImage("mob3bl", "mob3b/left/mob3", 3);
    IMAGE->AddImage("mob3br", "mob3b/right/mob3", 3);
    IMAGE->AddImage("mob3bt", "mob3b/up/mob3", 3);
    IMAGE->AddImage("mob3bb", "mob3b/down/mob3", 3);
    IMAGE->AddImage("boss3l", "boss3/left/boss3", 4);
    IMAGE->AddImage("boss3r", "boss3/right/boss3", 4);
    IMAGE->AddImage("boss3t", "boss3/up/boss3", 4);
    IMAGE->AddImage("boss3b", "boss3/down/boss3", 4);
    IMAGE->AddImage("boss3sk1", "boss3/ready/boss3", 4);
    IMAGE->AddImage("boss3sk2", "boss3/go/boss3", 2);
    IMAGE->AddImage("bdie", "bdie/die", 15);
    IMAGE->AddImage("gve", "gv/gve/gve", 7);
    IMAGE->AddImage("gc", "gc/gc", 15);
    IMAGE->AddImage("mob4l", "mob4/left/mob4", 4);
    IMAGE->AddImage("mob4r", "mob4/right/mob4", 4);
    IMAGE->AddImage("mob4t", "mob4/up/mob4", 4);
    IMAGE->AddImage("mob4b", "mob4/down/mob4", 4);
    IMAGE->AddImage("boss4l", "boss4/left/boss4", 4);
    IMAGE->AddImage("boss4r", "boss4/right/boss4", 4);
    IMAGE->AddImage("boss4t", "boss4/up/boss4", 4);
    IMAGE->AddImage("boss4b", "boss4/down/boss4", 4);
    //IMAGE->AddImage("boss4sk1", "boss4/ready/boss4", 4);
    IMAGE->AddImage("boss4sk2", "boss4/sk2/boss4", 6);
}

