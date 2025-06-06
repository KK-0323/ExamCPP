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

//“G‚Æ“G‚Ì‚Ô‚Â‚©‚Á‚½êŠ‚É”­¶‚µ‚Ä3•b‚ÅÁ‚¦‚é

