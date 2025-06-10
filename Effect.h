#pragma once
#include "GameObject.h"
#include "Globals.h"
#include <vector>

class Effect :
    public GameObject
{
public:
    Effect(Point _pos);
    ~Effect();
    void Update() override;
    void Draw() override;
protected:
private:
    std::vector<int>hImage_;
    Point pos_;
    float animeTimer_; // エフェクトの寿命
    float frameTimer_; // アニメのコマのタイマー
    int frame_; // フレーム番号
};

//敵と敵のぶつかった場所に発生して3秒で消える

