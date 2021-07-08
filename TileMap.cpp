#include "DXUT.h"
#include "TileMap.h"
#include "cMBullet.h"

TileMap::TileMap(vector<cBullet*>& bullet, const string stagename)
	:m_bullet(bullet), stagename(stagename)
{
}

TileMap::~TileMap()
{
	SAFE_DELETE(normal);
}

int TileMap::cell[CELLSIZEX][CELLSIZEY] = { 0, };

D3DXCOLOR TileMap::SaveImage[CELLSIZEX][CELLSIZEY];
D3DXCOLOR TileMap::Savebg[CELLSIZEX][CELLSIZEY];

void TileMap::Init(int stage)
{
	nowstage = stage;
	switch (stage)
	{
	case 1:
		stage_f = IMAGE->FindImage("stage_f");
		stage_c = IMAGE->FindImage("stage_c");
		m_gv = IMAGE->MakeVecImg("gve");
		m_gc = IMAGE->MakeVecImg("gc");
		break;
	case 2:
		stage_f = IMAGE->FindImage("2-0stage_f");
		stage_c = IMAGE->FindImage("2-0stage_c");
		m_gv = IMAGE->MakeVecImg("gve2");
		m_gc = IMAGE->MakeVecImg("gc2");
		break;
	}
	SetUp();

	IsDrawing = true;
	DrawArea();
	IsDrawing = false;

	start = true;
}

void TileMap::Update()
{
	ChangeScene();
	Skill();
	if(gc == false && gv == false)	Move();
	cc = { int(pos.x - x_gap), int(pos.y - y_gap) };

	SCENE->per(coloring_per, pos);
	if (INPUT->KeyUp(VK_F1)) nextstage = true;
	if (INPUT->KeyUp(VK_F2)) speed = 8;
	if (INPUT->KeyUp(VK_F3)) hp++;
	if (INPUT->KeyUp(VK_ESCAPE)) SCENE->ChangeScene("TitleScene");

	if (camera) {
		RENDER->SetjSize(1.3);

		if (RENDER->camPos.x > pos.x - 870 || RENDER->camPos.x < pos.x - 1050
			|| RENDER->camPos.y > -pos.y + 650 || RENDER->camPos.y < -pos.y + 450)
		{
			if (btimer < 8)		btimer += Delta * 8;
			else btimer = 4;

			if (b_cpos < 4)	b_cpos += (Delta / 4) * btimer;
			else b_cpos = 4;
		}
		else
		{
			if (btimer > 1)		btimer -= Delta * 16;
			else btimer = 1;

			if (b_cpos > 1)		b_cpos -= (Delta / 4) * btimer;
			else b_cpos = 1;
		}

		if (RENDER->camPos.x > pos.x - 920)			RENDER->PlusCamPos(Vec3(-2 * b_cpos, 0, 0));
		else if (RENDER->camPos.x < pos.x - 1000)	RENDER->PlusCamPos(Vec3(2 * b_cpos, 0, 0));

		if (RENDER->camPos.y > -pos.y + 600)		RENDER->PlusCamPos(Vec3(0, -2 * b_cpos, 0));
		else if (RENDER->camPos.y < -pos.y + 500)	RENDER->PlusCamPos(Vec3(0, 2 * b_cpos, 0));

		//RENDER->SetCamPos(Vec3(pos.x - 960, -pos.y + 540, 0));
		if (INPUT->KeyDown('Y')) { camera = false; RENDER->SetCam(); }
	}
	else if (INPUT->KeyDown('Y')) camera = true;
}

void TileMap::Skill()
{
	frame += 0.5;
	if (frame == m_ani.size())
		frame = 0;

	if (b_time > 0.15 && damage) { b_count++; b_time = 0; }
	if (b_count >= ani_bullet.size())	{ b_count = 0; damage = false; }

	if (gc == false) timer -= Delta;
	if (damage) b_time += Delta * 5;
}

void TileMap::Move()
{
	if (INPUT->KeyPress(VK_UP) && pos.y >= 0)  //움직
	{ 
		for (size_t i = 0; i < speed; i++)
		{
			KEY = KeyState::UP;
			pos.y--;

			if (Current() == 1) //선일 경우
				pos.y++;

			if (pos.y < T)
				pos.y = T;

			if (Current() == 2)
			{
				DrawArea();
			}
			else
				if (!Near(KEY, 3))
					DrawLine();
		}
	}
	if (INPUT->KeyPress(VK_DOWN) && pos.y <= (WINSIZEY - 0)) 
	{ 
		for (size_t i = 0; i < speed; i++)
		{
			KEY = KeyState::DOWN;
			pos.y++;

			if (Current() == 1)
				pos.y--;

			if (pos.y > B)
				pos.y = B;

			if (Current() == 2)
				DrawArea();
			else
				if (!Near(KEY, 3))
					DrawLine();
		}
	}
	if (INPUT->KeyPress(VK_LEFT) && pos.x >= 0) 
	{ 
		for (size_t i = 0; i < speed; i++)
		{
			KEY = KeyState::LEFT;
			pos.x--;

			if (Current() == 1)
				pos.x++;

			if (pos.x < L)
				pos.x = L;

			if (Current() == 2)
				DrawArea();
			else
				if (!Near(KEY, 3))
					DrawLine();
		}
	}
	if (INPUT->KeyPress(VK_RIGHT) && pos.x <= (WINSIZEX - 0)) 
	{ 
		for (size_t i = 0; i < speed; i++)
		{
			KEY = KeyState::RIGHT;

			pos.x++;

			if (Current() == 1)
				pos.x--;

			if (pos.x > R - 1)
				pos.x = R - 1;

			if (Current() == 2)
				DrawArea();
			else
				if (!Near(KEY, 3))
					DrawLine();
		}
	}
}

void TileMap::DrawLine()
{
	IsDrawing = true;

	D3DLOCKED_RECT lr;
	stage_f->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);

	DWORD* pixel = (DWORD*)lr.pBits;
	POINT c = { pos.x - x_gap,pos.y - y_gap };
	int index = c.y * CELLSIZEX + c.x;
	cell[c.x][c.y] = 1;
	pixel[index] = D3DCOLOR_RGBA(0, 255, 255, 255);

	stage_f->ptr->UnlockRect(0);
}

void TileMap::DrawArea(int draw_flag)
{
	if (!IsDrawing) { first = pos; return; }
	IsDrawing = false;

	DrawArea(1);

	if (draw_flag == 2)
		if (changecount > cellcount) ccs = true;

	D3DLOCKED_RECT lr;
	stage_f->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	DWORD* pixel = (DWORD*)lr.pBits;
	cellcount = CELLSIZEX * CELLSIZEY;

	for (int y = CELLSIZEY - 1; y != -1; --y)
	{
		for (int x = CELLSIZEX - 1; x != -1; --x)
		{
			D3DXCOLOR Opacity = pixel[y * CELLSIZEX + x];
			switch (cell[x][y])
			{
			case 0:
				Opacity = D3DCOLOR_RGBA(int(Opacity.r * 255), int(Opacity.g * 255), int(Opacity.b * 255), 255);
				break;
			case 1:
				if (draw_flag == 1)
				{
					cell[x][y] = 3;
					Opacity = Savebg[x][y];
					break;
				}
				if (draw_flag == 3)
				{
					cell[x][y] = 0;
					Opacity = Savebg[x][y];
					break;
				}
				Opacity = D3DCOLOR_RGBA(int(SaveImage[x][y].r * 255), int(SaveImage[x][y].g * 255), int(SaveImage[x][y].b * 255), 0);

				second = { float(x),float(y) };
				cell[x][y] = 2;

				if (cell[x + 1][y] & cell[x - 1][y] == 3 || cell[x][y + 1] & cell[x][y - 1] == 3)
					cell[x][y] = 3;

				coloring_cells++;
			case 2:
				if ((cell[x + 1][y] == 3 && cell[x - 1][y] == 3)
					|| (cell[x][y + 1] == 3 && cell[x][y - 1] == 3))
					cell[x][y] = 3;
			case 3:
				if (cell[x][y] == 3)
					Opacity = SaveImage[x][y];
				cellcount--;
			}

			pixel[y * CELLSIZEX + x] = Opacity;
		}
	}

	DrawArea(1);
	stage_f->ptr->UnlockRect(0);

	if (draw_flag == 0)
		AutoFill();
}

void TileMap::AutoFill()
{
	if (second == Vec2(0, 0)) return;
	bool isOk = FloodFill({ second.x + 1, second.y + 1 }, 0, 100);

	if (isOk) FloodFill({ second.x + 1, second.y + 1 }, 100, 3);
	else
	{
		FloodFill({ second.x - 1, second.y + 1 }, 0, 3);
		FloodFill({ second.x + 1, second.y + 1 }, 100, 0);

		isOk = FloodFill({ second.x + 1, second.y - 1 }, 0, 100);

		if (isOk) FloodFill({ second.x + 1, second.y - 1 }, 100, 3);
		else
		{
			FloodFill({ second.x + 1, second.y + 1 }, 0, 3);
			FloodFill({ second.x + 1, second.y - 1 }, 100, 0);
		}
	}
	DrawArea(2);
	second = { 0,0 };
}

bool TileMap::FloodFill(Vec2 pos, int target, int change)
{
	if (target == change) return true;
	if (cell[(int)pos.x][(int)pos.y] != target) return true;

	queue<Vec2> v2q;

	bool add = false;
	temp = 0;

	if (change == 3)
		add = true;

	cell[(int)pos.x][(int)pos.y] = change;

	v2q.push(pos);

	if (add)
		temp++;


	while (!v2q.empty())
	{
		Vec2 n = v2q.front();
		v2q.pop();

		if (n.x == (int)(SCENE->bpos.x - x_gap) &&
			n.y == (int)(SCENE->bpos.y - y_gap) && drawbug == false)
			return false;
		if (cell[(int)n.x - 1][(int)n.y] == target)
		{
			cell[(int)n.x - 1][(int)n.y] = change;
			v2q.push({ n.x - 1, n.y });
			if (add)
				temp++;
		}
		if (cell[(int)n.x + 1][(int)n.y] == target)
		{
			cell[(int)n.x + 1][(int)n.y] = change;
			v2q.push({ n.x + 1, n.y });
			if (add)
				temp++;
		}
		if (cell[(int)n.x][(int)n.y - 1] == target)
		{
			cell[(int)n.x][(int)n.y - 1] = change;
			v2q.push({ n.x, n.y - 1 });
			if (add)
				temp++;
		}
		if (cell[(int)n.x][(int)n.y + 1] == target)
		{
			cell[(int)n.x][(int)n.y + 1] = change;
			v2q.push({ n.x, n.y + 1 });
			if (add)
				temp++;
		}
	}

	coloring_cells += temp;

	float temp1 = coloring_cells * 100;
	coloring_per = temp1 / cellxy;

	IsDrawing = true;
	DrawArea(1);

	return true;
}

bool TileMap::Near(KeyState dir, int target)
{
	int cx = pos.x - x_gap;
	int cy = pos.y - y_gap;

	switch (dir)
	{
	case KeyState::UP:
		return cell[cx][cy - 1] == target;
		break;
	case KeyState::DOWN:
		return cell[cx][cy + 1] == target;
		break;
	case KeyState::LEFT:
		return cell[cx - 1][cy] == target;
		break;
	case KeyState::RIGHT:
		return cell[cx + 1][cy] == target;
		break;
	}
}

int TileMap::Current()
{
	return cell[(int)pos.x - x_gap][(int)pos.y - y_gap];
}

void TileMap::Render()
{
	RENDER->CenterRender(stage_c, CENTER, 1);
	RENDER->CenterRender(stage_f, CENTER, 1);
	if (hp <= 0 || timer <= 0) //죽으면
	{
		b_gv += Delta * 10;
		gv = true;
		if (b_gv >= m_gv.size()) b_gv = m_gv.size() - 1;
		if (INPUT->PointUp(VK_LBUTTON, { 820,640,910,730 }))	retry = true;
		if (INPUT->PointUp(VK_LBUTTON, { 990,640,1080,730 }))	title = true;

		b_alpha -= Delta;
		if (b_alpha <= 0) b_alpha = 0;
	}
	if (coloring_per >= 70)  // 80%채우면5
	{
		b_gc += Delta * 10;
		gc = true;
		if (b_gc >= m_gc.size()) b_gc = m_gc.size() - 1;
		if (INPUT->KeyUp(VK_RETURN))	nextstage = true;

		b_alpha -= Delta;
		if (b_alpha <= 0) b_alpha = 0;
	}
	if (damage)	RENDER->CenterRender(ani_bullet[int(b_count)], stop_pos);
}

void TileMap::UIRender()
{
	//UI->CenterRender(stage_c, CENTER, 1);
	//UI->CenterRender(stage_f, CENTER, 1);
}

void TileMap::SUI()
{
	if (gv)
	{
		UI->CenterRender(IMAGE->FindImage("AB"), CENTER);
		UI->CenterRender(m_gv[int(b_gv)], CENTER, 1.2);
	}
	if (gc)
	{
		UI->CenterRender(IMAGE->FindImage("AB"), CENTER);
		UI->CenterRender(m_gc[int(b_gc)], CENTER, 1.2);
		char str[256];
		sprintf(str, "%d", int(timer));
		UI->PrintText(str, Vec2(780,910), 100, 255 * (b_gc / m_gc.size() - 1), 40, 40, 40);
		sprintf(str, "%d", int(coloring_per * 100000 * (timer / 3000)));
		UI->PrintText(str, Vec2(1420, 910), 100, 255 * (b_gc / m_gc.size() - 1), 40, 40, 40);
	}

	if (pos.y <= 180)
	{
		UI->CenterRender2(timebar[0], Vec2(1800, 50), 1, 90 * b_alpha);
		UI->CenterRender2(IMAGE->FindImage("camera"), Vec2(10, 10), 1, 90 * b_alpha);
		Text(100, 100);
	}
	else
	{
		UI->CenterRender2(timebar[0], Vec2(1800, 50), 1, 255 * b_alpha);
		UI->CenterRender2(IMAGE->FindImage("camera"), Vec2(10, 10) , 1, 255 * b_alpha);
		Text(255, 100);
	}

	if (start)
	{
		b_start += 0.1;
		if (b_start >= m_start.size()) { start = false; b_start = 0; }
		UI->CenterRender(m_start[int(b_start)], CENTER, 1.2);
	}

	for (int i = 0; i < hp; i++) {
		if (pos.x <= (350 + i*60) && pos.y >= 0 && pos.y <= 100)	UI->CenterRender2(IMAGE->FindImage("hp"), Vec2(245 + i*60, 10), 1, 100 * b_alpha);
		else	UI->CenterRender2(IMAGE->FindImage("hp"), Vec2(245 + i*60, 10), 1, 255 * b_alpha);
	}
}

void TileMap::Text(int alpha, int y)
{
	char str[256];
	if (coloring_per < 10)  sprintf(str, "%.2f%%", (double)coloring_per);
	else					sprintf(str, "%.1f%%", (double)coloring_per);
	UI->PrintText(str, Vec2(150, 80 + (y / 1.2)), 50, alpha, 100, 100, 100);
	sprintf(str, "stage: %d", nowstage + 1);
	UI->PrintText(str, Vec2(350, 80 + (y / 1.2)), 50, alpha, 100, 100, 100);
	sprintf(str, "score: %d", int(coloring_per * 100000 * (timer / 3000)));
	UI->PrintText(str, Vec2(1700, 80) , 100, alpha, 50, 50, 50);
}

void TileMap::SetUp()
{
	memset(cell, 0, sizeof(cell));

	for (size_t x = 0; x < CELLSIZEX; x++)
		for (size_t y = 0; y < CELLSIZEY; y++)
		{
			if (x == 0 || x == CELLSIZEX - 1 || y == 0 || y == CELLSIZEY - 1)
				cell[x][y] = 1;                    
			else
				cell[x][y] = 0;
		}

	coloring_per = 0;
	coloring_cells = 0;
	temp = 0;

	hp = 5;
	speed = 4;
	timer = 100;
	second = { 0,0 };
	frame = 0;

	m_ani = IMAGE->MakeVecImg("boss");

	D3DLOCKED_RECT lr, Tr;
	stage_c->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD); //clear img 저장
	DWORD* pixel = (DWORD*)lr.pBits;
	for (int y = CELLSIZEY - 1; y != -1; --y)
	{
		for (int x = CELLSIZEX - 1; x != -1; --x)
		{
			SaveImage[x][y] = pixel[y * CELLSIZEX + x];
		}
	}
	stage_c->ptr->UnlockRect(0);

	stage_f->ptr->LockRect(0, &Tr, 0, D3DLOCK_DISCARD); //front img 저장
	pixel = (DWORD*)Tr.pBits;
	for (int y = CELLSIZEY - 1; y != -1; --y)
	{
		for (int x = CELLSIZEX - 1; x != -1; --x)
		{
			Savebg[x][y] = pixel[y * CELLSIZEX + x];
		}
	}
	stage_f->ptr->UnlockRect(0);
}

void TileMap::ChangeScene()
{
	if (title) //타이틀로
	{
		IMAGE->ReloadImage("stage_c");
		IMAGE->ReloadImage("stage_f");
		IMAGE->ReloadImage("2-0stage_c");
		IMAGE->ReloadImage("2-0stage_f");
		stage_f = IMAGE->FindImage("stage_f");
		stage_c = IMAGE->FindImage("stage_c");
		SetUp();
		DrawArea();
		SCENE->ChangeScene("TitleScene");
	}
	if (nextstage) //다음스테이지로
	{
		switch (nowstage)
		{
		case 1:
			IMAGE->ReloadImage("stage_c");
			IMAGE->ReloadImage("stage_f");
			SCENE->ChangeScene("Stage_2_0");
			break;
		case 2:
			IMAGE->ReloadImage("2-0stage_c");
			IMAGE->ReloadImage("2-0stage_f");
			SCENE->ChangeScene("TitleScene");
			break;
		}
	}
	if (retry) //스테이지 리로드
	{
		IMAGE->ReloadImage("stage_c");
		IMAGE->ReloadImage("stage_f");
		IMAGE->ReloadImage("2-0stage_c");
		IMAGE->ReloadImage("2-0stage_f");
		stage_f = IMAGE->FindImage("stage_f");
		stage_c = IMAGE->FindImage("stage_c");
		SetUp();
		DrawArea();
		switch (nowstage)
		{
		case 1:
			SCENE->ReloadScnee("Stage_1_0", new Stage_1_0);
			break;
		case 2:
			SCENE->ReloadScnee("Stage_2_0", new Stage_2_0);
			break;
		}
		retry = false;
	}
}

//델타 픽스업데이트
