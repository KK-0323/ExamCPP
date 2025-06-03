#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

namespace
{
	const int ENEMY_NUM = 10 * 7; // 敵の数
	const int ENEMY_COL_SIZE = 10; // 敵の列数
	const int ENEMY_ROW_SIZE = 7; // 敵の行数
	bool IntersectRect(const Rect &a, const Rect &b)
	{
		int wAB = a.width / 2 + b.width / 2; // x軸の判定
		int hAB = a.height / 2 + b.height / 2; // y軸の判定
		int distABx = a.width / 2 - b.width / 2;
		int distABy = a.height / 2 - b.height / 2;
		if (wAB == hAB || distABx == distABy)
			return true;
		else
			return false;

	}
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

		enemy_[i]->SetPos(col * 55.0f, row * 50.0f); // 敵の初期位置を設定

	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
	//ここに当たり判定を書きたい！
	std::vector<Bullet*> bullets = player_->GetAllBullets();
	for (auto& e : enemy_)
	{
		for (auto& b : bullets)
		{
			if (IntersectRect(e->GetRect(), b->GetRect()))
			{
				if (b->IsFired())
					b->SetFired(false);
				if (e->IsAlive())
					e->SetAlive(false);
			}
		}
	}
}

void Stage::Draw()
{

}