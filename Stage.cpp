#include <DxLib.h>
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

namespace
{
	const int ENEMY_NUM = 10 * 7; // �G�̐�
	const int ENEMY_COL_SIZE = 10; // �G�̗�
	const int ENEMY_ROW_SIZE = 7; // �G�̍s��
	const float ENEMY_ALIGN_X = 55.0f; //�G����ׂ镝
	const float ENEMY_ALIGN_Y = 50.0f; //�G����ׂ鍂��
	const int ENEMY_LEFT_MARGIN = (WIN_WIDTH - (ENEMY_ALIGN_X * ENEMY_COL_SIZE * 1.5));
	const int ENEMY_TOP_MARGIN = 75;

	bool IntersectRect(const Rect &a_, const Rect &b_)
	{
		// �����Ȃ�ɍl�������
		//int wAB = a.width / 2 + b.width / 2; // x���̔���
		//int hAB = a.height / 2 + b.height / 2; // y���̔���
		//int distABx = a.width - b.width; // 
		//int distABy = a.height - b.height;
		//if (distABx < wAB && distABy < hAB)
		//	return true;
		//else
		//	return false;

		// x�������̓����蔻��
		bool xOverlap = (a_.x < b_.x + b_.width) && (b_.x < a_.x + a_.width);
		// y�������̓����蔻��
		bool yOverlap = (a_.y < b_.y + b_.height) && (b_.y < a_.y + a_.height);

		// x����y�������ŏd�Ȃ��Ă���ΏՓ˂��Ă���
		return xOverlap && yOverlap;
	}
}

Stage::Stage()
	:GameObject(), player_(nullptr), hBackground(-1)
{
	AddGameObject(this); // �X�e�[�W�I�u�W�F�N�g�̂��Q�[���I�u�W�F�N�g
	player_ = new Player(); // �v���C���[�I�u�W�F�N�g�̐���
	enemy_ = std::vector<Enemy*>(ENEMY_NUM); // �G�I�u�W�F�N�g�̐���
	for (int i = 0; i < ENEMY_NUM; i++) {
		int col = i % ENEMY_COL_SIZE; // ��
		int row = i / ENEMY_COL_SIZE; // �s
		ETYPE enemyType[ENEMY_ROW_SIZE] = { BOSS, KNIGHT, MID, ZAKO, ZAKO, ZAKO, ZAKO }; // �G�̎��
		enemy_[i] = new Enemy(i, enemyType[row]); // �G�I�u�W�F�N�g�̐���

		enemy_[i]->SetPos(col * ENEMY_ALIGN_X + ENEMY_LEFT_MARGIN,
						  row * ENEMY_ALIGN_Y + ENEMY_TOP_MARGIN); // �G�̏����ʒu��ݒ�

	}
	hBackground = LoadGraph("Assets\\bg.png");
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
			if (b->IsFired() && e->IsAlive()) 
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
}

void Stage::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}