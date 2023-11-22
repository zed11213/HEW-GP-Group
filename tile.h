//===================================================
//�^�C��(tile.h)
//Auhor:�n� �C	Date:2023.8.26
//===================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAPCHIP_SIZE (DEFAULT_TILE_SIZE) //�}�b�v�`�b�v�T�C�Y
#define MAP_SIZE_X (64) //1�}�b�v(1���)��12�L�����N�^�[
#define MAP_SIZE_Y (14) //1�}�b�v(1���)�c7�L�����N�^�[
#define MAP_WIDTH_PATTERN (5)
#define MAP_HEIGHT_PATTERN (3)
#define MAP_FRAME_MAX (MAP_WIDTH_PATTERN * MAP_HEIGHT_PATTERN)//�t���[����
#define MAP_SPAWN_TIME (15)	//�G�o���Ԋu
#define STAGE_SIZE  (MAP_SIZE_X * MAPCHIP_SIZE)

//*****************************************************************************
// �񋓑̐錾
//*****************************************************************************
enum MAPATTRIB //�}�b�v�̃A�g���r���[�g(����)
{
	MAP_ATTRIB_NONE = 0,	//�ʉ߉\
	MAP_ATTRIB_STOP,		//�i���s��
	MAP_ATTRIB_SLOW,		//���x�ቺ
};

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
struct MAP_DATA_T //�^�C����ނ��Ƃ̃f�[�^
{
	D3DXVECTOR2 uv;		//�e�N�X�`���̍�����W
	MAPATTRIB attrib;	//���̃}�b�v�`�b�v��������
};

struct TILE_DATA //�^�C�����Ƃ̃f�[�^
{
	D3DXVECTOR2 pos;	//���S���W
	MAPATTRIB attrib;	//���̃}�b�v�`�b�v��������
	bool spawn;			//�G�����̃u���b�N�ʒu�ɗN�����ǂ���
};

struct POLYGON 
{
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2		vel;	//���x�x�N�g��
	D3DXCOLOR		color;	//���_�J���[
};

struct DIRECTION
{
	bool right;
	bool down;
	bool up;
	bool left;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTile(void);
void UninitTile(void);
void UpdateTile(void);
void DrawTile(void);
float GetTileU(int index);
float GetTileV(int index);
D3DXVECTOR2 GetTileUV(int index);
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos);//���W�����̃}�b�v����Ԃ�
DIRECTION TileHit(D3DXVECTOR2 pos, float hsp, float vsp, float hitBoxWidth, float hitBoxHeight);
