#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

namespace
{
	const int ENEMY_NUM = 10 * 7; // �G�̐�
	const int ENEMY_COL_SIZE = 10; // �G�̗�
	const int ENEMY_ROW_SIZE = 7; // �G�̍s��
	bool IntersectRect(const Rect &a, const Rect &b)
	{
		int wAB = a.width / 2 + b.width / 2; // x���̔���
		int hAB = a.height / 2 + b.height / 2; // y���̔���
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
	AddGameObject(this); // �X�e�[�W�I�u�W�F�N�g�̂��Q�[���I�u�W�F�N�g
	player_ = new Player(); // �v���C���[�I�u�W�F�N�g�̐���
	enemy_ = std::vector<Enemy*>(ENEMY_NUM); // �G�I�u�W�F�N�g�̐���
	for (int i = 0; i < ENEMY_NUM; i++) {
		int col = i % ENEMY_COL_SIZE; // ��
		int row = i / ENEMY_COL_SIZE; // �s
		ETYPE enemyType[ENEMY_ROW_SIZE] = { BOSS, KNIGHT, MID, ZAKO, ZAKO, ZAKO, ZAKO }; // �G�̎��
		enemy_[i] = new Enemy(i, enemyType[row]); // �G�I�u�W�F�N�g�̐���

		enemy_[i]->SetPos(col * 55.0f, row * 50.0f); // �G�̏����ʒu��ݒ�

	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
	//�����ɓ����蔻������������I
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