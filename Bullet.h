#pragma once
#include "GameObject.h"


class Bullet :
	public GameObject
{
private:
	int hImage_;  //弾の画像ハンドル
	float x_, y_; //弾の座標
	float speed_; //弾の移動速度
	int isize_x, isize_y; //弾の表示サイズ
public:
	Bullet();
	Bullet(float x, float y);
	~Bullet();
	void Update() override;
	void Draw() override;

	void SetPos(float x, float y);
};