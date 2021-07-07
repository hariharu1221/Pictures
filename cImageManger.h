#pragma once
#include "singleton.h"
class cImageManger :
	public singleton<cImageManger>
{
	map<string, cTexture*> m_images;
public:
	cImageManger();
	~cImageManger();
	void AddImage(const string& key, const string& path, int count = 0);
	void ReloadImage(const string& key);
	cTexture* FindImage(const string& key);
	vector<cTexture*> MakeVecImg(const string& key);
};

#define IMAGE cImageManger::GetInstance()