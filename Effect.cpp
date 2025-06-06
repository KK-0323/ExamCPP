#include <DxLib.h>
#include "Effect.h"

namespace {
	const float ANIME_TIME = { 3.0f };
	const int EFFECT_IMAGE_SIZE = { 48 };
}

Effect::Effect(Point _pos)
	:GameObject(),pos_(-10,-10), hImage_(-1),animeTimer_(ANIME_TIME)
{
	hImage_ = LoadGraph("Assets\\explosion.png");
	AddGameObject(this);
}

Effect::~Effect()
{
	DeleteGraph(hImage_);
}

void Effect::Update()
{
	float dt = GetDeltaTime();
	animeTimer_ = animeTimer_ - dt;
	if (animeTimer_ < 0)
	{
		this->isAlive_ = false;
	}
}

void Effect::Draw()
{
	DrawExtendGraphF(pos_.x, pos_.y, EFFECT_IMAGE_SIZE, EFFECT_IMAGE_SIZE, hImage_, TRUE);
}
