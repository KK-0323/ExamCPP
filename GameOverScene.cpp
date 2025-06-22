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
		// �摜�̓ǂݍ��݂Ɏ��s�����ꍇ�̃G���[�n���h�����O
		// �G���[��Ԃ��ăQ�[���I��
	}
}

void GameOverScene::Update()
{
	// 3�b��������^�C�g���V�[���Ɉڍs���鏈��
	timer_ -= GetDeltaTime(); // �^�C�}�[������
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