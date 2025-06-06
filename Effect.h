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

//“G‚Æ“G‚Ì‚Ô‚Â‚©‚Á‚½êŠ‚É”­¶‚µ‚Ä3•b‚ÅÁ‚¦‚é

