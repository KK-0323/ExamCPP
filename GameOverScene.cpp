#include "GameOverScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "DxLib.h"
#include "globals.h"

GameOverScene::GameOverScene(SceneManager* manager)
	:GameObject(), sceneManager_(manager), hBackground(-1), timer_(3.0f)
{
	hBackground = LoadGraph("Assets\\bg.png");
	if (hBackground == -1)
	{
		// 画像の読み込みに失敗した場合のエラーハンドリング
		// エラーを返してゲーム終了
	}
}

void GameOverScene::Update()
{
	// 3秒たったらタイトルシーンに移行する処理
	timer_ -= GetDeltaTime(); // タイマーを減少
	if (timer_ <= 0.0f)
	{
		sceneManager_->ChangeScene(SceneType::TITLE);
	}
}

void GameOverScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(WIN_WIDTH / 2 - 100, WIN_HEIGHT / 2, "GAME OVER", GetColor(255, 0, 0));
}