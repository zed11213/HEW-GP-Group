#include "Idle.h"
#include"..\FsmBase.h"
#include "..\..\tile.h"
#include "..\..\collision.h"


void Idle::Init()
{
	_stateId = StateID::Idle;
}

void Idle::EnterState(FSMBase* fsm)
{
	fsm->_target->_move = -1;
	fsm->_target->_animeFrameMax =4;
	fsm->_target->_animeBasePattern =12;
	fsm->_target->_animeWidthPattern = 4;
	fsm->_target->_walksp = 1.0f;
	if (fsm->_target->_move < 0)
	{
		fsm->_target->_reverse = true;
	}
	else
	{
		fsm->_target->_reverse = false;
	}
}

void Idle::StayState(FSMBase* fsm)
{
	if (fsm->_target->_knockBackX != 0)
	{
		if (fsm->_target->_knockBackX > 0) fsm->_target->_knockBackX -= 1.0f;
		if (fsm->_target->_knockBackX < 0) fsm->_target->_knockBackX += 1.0f;
	}

	//移動方向と速度
	fsm->_target->_hsp = (fsm->_target->_move * fsm->_target->_walksp) + fsm->_target->_knockBackX;

	//重力
	fsm->_target->_vsp = (fsm->_target->_vsp + fsm->_target->_grv) + fsm->_target->_knockBackY;

	//ジャンプ
	fsm->_target->_canjump -= 1;
	if (((fsm->_target->_canjump > 0) && fsm->_target->_jump) || fsm->_target->_grv == 0)
	{
		fsm->_target->_vsp = fsm->_target->_jumpPower;
		fsm->_target->_canjump = 0;
	}

	//壁の衝突判定
	fsm->_target->_Tile = GetMapInfo(fsm->_target->_pos);

	for (int j = 0; j < 9; j++)
	{
		if (fsm->_target->_Tile[j].attrib == MAP_ATTRIB_STOP)
		{
			//横に壁がある場合
			if (CollisionRot(fsm->_target->_pos.x + fsm->_target->_hsp, fsm->_target->_pos.y, fsm->_target->_Tile[j].pos.x, fsm->_target->_Tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				//壁に当たるまで１ピクセル壁に近づける
				while (!CollisionRot(fsm->_target->_pos.x + Sign(fsm->_target->_hsp), fsm->_target->_pos.y, fsm->_target->_Tile[j].pos.x, fsm->_target->_Tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
				{
					fsm->_target->_pos.x = fsm->_target->_pos.x + Sign(fsm->_target->_hsp);
				}
				fsm->_target->_hsp = 0;
			}

			//縦に壁がある場合
			if (CollisionRot(fsm->_target->_pos.x, fsm->_target->_pos.y + fsm->_target->_vsp, fsm->_target->_Tile[j].pos.x, fsm->_target->_Tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				//壁に当たるまで１ピクセル壁に近づける
				while (!CollisionRot(fsm->_target->_pos.x, fsm->_target->_pos.y + Sign(fsm->_target->_vsp), fsm->_target->_Tile[j].pos.x, fsm->_target->_Tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
				{
					fsm->_target->_pos.y = fsm->_target->_pos.y + Sign(fsm->_target->_vsp);
				}
				fsm->_target->_vsp = 0;
			}

			if (j == 7)
			{
				if (fsm->_target->_Tile[6].attrib == MAP_ATTRIB_NONE)
				{
					fsm->_target->_move = 1;
					fsm->_target->_reverse =false;
				}
				if (fsm->_target->_Tile[8].attrib == MAP_ATTRIB_NONE)
				{
					fsm->_target->_move = -1;
					fsm->_target->_reverse = true;
				}
			}
		}
	}

	//横移動
	fsm->_target->_pos.x += fsm->_target->_hsp;

	// ステージループ処理
	if (fsm->_target->_pos.x > STAGE_SIZE)
	{
		fsm->_target->_pos.x -= STAGE_SIZE;
	}
	else if (fsm->_target->_pos.x < 0)
	{
		fsm->_target->_pos.x += STAGE_SIZE;
	}
	//縦移動
	fsm->_target->_pos.y += fsm->_target->_vsp;

	if (fsm->_target->_vsp != 0)fsm->_target->_vsp -= fsm->_target->_knockBackY;
	fsm->_target->_knockBackY *= 0.5f;
	if (fsm->_target->_knockBackY < 0.9f)fsm->_target->_knockBackY = 0;
	fsm->_target->_Tile = GetMapInfo(fsm->_target->_pos);
	//下が地面の場合
	for (int j = 0; j < 9; j++)
	{
		if ((fsm->_target->_Tile[j].attrib == MAP_ATTRIB_STOP) && (j == 6 || j == 7 || j == 8))
		{
			//地面に触れているかの処理
			if (CollisionRot(fsm->_target->_pos.x, fsm->_target->_pos.y + 1, fsm->_target->_Tile[j].pos.x, fsm->_target->_Tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				fsm->_target->_ground = true;
				if (fsm->_target->_oldGround != fsm->_target->_ground)
				{
					//sound

				}
				break;
			}
			else
			{
				fsm->_target->_ground = false;
			}

		}
	}
}

void Idle::ExitState(FSMBase* fsm)
{
}
