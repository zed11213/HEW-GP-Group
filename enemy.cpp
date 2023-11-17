//===================================================
//エネミー(enemy.cpp)
//Auhor:渡邉 修	Date:2023.9.4
//===================================================
#include "enemy.h"
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
#include "item.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_TexNo1;
static int g_TexNo2;
static int g_TexNo3;
static int g_SE_landing;
static int g_SE_enemyDown;
static int g_SE_drop;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimePattern;
static ENEMY g_Enemy[ENEMY_MAX];
static TILE_DATA* p_Tile;
static BULLET* p_Bullet;
static PLAYER* p_Player;
static bool g_playSoundTrigger;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitEnemy(void)
{
	g_TexNo1 = LoadTexture((char*)"data/TEXTURE/Enemy1.png");
	g_TexNo2 = LoadTexture((char*)"data/TEXTURE/Enemy2.png");
	g_TexNo3 = LoadTexture((char*)"data/TEXTURE/Enemy3.png");
	//効果音作成
	char se1[] =
	{
		"data\\SE\\se_landing.wav"
	};
	g_SE_landing = LoadSound(&se1[0]);

	char se2[] =
	{
		"data\\SE\\se_enemyDown.wav"
	};
	g_SE_enemyDown = LoadSound(&se2[0]);

	char se3[] =
	{
		"data\\SE\\drop.wav"
	};
	g_SE_drop = LoadSound(&se3[0]);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].use = false;
		g_Enemy[i].pos.x = SCREEN_WIDTH / 2;
		g_Enemy[i].pos.y = SCREEN_HEIGHT / 4;
		g_Enemy[i].vel.x = ENEMY_SPEED;
		g_Enemy[i].vel.y = ENEMY_SPEED;
		//ベクトルの正規化
		D3DXVec2Normalize(&g_Enemy[i].vel, &g_Enemy[i].vel);
		g_Enemy[i].vel *= ENEMY_SPEED;//目的のスピードにするためにスピードを乗算する
		g_Enemy[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Enemy[i].hsp = 0;
		g_Enemy[i].vsp = 0;
		g_Enemy[i].grv = 0.3f;
		g_Enemy[i].walksp = ENEMY_SPEED;
		g_Enemy[i].controller = true;
		g_Enemy[i].hascontrol = false;
		g_Enemy[i].canjump = 0;
		g_Enemy[i].knockBackX = 0;
		g_Enemy[i].knockBackY = 0;
		g_Enemy[i].ground = false;
		g_Enemy[i].state = ENEMY_STATE_IDLE;
		g_Enemy[i].oldState = ENEMY_STATE_IDLE;
		g_Enemy[i].animeWidthPattern = 1;
		g_Enemy[i].animeHeightPattern = 1;
		g_Enemy[i].animeFrameMax = 0;
		g_Enemy[i].size = D3DXVECTOR2(ENEMY_WIDTH, ENEMY_HEIGHT);
		g_Enemy[i].leftMove = false;
		g_Enemy[i].rightMove = false;
		g_Enemy[i].jump = false;
		g_Enemy[i].move = 0;
		g_Enemy[i].stateCou = 0;
		g_Enemy[i].animeBasePattern = 0;
		g_Enemy[i].animePattern = 0;
		g_Enemy[i].animeSkipFrame = 0;
		g_Enemy[i].reverse = true;
		g_Enemy[i].hp = 0;
		g_Enemy[i].oldHp = 0;
		g_Enemy[i].unbeatable = false;
		g_Enemy[i].unbeatableTime = ENEMY_UNBEATABLE_TEME;
		g_Enemy[i].unbeatableCou = 0;
		g_Enemy[i].score = 0;
		g_Enemy[i].type = ENEMY_TYPE_1;
		g_Enemy[i].textureNo = g_TexNo1;
		g_Enemy[i].jumpPower = -15;
		g_Enemy[i].oldGround = false;
	}

	//グローバル変数初期化
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / ENEMY_WIDTH_PATTERN;
	g_VH = 1.0f / ENEMY_HEIGHT_PATTERN;
	g_AnimePattern = 0;
	g_playSoundTrigger = false;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateEnemy(void)
{
	g_playSoundTrigger = false;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use)
		{
			g_Enemy[i].oldState = g_Enemy[i].state;
			g_Enemy[i].oldGround = g_Enemy[i].ground;
			g_Enemy[i].jump = false;
			g_Enemy[i].color.a = 1;

			//行動パターン
			switch (g_Enemy[i].type)
			{
			case ENEMY_TYPE_1:
				//ランダムで移動する
				g_Enemy[i].stateCou = Counter(g_Enemy[i].stateCou, 30);
				if (0 == g_Enemy[i].stateCou)
				{
					int stateRan = RandomPercent(40, 25, 25, 10);
					if (stateRan == 1)g_Enemy[i].leftMove = g_Enemy[i].rightMove = false;
					if (stateRan == 2)
					{
						g_Enemy[i].leftMove = true;
						g_Enemy[i].rightMove = false;
					}

					if (stateRan == 3)
					{
						g_Enemy[i].rightMove = true;
						g_Enemy[i].leftMove = false;
					}

					if (stateRan == 4)g_Enemy[i].jump = true;
				}
					break;

			case ENEMY_TYPE_2:
				g_Enemy[i].jumpPower = -8;
				g_Enemy[i].stateCou = Counter(g_Enemy[i].stateCou, 10);
				if (0 == g_Enemy[i].stateCou)
				{

					int stateRan = RandomPercent(0, 5, 5, 90);
					if (stateRan == 1)g_Enemy[i].leftMove = g_Enemy[i].rightMove = false;
					if (stateRan == 2)
					{
						g_Enemy[i].leftMove = true;
						g_Enemy[i].rightMove = false;
					}

					if (stateRan == 3)
					{
						g_Enemy[i].rightMove = true;
						g_Enemy[i].leftMove = false;
					}

					if (stateRan == 4)g_Enemy[i].jump = true;
				}
				break;

			case ENEMY_TYPE_3:
				g_Enemy[i].grv = 0;
				g_Enemy[i].stateCou = Counter(g_Enemy[i].stateCou, 30);
				if (0 == g_Enemy[i].stateCou)
				{
					int stateRan = RandomPercent(25, 25, 25, 25);
					if (stateRan == 1)g_Enemy[i].leftMove = g_Enemy[i].rightMove = false;
					if (stateRan == 2)
					{
						g_Enemy[i].leftMove = true;
						g_Enemy[i].rightMove = false;
					}

					if (stateRan == 3)
					{
						g_Enemy[i].rightMove = true;
						g_Enemy[i].leftMove = false;
					}

					if (stateRan == 4)
					{
						g_Enemy[i].jumpPower = GetRandomInt(-10, 10);
						g_Enemy[i].jump = true;
					}	
				}
				break;

			default:
				break;
			}

			//何も押していない又はA,Dを両方押してるときは0(false)を返す
			g_Enemy[i].move = g_Enemy[i].rightMove - g_Enemy[i].leftMove;

			if (g_Enemy[i].knockBackX != 0)
			{
				if (g_Enemy[i].knockBackX > 0) g_Enemy[i].knockBackX -= 1.0f;
				if (g_Enemy[i].knockBackX < 0) g_Enemy[i].knockBackX += 1.0f;
			}

			//移動方向と速度
			g_Enemy[i].hsp = (g_Enemy[i].move * g_Enemy[i].walksp) + g_Enemy[i].knockBackX;

			//重力
			g_Enemy[i].vsp = (g_Enemy[i].vsp + g_Enemy[i].grv) + g_Enemy[i].knockBackY;

			//ジャンプ
			g_Enemy[i].canjump -= 1;
			if (((g_Enemy[i].canjump > 0) && g_Enemy[i].jump) || g_Enemy[i].grv == 0)
			{
				g_Enemy[i].vsp = g_Enemy[i].jumpPower;
				g_Enemy[i].canjump = 0;
			}

			//壁の衝突判定
			p_Tile = GetMapInfo(g_Enemy[i].pos);

			for (int j = 0; j < 9; j++)
			{
				if (p_Tile[j].attrib == MAP_ATTRIB_STOP)
				{
					//横に壁がある場合
					if (CollisionRot(g_Enemy[i].pos.x + g_Enemy[i].hsp, g_Enemy[i].pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
					{
						//壁に当たるまで１ピクセル壁に近づける
						while (!CollisionRot(g_Enemy[i].pos.x + Sign(g_Enemy[i].hsp), g_Enemy[i].pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
						{
							g_Enemy[i].pos.x = g_Enemy[i].pos.x + Sign(g_Enemy[i].hsp);
						}
						g_Enemy[i].hsp = 0;
					}

					//縦に壁がある場合
					if (CollisionRot(g_Enemy[i].pos.x, g_Enemy[i].pos.y + g_Enemy[i].vsp, p_Tile[j].pos.x, p_Tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
					{
						//壁に当たるまで１ピクセル壁に近づける
						while (!CollisionRot(g_Enemy[i].pos.x, g_Enemy[i].pos.y + Sign(g_Enemy[i].vsp), p_Tile[j].pos.x, p_Tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
						{
							g_Enemy[i].pos.y = g_Enemy[i].pos.y + Sign(g_Enemy[i].vsp);
						}
						g_Enemy[i].vsp = 0;
					}
				}
			}

			//横移動
			g_Enemy[i].pos.x += g_Enemy[i].hsp;

			// ステージループ処理
			if (g_Enemy[i].pos.x > STAGE_SIZE)
			{
				g_Enemy[i].pos.x -= STAGE_SIZE;
			}
			else if (g_Enemy[i].pos.x < 0)
			{
				g_Enemy[i].pos.x += STAGE_SIZE;
			}

			//縦移動
			g_Enemy[i].pos.y += g_Enemy[i].vsp;

			//ノックバックが加算されていくのを回避
			if (g_Enemy[i].vsp != 0)g_Enemy[i].vsp -= g_Enemy[i].knockBackY;
			g_Enemy[i].knockBackY *= 0.5f;
			if (g_Enemy[i].knockBackY < 0.9f)g_Enemy[i].knockBackY = 0;

			p_Tile = GetMapInfo(g_Enemy[i].pos);

			//下が地面の場合
			for (int j = 0; j < 9; j++)
			{
				if ((p_Tile[j].attrib == MAP_ATTRIB_STOP) && (j == 6 || j == 7 || j == 8))
				{
					//地面に触れているかの処理
					if (CollisionRot(g_Enemy[i].pos.x, g_Enemy[i].pos.y + 1, p_Tile[j].pos.x, p_Tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
					{
						g_Enemy[i].ground = true;

						if (g_Enemy[i].oldGround != g_Enemy[i].ground)
						{
							if (!g_playSoundTrigger)
							{
								//画面内なら鳴らす
								if (!OffScreenJudge(g_Enemy[i].pos.x, g_Enemy[i].pos.y, ENEMY_WIDTH, ENEMY_HEIGHT))
								{
									PlaySound(g_SE_landing, 0);
									g_playSoundTrigger = true;
								}
							}
						}

						break;
					}
					else
					{
						g_Enemy[i].ground = false;
					}
				}
			}

			if (g_Enemy[i].rightMove == true) g_Enemy[i].reverse = false;//進行方向基準
			else if (g_Enemy[i].leftMove == true) g_Enemy[i].reverse = true;

			//地面に触れている場合
			if (g_Enemy[i].ground)
			{
				g_Enemy[i].canjump = 10;
				g_Enemy[i].knockBackX = 0;

				//止まっているときの処理
				if (g_Enemy[i].hsp == 0)
				{
					g_Enemy[i].state = ENEMY_STATE_IDLE;
				}
				//動いているときの処理
				else
				{
					g_Enemy[i].state = ENEMY_STATE_WALK;
				}
			}
			//地面に触れていない場合
			else
			{
				//上昇しているか下降しているかの判定
				if (Sign(g_Enemy[i].vsp) > 0)
				{
					g_Enemy[i].state = ENEMY_STATE_FALL;
				}
				else
				{
					g_Enemy[i].state = ENEMY_STATE_RISE;
				}
			}

			//弾との当たり判定
			//p_Bullet = GetBullet();
			
			//float bulletRadian = 0;
			//for (int j = 0; j < BULLET_MAX; j++)
			//{
			//	if (!p_Bullet[j].use)continue;

			//	if (!g_Enemy[i].unbeatable && CollisionRot(g_Enemy[i].pos.x, g_Enemy[i].pos.y, p_Bullet[j].pos.x, p_Bullet[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, BULLET_HITBOX_WIDTH, BULLET_HITBOX_HEIGHT, 0.0f))
			//	{
			//		g_Enemy[i].hp--;
			//		bulletRadian = PointDirectionRadian(g_Enemy[i].pos.x, g_Enemy[i].pos.y, p_Bullet[j].pos.x, p_Bullet[j].pos.y);
			//		break;
			//	}
			//}
		
			//体力がなくなったときの処理
			if (g_Enemy[i].hp <= 0)
			{
				SetParticle(g_Enemy[i].pos.x, g_Enemy[i].pos.y, 30, 0, 0, 0);
				PlaySound(g_SE_enemyDown, 0);
				SetPlayerScore(g_Enemy[i].score);
				g_Enemy[i].use = false;

				int itemRan = RandomPercent(60, 5, 5);
					switch (itemRan)
					{
					case 1:
						SetItem(g_Enemy[i].pos.x, g_Enemy[i].pos.y, ITEM_TYPE_COIN);
						break;

					case 2:
						SetItem(g_Enemy[i].pos.x, g_Enemy[i].pos.y, ITEM_TYPE_TMATO);
						break;

					case 3:
						SetItem(g_Enemy[i].pos.x, g_Enemy[i].pos.y, ITEM_TYPE_TREASURE_BOX);
						break;

					default:
						break;
					}
				
			}

			//ダメージを食らった時の処理
			else if (g_Enemy[i].oldHp != g_Enemy[i].hp)
			{
				//g_Enemy[i].unbeatable = true;
			}
			g_Enemy[i].oldHp = g_Enemy[i].hp;

			//無敵中の処理
			if (g_Enemy[i].unbeatable)
			{
				if (g_Enemy[i].unbeatableCou % 10 == 0)g_Enemy[i].color.a = 0.1f;

				g_Enemy[i].unbeatableCou = Counter(g_Enemy[i].unbeatableCou, g_Enemy[i].unbeatableTime);
				if (g_Enemy[i].unbeatableCou == 0)g_Enemy[i].unbeatable = false;
			}

			//範囲外で消す
			if (g_Enemy[i].pos.y > SCREEN_HEIGHT)
			{
				g_Enemy[i].use = false;
				SetHitSpark(g_Enemy[i].pos.x, g_Enemy[i].pos.y, 0);
			}
				
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawEnemy(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//テクスチャのフィルターをOFF
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use)
		{
			if (g_Enemy[i].oldState != g_Enemy[i].state)
			{
				g_Enemy[i].animeSkipFrame = 0;
				g_Enemy[i].animePattern = 0;
				//モーションしないときのベースの値は縦で数えて幾つ目か
				//モーションするときは左上から横に数えて幾つ目か
				switch (g_Enemy[i].state)
				{
				case ENEMY_STATE_IDLE:
					g_Enemy[i].animeBasePattern = 0;
					g_Enemy[i].animeWidthPattern = 1;
					break;

				case ENEMY_STATE_WALK:
					g_Enemy[i].animeBasePattern = 12;
					g_Enemy[i].animeWidthPattern = 4;
					break;

				case ENEMY_STATE_RISE:
					g_Enemy[i].animeBasePattern = 4;
					g_Enemy[i].animeWidthPattern = 1;
					break;

				case ENEMY_STATE_FALL:
					g_Enemy[i].animeBasePattern = 8;
					g_Enemy[i].animeWidthPattern = 1;
					break;

				case ENEMY_STATE_DEAD:
					g_Enemy[i].animeBasePattern = 8;
					g_Enemy[i].animeWidthPattern = 1;
					break;

				default:
					break;
				}
			}

			g_Enemy[i].animeFrameMax = g_Enemy[i].animeWidthPattern * g_Enemy[i].animeHeightPattern;

			D3DXVECTOR2 uv = SetAnimation(g_Enemy[i].animeBasePattern, g_Enemy[i].animePattern, ENEMY_WIDTH_PATTERN, ENEMY_HEIGHT_PATTERN, g_Enemy[i].animeWidthPattern, g_Enemy[i].reverse);

			g_U = uv.x;
			g_V = uv.y;

			g_Enemy[i].animeSkipFrame = Counter(g_Enemy[i].animeSkipFrame, ENEMY_FRAME_SPAN);

			if (g_Enemy[i].animeSkipFrame == 0)
			{
				g_Enemy[i].animePattern = Counter(g_Enemy[i].animePattern, g_Enemy[i].animeFrameMax);
			}

			DrawSpriteColorRotateCamera(g_Enemy[i].textureNo,
				(int)g_Enemy[i].pos.x,
				(int)g_Enemy[i].pos.y,
				g_Enemy[i].size.x, g_Enemy[i].size.y,	//幅、高さ
				g_U, g_V,		//中心UV座標
				g_UW, g_VH,		//テクスチャ幅、高さ
				g_Enemy[i].color.r, g_Enemy[i].color.g, g_Enemy[i].color.b, g_Enemy[i].color.a,
				0.0f
			);
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitEnemy(void)
{
	delete[] p_Tile;
}

//---------------------------------------------------
// エネミー取得処理
//---------------------------------------------------
ENEMY* GetEnemy()
{
	return &g_Enemy[0];
}

//---------------------------------------------------
// ノックバック設定 [引数]index: 配列番号
//---------------------------------------------------
void SetEnemyKnockBack(int index, float power, float radian)
{
	// ラジアンを度に変換
	double degrees = radian * 180.0f / 3.14159f;

	//上にのみ跳ぶようにする(上半円が右を0°とし0～-180、下半円が左を180°とし180～0)
	if (abs(degrees) < 90.0f) degrees = 45;
	if (abs(degrees) > 90.0f) degrees = 135;

	float radianA = degrees * 3.14159f / 180.0f;

	D3DXVECTOR2 vector = CalculateVector(-power, radianA);

	if (g_Enemy[index].use)
	{
		g_Enemy[index].knockBackX = vector.x;
		g_Enemy[index].knockBackY = vector.y;
	}
}

//---------------------------------------------------
// 反動を設定 [引数]index: 配列番号
//---------------------------------------------------
void SetEnemyGunKick(int index, float power, float radian)
{
	D3DXVECTOR2 vector = CalculateVector(-power, radian);

	if (g_Enemy[index].use)
	{
		g_Enemy[index].knockBackX = vector.x;
		g_Enemy[index].knockBackY = vector.y;
	}
}

//---------------------------------------------------
// エネミーを配置
//---------------------------------------------------
void SetEnemy(float posX, float posY, ENEMY_TYPE type)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!g_Enemy[i].use)
		{
			g_Enemy[i].leftMove = false;
			g_Enemy[i].rightMove = false;
			g_Enemy[i].jump = false;
			g_Enemy[i].pos.x = posX;
			g_Enemy[i].pos.y = posY;
			g_Enemy[i].hsp = 0;
			g_Enemy[i].vsp = 0;
			g_Enemy[i].stateCou = 0;
			g_Enemy[i].reverse = true;
			g_Enemy[i].oldHp = 0;
			g_Enemy[i].unbeatable = false;
			g_Enemy[i].unbeatableTime = ENEMY_UNBEATABLE_TEME;
			g_Enemy[i].unbeatableCou = 0;
			g_Enemy[i].color.a = 1.0f;
			g_Enemy[i].grv = 0.3f;
			g_Enemy[i].animeBasePattern = 0;
			g_Enemy[i].animePattern = 0;
			g_Enemy[i].animeSkipFrame = 0;
			g_Enemy[i].state = ENEMY_STATE_IDLE;
			g_Enemy[i].jumpPower = -15;
			g_Enemy[i].animeSkipFrame = 0;
			g_Enemy[i].animePattern = 0;
			g_Enemy[i].animeBasePattern = 0;
			g_Enemy[i].animeWidthPattern = 1;
			g_Enemy[i].canjump = 0;
			g_Enemy[i].walksp = ENEMY_SPEED;
			g_Enemy[i].knockBackX = 0;
			g_Enemy[i].knockBackY = 0;

			g_Enemy[i].type = type;

			switch (g_Enemy[i].type)
			{
			case ENEMY_TYPE_1:
				g_Enemy[i].textureNo = g_TexNo1;
				g_Enemy[i].score = 5;
				g_Enemy[i].hp = 30;
				break;

			case ENEMY_TYPE_2:
				g_Enemy[i].textureNo = g_TexNo2;
				g_Enemy[i].score = 10;
				g_Enemy[i].hp = 3;
				break;

			case ENEMY_TYPE_3:
				g_Enemy[i].textureNo = g_TexNo3;
				g_Enemy[i].score = 30;
				g_Enemy[i].hp = 3;
				break;

			default:
				break;
			}

			g_Enemy[i].use = true;

			break;
		}
	}
}

//---------------------------------------------------
// エネミー全削除
//---------------------------------------------------
void EnemyAllDelete()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use)
		{
			if (!OffScreenJudge(g_Enemy[i].pos.x, g_Enemy[i].pos.y, ENEMY_WIDTH, ENEMY_HEIGHT))
			{
				SetParticle(g_Enemy[i].pos.x, g_Enemy[i].pos.y, 30, 0, 0, 0);
			}

			g_Enemy[i].use = false;
		}
	}
}

//---------------------------------------------------
// エネミーの体力増減
//---------------------------------------------------
void EnemyHpDown(int index, int damage)
{
	g_Enemy[index].hp -= damage;
}