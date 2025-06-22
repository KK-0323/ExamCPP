#pragma once
#include "GameObject.h"
#include <vector>

class SceneManager; // 前方宣言
class Player;
class Enemy;

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
    Player* player_; // プレイヤーオブジェクト
    std::vector<Enemy*> enemy_; // 敵オブジェクト
    int hBackground;
};

extern std::vector<GameObject*> gameObjects; // ゲームオブジェクトのベクター
extern std::vector<GameObject*> newObjects; // ゲームオブジェクトのベクター
inline void AddGameObject(GameObject* obj)
{
    newObjects.push_back(obj); // ゲームオブジェクトをベクターに追加
}
