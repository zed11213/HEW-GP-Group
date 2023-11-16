//===================================================
//����(textDW.cpp)
//Auhor:�n� �C	Date:2023.11.1
//===================================================
#include "textDW.h"
#include "directWrite.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
DirectWrite *Write;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitTextDW(void)
{
	//�t�H���g�f�[�^�錾
	FontData* data = new FontData();

	//�t�H���g�f�[�^����
	data->fontSize = 60;
	data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;

	//DirectWrite�p�R���|�[�l���g���쐬
	Write = new DirectWrite(data);

	Write->Init();
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateTextDW(void)
{

}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawTextDW(void)
{
	//Write->DrawString("https://islingtonsystem.hatenablog.jp/entry/2022/06/18/222040�̃R�[�h���g�p���Ă��܂�", D2D1::RectF(300, 0, 600, 200), D2D1_DRAW_TEXT_OPTIONS_NONE);
	//Write->DrawString("https://islingtonsystem.hatenablog.jp/entry/2022/06/18/222040�̃R�[�h���g�p���Ă��܂�", D3DXVECTOR2(90, 300), D2D1_DRAW_TEXT_OPTIONS_NONE);
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitTextDW(void)
{
	Write->Release();
}

