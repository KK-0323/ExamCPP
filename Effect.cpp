#include "Effect.h"
#include <DxLib.h>
#include <string>

namespace {
	const float ANIME_TIME = { 1.0f }; //アニメの総時間の初期値
	const int EFFECT_IMAGE_SIZE = 48;//画像サイズ
	const std::string EIMG_PATH = "Assets\\explosion.png";
	const int MAX_FRAME = 9; //画像の分割数
	const int DIV_NUM = 3; //画像の分割数（割り算用）
	const float FRAME_TIME = ANIME_TIME / MAX_FRAME; //1コマの時間の初期値
}
//
//FileName　　　:　分割読み込みする画像ファイル文字列のポインタ
//AllNum　　　　 : 画像の分割総数
//XNum, YNum　　 : 画像の横向きに対する分割数と縦に対する分割数
//SizeX, SizeY　 : 分割された画像一つの大きさ
//HandleBuf　　 : 分割読み込みして得たグラフィックハンドルを
//保存するint型の配列へのポインタ

Effect::Effect(Point _pos)
	:GameObject(), pos_({ _pos.x, _pos.y }),
	animeTimer_(ANIME_TIME), hImage_(std::vector<int>(MAX_FRAME, -1)),
	frameTimer_(FRAME_TIME), frame_(0)
{
	//hImage_ = LoadGraph(EIMG_PATH.c_str());
	LoadDivGraph(EIMG_PATH.c_str(), MAX_FRAME, DIV_NUM, DIV_NUM,
		EFFECT_IMAGE_SIZE, EFFECT_IMAGE_SIZE, hImage_.data());
}

Effect::~Effect()
{
	//DeleteGraph(hImage_);
	for (auto& itr : hImage_)
		DeleteGraph(itr);
	hImage_.clear();
}

void Effect::Update()
{
	float dt = GetDeltaTime();
	animeTimer_ = animeTimer_ - dt;
	if (animeTimer_ < 0)
	{
		this->isAlive_ = false;
	}

	frameTimer_ = frameTimer_ - dt;
	if (frameTimer_ < 0)
	{
		frame_++;//フレームを１増やす
		frameTimer_ = FRAME_TIME - frameTimer_;//リセット
	}
}

void Effect::Draw()
{
	DrawExtendGraphF(pos_.x, pos_.y,
		pos_.x + EFFECT_IMAGE_SIZE, pos_.y + EFFECT_IMAGE_SIZE,
		hImage_[frame_], TRUE);
}