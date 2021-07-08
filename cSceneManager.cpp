#include "DXUT.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
{
	PlayerInit();
}

cSceneManager::~cSceneManager()
{
	Release();
}

void cSceneManager::Update()
{
	if (nowScene) nowScene->Update();
	if (nextScene)
	{
		if (nowScene) nowScene->Release();
		nextScene->Init();
		nowScene = nextScene;
		nextScene = nullptr;
		RENDER->SetCam();
	}
}

void cSceneManager::Render()
{
	if (nowScene) nowScene->Render();
}

void cSceneManager::UIRender()
{
	if (nowScene) nowScene->UIRender();
}

void cSceneManager::Release()
{
	if (nowScene) nowScene->Release();
	for (auto iter : m_scenes) SAFE_DELETE(iter.second);
	m_scenes.clear();
}

void cSceneManager::AddScene(string key, cScene* scene)
{
	m_scenes.insert(make_pair(key, scene));
}

void cSceneManager::ChangeScene(string key)
{
	auto find = m_scenes.find(key);
	nextScene = find->second;
}

void cSceneManager::ResetScnee(string key, cScene* scene)
{
	auto find = m_scenes.find(key);
	auto temp = find->second;
	SAFE_DELETE(temp);
	m_scenes.erase(key);
	m_scenes.insert(make_pair(key, scene));
}

void cSceneManager::ReloadScnee(string key, cScene* scene)
{
	SCENE->ChangeScene("nullScene");
	if (nowScene) nowScene->Release();
	nextScene->Init();
	nowScene = nextScene;
	nextScene = nullptr;
	auto find = m_scenes.find(key);
	auto temp = find->second;
	SAFE_DELETE(temp);
	m_scenes.erase(key);
	m_scenes.insert(make_pair(key, scene));
	SCENE->ChangeScene(key);
}

void cSceneManager::per(float cper, Vec2 pos)
{
	colorper = cper;
	v_pos = pos;
}

void cSceneManager::PlayerInit()
{
	m_Hp = 6;
	m_MaxHp = 100;
	m_Score = 0;
}