#include "Stage.h"
#include "Player.h"
#include "Enemy.h"

namespace
{
	const int ENEMY_NUM = 10 * 7; // 敵の数
	const int ENEMY_COL_SIZE = 10; // 敵の列数
	const int ENEMY_ROW_SIZE = 7; // 敵の行数
}

Stage::Stage()
	:GameObject(), player_(nullptr)
{
	AddGameObject(this); // ステージオブジェクトのをゲームオブジェクト
	player_ = new Player(); // プレイヤーオブジェクトの生成
	enemy_ = std::vector<Enemy*>(ENEMY_NUM); // 敵オブジェクトの生成
	for (int i = 0; i < ENEMY_NUM; i++) {
		int col = i % ENEMY_COL_SIZE; // 列
		int row = i / ENEMY_COL_SIZE; // 行
		ETYPE enemyType[ENEMY_ROW_SIZE] = { BOSS, KNIGHT, MID, ZAKO, ZAKO, ZAKO, ZAKO }; // 敵の種類
		enemy_[i] = new Enemy(i, enemyType[row]); // 敵オブジェクトの生成

		enemy_[i]->SetPos(col * 55, row * 50); // 敵の初期位置を設定

	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
	player_->Update(); // プレイヤーの更新
	for (auto& elm : enemy_) {
		elm->Update(); // 敵の更新
	}
}

void Stage::Draw()
{
	player_->Draw(); // プレイヤーの描画
	for (auto& elm : enemy_) {
		elm->Draw(); // 敵の描画
	}
}