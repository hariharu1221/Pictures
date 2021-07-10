#pragma once
#pragma comment(lib,"dsound.lib")
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include <queue>
#include <random>
#include <cmath>
#include <functional>

#define g_device DXUTGetD3D9Device()
#define Delta DXUTGetElapsedTime()

#define WI 400
#define HE 225
#define coldraw true
const bool drawbug = false;
const bool esct = false;

using namespace std;

using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;

const int WINSIZEX = 1920;
const int WINSIZEY = 1080;
const int CELLSIZEX = 1920;
const int CELLSIZEY = 1080;
const Vec2 CENTER = { WINSIZEX / 2,WINSIZEY / 2 };
const int L = CENTER.x - CELLSIZEX / 2;
const int R = CENTER.x + CELLSIZEX / 2;
const int T = CENTER.y - CELLSIZEY / 2;
const int B = CENTER.y + CELLSIZEY / 2;
const int x_gap = (WINSIZEX - CELLSIZEX) / 2;
const int y_gap = (WINSIZEY - CELLSIZEY) / 2;

#include "SDKsound.h"
#include "SDKwavefile.h"

#include "cTexture.h"
#include "cScene.h"
#include "cTimer.h"
#include "cParticle.h"

#include "cImageManger.h"
#include "cSceneManager.h"
#include "cUIManager.h"
#include "cRenderManager.h"
#include "cInputManager.h"
#include "cParticleManager.h"
#include "cCameraManager.h"
#include "RandomMgr.h"

#include "Stage_1_0.h"
#include "Stage_2_0.h"
#include "Stage_3_0.h"
#include "TitleScene.h"
#include "nullScene.h"