//===================================================
//DirectWrite(directWrite.cpp)
//Auhor:�n� �C	Date:2023.11.5
// �Q�l�� https://islingtonsystem.hatenablog.jp/entry/2022/06/18/222040
//===================================================
#include "directWrite.h"
#include "renderer.h"	// Renderer

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------


//---------------------------------------------------
//������
//---------------------------------------------------
void DirectWrite::Init(void)
{
	// Direct2D,DirectWrite�̏�����
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	// �o�b�N�o�b�t�@�̎擾
	// �^�FIDXGISwapChain
	GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

	// dpi�̐ݒ�
	FLOAT dpiX;
	FLOAT dpiY;
	pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

	// �����_�[�^�[�Q�b�g�̍쐬
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	// �T�[�t�F�X�ɕ`�悷�郌���_�[�^�[�Q�b�g���쐬
	pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &props, &pRT);

	// �A���`�G�C���A�V���O���[�h
	pRT->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	// IDWriteFactory�̍쐬
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));

	//�֐�CreateTextFormat()
	//��1�����F�t�H���g���iL"���C���I", L"Arial", L"Meiryo UI"���j
	//��2�����F�t�H���g�R���N�V�����inullptr�j
	//��3�����F�t�H���g�̑����iDWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD���j
	//��4�����F�t�H���g�X�^�C���iDWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC�j
	//��5�����F�t�H���g�̕��iDWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED���j
	//��6�����F�t�H���g�T�C�Y�i20, 30���j
	//��7�����F���P�[�����iL""�j
	//��8�����F�e�L�X�g�t�H�[�}�b�g�i&g_pTextFormat�j
	pDWriteFactory->CreateTextFormat(FontList[(int)Setting->font],
		Setting->fontCollection,
		Setting->fontWeight,
		Setting->fontStyle,
		Setting->fontStretch,
		Setting->fontSize,
		Setting->localeName,
		&pTextFormat);

	//�֐�SetTextAlignment()
	//��1�����F�e�L�X�g�̔z�u�iDWRITE_TEXT_ALIGNMENT_LEADING�F�O, DWRITE_TEXT_ALIGNMENT_TRAILING�F��, DWRITE_TEXT_ALIGNMENT_CENTER�F����,
	//                         DWRITE_TEXT_ALIGNMENT_JUSTIFIED�F�s�����ς��j
	pTextFormat->SetTextAlignment(Setting->textAlignment);

	//�֐�CreateSolidColorBrush()
	//��1�����F�t�H���g�F�iD2D1::ColorF(D2D1::ColorF::Black)�F��, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))�FRGBA�w��j
	pRT->CreateSolidColorBrush(Setting->Color, &pSolidBrush);
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void DirectWrite::Release(void)
{
	// �����`��֘A�̃A�����[�h
	if (pBackBuffer) pBackBuffer->Release();
	if (pSolidBrush) pSolidBrush->Release();
	if (pRT) pRT->Release();
	if (pTextFormat) pTextFormat->Release();
	if (pDWriteFactory) pDWriteFactory->Release();
	if (pD2DFactory) pD2DFactory->Release();
	if (pTextLayout) pTextLayout->Release();
}

//=============================================================================
//     string��wstring�֕ϊ�����
//=============================================================================
std::wstring DirectWrite::StringToWString(std::string oString)
{
	// SJIS �� wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, (wchar_t*)NULL, 0);

	// �o�b�t�@�̎擾
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	// SJIS �� wstring
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2, iBufferSize);

	// string�̐���
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	// �o�b�t�@�̔j��
	delete[] cpUCS2;

	// �ϊ����ʂ�Ԃ�
	return(oRet);
}

//=================================================================================================================================
// ��1�����F�t�H���g���iL"���C���I", L"Arial", L"Meiryo UI"���j
// ��2�����F�t�H���g�R���N�V�����inullptr�j
// ��3�����F�t�H���g�̑����iDWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD���j
// ��4�����F�t�H���g�X�^�C���iDWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC�j
// ��5�����F�t�H���g�̕��iDWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED���j
// ��6�����F�t�H���g�T�C�Y�i20, 30���j
// ��7�����F���P�[�����iL"ja-jp"���j
// ��8�����F�e�L�X�g�̔z�u�iDWRITE_TEXT_ALIGNMENT_LEADING�F�O, ���j
// ��9�����F�t�H���g�̐F�iD2D1::ColorF(D2D1::ColorF::Black)�F��, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))�FRGBA�w�蓙�j
//=================================================================================================================================
DirectWrite::DirectWrite(Font font, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle,
	DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName, DWRITE_TEXT_ALIGNMENT textAlignment,
	D2D1_COLOR_F Color)
{
	Setting->font = font;
	Setting->fontCollection = fontCollection;
	Setting->fontWeight = fontWeight;
	Setting->fontStyle = fontStyle;
	Setting->fontStretch = fontStretch;
	Setting->fontSize = fontSize;
	Setting->localeName = localeName;
	Setting->textAlignment = textAlignment;
	Setting->Color = Color;
}

//=============================================================================
// �t�H���g�ݒ�
// ��1�����F�t�H���g�f�[�^�i�|�C���^�j
//=============================================================================
void DirectWrite::SetFont(FontData* set)
{
	pDWriteFactory->CreateTextFormat(FontList[(int)set->font], set->fontCollection, set->fontWeight, set->fontStyle, set->fontStretch, set->fontSize, set->localeName, &pTextFormat);
	pTextFormat->SetTextAlignment(set->textAlignment);
	pRT->CreateSolidColorBrush(set->Color, &pSolidBrush);
}

//=================================================================================================================================
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
//=================================================================================================================================
void DirectWrite::SetFont(Font font, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight,
	DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName,
	DWRITE_TEXT_ALIGNMENT textAlignment, D2D1_COLOR_F Color)
{
	pDWriteFactory->CreateTextFormat(FontList[(int)font], fontCollection, fontWeight, fontStyle, fontStretch, fontSize, localeName, &pTextFormat);
	pTextFormat->SetTextAlignment(textAlignment);
	pRT->CreateSolidColorBrush(Color, &pSolidBrush);
}

//=============================================================================
// �����`��
// string�F������
// pos�F�`��|�W�V����
// rect�F�̈�w��
// options�F�e�L�X�g�̐��`
//=============================================================================
void DirectWrite::DrawString(std::string str, D3DXVECTOR2 pos, D2D1_DRAW_TEXT_OPTIONS options)
{
	// ������̕ϊ�
	std::wstring wstr = StringToWString(str.c_str());

	// �^�[�Q�b�g�T�C�Y�̎擾
	D2D1_SIZE_F TargetSize = pRT->GetSize();

	// �e�L�X�g���C�A�E�g���쐬
	pDWriteFactory->CreateTextLayout(wstr.c_str(), wstr.size(), pTextFormat, TargetSize.width, TargetSize.height, &pTextLayout);

	// �`��ʒu�̊m��
	D2D1_POINT_2F pounts;
	pounts.x = pos.x;
	pounts.y = pos.y;

	// �`��̊J�n
	pRT->BeginDraw();

	// �`�揈��
	pRT->DrawTextLayout(pounts, pTextLayout, pSolidBrush, options);

	// �`��̏I��
	pRT->EndDraw();
}

//=============================================================================
// �����`��
// string�F������
// pos�F�`��|�W�V����
// rect�F�̈�w��
// options�F�e�L�X�g�̐��`
//=============================================================================
void DirectWrite::DrawString(std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options)
{
	// ������̕ϊ�
	std::wstring wstr = StringToWString(str.c_str());

	// �`��̊J�n
	pRT->BeginDraw();

	// �`�揈��
	pRT->DrawText(wstr.c_str(), wstr.size(), pTextFormat, rect, pSolidBrush, options);

	// �`��̏I��
	pRT->EndDraw();
}