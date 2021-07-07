#pragma once
#include "cBullet.h"

class TileMap
{
public:
	int hp = 5;							// 개체 정보
	int max_hp = 5;						//
	int speed = 2;						//
	Vec2 pos = Vec2(CENTER.x, float(B)); //
	Vec2 stop_pos;
public:
	static int cell[CELLSIZEX][CELLSIZEY];

	Vec2 first;
	Vec2 second;
	bool line;
	bool IsDrawing;
	bool nodamage = false;
	bool damage = false;
	bool hpal = false;

	bool start = false;
	bool gc = false;
	bool gv = false;

	bool retry = false;
	bool nextstage = false;
	bool title = false;

	float b_start = 0;

	float timer = 300;
	int coloring_cells = 0;
	int temp = 0;
	int cellxy = CELLSIZEX * CELLSIZEY;
	float frame;
	float bultime = 0;
	float skilltime = 0;
	float b_count = 4;
	float b_time = 0;
	float b_gc = 0;
	float b_gv = 0;
	
	float y = 0;
	int nowstage;

	POINT cc;

	cTimer* normal = nullptr;

	vector<cTexture*> m_ani;
	vector<cTexture*> m_start = IMAGE->MakeVecImg("start");
	vector<cTexture*> m_gv = IMAGE->MakeVecImg("gve");
	vector<cTexture*> m_gc = IMAGE->MakeVecImg("gc");
	vector<cBullet*>& m_bullet;
	vector<cTexture*> ani_bullet = IMAGE->MakeVecImg("damage");
	cTexture* stage_f;
	cTexture* stage_c;
	string stagename;

	static D3DXCOLOR SaveImage[CELLSIZEX][CELLSIZEY];
	static D3DXCOLOR Savebg[CELLSIZEX][CELLSIZEY];

	float coloring_per = 0;
	int cellcount = CELLSIZEX * CELLSIZEY;
	int changecount = 0;
	bool ccs = false;

	enum class KeyState
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};
	KeyState KEY;

	TileMap(vector<cBullet*>& m_bullet, const string stagename);
	~TileMap();

	void Init(int stage);
	void Update();
	void Render();
	void UIRender();
	void SUI();
	void Text(int alpha, int y);


	void Move();
	void Skill();
	void DrawLine();
	void DrawArea(int draw_flag = 0);
	void AutoFill();
	void SetUp();
	void ChangeScene();

	bool FloodFill(Vec2 pos, int target, int change);
	bool Near(KeyState dir, int target);
	int  Current();
};

