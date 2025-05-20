#include "Globals.h"
#include "Bullet.h"
#include "DxLib.h"
#include <string>

namespace
{
	const int BULLET_IMAGE_WIDTH = 13; // ’e‚Ì‰æ‘œ‚Ì•
	const int BULLET_IMAGE_HEIGHT = 33; // ’e‚Ì‰æ‘œ‚Ì‚‚³
	const float BULLET_INIT_SPEED = 200.0f; //’e‚Ì‰ŠúˆÚ“®‘¬“x
	const std::string BULLET_IMAGE_PATH = "Assets\\laserBlue03.png"; // ’e‚Ì‰æ‘œƒpƒX
}

Bullet::Bullet()
	:GameObject(), hImage_(-1),
	x_(0),y_(0),speed_(0),
	isAlive_(true),isize_x(BULLET_IMAGE_WIDTH),isize_y(BULLET_IMAGE_HEIGHT)
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str()); // ’e‚Ì‰æ‘œ‚ğ“Ç‚İ‚Ş
	speed_ = BULLET_INIT_SPEED; // ˆÚ“®‘¬“x
	AddGameObject(this);
}

Bullet::Bullet(float x, float y)
	:GameObject(), hImage_(-1),
	x_(x), y_(y), speed_(0),
	isAlive_(true), isize_x(BULLET_IMAGE_WIDTH), isize_y(BULLET_IMAGE_HEIGHT)
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str()); // ’e‚Ì‰æ‘œ‚ğ“Ç‚İ‚Ş
	speed_ = BULLET_INIT_SPEED; // ˆÚ“®‘¬“x
	AddGameObject(this);
}

Bullet::~Bullet()
{
	if (hImage_ != -1) {
		DeleteGraph(hImage_); // ‰æ‘œ‚Ì‰ğ•ú
	}
	hImage_ = -1; // ‰æ‘œƒnƒ“ƒhƒ‹‚ğ–³Œø‰»
}

void Bullet::Update()
{
	float dt = GetDeltaTime();
	y_ = y_ - speed_ * dt; // ’e‚ÌˆÚ“®
	if (y_ < 0) {
		isAlive_ = false; // ‰æ–ÊŠO‚Éo‚½‚ç’e‚ğÁ‚·
	}
}

void Bullet::Draw()
{
	if (isAlive_)
	{
		DrawExtendGraph(x_, y_, x_ + isize_x, y_ + isize_y,
			hImage_, TRUE); // ’e‚Ì•`‰æ
	}
}

void Bullet::SetPos(float x, float y)
{
	x_ = x;
	y_ = y;
}
