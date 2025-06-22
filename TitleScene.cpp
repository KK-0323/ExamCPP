#include "TitleScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "DxLib.h"

TitleScene::TitleScene(SceneManager* manager)
	:GameObject(), sceneManager_(manager), hBackground(-1)
{
	hBackground = LoadGraph("Assets\\bg.png");
	if (hBackground == -1) 
	{
		// 画像の読み込みに失敗した場合のエラーハンドリング
		// エラーを返してゲーム終了
	}
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	// プレイシーンに移行する処理
	if (Input::IsKeyDown(KEY_INPUT_P))
	{
		sceneManager_->ChangeScene(SceneType::PLAY);
	}
}

void TitleScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(WIN_WIDTH / 2 - 100, WIN_HEIGHT / 2, "Press P to Start", GetColor(255, 255, 255));
}
