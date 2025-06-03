#pragma once
#include "GameObject.h"
#include "Globals.h"


class Bullet :
	public GameObject
{
public:
	Bullet();
	Bullet(float x, float y);
	~Bullet();
	void Update() override;
	void Draw() override;

	void SetPos(float x, float y);
	void SetFired(bool fired) { isFired_ = fired; } // 発射状態を設定
	bool IsFired() const { return isFired_; } // 発射状態を取得
	Rect GetRect() const { return { x_,y_,imageSize_.x, imageSize_.y }; } // 弾の矩形を取得
protected:
private:
	int hImage_;  //弾の画像ハンドル
	float x_, y_; //弾の座標
	float speed_; //弾の移動速度
	Point imageSize_;
	//int isize_x, isize_y; //弾の表示サイズ
	bool isFired_; //発射されているかどうか ture: 発射されている false: 発射されていない
};