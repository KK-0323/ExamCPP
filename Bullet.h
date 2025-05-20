#pragma once
#include "GameObject.h"


class Bullet :
    public GameObject
{
private:
    int hImage_;    //弾の画像バンドル
    float x_, y_;   //弾の座標
    float speed_;   //弾の移動速度
    bool isAlive_;  //弾が生きているか
    int isize_x, isize_y;   //弾の表示サイズ
public:
    Bullet();
    Bullet(float x, float y);
    ~Bullet();
    void Update() override;
    void Draw() override;

    void SetPos(float x, float y);
};

