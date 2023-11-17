/*==============================================================================

   メイン [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)

#include <string>

#include <dwrite.h>    
#include <d2d1helper.h>

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")

#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dwrite.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1920)				// 横の解像度
#define SCREEN_HEIGHT	(1080)				// 縦の解像度
#define SCREEN_WIDTH_HALF	(SCREEN_WIDTH * 0.5f)				// 横の解像度の半分
#define SCREEN_HEIGHT_HALF	(SCREEN_HEIGHT * 0.5f)				// 縦の解像度の半分
#define WINDOW_WIDTH	(1920)	//ウィンドウの横の大きさ
#define WINDOW_HEIGHT	(1080)	//ウィンドウの縦の大きさ
#define START_SCENE	(SCENE_GAME) 
#define LEFT	(-1)
#define RIGHT	(1)
#define DEFAULT_TILE_SIZE (80 * 2)//80

//*****************************************************************************
//列挙体宣言
//*****************************************************************************
typedef enum
{
	SCENE_NONE,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_EXIT
}SCENE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float frand(void);
void SetScene(SCENE scene);
SCENE GetScene();
int Sign(float value);
int Nat(float value);
float Round(float num, int digit);
double PointDirection(double x1, double y1, double x2, double y2);
double PointDirectionRadian(double x1, double y1, double x2, double y2);
D3DXVECTOR2 PointDistance(double x1, double y1, double x2, double y2);
D3DXVECTOR2 CalculateVector(double length, double angleRadians);
//HWND GethWnd();
//MSG GetMsg();
//HWND GetActiveWindowHandle();
RECT GetWindowContainerSize(int option);
LONG GetWindowWidth();
LONG GetWindowHeight();
LONG GetClientWidth();
LONG GetClientHeight();
D3DXVECTOR2 SetAnimation(int basePattern = 0, int animeCount = 0, int allWidthPattern = 1, int allHeightPattern = 1, int widthPattern = 1, bool reverse = false);
D3DXVECTOR2 GetUV(int index, int widthPattern, int heightPattern);
int Counter(int count, int max);
void DebugPrint(const std::string& message);
void DebugPrint(const float& message1, const float& message2 = 0.00, std::string message3 = " ");
int GetRandomInt(int min, int max);
float GetRandomFloat(float min, float max);
int RandomPercent(float percent1, float percent2 = 0, float percent3 = 0, float percent4 = 0, float percent5 = 0, float percent6 = 0, float percent7 = 0, float percent8 = 0, float percent9 = 0, float percent10 = 0);
bool OffScreenJudge(float posX, float posY, float sizeX, float sizeY);