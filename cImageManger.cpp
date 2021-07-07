#include "DXUT.h"
#include "cImageManger.h"

cImageManger::cImageManger()
{
}

cImageManger::~cImageManger()
{
	for (auto iter : m_images)
	{
		iter.second->ptr->Release();
		SAFE_DELETE(iter.second);
	}
	m_images.clear();
}

void cImageManger::AddImage(const string& key, const string& path, int count)
{
	auto find = m_images.find(key);
	char Path[128];
	if (count == 0)
	{
		sprintf(Path, "./Resource/Image/%s.png", path.c_str());
		if (find == m_images.end())
		{
			LPDIRECT3DTEXTURE9 ptr;
			D3DXIMAGE_INFO info;
			if (D3DXCreateTextureFromFileExA(g_device, Path, -2, -2, 0, 0,
				D3DFMT_UNKNOWN, D3DPOOL_MANAGED, -1, -1, 0, &info, nullptr, &ptr) == S_OK)
			{
				cTexture* texture = new cTexture(ptr, info);
				m_images.insert(make_pair(key, texture));
			}
		}
	}
	else
	{
		char Key[128];
		for (int i = 0; i < count; i++)
		{
			sprintf(Path, "./Resource/Image/%s (%d).png", path.c_str(), i);
			sprintf(Key, "%s%d", key.c_str(), i);
			if (find == m_images.end())
			{
				LPDIRECT3DTEXTURE9 ptr;
				D3DXIMAGE_INFO info;
				if (D3DXCreateTextureFromFileExA(g_device, Path, -2, -2, 0, 0,
					D3DFMT_UNKNOWN, D3DPOOL_MANAGED, -1, -1, 0, &info, nullptr, &ptr) == S_OK)
				{
					cTexture* texture = new cTexture(ptr, info);
					m_images.insert(make_pair(Key, texture));

				}
			}
		}
	}
}

void cImageManger::ReloadImage(const string& key)
{
	cTexture* temp = FindImage(key);
	if (temp == nullptr)
	{
		AddImage(key, key);
	}
	else
	{
		temp->ptr->Release();
		SAFE_DELETE(temp);
		m_images.erase(key);
	}
	IMAGE->AddImage(key, key);
}

cTexture* cImageManger::FindImage(const string& key)
{
	auto find = m_images.find(key);
	if (find == m_images.end()) return nullptr;
	return find->second;
}

vector<cTexture*> cImageManger::MakeVecImg(const string& key)
{
	vector<cTexture*> m_vecimg;
	for (int i = 0;; i++)
	{
		char Key[128];
		sprintf(Key, "%s%d", key.c_str(), i);
		auto find = FindImage(Key);
		if (find == nullptr) break;
		m_vecimg.push_back(find);
	}
	return m_vecimg;
}
