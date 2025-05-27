#pragma once
#include "GameObject.h"

class Bullet; //前方宣言

class Player :
    public GameObject
{
    int hImage_;    //プレイヤーの画像のハンドル
    float x_, y_;   //プレイヤーの座標
    float speed_;   //プレイヤーの移動速度
    std::vector<Bullet*> bullets_; // プレイヤーが発射した弾のベクター
public:
    Player();
    ~Player();
    void Update() override;
    void Draw() override;
};

