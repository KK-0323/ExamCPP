#pragma once
#include "GameObject.h"
#include <vector>

class Player; // 前方宣言
class Enemy; // 前方宣言
class Effect; // 前方宣言

class Stage :
	public GameObject
{
private:
	Player* player_; // プレイヤーオブジェクト
	std::vector<Enemy*> enemy_; // 敵オブジェクト
	int hBackground;

	bool playerIsDead_;		// プレイヤーが死亡したかどうか
	bool effectsFinished_;	// プレイヤーが死亡時のエフェクトが終了したかどうか
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	Player* GetPlayer() const { return player_; }

	// ゲームオーバーに移行する準備ができてるかの関数
	bool IsGameOverReady() const { return playerIsDead_ && effectsFinished_; }
};