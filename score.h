//===================================================
//スコア(score.h)
//Auhor:渡邉 修	Date:2023.9.13
//===================================================
#pragma once

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define SCORE_MAX		(30)
#define SCORE_FIGURE	(6)
#define RANK_FIGURE		(1)
#define WAVE_UP_SCORE	(100)
#define SCORE_INIT_SCORE (0)

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitScore();
void UninitScore();
void UpdateScore();
void DrawScore();

void AddScore(int Score);

bool SaveScore();
bool LoadScore();
void SortScore();
void SetDrawScore(int score, float posX, float posY, float sizeX, float sizeY, float scale);
void SetDrawRank(int score, float posX, float posY, float sizeX, float sizeY);
int GetScore();
float EaseInOut(float t);
void SetScore(int Score);
int GetWave();
void SetWave(int wave);