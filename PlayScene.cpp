#include "PlayScene.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Input.h"
#include "Effect.h"

std::vector<GameObject*> gameObjects; // �Q�[���I�u�W�F�N�g�̃x�N�^�[
std::vector<GameObject*> newObjects; // �Q�[���I�u�W�F�N�g�̃x�N�^�[

namespace
{
	const int ENEMY_NUM = 10 * 7; // �G�̐�
	const int ENEMY_COL_SIZE = 10; // �G�̗�
	const int ENEMY_ROW_SIZE = 7; // �G�̍s��
	const float ENEMY_ALIGN_X = 55.0f; //�G����ׂ镝
	const float ENEMY_ALIGN_Y = 50.0f; //�G����ׂ鍂��
	const int ENEMY_LEFT_MARGIN = (WIN_WIDTH - (ENEMY_ALIGN_X * ENEMY_COL_SIZE)) / 2;
	const int ENEMY_TOP_MARGIN = 75;

	bool IntersectRect(const Rect& _a, const Rect& _b)
	{
		// X�������̏d�Ȃ�𔻒�
		bool xOverlap = (_a.x < _b.x + _b.width) && (_b.x < _a.x + _a.width);

		// Y�������̏d�Ȃ�𔻒�
		bool yOverlap = (_a.y < _b.y + _b.height) && (_b.y < _a.y + _a.height);

		// X����Y���̗����ŏd�Ȃ��Ă���ΏՓ˂��Ă���
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


	player_ = new Player(); // �v���C���[�I�u�W�F�N�g�̐���
	AddGameObject(player_);
	for (auto& blt : player_->GetAllBullets())
	{
		AddGameObject(blt);
	}

	enemy_ = std::vector<Enemy*>(ENEMY_NUM); // �G�I�u�W�F�N�g�̐���
	for (int i = 0; i < ENEMY_NUM; i++) {
		int col = i % ENEMY_COL_SIZE; // ��
		int row = i / ENEMY_COL_SIZE; // �s
		ETYPE enemyType[ENEMY_ROW_SIZE] = { BOSS, KNIGHT, MID, ZAKO, ZAKO, ZAKO, ZAKO }; // �G�̎��
		enemy_[i] = new Enemy(i, enemyType[row]); // �G�I�u�W�F�N�g�̐���

		enemy_[i]->SetMaxMoveX(ENEMY_LEFT_MARGIN);

		enemy_[i]->SetPos(static_cast<float>( col * ENEMY_ALIGN_X + ENEMY_LEFT_MARGIN),
						  static_cast<float>( row * ENEMY_ALIGN_Y + ENEMY_TOP_MARGIN)); // �G�̏����ʒu��ݒ�
		enemy_[i]->SetXorigin(static_cast<float>( col * ENEMY_ALIGN_X + ENEMY_LEFT_MARGIN));

		enemy_.push_back(enemy_[i]);
		AddGameObject(enemy_[i]);
	}
	

	hBackground = LoadGraph("Assets\\bg.png");

	// �I�u�W�F�N�g���������ꂽ��ɁAnewObjects�ɗ��܂����I�u�W�F�N�g��gameObjects�Ɉړ�������
	for (auto& obj : newObjects)
	{
		gameObjects.push_back(obj);
	}
	newObjects.clear();
}

PlayScene::~PlayScene()
{
	// �S�ẴQ�[���I�u�W�F�N�g�����
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
	//�Q�[���I�u�W�F�N�g�̒ǉ�
	if (newObjects.size() > 0) {
		for (auto& obj : newObjects) {
			gameObjects.push_back(obj); // �V�����Q�[���I�u�W�F�N�g��ǉ�	
		}
		newObjects.clear(); // �V�����Q�[���I�u�W�F�N�g�̃x�N�^�[���N���A
	}
	//gameObjects�̍X�V
	for (auto& obj : gameObjects) {
		if (obj->IsAlive())
		{
			obj->Update(); // �Q�[���I�u�W�F�N�g�̍X�V
		}
	}

	// �����蔻��̏���
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
			delete* it; // �Q�[���I�u�W�F�N�g���폜
			it = gameObjects.erase(it); // �x�N�^�[����폜
		}
		else {
			++it; // ���̗v�f��
		}
	}

	// ���̃Q�[���I�[�o�[�����i��: O�L�[�ŃQ�[���I�[�o�[�V�[���ցj
	if (Input::IsKeyDown(KEY_INPUT_O)) {
		sceneManager_->ChangeScene(SceneType::GAMEOVER);
	}
}

void PlayScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//gameObjects�̕`��
	for (auto& obj : gameObjects) {
		obj->Draw(); // �Q�[���I�u�W�F�N�g�̕`��
	}
}
