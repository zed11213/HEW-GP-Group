//===================================================
//アイテム(item.cpp)
//Auhor:渡邉 修	Date:2023.9.15
//===================================================
#include "item.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "dead.h"
#include "main.h"
#include "tile.h"
#include "hit_spark.h"
#include "bullet.h"
#include "player.h"
#include "particle.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_TexNo;
static int g_SE_landing;
static int g_SE_itemDown;
static int g_SE_drop;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimePattern;
static ITEM g_Item[ITEM_MAX];
static TILE_DATA* p_Tile;
static BULLET* p_Bullet;
static PLAYER* p_Player;
static bool g_playSoundTrigger;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitItem(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Item.png");

	////効果音作成
	//char se1[] =
	//{
	//	"data\\SE\\se_landing.wav"
	//};
	//g_SE_landing = LoadSound(&se1[0]);

	//char se2[] =
	//{
	//	"data\\SE\\se_itemDown.wav"
	//};
	//g_SE_itemDown = LoadSound(&se2[0]);

	//char se3[] =
	//{
	//	"data\\SE\\drop.wav"
	//};
	//g_SE_drop = LoadSound(&se3[0]);

	for (int i = 0; i < ITEM_MAX; i++)
	{
		g_Item[i].use = false;
		g_Item[i].pos.x = SCREEN_WIDTH / 2;
		g_Item[i].pos.y = SCREEN_HEIGHT / 4;
		g_Item[i].vel.x = 0;
		g_Item[i].vel.y = 0;
		g_Item[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Item[i].hsp = 0;
		g_Item[i].vsp = 0;
		g_Item[i].grv = 0.3f;
		g_Item[i].walksp = 0;
		g_Item[i].controller = true;
		g_Item[i].hascontrol = false;
		g_Item[i].canjump = 0;
		g_Item[i].knockBackX = 0;
		g_Item[i].knockBackY = 0;
		g_Item[i].ground = false;
		g_Item[i].state = ITEM_STATE_IDLE;
		g_Item[i].oldState = ITEM_STATE_IDLE;
		g_Item[i].animeWidthPattern = 1;
		g_Item[i].animeHeightPattern = 1;
		g_Item[i].animeFrameMax = 0;
		g_Item[i].anime = false;
		g_Item[i].size = D3DXVECTOR2(ITEM_WIDTH, ITEM_HEIGHT);
		g_Item[i].leftMove = false;
		g_Item[i].rightMove = false;
		g_Item[i].jump = false;
		g_Item[i].move = 0;
		g_Item[i].stateCou = 0;
		g_Item[i].animeBasePattern = 0;
		g_Item[i].animePattern = 0;
		g_Item[i].animeSkipFrame = 0;
		g_Item[i].reverse = false;
		g_Item[i].type = ITEM_TYPE_PAPER;
		g_Item[i].animeLoop = false;
		g_Item[i].gunType = GUN_TYPE_SEMI_AUTO;
		g_Item[i].fadeOut = false;
	}

	//グローバル変数初期化
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / ITEM_WIDTH_PATTERN;
	g_VH = 1.0f / ITEM_HEIGHT_PATTERN;
	g_AnimePattern = 0;
	g_playSoundTrigger = false;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateItem(void)
{
	g_playSoundTrigger = false;

	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (g_Item[i].use)
		{
			g_Item[i].oldState = g_Item[i].state;

			//何も押していない又はA,Dを両方押してるときは0(false)を返す
			g_Item[i].move = g_Item[i].rightMove - g_Item[i].leftMove;
			//移動方向と速度
			g_Item[i].hsp = (g_Item[i].move * g_Item[i].walksp) + g_Item[i].knockBackX;
			g_Item[i].knockBackX *= 0.5f;
			if (g_Item[i].knockBackX < 0.9f)g_Item[i].knockBackX = 0;

			//重力
			g_Item[i].vsp = (g_Item[i].vsp + g_Item[i].grv) + g_Item[i].knockBackY;

			//壁の衝突判定
			p_Tile = GetMapInfo(g_Item[i].pos);

			for (int j = 0; j < 9; j++)
			{
				if (p_Tile[j].attrib == MAP_ATTRIB_STOP)
				{
					//横に壁がある場合
					if (CollisionRot(g_Item[i].pos.x + g_Item[i].hsp, g_Item[i].pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, ITEM_HITBOX_WIDTH, ITEM_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
					{
						//壁に当たるまで１ピクセル壁に近づける
						while (!CollisionRot(g_Item[i].pos.x + Sign(g_Item[i].hsp), g_Item[i].pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, ITEM_HITBOX_WIDTH, ITEM_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
						{
							g_Item[i].pos.x = g_Item[i].pos.x + Sign(g_Item[i].hsp);
						}
						g_Item[i].hsp = 0;
					}

					//縦に壁がある場合
					if (CollisionRot(g_Item[i].pos.x, g_Item[i].pos.y + g_Item[i].vsp, p_Tile[j].pos.x, p_Tile[j].pos.y, ITEM_HITBOX_WIDTH, ITEM_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
					{
						//壁に当たるまで１ピクセル壁に近づける
						while (!CollisionRot(g_Item[i].pos.x, g_Item[i].pos.y + Sign(g_Item[i].vsp), p_Tile[j].pos.x, p_Tile[j].pos.y, ITEM_HITBOX_WIDTH, ITEM_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
						{
							g_Item[i].pos.y = g_Item[i].pos.y + Sign(g_Item[i].vsp);
						}
						g_Item[i].vsp = 0;

						if (g_Item[i].ground == false)
						{
							if (!g_playSoundTrigger)
							{
								//画面内なら鳴らす
								if (!OffScreenJudge(g_Item[i].pos.x, g_Item[i].pos.y, ITEM_WIDTH, ITEM_HEIGHT))
								{
									//PlaySound(g_SE_landing, 0);
								}
								g_playSoundTrigger = false;
							}
						}
					}
				}
			}

			//横移動
			g_Item[i].pos.x += g_Item[i].hsp;

			////画面端ループ処理
			//if (g_Item[i].pos.x > MAP_SIZE_X * MAPCHIP_SIZE)
			//{
			//	g_Item[i].pos.x -= MAP_SIZE_X * MAPCHIP_SIZE;
			//}
			//if (g_Item[i].pos.x < 0)
			//{
			//	g_Item[i].pos.x += MAP_SIZE_X * MAPCHIP_SIZE;
			//}

			//縦移動
			g_Item[i].pos.y += g_Item[i].vsp;

			//ノックバックが加算されていくのを回避
			if (g_Item[i].vsp != 0)g_Item[i].vsp -= g_Item[i].knockBackY;
			g_Item[i].knockBackY *= 0.5f;
			if (g_Item[i].knockBackY < 0.9f)g_Item[i].knockBackY = 0;

			p_Tile = GetMapInfo(g_Item[i].pos);

			//下が地面の場合
			for (int j = 0; j < 9; j++)
			{
				if ((p_Tile[j].attrib == MAP_ATTRIB_STOP) && (j == 6 || j == 7 || j == 8))
				{
					//地面に触れているかの処理
					if (CollisionRot(g_Item[i].pos.x, g_Item[i].pos.y + 1, p_Tile[j].pos.x, p_Tile[j].pos.y, ITEM_HITBOX_WIDTH, ITEM_HITBOX_HEIGHT, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, 0.0f))
					{
						g_Item[i].ground = true;
						break;
					}
					else
					{
						g_Item[i].ground = false;
					}
				}
			}

			if (g_Item[i].rightMove == true) g_Item[i].reverse = false;//進行方向基準
			else if (g_Item[i].leftMove == true) g_Item[i].reverse = true;

			//地面に触れている場合
			if (g_Item[i].ground)
			{
				g_Item[i].canjump = 10;

				//止まっているときの処理
				if (g_Item[i].hsp == 0)
				{
					g_Item[i].state = ITEM_STATE_IDLE;
				}
				//動いているときの処理
				else
				{
					g_Item[i].state = ITEM_STATE_WALK;
				}
			}
			//地面に触れていない場合
			else
			{
				//上昇しているか下降しているかの判定
				if (Sign(g_Item[i].vsp) > 0)
				{
					g_Item[i].state = ITEM_STATE_FALL;
				}
				else
				{
					g_Item[i].state = ITEM_STATE_RISE;
				}
			}

			//フェードアウト処理
			if (g_Item[i].fadeOut)
			{
				g_Item[i].color.a -= 0.01f;
			}

			//アルファ値0で消す
			if (g_Item[i].color.a <= 0)g_Item[i].use = false;

			//範囲外で消す
			if (g_Item[i].pos.y > SCREEN_HEIGHT)
			{
				g_Item[i].use = false;
				SetHitSpark(g_Item[i].pos.x, g_Item[i].pos.y, 0);
			}
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawItem(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//テクスチャのフィルターをOFF
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (g_Item[i].use)
		{
			g_Item[i].animeFrameMax = g_Item[i].animeWidthPattern * g_Item[i].animeHeightPattern;

			D3DXVECTOR2 uv = SetAnimation(g_Item[i].animeBasePattern, g_Item[i].animePattern, ITEM_WIDTH_PATTERN, ITEM_HEIGHT_PATTERN, g_Item[i].animeWidthPattern, 1);
			g_U = uv.x;
			g_V = uv.y;

			if (g_Item[i].anime)
			{
				g_Item[i].animeSkipFrame = Counter(g_Item[i].animeSkipFrame, ITEM_FRAME_SPAN);

				if (g_Item[i].animeSkipFrame == 0)
				{
					g_Item[i].animePattern = Counter(g_Item[i].animePattern, g_Item[i].animeFrameMax);
				}
				//アニメーション終了
				if (g_Item[i].animeLoop == false && g_Item[i].animePattern == g_Item[i].animeFrameMax - 1)g_Item[i].anime = false;
			}

			DrawSpriteColorRotateCamera(g_TexNo,
				g_Item[i].pos.x,
				g_Item[i].pos.y,
				g_Item[i].size.x, g_Item[i].size.y,	//幅、高さ
				g_U, g_V,		//中心UV座標
				g_UW, g_VH,		//テクスチャ幅、高さ
				g_Item[i].color.r, g_Item[i].color.g, g_Item[i].color.b, g_Item[i].color.a,
				0.0f
			);
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitItem(void)
{
	delete[] p_Tile;
}

//---------------------------------------------------
// アイテム取得処理
//---------------------------------------------------
ITEM* GetItem()
{
	return &g_Item[0];
}

//---------------------------------------------------
// ノックバック設定 [引数]index: 配列番号
//---------------------------------------------------
void SetItemKnockBack(int index, float power)
{
	// ラジアンを度に変換
	double degrees = -90;

	float radian = degrees * 3.14159f / 180.0f;

	D3DXVECTOR2 vector = CalculateVector(-power, radian);

	if (g_Item[index].use)
	{
		g_Item[index].knockBackY = vector.y;
	}
}

//---------------------------------------------------
// 反動を設定 [引数]index: 配列番号
//---------------------------------------------------
void SetItemGunKick(int index, float power, float radian)
{
	D3DXVECTOR2 vector = CalculateVector(-power, radian);

	if (g_Item[index].use)
	{
		g_Item[index].knockBackX = vector.x;
		g_Item[index].knockBackY = vector.y;
	}
}

//---------------------------------------------------
// アイテムを配置
//---------------------------------------------------
int SetItem(float posX, float posY, ITEM_TYPE type)
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (!g_Item[i].use)
		{
			g_Item[i].leftMove = false;
			g_Item[i].rightMove = false;
			g_Item[i].jump = false;
			g_Item[i].pos.x = posX;
			g_Item[i].pos.y = posY;
			g_Item[i].stateCou = 0;
			g_Item[i].reverse = true;
			g_Item[i].color.a = 1.0f;
			g_Item[i].grv = 1.0f;
			g_Item[i].animePattern = 0;
			g_Item[i].animeSkipFrame = 0;
			g_Item[i].vsp = -20;
			g_Item[i].animeLoop = true;
			g_Item[i].type = type;
			g_Item[i].fadeOut = false;

			switch (g_Item[i].type)
			{
			case ITEM_TYPE_PAPER:
				g_Item[i].animeBasePattern = ITEM_WIDTH_PATTERN * 0;
				g_Item[i].anime = true;
				g_Item[i].animeWidthPattern = 1;
				break;

			case ITEM_TYPE_PAPER2:
				g_Item[i].animeBasePattern = ITEM_WIDTH_PATTERN * 1;
				g_Item[i].anime = true;
				g_Item[i].animeWidthPattern = 1;
				break;

			case ITEM_TYPE_PAPER3:
				g_Item[i].animeBasePattern = ITEM_WIDTH_PATTERN * 2;
				g_Item[i].anime = false;
				g_Item[i].animeWidthPattern = 1;
				break;

			default:
				break;
			}

			g_Item[i].use = true;

			return i;
		}
	}
}

//---------------------------------------------------
// 武器を配置
//---------------------------------------------------
void SetWeapon(float posX, float posY, GUN_TYPE type)
{
	int index = SetItem(posX, posY, ITEM_TYPE_WEAPON);
	g_Item[index].gunType = type;

	switch (g_Item[index].gunType)
	{
	case GUN_TYPE_SEMI_AUTO:
		g_Item[index].animeBasePattern = ITEM_WIDTH_PATTERN * 3;
		g_Item[index].anime = false;
		g_Item[index].animeWidthPattern = 1;
		break;

	case GUN_TYPE_FULL_AUTO:
		g_Item[index].animeBasePattern = ITEM_WIDTH_PATTERN * 4;
		g_Item[index].anime = false;
		g_Item[index].animeWidthPattern = 1;
		break;

	case GUN_TYPE_CHARGE_FULL_AUTO:
		g_Item[index].animeBasePattern = ITEM_WIDTH_PATTERN * 5;
		g_Item[index].anime = false;
		g_Item[index].animeWidthPattern = 1;
		break;

	default:
		break;
	}
}

//---------------------------------------------------
// アイテムをアニメーション
//---------------------------------------------------
void ItemAnime(int index)
{
	if (g_Item[index].use)
	{
		g_Item[index].anime = true;
		g_Item[index].animeLoop = false;
	}
}

//---------------------------------------------------
// アイテムをフェードアウト
//---------------------------------------------------
void ItemFadeOut(int index)
{
	if (g_Item[index].use)
	{
		g_Item[index].fadeOut = true;
	}
}

//---------------------------------------------------
// アイテムを全て消す
//---------------------------------------------------
void ItemAllDelete()
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		g_Item[i].use = false;
	}
}