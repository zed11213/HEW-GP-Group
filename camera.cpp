//===================================================
//カメラ(camera.cpp)
//Auhor:渡邉 修	Date:2023.8.27
//===================================================
#include <random>
#include "camera.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "main.h"
#include "tile.h"
#include "player.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_TexNo;
static int g_SE_crushed_tomato;
static int g_SE_move;
static int g_SE_drop;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimePattern;
static int g_AnimeBasePattern;//アニメーション番号の方向ごとのベース値
static int g_AnimeSkipFrame;
static float g_AnimeSkipFrameFloat;
static CAMERA g_Camera[CAMERA_MAX];
static TILE_DATA* p_Tile;
static bool g_Reverse;
static PLAYER* p_Player;
static float g_ShakeRemain;
static float g_ShakeMagnitude;
static float g_ShakeLength;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitCamera(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Camera.png");

	for (int i = 0; i < CAMERA_MAX; i++)
	{
		g_Camera[i].use = true;
		g_Camera[i].pos.x = SCREEN_WIDTH / 2;
		g_Camera[i].pos.y = SCREEN_HEIGHT / 2;
		g_Camera[i].oldPos = D3DXVECTOR2(0, 0);
		g_Camera[i].vel.x = 0.0f;
		g_Camera[i].vel.y = 0.0f;
		g_Camera[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Camera[i].size = D3DXVECTOR2(CAMERA_WIDTH, CAMERA_HEIGHT);
		g_Camera[i].use = true;
		g_Camera[i].cameraMove = D3DXVECTOR2(0, 0);
		g_Camera[i].notLoopPos = D3DXVECTOR2(0, 0);
		g_Camera[i].oldNotLoopPos = D3DXVECTOR2(0, 0);
		g_Camera[i].trackingDelay = D3DXVECTOR2(25, 25);
		g_Camera[i].cameraTotalMove = D3DXVECTOR2(0, 0);
		g_Camera[i].loopTrigger = 0;
	}

	//グローバル変数初期化
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / CAMERA_WIDTH_PATTERN;
	g_VH = 1.0f / CAMERA_HEIGHT_PATTERN;
	g_ShakeRemain = 0;
	g_ShakeMagnitude = 0;
	g_ShakeLength = 0;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateCamera(void)
{
	for (int i = 0; i < CAMERA_MAX; i++)
	{
		p_Player = GetPlayer();

		g_Camera[i].oldPos = g_Camera[i].pos;
		g_Camera[i].oldNotLoopPos = g_Camera[i].notLoopPos;

		if (g_Camera[i].use && p_Player[0].use)
		{
			if (GetKeyboardPress(DIK_RIGHT))g_Camera[i].pos.x++;
			if (GetKeyboardPress(DIK_LEFT))g_Camera[i].pos.x--;
			if (GetKeyboardPress(DIK_UP))g_Camera[i].pos.y--;
			if (GetKeyboardPress(DIK_DOWN))g_Camera[i].pos.y++;

			//カメラを揺らす
			if (g_ShakeRemain != 0)
			{
				g_Camera[i].pos.x += GetRandomFloat(-g_ShakeRemain, g_ShakeRemain);
				g_Camera[i].pos.y += GetRandomFloat(-g_ShakeRemain, g_ShakeRemain);

				g_ShakeRemain = max(0, g_ShakeRemain - ((1 / g_ShakeLength) * g_ShakeMagnitude));//max: 2つの値から大きいほうを返す
			}

			//プレイヤーが反対側に行ったらワープする
			if (p_Player[i].loopTrigger == 1)g_Camera[i].pos.x -= STAGE_SIZE;
			else if (p_Player[i].loopTrigger == -1)g_Camera[i].pos.x += STAGE_SIZE;

			//プレイヤーに追従する
			g_Camera[0].vel.x = (p_Player[0].pos.x - g_Camera[0].pos.x) / g_Camera[0].trackingDelay.x;
			g_Camera[0].vel.y = (p_Player[0].pos.y - 400 - g_Camera[0].pos.y) / g_Camera[0].trackingDelay.y;
			g_Camera[0].pos += g_Camera[0].vel;

			g_Camera[0].vel.x = (p_Player[0].notLoopPos.x - g_Camera[0].notLoopPos.x) / g_Camera[0].trackingDelay.x;
			g_Camera[0].vel.y = (p_Player[0].notLoopPos.y - 400 - g_Camera[0].notLoopPos.y) / g_Camera[0].trackingDelay.y;
			g_Camera[0].notLoopPos += g_Camera[0].vel;

			//縦のカメラの動きに上限を設定
			if (g_Camera[i].pos.y < 700)g_Camera[i].pos.y = g_Camera[i].oldPos.y;
			if (g_Camera[i].pos.y > SCREEN_HEIGHT)g_Camera[i].pos.y = g_Camera[i].oldPos.y;

			//描写に加算するカメラの移動量
			g_Camera[i].cameraMove.x -= g_Camera[i].oldPos.x - g_Camera[i].pos.x;
			g_Camera[i].cameraMove.y -= g_Camera[i].oldPos.y - g_Camera[i].pos.y;
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawCamera(void)
{
	for (int i = 0; i < CAMERA_MAX; i++)
	{
		if (g_Camera[i].use)
		{
			DrawSpriteCamera(g_TexNo,
				g_Camera[i].pos.x,
				g_Camera[i].pos.y,
				g_Camera[i].size.x, g_Camera[i].size.y,	//幅、高さ
				g_U, g_V,		//中心UV座標
				g_UW, g_VH		//テクスチャ幅、高さ
			);
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitCamera(void)
{

}

//---------------------------------------------------
// カメラ取得処理
//---------------------------------------------------
CAMERA* GetCamera()
{
	return &g_Camera[0];
}

//---------------------------------------------------
// カメラポジション取得
//---------------------------------------------------
D3DXVECTOR2 GetCameraPos(int cameraIndex)
{
	return g_Camera[cameraIndex].pos;
}

//---------------------------------------------------
// カメラポジション取得
//---------------------------------------------------
D3DXVECTOR2 GetCameraNotLoopPos(int cameraIndex)
{
	return g_Camera[cameraIndex].notLoopPos;
}

//---------------------------------------------------
// カメラ描画補正値取得
//---------------------------------------------------
D3DXVECTOR2 GetCameraMoveVolume(int cameraIndex)
{
	return g_Camera[cameraIndex].cameraMove;
}

//---------------------------------------------------
// カメラ描画補正値取得(背景用)
//---------------------------------------------------
D3DXVECTOR2 GetCameraMoveTotalVolume(int cameraIndex)
{
	return g_Camera[cameraIndex].cameraTotalMove;
}

//---------------------------------------------------
// シェイク [引数]shakeMagnitude: 揺らす大きさ, shakeLength: 揺らす長さ
//---------------------------------------------------
void Shake(float shakeMagnitude, float shakeLength)
{
	g_ShakeRemain = shakeMagnitude;
	g_ShakeMagnitude = shakeMagnitude;
	g_ShakeLength = shakeLength;
}