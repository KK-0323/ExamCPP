#pragma once
#include "GameObject.h"
#include <vector>

class SceneManager; // �O���錾
class Player;
class Enemy;
class GameObject;

class PlayScene : public GameObject
{
public:
    PlayScene(SceneManager* manager);
    ~PlayScene();
    void Update() override;
    void Draw() override;
protected:
private:
    SceneManager* sceneManager_;
    Player* player_; // �v���C���[�I�u�W�F�N�g
    std::vector<Enemy*> enemy_; // �G�I�u�W�F�N�g
    int hBackground;

    std::vector<GameObject*> gameObjects; // �Q�[���I�u�W�F�N�g�̃x�N�^�[
    std::vector<GameObject*> newObjects; // �Q�[���I�u�W�F�N�g�̃x�N�^�[
    inline void AddGameObject(GameObject* obj)
    {
        newObjects.push_back(obj);
    }

};
