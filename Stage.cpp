#include <DxLib.h>
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EnemyBeam.h"
#include "GameObject.h"
#include "Effect.h"

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

Stage::Stage()
	:GameObject(), player_(nullptr), hBackground(-1)
{
	AddGameObject(this); // �X�e�[�W�I�u�W�F�N�g���Q�[���I�u�W�F�N�g�̃x�N�^�[�ɒǉ�
	player_ = new Player(); // �v���C���[�I�u�W�F�N�g�̐���
	enemy_ = std::vector<Enemy*>(ENEMY_NUM); // �G�I�u�W�F�N�g�̐���
	for (int i = 0; i < ENEMY_NUM; i++) {
		int col = i % ENEMY_COL_SIZE; // ��
		int row = i / ENEMY_COL_SIZE; // �s
		ETYPE enemyType[ENEMY_ROW_SIZE] = { BOSS, KNIGHT, MID, ZAKO, ZAKO, ZAKO, ZAKO }; // �G�̎��
		enemy_[i] = new Enemy(i, enemyType[row]); // �G�I�u�W�F�N�g�̐���

		enemy_[i]->SetPos(col * 55.0f, row * 50.0f); // �G�̏����ʒu��ݒ�
		enemy_[i]->SetMaxMoveX(ENEMY_LEFT_MARGIN);

		enemy_[i]->SetPos(col * ENEMY_ALIGN_X + ENEMY_LEFT_MARGIN,
			row * ENEMY_ALIGN_Y + ENEMY_TOP_MARGIN); // �G�̏����ʒu��ݒ�
		enemy_[i]->SetXorigin(col * ENEMY_ALIGN_X + ENEMY_LEFT_MARGIN);
	}

	hBackground = LoadGraph("Assets\\bg.png");
}

Stage::~Stage()
{
}

void Stage::Update()
{
	//�����ɓ����蔻���`�������I
	std::vector<Bullet*> bullets = player_->GetAllBullets();
	
	//�v���C���[�̒e�ƓG�̓����蔻��
	for (auto& e : enemy_)
	{
		for (auto& b : bullets)
		{
			if (b->IsFired() && e->IsAlive()) {
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

	// �v���C���[�ƓG�̒e�̓����蔻��
	// gameObject �x�N�^�[���� EnemyBeam �I�u�W�F�N�g���t�B���^�����O���Ď擾
	if (!playerIsDead_ && player_->IsAlive()) { // �v���C���[�������Ă���ԓ����蔻�������
		for (auto& obj : gameObjects)
		{
			EnemyBeam* beam = dynamic_cast<EnemyBeam*>(obj);
			if (beam != nullptr && beam->IsFired()) {
				if (IntersectRect(player_->GetRect(), beam->GetRect()))
				{
					beam->SetFired(false);
					player_->SetAlive(false); // �v���C���[���e�ɓ��������玀�S
					playerIsDead_ = true; // �v���C���[�����S�������Ƃ��L�^

					// �v���C���[�����S������G�t�F�N�g�𐶐�
					new Effect({ player_->GetRect().x + player_->GetRect().width / 2,
								player_->GetRect().y + player_->GetRect().height / 2 });
					break;
				}
			}
		}
	}
	
	// �v���C���[�����S���Ă��ăG�t�F�N�g��������̂�҂�
	if (playerIsDead_ && !effectsFinished_) {
		bool playerEffectAlive = false;
		for (const auto& obj : gameObjects) {
			if (dynamic_cast<Effect*>(obj) != nullptr) {
				playerEffectAlive = true;
				break;
			}
		}
		if (!playerEffectAlive) {
			effectsFinished_ = true; // �G�t�F�N�g��������
		}
	}
}

void Stage::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}