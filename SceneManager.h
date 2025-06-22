#pragma once
#include "GameObject.h"

enum class SceneType
{
    TITLE,
    PLAY,
    GAMEOVER
};

class SceneManager :
    public GameObject
{
public:
    SceneManager();
    ~SceneManager();
    void ChangeScene(SceneType type);
    void Update() override;
    void Draw() override;
protected:
private:
    GameObject* currentScene_;
    SceneType currentSceneType_;
};

