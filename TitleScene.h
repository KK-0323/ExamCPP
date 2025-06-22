#pragma once
#include "GameObject.h"
#include "globals.h"

class SceneManager; // �O���錾

class TitleScene : public GameObject
{
public:
    TitleScene(SceneManager* manager);
    ~TitleScene();
    void Update() override;
    void Draw() override;
protected:
private:
    SceneManager* sceneManager_;
    int hBackground;
};