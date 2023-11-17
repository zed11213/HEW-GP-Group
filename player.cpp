//===================================================
//プレイヤー(player.cpp)
//Auhor:渡邉 修	Date:2023.8.25
//===================================================
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "dead.h"
#include "main.h"
#include "tile.h"
#include "icon.h"
#include "enemy.h"
#include "particle.h"
#include "text_create.h"
#include "score.h"
#include "item.h"
#include "hit_spark.h"
#include "gun.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_TexNo;
static int g_SE_landing;
static int g_SE_playerHit;
static int g_SE_playerDown;
static int g_SE_coinGet;
static int g_SE_hpUp;
static int g_SE_powerUp;
static int g_SE_boxOpen;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimePattern;
static int g_AnimeBasePattern;//アニメーション番号の方向ごとのベース値
static int g_AnimeSkipFrame;
static float g_AnimeSkipFrameFloat;
static PLAYER g_Player[PLAYER_MAX];
static TILE_DATA* p_Tile;
static ENEMY* p_Enemy;
static bool g_Reverse;
static D3DXVECTOR2 g_LastGroundPos;
static int g_DropRevivalTime;
static int g_DropRevivalCou;
static ITEM* p_Item;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitPlayer(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Player.png");
	//効果音作成
	char se1[] =
	{
		"data\\SE\\se_landing.wav"
	};
	g_SE_landing = LoadSound(&se1[0]);

	char se2[] =
	{
		"data\\SE\\se_playerHit.wav"
	};
	g_SE_playerHit = LoadSound(&se2[0]);

	char se3[] =
	{
		"data\\SE\\se_playerDown.wav"
	};
	g_SE_playerDown = LoadSound(&se3[0]);

	char se4[] =
	{
		"data\\SE\\se_coinGet.wav"
	};
	g_SE_coinGet = LoadSound(&se4[0]);

	char se5[] =
	{
		"data\\SE\\se_hpUp.wav"
	};
	g_SE_hpUp = LoadSound(&se5[0]);

	char se6[] =
	{
		"data\\SE\\se_powerUp.wav"
	};
	g_SE_powerUp = LoadSound(&se6[0]);

	char se7[] =
	{
		"data\\SE\\se_boxOpen.wav"
	};
	g_SE_boxOpen = LoadSound(&se7[0]);

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_Player[i].use = false;
		g_Player[i].pos.x = SCREEN_WIDTH / 2;
		g_Player[i].pos.y = SCREEN_HEIGHT / 4;
		g_Player[i].vel.x = PLAYER_SPEED;
		g_Player[i].vel.y = PLAYER_SPEED;
		//ベクトルの正規化
		D3DXVec2Normalize(&g_Player[i].vel, &g_Player[i].vel);
		g_Player[i].vel *= PLAYER_SPEED;//目的のスピードにするためにスピードを乗算する
		g_Player[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Player[i].hsp = 0;
		g_Player[i].vsp = 0;
		g_Player[i].grv = 0;
		g_Player[i].walksp = PLAYER_SPEED;
		g_Player[i].controller = true;
		g_Player[i].hascontrol = false;
		g_Player[i].canjump = 0;
		g_Player[i].knockBackX = 0;
		g_Player[i].knockBackY = 0;
		g_Player[i].ground = false;
		g_Player[i].state = STATE_IDLE;
		g_Player[i].oldState = STATE_IDLE;
		g_Player[i].animeWidthPattern = 1;
		g_Player[i].animeHeightPattern = 1;
		g_Player[i].animeFrameMax = 0;
		g_Player[i].size = D3DXVECTOR2(PLAYER_WIDTH, PLAYER_HEIGHT);
		g_Player[i].hp = PLAYER_INIT_HP;
		g_Player[i].oldHp = PLAYER_INIT_HP;
		g_Player[i].unbeatable = false;
		g_Player[i].unbeatableCou = 0;
		g_Player[i].unbeatableTime = PLAYER_UNBEATABLE_TEME;
		g_Player[i].score = 0;
		g_Player[i].notLoopPos = D3DXVECTOR2(0, 0);
		g_Player[i].loopTrigger = 0;
		g_Player[i].oldPos = D3DXVECTOR2(0, 0);
		g_Player[i].oldGround = false;
		g_Player[i].coin = 0;
		g_Player[i].maxHp = 3;
	}

	//グローバル変数初期化
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / PLAYER_WIDTH_PATTERN;
	g_VH = 1.0f / PLAYER_HEIGHT_PATTERN;
	g_AnimePattern = 0;
	g_AnimeSkipFrame = 0;
	g_AnimeSkipFrameFloat = 0;
	g_AnimeBasePattern = 0;
	g_Reverse = false;
	g_LastGroundPos = D3DXVECTOR2(0, 0);
	g_DropRevivalTime = 60;
	g_DropRevivalCou = 0;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdatePlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use)
		{
			g_Player[i].oldState = g_Player[i].state;
			g_Player[i].oldGround = g_Player[i].ground;
			g_Player[i].oldHp = g_Player[i].hp;
			g_Player[i].oldPos = g_Player[i].pos;
			
			bool keyLeft = GetKeyboardPress(DIK_A);
			bool keyRight = GetKeyboardPress(DIK_D);
			bool keyJump = GetKeyboardPress(DIK_SPACE);
			bool keySelect = GetKeyboardTrigger(DIK_E);

			//何も押していない又はA,Dを両方押してるときは0(false)を返す
			int move = keyRight - keyLeft;

			if (g_Player[i].knockBackX != 0)
			{
				if (g_Player[i].knockBackX > 0) g_Player[i].knockBackX -= 1.0f;
				if (g_Player[i].knockBackX < 0) g_Player[i].knockBackX += 1.0f;
			}

			//移動方向と速度
			g_Player[i].hsp = (move * g_Player[i].walksp) + g_Player[i].knockBackX;

			//重力
			g_Player[i].vsp = (g_Player[i].vsp + g_Player[i].grv) + g_Player[i].knockBackY;

			//ジャンプ
			g_Player[i].canjump -= 1;
			if((g_Player[i].canjump > 0) && keyJump)
			{
				g_Player[i].vsp = -10;
				g_Player[i].canjump = 0;
			}

			//壁の衝突判定
			p_Tile = GetMapInfo(g_Player[i].pos);

			for (int j = 0; j < 9; j++)
			{
				if (p_Tile[j].attrib == MAP_ATTRIB_STOP)
				{
					//横に壁がある場合
					if (CollisionRot(g_Player[i].pos.x + g_Player[i].hsp , g_Player[i].pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
					{
						//壁に当たるまで１ピクセル壁に近づける
						while (!CollisionRot(g_Player[i].pos.x + Sign(g_Player[i].hsp), g_Player[i].pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
						{
							g_Player[i].pos.x = g_Player[i].pos.x + Sign(g_Player[i].hsp);
						}
						g_Player[i].hsp = 0;
					}

					//縦に壁がある場合
					if (CollisionRot(g_Player[i].pos.x, g_Player[i].pos.y + g_Player[i].vsp, p_Tile[j].pos.x, p_Tile[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
					{
						//壁に当たるまで１ピクセル壁に近づける
						while (!CollisionRot(g_Player[i].pos.x, g_Player[i].pos.y + Sign(g_Player[i].vsp), p_Tile[j].pos.x, p_Tile[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
						{
							g_Player[i].pos.y = g_Player[i].pos.y + Sign(g_Player[i].vsp);
						}
						g_Player[i].vsp = 0;
					}
				}
			}
			
			//横移動
			g_Player[i].pos.x += g_Player[i].hsp;

			// ステージループ処理
			g_Player[i].loopTrigger = 0;
			g_Player[i].notLoopPos.x += g_Player[i].pos.x - g_Player[i].oldPos.x;

			if (g_Player[i].pos.x > STAGE_SIZE)
			{
				g_Player[i].pos.x -= STAGE_SIZE;
				g_Player[i].loopTrigger = 1;
			}
			else if (g_Player[i].pos.x < 0)
			{
				g_Player[i].pos.x += STAGE_SIZE;
				g_Player[i].loopTrigger = -1;
			}

			//縦移動
			g_Player[i].pos.y += g_Player[i].vsp;
			g_Player[i].notLoopPos.y = g_Player[i].pos.y;

			//ノックバックが加算されていくのを回避
			if (g_Player[i].vsp != 0)g_Player[i].vsp -= g_Player[i].knockBackY;
			g_Player[i].knockBackY = 0;

			p_Tile = GetMapInfo(g_Player[i].pos);

			//下が地面の場合
			for (int j = 0; j < 9; j++)
			{
				if ((p_Tile[j].attrib == MAP_ATTRIB_STOP) && (j == 6 || j == 7 || j == 8))
				{
					//地面に触れているかの処理
					if (CollisionRot(g_Player[i].pos.x, g_Player[i].pos.y + 1, p_Tile[j].pos.x, p_Tile[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
					{
						g_Player[i].ground = true;

						if (g_Player[i].oldGround != g_Player[i].ground)
						{
							PlaySound(g_SE_landing, 0);
						}

						break;
					}
					else
					{
						g_Player[i].ground = false;
					}
				}
			}
	
			//プレイヤーに対してマウスが左右どっちにあるか調べる
			int aimSide = GetMouseAbsoluteX() - g_Player[i].pos.x;
			//テクスチャ反転
			//if (aimSide > 0) g_Reverse = false;//マウス基準
			//else if(aimSide < 0) g_Reverse = true;

			if (g_Player[i].hsp > 0) g_Reverse = false;//進行方向基準
			else if (g_Player[i].hsp < 0) g_Reverse = true;

			//地面に触れている場合
			if (g_Player[i].ground)
			{
				g_Player[i].canjump = 10;
				g_Player[i].knockBackX = 0;

				//止まっているときの処理
				if (g_Player[i].hsp == 0)
				{
					g_Player[i].state = STATE_IDLE;
					g_LastGroundPos = g_Player[i].pos;
				}
				//動いているときの処理
				else
				{
					g_Player[i].state = STATE_WALK;
					if (aimSide != Sign(g_Player[i].hsp));
				}
			}
			//地面に触れていない場合
			else
			{
				//上昇しているか下降しているかの判定
				if (Sign(g_Player[i].vsp) > 0)
				{
					g_Player[i].state = STATE_FALL;
				}
				else
				{
					g_Player[i].state = STATE_RISE;
				}
			}

			//ダメージ関係
			p_Enemy = GetEnemy();
			float enemyRadian = 0;
			for (int j = 0; j < ENEMY_MAX; j++)
			{
				if (!p_Enemy[j].use || OffScreenJudge(p_Enemy[j].pos.x, p_Enemy[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT))
				{
					continue;
				}
				if (!g_Player[i].unbeatable && CollisionRot(g_Player[i].pos.x, g_Player[i].pos.y, p_Enemy[j].pos.x, p_Enemy[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
				{
					g_Player[i].hp--;
					enemyRadian = PointDirectionRadian(g_Player[i].pos.x, g_Player[i].pos.y, p_Enemy[j].pos.x, p_Enemy[j].pos.y);
					SetPlayerKnockBack(50, enemyRadian);
					break;
				}
			}
			
			//アイテム関係
			p_Item = GetItem();
			for (int j = 0; j < ITEM_MAX; j++)
			{
				if (!p_Item[j].use || OffScreenJudge(p_Item[j].pos.x, p_Item[j].pos.y, ITEM_HITBOX_WIDTH, ITEM_HITBOX_HEIGHT))
				{
					continue;
				}
				if (CollisionRot(g_Player[i].pos.x, g_Player[i].pos.y, p_Item[j].pos.x, p_Item[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, ITEM_WIDTH * 0.5f, ITEM_HEIGHT * 0.5f, 0.0f))
				{
					switch (p_Item[j].type)
					{
					case ITEM_TYPE_COIN:
						PlaySound(g_SE_coinGet, 0);
						g_Player[i].coin++;
						SetHitSpark(p_Item[j].pos.x, p_Item[j].pos.y, 0, 251, 185, 84);
						p_Item[j].use = false;
						j += ITEM_MAX;
						break;

					case ITEM_TYPE_TMATO:
						if (g_Player[i].hp < g_Player[i].maxHp)
						{
							PlaySound(g_SE_hpUp, 0);
							g_Player[i].hp++;
							SetHitSpark(p_Item[j].pos.x, p_Item[j].pos.y, 0, 232, 59, 59);
							p_Item[j].use = false;
						}
						j += ITEM_MAX;
						break;

					case ITEM_TYPE_TREASURE_BOX:
						if (keySelect && p_Item[j].color.a == 1.0f)
						{
							if (g_Player[i].coin < 20)
							{
								//コイン枚数表示
								SetDrawTextCreate("NOT ENOUGH COINS " + std::to_string(20 - g_Player[i].coin), SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 4.0f, 1.0f, 90, 0.1f, 0.01f, 255.0f, 0.0f, 0.0f);
							}
							else
							{
								PlaySound(g_SE_boxOpen, 0);
								g_Player[i].coin -= 20;
								int ran = RandomPercent(40, 30, 30);
								GUN_TYPE gun;
								switch (ran)
								{
								case 1:
									gun = GUN_TYPE_SEMI_AUTO;
									break;
								case 2:
									gun = GUN_TYPE_FULL_AUTO;
									break;
								case 3:
									gun = GUN_TYPE_CHARGE_FULL_AUTO;
									break;
								default:
									break;
								}
								SetWeapon(p_Item[j].pos.x, p_Item[j].pos.y, gun);
								SetParticle(p_Item[j].pos.x, p_Item[j].pos.y, 10, 251, 185, 84);
								ItemAnime(j);
								ItemFadeOut(j);
							}
						}
						j += ITEM_MAX;
						break;

					case ITEM_TYPE_WEAPON:
						if (keySelect)
						{
							PlaySound(g_SE_powerUp, 0);
							SetHitSpark(p_Item[j].pos.x, p_Item[j].pos.y, 0, 155, 155, 255);
							p_Item[j].use = false;
							ChangeGun(p_Item[j].gunType);
						}
						j += ITEM_MAX;
						break;

					default:
						break;
					}
				}
			}

			//落下時の処理
			if (g_Player[i].pos.y > SCREEN_HEIGHT + PLAYER_HEIGHT)
			{
				g_DropRevivalCou = Counter(g_DropRevivalCou, g_DropRevivalTime);
				if(g_DropRevivalCou == g_DropRevivalTime - 1) g_Player[i].hp--;
				if (g_DropRevivalCou == 0) g_Player[i].pos = g_LastGroundPos;
			}

			//体力がなくなったときの処理
			if (g_Player[i].hp <= 0)
			{
				SetParticle(g_Player[i].pos.x, g_Player[i].pos.y, 30, 0, 0, 0);
				PlaySound(g_SE_playerDown, 0);
				g_Player[i].use = false;
				
			}
			//ダメージを食らった時の処理
			else if (g_Player[i].oldHp > g_Player[i].hp)
			{
				g_Player[i].unbeatable = true;
				PlaySound(g_SE_playerHit, 0);

			}

			//無敵中の処理
			if (g_Player[i].unbeatable)
			{
				g_Player[i].color.a = 1;
				g_Player[i].color.a = 0.5f;

				g_Player[i].unbeatableCou = Counter(g_Player[i].unbeatableCou, g_Player[i].unbeatableTime);
				if (g_Player[i].unbeatableCou == 0)
				{
					g_Player[i].unbeatable = false;
					g_Player[i].color.a = 1.0f;
				}
			}
			else
			{
				if (g_Player[i].color.a == 0)g_Player[i].color.a = 1;
			}
		}

		if (g_Player[i].hp <= 0)
		{
			bool keyRespawn = GetKeyboardTrigger(DIK_R);

			//ゲームオーバー時の処理
			SetDrawTextCreate("RESPAWN", SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 80, 10, 3);
			SetDrawTextCreate("R", SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 80, 10, 3);

			if (keyRespawn)
			{
				SetWave(1);
				EnemyAllDelete();
				ItemAllDelete();
				SetPlayer(g_LastGroundPos.x, g_LastGroundPos.y);
			}
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawPlayer(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//テクスチャのフィルターをOFF
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use)
		{
			if (g_Player[i].oldState != g_Player[i].state)
			{
				g_AnimeSkipFrame = 0;
				g_AnimePattern = 0;

				switch (g_Player[i].state)
				{
				case STATE_IDLE:
					g_AnimeBasePattern = 0;
					g_Player[i].animeWidthPattern = 1;
					break;

				case STATE_WALK:
					g_AnimeBasePattern = 17 * 3;
					g_Player[i].animeWidthPattern = 15;
					break;

				case STATE_RISE:
					g_AnimeBasePattern = 17;
					g_Player[i].animeWidthPattern = 17;
					break;

				case STATE_FALL:
					g_AnimeBasePattern = 17 * 2;
					g_Player[i].animeWidthPattern = 1;
					break;

				default:
					break;
				}
			}
			
			g_Player[i].animeFrameMax = g_Player[i].animeWidthPattern * g_Player[i].animeHeightPattern;

			D3DXVECTOR2 uv = SetAnimation(g_AnimeBasePattern, g_AnimePattern, PLAYER_WIDTH_PATTERN, PLAYER_HEIGHT_PATTERN, g_Player[i].animeWidthPattern, g_Reverse);
			
			g_U = uv.x;
			g_V = uv.y;
			
			g_AnimeSkipFrame = Counter(g_AnimeSkipFrame, PLAYER_FRAME_SPAN);

			if (g_AnimeSkipFrame == 0)
			{
				g_AnimePattern = Counter(g_AnimePattern, g_Player[i].animeFrameMax);
			}

			DrawSpriteColorRotateCamera(g_TexNo,
				(int)g_Player[i].pos.x,
				(int)g_Player[i].pos.y,
				g_Player[i].size.x, g_Player[i].size.y,	//幅、高さ
				g_U, g_V,		//中心UV座標
				g_UW, g_VH,		//テクスチャ幅、高さ
				g_Player[i].color.r, g_Player[i].color.g, g_Player[i].color.b, g_Player[i].color.a,
				0.0f
			);
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitPlayer(void)
{
	delete[] p_Tile;
}

//---------------------------------------------------
// プレイヤー取得処理
//---------------------------------------------------
PLAYER* GetPlayer()
{
	return &g_Player[0];
}

//---------------------------------------------------
// ノックバック設定 [引数]index: 配列番号
//---------------------------------------------------
void SetPlayerKnockBack(float power, float radian)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use)
		{
			// ラジアンを度に変換
			double degrees = radian * 180.0f / 3.14159f;

			//上にのみ跳ぶようにする(上半円が右を0°とし0～-180、下半円が左を180°とし180～0)
			if (abs(degrees) < 90.0f) degrees = 45;
			if (abs(degrees) > 90.0f) degrees = 135;

			float radianA = degrees * 3.14159f / 180.0f;

			D3DXVECTOR2 vector = CalculateVector(-power, radianA);

			if (g_Player[i].use)
			{
				g_Player[i].knockBackX = vector.x;
				g_Player[i].knockBackY = vector.y;
			}
		}
	}
}

//---------------------------------------------------
// 反動を設定
//---------------------------------------------------
void SetPlayerGunKick(float power, float radian)
{
	D3DXVECTOR2 vector = CalculateVector(-power, radian);

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use)
		{
			g_Player[i].knockBackX = vector.x;
			g_Player[i].knockBackY = vector.y;
		}
	}
}

//---------------------------------------------------
// プレイヤーを配置
//---------------------------------------------------
void SetPlayer(float posX, float posY)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (!g_Player[i].use)
		{
			g_Player[i].pos.x = posX;
			g_Player[i].pos.y = posY;
			g_Player[i].notLoopPos.x = posX;
			g_Player[i].notLoopPos.y = posY;
			g_Player[i].vel.x = PLAYER_SPEED;
			g_Player[i].vel.y = PLAYER_SPEED;
			//ベクトルの正規化
			D3DXVec2Normalize(&g_Player[i].vel, &g_Player[i].vel);
			g_Player[i].vel *= PLAYER_SPEED;//目的のスピードにするためにスピードを乗算する
			g_Player[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Player[i].hsp = 0;
			g_Player[i].vsp = 0;
			g_Player[i].grv = 0.3f;
			g_Player[i].walksp = PLAYER_SPEED;
			g_Player[i].controller = true;
			g_Player[i].hascontrol = false;
			g_Player[i].canjump = 0;
			g_Player[i].knockBackX = 0;
			g_Player[i].knockBackY = 0;
			g_Player[i].ground = false;
			g_Player[i].state = STATE_IDLE;
			g_Player[i].oldState = STATE_IDLE;
			g_Player[i].animeWidthPattern = 1;
			g_Player[i].animeHeightPattern = 1;
			g_Player[i].animeFrameMax = 0;
			g_Player[i].size = D3DXVECTOR2(PLAYER_WIDTH, PLAYER_HEIGHT);
			g_Player[i].hp = PLAYER_INIT_HP;
			g_Player[i].oldHp = PLAYER_INIT_HP;
			g_Player[i].unbeatable = false;
			g_Player[i].unbeatableCou = 0;
			g_Player[i].unbeatableTime = PLAYER_UNBEATABLE_TEME;
			g_Player[i].score = 0;
			g_Player[i].coin = 0;

			g_Player[i].use = true;
		}
	}
}

//---------------------------------------------------
// スコアを設定
//---------------------------------------------------
void SetPlayerScore(int add)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_Player[i].score += add;
	}
}