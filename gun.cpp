//===================================================
//銃(gun.cpp)
//Auhor:渡邉 修	Date:2023.8.27
//===================================================
#include "gun.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "dead.h"
#include "main.h"
#include "tile.h"
#include "camera.h"
#include "player.h"
#include "bullet.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_TexGun01;
static int g_TexMouseCursor;
static int g_SE_shot;
static int g_SE_charge;
static int g_SE_chargeOk;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimeSkipFrame;
static float g_AnimeSkipFrameFloat;
static GUN g_Gun[GUN_MAX];
static TILE_DATA* p_Tile;
static bool g_Reverse;
static PLAYER* p_Player;
static D3DXVECTOR2 g_Distance;
static bool g_Shot;
static bool g_Event;
static float g_Offset;
static double g_Radian;
static D3DXVECTOR2 g_MouseCursorPos;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitGun(void)
{
	g_TexGun01 = LoadTexture((char*)"data/TEXTURE/Gun01.png");
	g_TexMouseCursor = LoadTexture((char*)"data/TEXTURE/MouseCursor.png");

	//効果音作成
	char se1[] =
	{
		"data\\SE\\se_shot.wav"
	};
	g_SE_shot = LoadSound(&se1[0]);

	char se2[] =
	{
		"data\\SE\\se_charge.wav"
	};
	g_SE_charge = LoadSound(&se2[0]);

	char se3[] =
	{
		"data\\SE\\se_chargeOk.wav"
	};
	g_SE_chargeOk = LoadSound(&se3[0]);

	for (int i = 0; i < GUN_MAX; i++)
	{
		g_Gun[i].use = true;
		g_Gun[i].type = GUN_TYPE_INIT;
		g_Gun[i].oldType = g_Gun[i].type;
		g_Gun[i].pos.x = 0.0f;
		g_Gun[i].pos.y = 0.0f;
		g_Gun[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Gun[i].size = D3DXVECTOR2(GUN_WIDTH, GUN_HEIGHT);
		g_Gun[i].rot = 0.0f;
		g_Gun[i].animeWidthPattern = GUN_WIDTH_PATTERN;
		g_Gun[i].animeHeightPattern = GUN_HEIGHT_PATTERN;
		g_Gun[i].animeBasePattern = 0;
		g_Gun[i].anime = false;
		g_Gun[i].shotDelay = GUN_SHOT_DELAY;
		g_Gun[i].shotCou = 0;
		g_Gun[i].charge = 0;
		g_Gun[i].animePattern = 0;
	}

	//グローバル変数初期化
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / GUN_WIDTH_PATTERN;
	g_VH = 1.0f / GUN_HEIGHT_PATTERN;
	g_AnimeSkipFrame = GUN_FRAME_SPAN;
	g_Reverse = false;
	g_Distance = D3DXVECTOR2(0, 0);
	g_Shot = false;
	g_Offset = GUN_BULLET_OFFSET;
	g_Radian = 0;
	g_Event = false;
	g_MouseCursorPos = D3DXVECTOR2(0, 0);
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateGun(void)
{
	p_Player = GetPlayer();

	for (int i = 0; i < GUN_MAX; i++)
	{
		if (!p_Player[0].use)g_Gun[i].type = GUN_TYPE_INIT;

		g_Gun[i].use = p_Player[0].use;

		if (g_Gun[i].use)
		{
			g_Gun[i].oldType = g_Gun[i].type;
			g_Gun[i].color.a = p_Player[0].color.a;
			g_Gun[i].pos = p_Player[0].pos;

			g_MouseCursorPos = D3DXVECTOR2(GetMouseAbsoluteXCamera(), GetMouseAbsoluteYCamera());

			if (p_Player[0].loopTrigger == 0)
			{
				g_Gun[i].rot = PointDirectionRadian(g_Gun[i].pos.x, g_Gun[i].pos.y, GetMouseAbsoluteXCamera(), GetMouseAbsoluteYCamera());
				g_Distance = PointDistance(g_Gun[i].pos.x, g_Gun[i].pos.y, GetMouseAbsoluteXCamera(), GetMouseAbsoluteYCamera());
			}

			//発射ボタンを押したら
			bool keyShotPre = IsMouseLeftPressed();
			bool keyShotTri = IsMouseLeftTriggered();

			//銃変更時のリセット
			if (g_Gun[i].oldType != g_Gun[i].type)
			{
				g_Event = false;
				g_Shot = false;
				g_Gun[i].animePattern = 0;
				g_Gun[i].anime = false;
				g_Gun[i].shotCou = 0;
			}

			switch (g_Gun[i].type)
			{
			case GUN_TYPE_INIT:

				if (keyShotPre && g_Event == false)
				{
					//アニメ開始
					g_Gun[i].anime = true;

					g_Event = true;
					g_Shot = true;
				}

				//弾を発射した時の処理
				if (g_Event)
				{
					//アニメが指定まで再生されたら発射
					if (g_Gun[i].animePattern == 2 && g_Shot == true)
					{
						PlaySound(g_SE_shot, 0);

						//弾を配置
						SetBullet(BULLET_TYPE_NORMAL, g_Gun[i].pos.x + g_Offset * cos(g_Gun[i].rot), g_Gun[i].pos.y + g_Offset * sin(g_Gun[i].rot), g_Distance.x, g_Distance.y, g_Gun[i].rot, 50);
						//ガンキック
						SetPlayerGunKick(5, g_Gun[i].rot);
						g_Shot = false;
					}

					if (!g_Shot)Shake(1, 1);

					//アニメが修了したら処理する
					if (g_Gun[i].animePattern == 0 && !g_Shot)
					{
						g_Gun[i].anime = false;
						//次弾を撃てるようになるまでのディレイ
						g_Gun[i].shotDelay = 0;
						g_Gun[i].shotCou = Counter(g_Gun[i].shotCou, g_Gun[i].shotDelay);
						if (g_Gun[i].shotCou == 0)
						{
							g_Event = false;
						}
					}
				}

				break;

			case GUN_TYPE_FULL_AUTO:

				if (keyShotPre && g_Event == false)
				{
					//アニメ開始
					g_Gun[i].anime = true;

					g_Event = true;
					g_Shot = true;
				}

				//弾を発射した時の処理
				if (g_Event)
				{
					//アニメが指定まで再生されたら発射
					if (g_Gun[i].animePattern == 2 && g_Shot == true)
					{
						PlaySound(g_SE_shot, 0);
						//角度取得
						g_Distance.x += GetRandomInt(-50, 50);
						g_Distance.y += GetRandomInt(-50, 50);
						//弾を配置
						SetBullet(BULLET_TYPE_NORMAL, g_Gun[i].pos.x + g_Offset * cos(g_Gun[i].rot), g_Gun[i].pos.y + g_Offset * sin(g_Gun[i].rot), g_Distance.x, g_Distance.y, g_Gun[i].rot, 20);
						//ガンキック
						SetPlayerGunKick(5, g_Gun[i].rot);
						g_Shot = false;
					}

					if (!g_Shot)Shake(5, 3);

					//アニメが修了したら処理する
					if (g_Gun[i].animePattern == 0 && !g_Shot)
					{
						g_Gun[i].anime = false;
						//次弾を撃てるようになるまでのディレイ
						g_Gun[i].shotDelay = 10;
						g_Gun[i].shotCou = Counter(g_Gun[i].shotCou, g_Gun[i].shotDelay);
						if (g_Gun[i].shotCou == 0)
						{
							g_Event = false;
						}
					}
				}

				break;
			case GUN_TYPE_SEMI_AUTO:

				if (keyShotTri && g_Event == false)
				{
					//アニメ開始
					g_Gun[i].anime = true;

					g_Event = true;
					g_Shot = true;
				}

				//弾を発射した時の処理
				if (g_Event)
				{
					//アニメが指定まで再生されたら発射
					if (g_Gun[i].animePattern == 2 && g_Shot == true)
					{
						PlaySound(g_SE_shot, 0);

						//弾を配置
						SetBullet(BULLET_TYPE_NORMAL, g_Gun[i].pos.x + g_Offset * cos(g_Gun[i].rot), g_Gun[i].pos.y + g_Offset * sin(g_Gun[i].rot), g_Distance.x, g_Distance.y, g_Gun[i].rot, 50);
						//ガンキック
						SetPlayerGunKick(50, g_Gun[i].rot);
						g_Shot = false;
					}

					if (!g_Shot)Shake(10, 5);

					//アニメが修了したら処理する
					if (g_Gun[i].animePattern == 0 && !g_Shot)
					{
						g_Gun[i].anime = false;
						//次弾を撃てるようになるまでのディレイ
						g_Gun[i].shotDelay = 1;
						g_Gun[i].shotCou = Counter(g_Gun[i].shotCou, g_Gun[i].shotDelay);
						if (g_Gun[i].shotCou == 0)
						{
							g_Event = false;
						}
					}
				}

				break;
			case GUN_TYPE_CHARGE_FULL_AUTO:
				if ((!keyShotPre || g_Event) && g_Gun[i].charge > 0)
				{
					g_Gun[i].charge--;
					g_Gun[i].animePattern = 0;
				}

				if (keyShotPre && !g_Event)
				{
					//押している間溜める
					g_Gun[i].charge++;
					PlaySound(g_SE_charge, 0);

					//アニメ開始
					g_Gun[i].anime = false;
					g_Gun[i].animePattern = 1;

					if(g_Gun[i].charge == 50)PlaySound(g_SE_chargeOk, 0);

				}
				else if(g_Gun[i].charge >= 50 && (!keyShotPre || g_Event))
				{
					g_Gun[i].animePattern = 2;
					g_Gun[i].anime = true;
					g_Event = true;
					g_Shot = true;
				}

				//弾を発射した時の処理
				if (g_Event)
				{
					//アニメが指定まで再生されたら発射
					if (g_Gun[i].animePattern == 2 && g_Shot == true)
					{
						PlaySound(g_SE_shot, 0);
						//角度取得
						g_Distance.x += GetRandomInt(-50, 50);
						g_Distance.y += GetRandomInt(-50, 50);
						//弾を配置
						SetBullet(BULLET_TYPE_NORMAL, g_Gun[i].pos.x + g_Offset * cos(g_Gun[i].rot), g_Gun[i].pos.y + g_Offset * sin(g_Gun[i].rot), g_Distance.x, g_Distance.y, g_Gun[i].rot, 20);
						//ガンキック
						SetPlayerGunKick(20, g_Gun[i].rot);
						g_Shot = false;
					}

					if (!g_Shot)Shake(5, 3);

					//アニメが修了したら処理する
					if (g_Gun[i].animePattern == 0 && !g_Shot)
					{
						g_Gun[i].anime = false;
						//次弾を撃てるようになるまでのディレイ
						g_Gun[i].shotDelay = 10;
						g_Gun[i].shotCou = Counter(g_Gun[i].shotCou, g_Gun[i].shotDelay);
						if (g_Gun[i].shotCou == 0)
						{
							g_Gun[i].charge = 0;
							g_Event = false;
						}
					}
				}

				break;
			default:
				break;
			}

		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawGun(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//テクスチャのフィルターをOFF
	for (int i = 0; i < GUN_MAX; i++)
	{
		if (g_Gun[i].use)
		{
			//アニメーション
			D3DXVECTOR2 uv = SetAnimation(g_Gun[i].animeBasePattern, g_Gun[i].animePattern, GUN_WIDTH_PATTERN, GUN_HEIGHT_PATTERN, g_Gun[i].animeWidthPattern, g_Reverse);

			g_U = uv.x;
			g_V = uv.y;

			if (g_Gun[i].anime)
			{
				g_AnimeSkipFrame = Counter(g_AnimeSkipFrame, GUN_FRAME_SPAN);

				if (g_AnimeSkipFrame == 0)
				{
					g_Gun[i].animePattern = Counter(g_Gun[i].animePattern, g_Gun[i].animeWidthPattern * g_Gun[i].animeHeightPattern);
				}
			}

			DrawSpriteColorRotateCamera(g_TexGun01,
				g_Gun[i].pos.x,
				g_Gun[i].pos.y,
				g_Gun[i].size.x, g_Gun[i].size.y,	//幅、高さ
				g_U, g_V,		//中心UV座標
				g_UW, g_VH,		//テクスチャ幅、高さ
				g_Gun[i].color.r, g_Gun[i].color.g, g_Gun[i].color.b, g_Gun[i].color.a,
				g_Gun[i].rot
			);

			//マウスカーソル表示
			DrawSpriteColorRotateCamera(g_TexMouseCursor,
				g_MouseCursorPos.x,
				g_MouseCursorPos.y,
				g_Gun[i].size.x, g_Gun[i].size.y,	//幅、高さ
				g_U, g_V,		//中心UV座標
				g_UW, g_VH,		//テクスチャ幅、高さ
				1, 1, 1, 0.7f,
				0
			);

			double degrees = g_Gun[i].rot * 180.0f / 3.14159f;
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitGun(void)
{

}

//---------------------------------------------------
// 銃取得処理
//---------------------------------------------------
GUN* GetGun()
{
	return &g_Gun[0];
}

//---------------------------------------------------
// 銃を変更
//---------------------------------------------------
void ChangeGun(int type)
{
	for (int i = 0; i < GUN_MAX; i++)
	{
		if (g_Gun[i].use)
		{
			g_Gun[i].type = type;
		}
	}
}