//===================================================
//メイン(main.cpp)
//Auhor:渡邉 修	Date:2023.7.7
//===================================================
#include <time.h>
#include <random>
#include <tchar.h>
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "collision.h"
#include "sound.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "camera.h"
#include "tile.h"
#include "directWrite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// ウインドウのクラス名
#define WINDOW_CAPTION		"加味していただいても..."	// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_CAPTION;	// デバッグ文字表示用

#endif

SCENE g_Scene = SCENE_NONE;

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	//ランダムシードの初期化
	srand((unsigned int)time(NULL));

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	int window_width = WINDOW_WIDTH;//初期設定 960
	int window_height = WINDOW_HEIGHT;//初期設定 540

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_CAPTION,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// ウィンドウの左座標
		CW_USEDEFAULT,																		// ウィンドウの上座標
		window_width + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// ウィンドウ横幅
		window_height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
		NULL,
		NULL,
		hInstance,
		NULL);


	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStr);
#endif

				Update();			// 更新処理
				Draw();				// 描画処理

				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダリング処理の初期化
	InitRenderer(hInstance, hWnd, bWindow);

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// スプライトの初期化
	InitSprite();

	//サウンドの初期化
	InitSound(hWnd);

	InitFade();

	switch (g_Scene)//シーンごとの分岐
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		InitTitle();
		break;

	case SCENE_GAME:
		InitGame();
		break;

	case SCENE_RESULT:
		InitResult();
		break;
	}

	//最初のシーン
	SetScene(START_SCENE);

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	switch (g_Scene)//シーンごとの分岐
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_GAME:
		UninitGame();
		break;

	case SCENE_RESULT:
		UninitResult();
		break;
	}

	UninitFade();

	// スプライトの終了処理
	UninitSprite();

	// 入力処理の終了処理
	UninitInput();

	// レンダリングの終了処理
	UninitRenderer();

	//サウンドの終了処理
	StopSoundAll();
	UninitSound();

	// テクスチャの解放
	UninitTexture();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力処理の更新処理
	UpdateInput();

	UpdateFade();

	UpdateSound();

	switch (g_Scene)//シーンごとの分岐
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_GAME:
		UpdateGame();
		break;

	case SCENE_RESULT:
		UpdateResult();
		break;
	}

	// 当たり判定の更新処理
	UpdateCollision();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	Clear();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	switch (g_Scene)//シーンごとの分岐
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		DrawTitle();
		break;

	case SCENE_GAME:
		DrawGame();
		break;

	case SCENE_RESULT:
		DrawResult();
		break;
	}

	DrawFade();

	// バックバッファ、フロントバッファ入れ替え
	Present();
}


float frand(void)
{
	return (float)rand() / RAND_MAX;
}

//=============================================================================
// シーン切り替えリクエスト
//=============================================================================
void SetScene(SCENE scene)
{
	switch (g_Scene)//今のシーンの終了処理
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_GAME:
		UninitGame();
		break;

	case SCENE_RESULT:
		UninitResult();
		break;
	}


	g_Scene = scene;


	switch (g_Scene)//遷移後のシーンの初期化処理
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		InitTitle();
		break;

	case SCENE_GAME:
		InitGame();
		break;

	case SCENE_RESULT:
		InitResult();
		break;
	}
}

//=============================================================================
// シーンを返す
//=============================================================================
SCENE GetScene()
{
	return g_Scene;
}

//-----------------------------------------------------------------------------
// 0なら0、正の符号なら1、不の符号なら-1を返す
//-----------------------------------------------------------------------------
int Sign(float value)
{
	if (value == 0)return 0;
	else if (value > 0)return 1;
	else return -1;
}

//-----------------------------------------------------------------------------
// 自然数を返す
//-----------------------------------------------------------------------------
int Nat(float value)
{
	if (value < 0)return 0;

	return (int)value;
}

//-----------------------------------------------------------------------------
// 小数の切り捨て (digit = 10, 100, 1000...)
//-----------------------------------------------------------------------------
float Round(float num, int digit)
{
	num = int(num * digit);
	num = num / digit;
	return num;
}

//-----------------------------------------------------------------------------
// 座標から角度を計算する関数 度
//-----------------------------------------------------------------------------
double PointDirection(double x1, double y1, double x2, double y2)
{
	// ラジアン単位の角度を計算
	double angle = std::atan2(y2 - y1, x2 - x1);

	// ラジアンを度に変換
	double degrees = angle * 180.0f / 3.14159f;

	// 0から360度の範囲に調整
	if (degrees < 0)
	{
		degrees += 360.0;
	}

	return degrees;
}

//-----------------------------------------------------------------------------
// 座標から角度を計算する関数 ラジアン
//-----------------------------------------------------------------------------
double PointDirectionRadian(double x1, double y1, double x2, double y2)
{
	// ラジアン単位の角度を計算
	double angle = std::atan2(y2 - y1, x2 - x1);

	return angle;
}

//-----------------------------------------------------------------------------
// 対象までのxとyの距離を返す
//-----------------------------------------------------------------------------
D3DXVECTOR2 PointDistance(double x1, double y1, double x2, double y2)
{
	D3DXVECTOR2 distance;
	distance.x = x2 - x1;
	distance.y = y2 - y1;
	
	return distance;
}

//-----------------------------------------------------------------------------
// 角度と長さからベクトル (x, y) を計算
//-----------------------------------------------------------------------------
D3DXVECTOR2 CalculateVector(double length, double angleRadians)
{
	D3DXVECTOR2 result;

	result.x = cos(angleRadians);
	result.y = sin(angleRadians);

	D3DXVec2Normalize(&result, &result);
	result *= length;//目的のスピードにするためにスピードを乗算する

	return result;
}

////-----------------------------------------------------------------------------
//// ウィンドウを取得
////-----------------------------------------------------------------------------
//HWND GethWnd()
//{
//	HWND hWnd = FindWindow("GameWindow", NULL);
//	if (hWnd)
//	{
//		return hWnd;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
////-----------------------------------------------------------------------------
//// メッセージを取得
////-----------------------------------------------------------------------------
//MSG GetMsg()
//{
//	HWND hWnd = FindWindow("GameWindow", NULL);  // ウィンドウハンドルを取得
//	if (hWnd)
//	{
//		MSG msg;
//		while (GetMessage(&msg, NULL, 0, 0)) {
//			TranslateMessage(&msg);// キーボードメッセージを処理
//			DispatchMessage(&msg); // メッセージをウィンドウプロシージャに送る
//			return msg;
//		}
//	}
//}

//-----------------------------------------------------------------------------
// ウィンドウを取得(ウィンドウサイズが変わったときに対象から外れないようにする)
//-----------------------------------------------------------------------------
//HWND GetActiveWindowHandle()
//{
//	return hWnd;
////	HWND prevActiveWindow = GetActiveWindow();
////
////	// 一時的にウィンドウを最小化してから元に戻す
////	ShowWindow(prevActiveWindow, SW_MINIMIZE);
////	ShowWindow(prevActiveWindow, SW_RESTORE);
////
////	// アクティブウィンドウが変更されるのを待つ
////	while (true)
////	{
////		HWND currentActiveWindow = GetActiveWindow();
////		if (currentActiveWindow != prevActiveWindow)
////		{
////			return currentActiveWindow;
////		}
////
////		Sleep(100); // 100ミリ秒待機して再試行
////	}
//}

//-----------------------------------------------------------------------------
// ウィンドウやクライアントの大きさを取得する
// [引数] 0: ウィンドウサイズ, 1: クライアントサイズ 
//-----------------------------------------------------------------------------
RECT GetWindowContainerSize(int option)
{
	HWND hWnd = GetActiveWindow();//ウィンドウを取得
	RECT rect = { 0 };//四角形構造体
	if (option == 0)GetWindowRect(hWnd, &rect);//ウィンドウの左上隅と右下隅の座標を取得
	else if (option == 1)GetClientRect(hWnd, &rect);//クライアント(アプリ画面)の左上隅と右下隅の座標を取得
	return rect;
}

//-----------------------------------------------------------------------------
// ウィンドウの横幅を取得する
//-----------------------------------------------------------------------------
LONG GetWindowWidth()
{
	RECT rect = GetWindowContainerSize(0);

	return 	rect.right;
}

//-----------------------------------------------------------------------------
// ウィンドウの縦幅を取得する
//-----------------------------------------------------------------------------
LONG GetWindowHeight()
{
	RECT rect = GetWindowContainerSize(0);

	return 	rect.bottom;
}

//-----------------------------------------------------------------------------
// クライアント(ウィンドウの周りを抜いた画面部分)の横幅を取得する
//-----------------------------------------------------------------------------
LONG GetClientWidth()
{
	RECT rect = GetWindowContainerSize(1);

	return 	rect.right;
}

//-----------------------------------------------------------------------------
// クライアント(ウィンドウの周りを抜いた画面部分)の縦幅を取得する
//-----------------------------------------------------------------------------
LONG GetClientHeight()
{
	RECT rect = GetWindowContainerSize(1);

	return 	rect.bottom;
}

//-----------------------------------------------------------------------------
// アニメーションを設定する
// [引数] basePattern: 左上を0とした開始フレーム, 
//		  widthPattern: 横のアニメパターン数, 
//-----------------------------------------------------------------------------
D3DXVECTOR2 SetAnimation(int basePattern, int animeCount, int allWidthPattern, int allHeightPattern, int widthPattern, bool reverse)
{
	D3DXVECTOR2 uv;
	//U      W											N番目の % 横のパターン数
	uv.x = (1.0f / allWidthPattern) * ((animeCount + basePattern) % widthPattern);	//横の座標計算
	//V     H											N番目の / 横の全パターン
	uv.y = (1.0f / allHeightPattern) * ((animeCount + basePattern) / allWidthPattern); //縦の座標計算

	//テクスチャ反転
	if (reverse)
	{
		
		//float num = int(1.0f / allWidthPattern * 100);
		//num = num / 100.0f;
		uv.x = 1 + (1 - uv.x) - Round(1.0f / allWidthPattern, 100);//左端なので-0.25
	}

	return uv;
}

//-----------------------------------------------------------------------------
// UV座標をセット(引数 : 左上端を0その右隣りを1,2,3...としたときの数)
//-----------------------------------------------------------------------------
D3DXVECTOR2 GetUV(int index, int widthPattern, int heightPattern)
{
	float U = (index % widthPattern) * (1.0f / widthPattern);
	float V = (index / widthPattern) * (1.0f / heightPattern);
	D3DXVECTOR2 UV = D3DXVECTOR2(U, V);
	return UV;
}

//-----------------------------------------------------------------------------
// 第一引数が第二引数になったら0にする
//-----------------------------------------------------------------------------
int Counter(int count, int max)
{
	count++;

	if (count >= max)
	{
		count = 0;
	}
	return count;
}

//-----------------------------------------------------------------------------
// デバッグの出力
// 例 ("X" + std::to_string(cursorPos.x) + "   Y" + std::to_string(cursorPos.y));
//-----------------------------------------------------------------------------
void DebugPrint(const std::string& message) 
{
	OutputDebugStringA(("デバッグ: " + message + "\n").c_str());
}

void DebugPrint(const float& message1, const float& message2, std::string message3)
{
	OutputDebugStringA(("デバッグ: " + std::to_string(message1) + "		" + std::to_string(message2) + "	:" + message3 + "\n").c_str());
}

//-----------------------------------------------------------------------------
// ランダム
//-----------------------------------------------------------------------------
int GetRandomInt(int min, int max)
{
	std::random_device rd;
	std::uniform_int_distribution<> dist(min, max);
	return dist(rd);
}

float GetRandomFloat(float min, float max)
{
	std::random_device rd;
	std::uniform_real_distribution<> dist(min, max);
	return dist(rd);
}

//-----------------------------------------------------------------------------
// ％で抽選します
// 引数に何%かを入れ第一引数が選ばれれば1を第二引数なら2を返します
// どれも選ばれなければ0を返します
//-----------------------------------------------------------------------------
int RandomPercent(float percent1, float percent2, float percent3, float percent4, float percent5, float percent6, float percent7, float percent8, float percent9, float percent10)
{
	float percent[10] = { percent1 , percent2 ,percent3 ,percent4 ,percent5 ,percent6 ,percent7 ,percent8 ,percent9 ,percent10 };
	int ran = GetRandomInt(1, 100);

	for (int i = 0; i < 10; i++)
	{
		if (ran < percent[i])return i + 1;

		ran -= percent[i];
	}

	return 0;
}

//-----------------------------------------------------------------------------
// 画面外に出たか判定
//-----------------------------------------------------------------------------
bool OffScreenJudge(float posX, float posY, float sizeX, float sizeY)
{
	bool judge = false;
	D3DXVECTOR2  cameraPos = GetCameraPos(0);

	//左右判定
	//画面外範囲算出
	float offScreenL = (cameraPos.x - SCREEN_WIDTH * 0.5f);
	float offScreenR = (cameraPos.x + SCREEN_WIDTH * 0.5f);
	//判定範囲ループ時の処理
	if (offScreenL < 0)
	{
		offScreenL += STAGE_SIZE;
		if (posX + sizeX < offScreenL && posX - sizeX > offScreenR)judge = true;
	}
	else if (offScreenR > STAGE_SIZE)
	{
		offScreenR -= STAGE_SIZE;
		if (posX + sizeX < offScreenL && posX - sizeX > offScreenR)judge = true;
	}
	//ループしてないときの処理
	else
	{
		if (posX + sizeX < offScreenL || posX - sizeX > offScreenR)judge = true;
	}
	
	//上下判定
	if (posY + sizeY < 0 || posY - sizeY > SCREEN_HEIGHT)judge = true;

	return judge;
}
