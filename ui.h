//===================================================
//ui(ui.h)
//Auhor:�n� �C	Date:2023.9.11
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
class UI {
	//ICON_DATA iconData;
	//std::string name;
public:
	bool use;			//�g�p���t���O

	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXCOLOR color;	//���_�J���[
	D3DXVECTOR2 size;	//�T�C�Y

	float _U = 0;
	float _V = 0;
	bool _reverse = false;
	int _animState = 0;
	int _animPattern = 0;
	int _basePattern = 0;

	int _animSkipFrame = 0;
	//int anumeFrameSpan;
	bool anime;
	float scale;
	int texture;

public:
	void ChangeAnimState(int changeTo);
	void AnimFold();
};


//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);





