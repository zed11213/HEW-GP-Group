//===================================================
//�A�C�R��(icon.h)
//Auhor:�n� �C	Date:2023.9.11
//===================================================
#pragma once

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define ICON_MAX					(100)
#define ICON_WIDTH					(80)//�摜����
#define ICON_HEIGHT					(80)//�摜�c����
#define ICON_MAP_WIDTH				(40)//�z�u�w��Ԋu��
#define ICON_MAP_HEIGHT				(40)//�z�u�w��Ԋu����
#define ICON_WIDTH_PATTERN			(2)
#define ICON_HEIGHT_PATTERN			(3)
#define ICON_FRAME_MAX				(ICON_WIDTH_PATTERN * ICON_HEIGHT_PATTERN)//�����̑S���
#define ICON_FANFARE_ICON			(200)
#define ICON_INIT_ICON				(0)
#define ICON_SCREEN_SIZE_X			(49)
#define ICON_SCREEN_SIZE_Y			(27)

//---------------------------------------------------
// �񋓑̐錾
//---------------------------------------------------
enum ICON_ATTRIB
{
	ICON_NONE = 0,
	ICON_HEART,	//�n�[�g
	ICON_COIN //�R�C��
};

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct ICON_DATA
{
	ICON_ATTRIB attrib;
	int animeBasePattern;
	int animeWidthPattern;
	int animeHeightPattern;
	int animeFrameMax;
};

struct ICON {
	ICON_DATA iconData;
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
};
//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitIcon();
void UninitIcon();
void UpdateIcon();
void DrawIcon();
void SetIconData(ICON_DATA data, std::string name, float posX, float posY, bool anime);
void ChangeIcon(std::string name, ICON_DATA iconData, bool anime);
float GetIconU(int index);
float GetIconV(int index);
D3DXVECTOR2 GetIconUV(int index);


