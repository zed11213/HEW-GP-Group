//===================================================
//�~�j�}�b�v�\��	(minimap.h)
//Author:���q �V		Date:2023/12/15
//===================================================
#pragma once

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define MINIMAP_MAX					(100)
#define MINIMAP_WIDTH				(80)//�摜����
#define MINIMAP_HEIGHT				(80)//�摜�c����
#define MINIMAP_MAP_WIDTH			(40)//�z�u�w��Ԋu��
#define MINIMAP_MAP_HEIGHT			(40)//�z�u�w��Ԋu����
#define MINIMAP_WIDTH_PATTERN		(2)
#define MINIMAP_HEIGHT_PATTERN		(3)
#define MINIMAP_FRAME_MAX			(10)//�����̑S���
#define MINIMAP_SCREEN_SIZE_X		(49)
#define MINIMAP_SCREEN_SIZE_Y		(27)

//---------------------------------------------------
// �񋓑̐錾
//---------------------------------------------------
enum MINIMAP_ATTRIB
{
	MINIMAP_NONE = 0,
	MINIMAP_ADLE,
	MINIMAP_TURN_RIGHT,
	MINIMAP_TURN_LEFT
};

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct MINIMAP_DATA
{
	MINIMAP_ATTRIB attrib;
	int animeBasePattern;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeFrameMax;
	int texture;
};

struct MINIMAP {
	MINIMAP_DATA minimapData;
	std::string name;
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXCOLOR color;	//���_�J���[
	bool use;			//�g�p���t���O
	D3DXVECTOR2 size;	//�T�C�Y

	int animePattern;
	int animeSkipFrame;
	int anumeFrameSpan;
	bool anime;
	float scale;
	int texture;
};
//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitMinimap(void);
void UninitMinimap(void);
void UpdateMinimap(void);
void DrawMinimap(void);
void SetMinimapData(MINIMAP_DATA data, std::string name, int texture, float posX, float posY, float sizeX = MINIMAP_WIDTH, float sizeY = MINIMAP_HEIGHT, bool anime = false, int frameSpan = 60);
void ChangeMinimap(std::string name, MINIMAP_DATA iconData, bool anime, int frameSpan = 60);
float GetMinimapU(int index);
float GetMinimapV(int index);
D3DXVECTOR2 GetMinimapUV(int index);





