#pragma once
class boss_2
{
public:
	cTimer* playerAS = nullptr;
	vector<cTexture*> m_ani;
	Vec2 bpos = CENTER;
	vector<cTexture*> die = IMAGE->MakeVecImg("bdie");
	float b_die = 0;

	float m_Hp;
	float frame = 0;
	float bultime = 0;
	float skilltime = 0;
	float b_count = 4;
	float b_time = 0;

	int sk = 0;

	boss_2();
	~boss_2();

	void Update(Vec2 m_pos);
	void Skill(Vec2 m_pos);
	void Render();
	void UIRender();
};

