#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "GameOverScene.h"

SceneManager::SceneManager()
	:GameObject(), currentScene_(nullptr), currentSceneType_(SceneType::TITLE)
{
	ChangeScene(SceneType::TITLE); // �^�C�g���V�[������J�n
}

SceneManager::~SceneManager()
{
	delete currentScene_;
}

void SceneManager::ChangeScene(SceneType type)
{
	if (currentScene_)
	{
		delete currentScene_; // �O�̃V�[���I�u�W�F�N�g�����
		currentScene_ = nullptr;
	}

	currentSceneType_ = type;

	switch (type)
	{
	case SceneType::TITLE:
		currentScene_ = new TitleScene(this);
		break;
	case SceneType::PLAY:
		currentScene_ = new PlayScene(this);
		break;
	case SceneType::GAMEOVER:
		currentScene_ = new GameOverScene(this);
		break;
	default:
		break;
	}
}

void SceneManager::Update()
{
	if (currentScene_)
	{
		currentScene_->Update();
	}
}

void SceneManager::Draw()
{
	if (currentScene_)
	{
		currentScene_->Draw();
	}
}
