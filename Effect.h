#pragma once
#include "GameObject.h"
#include "Globals.h"

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
    int hImage_;
    Point pos_;
    float animeTimer_;
};

//�G�ƓG�̂Ԃ������ꏊ�ɔ�������3�b�ŏ�����

