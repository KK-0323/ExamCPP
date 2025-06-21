#include "DxLib.h"
#include "globals.h"
#include "input.h"
#include <vector>
#include "Stage.h"
#include "Player.h"


namespace
{
	const int BGCOLOR[3] = { 0, 0, 0 }; // �w�i�F{ 255, 250, 205 }; // �w�i�F
	enum Scene
	{
		TITLE,
		PLAY,
		GAMEOVER
	};
}

// �O���[�o���ϐ��Ƃ��ď�����
int crrTime;
int prevTime;

std::vector<GameObject*> gameObjects; // �Q�[���I�u�W�F�N�g�̃x�N�^�[
std::vector<GameObject*> newObjects; // �Q�[���I�u�W�F�N�g�̃x�N�^�[


float gDeltaTime = 0.0f; // �t���[���Ԃ̎��ԍ�

// �Q�[���I�u�W�F�N�g��S�ĉ������֐�
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

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

// ���݂̃V�[��
Scene currentScene = TITLE;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowCount();
	prevTime = GetNowCount();

	Stage* stage = new Stage(); // �X�e�[�W�I�u�W�F�N�g�̐���
	Player* player = nullptr; // �v���C���[�|�C���^��������


	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate(); // �L�[���͂̏�Ԃ��X�V

		crrTime = GetNowCount(); // ���݂̎��Ԃ��擾
		// �O��̎��ԂƂ̍������v�Z
		float deltaTime = (crrTime - prevTime) / 1000.0f; // �b�P�ʂɕϊ�
		gDeltaTime = deltaTime; // �O���[�o���ϐ��ɕۑ�

		//�����ɂ�肽������������(��������j
		// �V�[������
		switch (currentScene)
		{
		case TITLE:
			DrawString(100, 100, "TITLE Scene", GetColor(255, 255, 255));
			DrawString(100, 200, "Push [P] the PlayScene", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_P))
			{
				ReleaseAllGameObjects(); // �V�[���ڍs�O�ɂ��ׂẴI�u�W�F�N�g�����
				stage = new Stage();
				player = dynamic_cast<Player*>(stage->GetPlayer());
				currentScene = PLAY;
			}
			break;
		case PLAY:
			//�Q�[���I�u�W�F�N�g�̒ǉ�
			if (newObjects.size() > 0) {
				for (auto& obj : newObjects) {
					gameObjects.push_back(obj); // �V�����Q�[���I�u�W�F�N�g��ǉ�	
				}
				newObjects.clear(); // �V�����Q�[���I�u�W�F�N�g�̃x�N�^�[���N���A
			}
			
			//gameObjects�̍X�V
			for (auto& obj : gameObjects) {
				obj->Update(); // �Q�[���I�u�W�F�N�g�̍X�V
			}
			//gameObjects�̕`��
			for (auto& obj : gameObjects) {
				obj->Draw(); // �Q�[���I�u�W�F�N�g�̕`��
			}

			// Stage�N���X�ɃQ�[���I�[�o�[�ւ̈ڍs���f���ڏ�
			if (stage != nullptr && stage->IsGameOverReady()) {
				currentScene = GAMEOVER;
			}

			for (auto it = gameObjects.begin(); it != gameObjects.end();) {
				if (!(*it)->IsAlive()) {
					delete* it; // �Q�[���I�u�W�F�N�g���폜
					it = gameObjects.erase(it); // �x�N�^�[����폜
				}
				else {
					++it; // ���̗v�f��
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
		
		//�����ɂ�肽�������������i�����܂Łj


		//����ʂ̕`��
		ScreenFlip();
		WaitTimer(16);

		prevTime = crrTime; // ���݂̎��Ԃ�O��̎��ԂƂ��ĕۑ�

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	// �I�����ɃQ�[���I�u�W�F�N�g�����ׂĉ��
	ReleaseAllGameObjects();

	DxLib_End();
	return 0;
}