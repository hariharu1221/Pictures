#pragma once
class RandomMgr :
	public singleton<RandomMgr>
{
public:
	RandomMgr()
		:rd(), gen(rd()), r() {}

	~RandomMgr() { ; };

	int INT(int min, int max);
	Vec2 Vecc2(Vec2 origin);

	random_device rd;
	mt19937 gen;
	uniform_int_distribution<int> r;
};

#define RANDOM RandomMgr::GetInstance()