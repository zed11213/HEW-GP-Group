//===================================================
//DirectWrite(directWrite.h)
//Auhor:�n� �C	Date:2023.11.5
// �Q�l�� https://islingtonsystem.hatenablog.jp/entry/2022/06/18/222040
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------
enum class Font
{
	Meiryo,
	Arial,
	MeiryoUI
};

//---------------------------------------------------
//���O���
//---------------------------------------------------
namespace
{
	const WCHAR* FontList[]
	{
		L"���C���I",
		L"Arial",
		L"Meiryo UI"
	};
}

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct FontData
{
	Font font;								// �t�H���g��
	IDWriteFontCollection* fontCollection;	// �t�H���g�R���N�V����
	DWRITE_FONT_WEIGHT fontWeight;			// �t�H���g�̑���
	DWRITE_FONT_STYLE fontStyle;			// �t�H���g�X�^�C��
	DWRITE_FONT_STRETCH fontStretch;		// �t�H���g�̕�
	FLOAT fontSize;							// �t�H���g�T�C�Y
	WCHAR const* localeName;				// ���P�[����
	DWRITE_TEXT_ALIGNMENT textAlignment;	// �e�L�X�g�̔z�u
	D2D1_COLOR_F Color;						// �t�H���g�̐F

	// �f�t�H���g�ݒ�
	FontData()
	{
		font = Font::Meiryo;
		fontCollection = nullptr;
		fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL;
		fontStyle = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;
		fontStretch = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;
		fontSize = 20;
		localeName = L"ja-jp";
		textAlignment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;
		Color = D2D1::ColorF(D2D1::ColorF::White);
	}
};


class DirectWrite
{
private:
	ID2D1Factory* pD2DFactory = NULL;
	IDWriteFactory* pDWriteFactory = NULL;
	IDWriteTextFormat* pTextFormat = NULL;
	IDWriteTextLayout* pTextLayout = NULL;
	ID2D1RenderTarget* pRT = NULL;
	ID2D1SolidColorBrush* pSolidBrush = NULL;
	IDXGISurface* pBackBuffer = NULL;

	// �t�H���g�f�[�^
	FontData* Setting = new FontData();

	// string��wstring�֕ϊ�����
	std::wstring StringToWString(std::string oString);

public:
	// �f�t�H���g�R���X�g���N�^�𐧌�
	DirectWrite() = delete;

	// �R���X�g���N�^
	// ��1�����F�t�H���g�ݒ�
	DirectWrite(FontData* set) :Setting(set) {};

	// �R���X�g���N�^
	// ��1�����F�t�H���g���iL"���C���I", L"Arial", L"Meiryo UI"���j
	// ��2�����F�t�H���g�R���N�V�����inullptr�j
	// ��3�����F�t�H���g�̑����iDWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD���j
	// ��4�����F�t�H���g�X�^�C���iDWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC�j
	// ��5�����F�t�H���g�̕��iDWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED���j
	// ��6�����F�t�H���g�T�C�Y�i20, 30���j
	// ��7�����F���P�[�����iL"ja-jp"���j
	// ��8�����F�e�L�X�g�̔z�u�iDWRITE_TEXT_ALIGNMENT_LEADING�F�O, ���j
	// ��9�����F�t�H���g�̐F�iD2D1::ColorF(D2D1::ColorF::Black)�F��, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))�FRGBA�w�蓙�j
	DirectWrite(Font font,					// �t�H���g��
		IDWriteFontCollection* fontCollection,	// �t�H���g�R���N�V����
		DWRITE_FONT_WEIGHT fontWeight,		// �t�H���g�̑���
		DWRITE_FONT_STYLE fontStyle,		// �t�H���g�X�^�C��
		DWRITE_FONT_STRETCH fontStretch,		// �t�H���g�̕�
		FLOAT fontSize,				// �t�H���g�T�C�Y
		WCHAR const* localeName,			// ���P�[����
		DWRITE_TEXT_ALIGNMENT textAlignment,	// �e�L�X�g�̔z�u
		D2D1_COLOR_F Color				// �t�H���g�̐F
	);

	// �t�H���g�ݒ�
	// ��1�����F�t�H���g�f�[�^�\����
	void SetFont(FontData* set);

	// �t�H���g�ݒ�
	// ��1�����F�t�H���g���iL"���C���I", L"Arial", L"Meiryo UI"���j
	// ��2�����F�t�H���g�R���N�V�����inullptr�j
	// ��3�����F�t�H���g�̑����iDWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD���j
	// ��4�����F�t�H���g�X�^�C���iDWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC�j
	// ��5�����F�t�H���g�̕��iDWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED���j
	// ��6�����F�t�H���g�T�C�Y�i20, 30���j
	// ��7�����F���P�[�����iL"ja-jp"���j
	// ��8�����F�e�L�X�g�̔z�u�iDWRITE_TEXT_ALIGNMENT_LEADING�F�O, ���j
	// ��9�����F�t�H���g�̐F�iD2D1::ColorF(D2D1::ColorF::Black)�F��, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))�FRGBA�w�蓙�j
	void SetFont(Font font,						// �t�H���g��
		IDWriteFontCollection* fontCollection,		// �t�H���g�R���N�V����
		DWRITE_FONT_WEIGHT fontWeight,			// �t�H���g�̑���
		DWRITE_FONT_STYLE fontStyle,			// �t�H���g�X�^�C��
		DWRITE_FONT_STRETCH fontStretch,			// �t�H���g�̕�
		FLOAT fontSize,					// �t�H���g�T�C�Y
		WCHAR const* localeName,				// ���P�[����
		DWRITE_TEXT_ALIGNMENT textAlignment,		// �e�L�X�g�̔z�u
		D2D1_COLOR_F Color);				// �t�H���g�̐F

	// �����`��
	// string�F������
	// pos�F�`��|�W�V����
	// options�F�e�L�X�g�̐��`
	void DrawString(std::string str, D3DXVECTOR2 pos, D2D1_DRAW_TEXT_OPTIONS options);

	// �����`��
	// string�F������
	// rect�F�̈�w��
	// options�F�e�L�X�g�̐��`
	void DrawString(std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options);

	// ������
	void Init();

	// �I������
	void Release();
};

