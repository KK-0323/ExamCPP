#include "DxLib.h"
#include "globals.h"
#include "input.h"
#include <vector>
#include "Stage.h"
#include "Player.h"


namespace
{
	const int BGCOLOR[3] = { 0, 0, 0 }; // 背景色{ 255, 250, 205 }; // 背景色
	enum Scene
	{
		TITLE,
		PLAY,
		GAMEOVER
	};
}

// グローバル変数として初期化
int crrTime;
int prevTime;

std::vector<GameObject*> gameObjects; // ゲームオブジェクトのベクター
std::vector<GameObject*> newObjects; // ゲームオブジェクトのベクター


float gDeltaTime = 0.0f; // フレーム間の時間差

// ゲームオブジェクトを全て解放する関数
void ReleaseAllGameObjects()
{
	for (auto& obj : gameObjects) {
		delete obj;
	}
	gameObjects.clear();
}

void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("TITLE");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(BGCOLOR[0], BGCOLOR[1], BGCOLOR[2]);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

// 現在のシーン
Scene currentScene = TITLE;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowCount();
	prevTime = GetNowCount();

	Stage* stage = new Stage(); // ステージオブジェクトの生成
	Player* player = nullptr; // プレイヤーポインタを初期化


	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate(); // キー入力の状態を更新

		crrTime = GetNowCount(); // 現在の時間を取得
		// 前回の時間との差分を計算
		float deltaTime = (crrTime - prevTime) / 1000.0f; // 秒単位に変換
		gDeltaTime = deltaTime; // グローバル変数に保存

		//ここにやりたい処理を書く(ここから）
		// シーン分け
		switch (currentScene)
		{
		case TITLE:
			DrawString(100, 100, "TITLE Scene", GetColor(255, 255, 255));
			DrawString(100, 200, "Push [P] the PlayScene", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_P))
			{
				ReleaseAllGameObjects(); // シーン移行前にすべてのオブジェクトを解放
				stage = new Stage();
				player = dynamic_cast<Player*>(stage->GetPlayer());
				currentScene = PLAY;
			}
			break;
		case PLAY:
			//ゲームオブジェクトの追加
			if (newObjects.size() > 0) {
				for (auto& obj : newObjects) {
					gameObjects.push_back(obj); // 新しいゲームオブジェクトを追加	
				}
				newObjects.clear(); // 新しいゲームオブジェクトのベクターをクリア
			}
			
			//gameObjectsの更新
			for (auto& obj : gameObjects) {
				obj->Update(); // ゲームオブジェクトの更新
			}
			//gameObjectsの描画
			for (auto& obj : gameObjects) {
				obj->Draw(); // ゲームオブジェクトの描画
			}

			// Stageクラスにゲームオーバーへの移行判断を移譲
			if (stage != nullptr && stage->IsGameOverReady()) {
				currentScene = GAMEOVER;
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
			
		case GAMEOVER:
			DrawString(100, 100, "GAMEOVER", GetColor(255, 255, 255));
			DrawString(100, 200, "Push [T] the TitleScene", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_T))
			{
				ReleaseAllGameObjects();
				stage = nullptr;
				player = nullptr;
				currentScene = TITLE;
			}
			break;
		default:
			break;
		}
		
		//ここにやりたい処理を書く（ここまで）


		//裏画面の描画
		ScreenFlip();
		WaitTimer(16);

		prevTime = crrTime; // 現在の時間を前回の時間として保存

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	// 終了時にゲームオブジェクトをすべて解放
	ReleaseAllGameObjects();

	DxLib_End();
	return 0;
}