#include "PlayScene.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Input.h"
#include "Effect.h"

std::vector<GameObject*> gameObjects; // ゲームオブジェクトのベクター
std::vector<GameObject*> newObjects; // ゲームオブジェクトのベクター

namespace
{
	const int ENEMY_NUM = 10 * 7; // 敵の数
	const int ENEMY_COL_SIZE = 10; // 敵の列数
	const int ENEMY_ROW_SIZE = 7; // 敵の行数
	const float ENEMY_ALIGN_X = 55.0f; //敵を並べる幅
	const float ENEMY_ALIGN_Y = 50.0f; //敵を並べる高さ
	const int ENEMY_LEFT_MARGIN = (WIN_WIDTH - (ENEMY_ALIGN_X * ENEMY_COL_SIZE)) / 2;
	const int ENEMY_TOP_MARGIN = 75;

	bool IntersectRect(const Rect& _a, const Rect& _b)
	{
		// X軸方向の重なりを判定
		bool xOverlap = (_a.x < _b.x + _b.width) && (_b.x < _a.x + _a.width);

		// Y軸方向の重なりを判定
		bool yOverlap = (_a.y < _b.y + _b.height) && (_b.y < _a.y + _a.height);

		// X軸とY軸の両方で重なっていれば衝突している
		return xOverlap && yOverlap;
	}
}


PlayScene::PlayScene(SceneManager* manager)
	:GameObject(), sceneManager_(manager), hBackground(-1)
{
	for (auto& obj : gameObjects)
	{
		//delete obj;
	}
	gameObjects.clear();
	newObjects.clear();


	player_ = new Player(); // プレイヤーオブジェクトの生成
	AddGameObject(player_);
	for (auto& blt : player_->GetAllBullets())
	{
		AddGameObject(blt);
	}

	enemy_ = std::vector<Enemy*>(ENEMY_NUM); // 敵オブジェクトの生成
	for (int i = 0; i < ENEMY_NUM; i++) {
		int col = i % ENEMY_COL_SIZE; // 列
		int row = i / ENEMY_COL_SIZE; // 行
		ETYPE enemyType[ENEMY_ROW_SIZE] = { BOSS, KNIGHT, MID, ZAKO, ZAKO, ZAKO, ZAKO }; // 敵の種類
		enemy_[i] = new Enemy(i, enemyType[row]); // 敵オブジェクトの生成

		enemy_[i]->SetMaxMoveX(ENEMY_LEFT_MARGIN);

		enemy_[i]->SetPos(static_cast<float>( col * ENEMY_ALIGN_X + ENEMY_LEFT_MARGIN),
						  static_cast<float>( row * ENEMY_ALIGN_Y + ENEMY_TOP_MARGIN)); // 敵の初期位置を設定
		enemy_[i]->SetXorigin(static_cast<float>( col * ENEMY_ALIGN_X + ENEMY_LEFT_MARGIN));

		enemy_.push_back(enemy_[i]);
		AddGameObject(enemy_[i]);
	}
	

	hBackground = LoadGraph("Assets\\bg.png");

	// オブジェクトが生成された後に、newObjectsに溜まったオブジェクトをgameObjectsに移動させる
	for (auto& obj : newObjects)
	{
		gameObjects.push_back(obj);
	}
	newObjects.clear();
}

PlayScene::~PlayScene()
{
	// 全てのゲームオブジェクトを解放
	for (auto& obj : gameObjects)
	{
		delete obj;
	}
	gameObjects.clear();

	for (auto& obj : newObjects)
	{
		delete obj;
	}
	newObjects.clear();
}

void PlayScene::Update()
{
	//ゲームオブジェクトの追加
	if (newObjects.size() > 0) {
		for (auto& obj : newObjects) {
			gameObjects.push_back(obj); // 新しいゲームオブジェクトを追加	
		}
		newObjects.clear(); // 新しいゲームオブジェクトのベクターをクリア
	}
	//gameObjectsの更新
	for (auto& obj : gameObjects) {
		if (obj->IsAlive())
		{
			obj->Update(); // ゲームオブジェクトの更新
		}
	}

	// 当たり判定の処理
	std::vector<Bullet*> bullets = player_->GetAllBullets();
	for (auto& e : enemy_)
	{
		for (auto& b : bullets)
		{
			if (b->IsFired() && e->IsAlive()) {
				if (IntersectRect(e->GetRect(), b->GetRect()))
				{
						b->SetFired(false);
						e->SetAlive(false);
						AddGameObject(new Effect(e->GetRect().GetCenter()));
				}
			}
		}
	}

	for (auto it = gameObjects.begin(); it != gameObjects.end();) {
		if (!(*it)->IsAlive()) {
			delete* it; // ゲームオブジェクトを削除
			it = gameObjects.erase(it); // ベクターから削除
		}
		else {
			++it; // 次の要素へ
		}
	}

	// 仮のゲームオーバー条件（例: Oキーでゲームオーバーシーンへ）
	if (Input::IsKeyDown(KEY_INPUT_O)) {
		sceneManager_->ChangeScene(SceneType::GAMEOVER);
	}
}

void PlayScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//gameObjectsの描画
	for (auto& obj : gameObjects) {
		obj->Draw(); // ゲームオブジェクトの描画
	}
}
