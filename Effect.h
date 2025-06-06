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
    float animeTimer_;
    float frameTimer_;
    int frame_;
};

//�G�ƓG�̂Ԃ������ꏊ�ɔ�������3�b�ŏ�����

