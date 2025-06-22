#pragma once
#include "GameObject.h"
#include "globals.h"

class SceneManager; // ‘O•ûéŒ¾

class GameOverScene : public GameObject
{
public:
    GameOverScene(SceneManager* manager);
    ~GameOverScene() = default;
    void Update() override;
    void Draw() override;
protected:
private:
    SceneManager* sceneManager_;
    int hBackground;
    float timer_;
};