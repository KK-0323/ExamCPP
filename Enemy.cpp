#include "Enemy.h"
#include "DxLib.h"
#include <string>
#include "Effect.h"
#include "EnemyBeam.h"

namespace
{
	const int ENEMY_IMAGE_WIDTH = 48; // �G�̉摜�̕�;
	const int ENEMY_IMAGE_HEIGHT = 48; // �G�̉摜�̍���;

	const float ENEMY_INIT_X = 100; // �G�̏���X���W;
	const float ENEMY_INIT_Y = 100; // �G�̏���Y���W;
	const float ENEMY_INIT_SPEED = 100.0f; // �G�̏����ړ����x;
	const float ENEMY_BEAM_INTERVAL = 5.0f;
	const int ENEMY_BEAM_NUM = 5; // �G�������ɔ��˂���e�̐�
}


Enemy::Enemy()
	:GameObject(),
	hImage_(-1),
	x_(0), y_(0),
	speed_(0),
	imageSize_({ ENEMY_IMAGE_WIDTH, ENEMY_IMAGE_HEIGHT })
{
	hImage_ = LoadGraph("Assets\\tiny_ship10.png"); // �G�̉摜��ǂݍ���
	if (hImage_ == -1) {
		// �摜�̓ǂݍ��݂Ɏ��s�����ꍇ�̃G���[�n���h�����O
		// �G���[��Ԃ��ăQ�[���I��
	}
	x_ = ENEMY_INIT_X; // �������W
	y_ = ENEMY_INIT_Y; // �������W
	speed_ = ENEMY_INIT_SPEED; // �ړ����x
	//for (int i = 0; i < ENEMY_BEAM_NUM; i++)
	//{
	//	beams_.push_back(new EnemyBeam(-10, -10));
	//}
	//id��type���w�肳��Ȃ������Ƃ��̂����������ɏ����˂�
}

Enemy::Enemy(int id, ETYPE type)
	:GameObject(),
	hImage_(-1),
	x_(0), y_(0),
	speed_(0),
	ID_(id), type_(type), imageSize_({ ENEMY_IMAGE_WIDTH, ENEMY_IMAGE_HEIGHT })

{
	//ETYPE::ZAKO =>  "Assets/tiny_ship10.png"
	//ETYPE::MID = > "Assets/tiny_ship18.png"
	//ETYPE::KNIGHT = > "Assets/tiny_ship16.png"
	//ETYPE::BOSS = > "Assets/tiny_ship9.png"
	// �摜�̓ǂݍ���
	std::string imagePath[MAX_ETYPE] = {
		"Assets\\tiny_ship10.png", // ZAKO
		"Assets\\tiny_ship18.png", // MID
		"Assets\\tiny_ship16.png", // KNIGHT
		"Assets\\tiny_ship9.png"   // BOSS
	};

	moveTime_ = 0.0f;
	hImage_ = LoadGraph(imagePath[type_].c_str()); // �G�̉摜��ǂݍ���
	if (hImage_ == -1) {
		// �摜�̓ǂݍ��݂Ɏ��s�����ꍇ�̃G���[�n���h�����O
		// �G���[��Ԃ��ăQ�[���I��
	}
	x_ = ENEMY_INIT_X; // �������W
	y_ = ENEMY_INIT_Y; // �������W
	speed_ = ENEMY_INIT_SPEED; // �ړ����x
	//for (int i = 0; i < ENEMY_BEAM_NUM; i++) {
	//	beams_.push_back(new EnemyBeam(-10, -10)); // �e�̃x�N�^�[��������
	//}
	AddGameObject(this); // �G�I�u�W�F�N�g���Q�[���I�u�W�F�N�g�̃x�N�^�[�ɒǉ�
}

Enemy::~Enemy()
{
	new Effect({ x_, y_ });
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_); // �摜�̃n���h�������
	}
}

void Enemy::Update()
{
	static float beamTimer = 3.0f; // �e�̔��˃^�C�}�[

	float period = 10.0f; // 1�����ɂ����鎞�ԁi�b�j
	float omega = 2.0f * 3.14159265f / period; // �p���x �� = 2�� / T
	moveTime_ = moveTime_ + GetDeltaTime();
	x_ = xorigin_ + xMoveMax_ / 2.0 * sinf(omega * moveTime_);
	y_ = y_;
	
	if (beamTimer < 0)
	{
		// �e�𔭎�
		//Shoot();
		new EnemyBeam(x_ + ENEMY_IMAGE_WIDTH / 2, y_ + ENEMY_IMAGE_HEIGHT);
		
		beamTimer = ENEMY_BEAM_INTERVAL;
	}
	beamTimer -= GetDeltaTime(); // �^�C�}�[������
}

void Enemy::Draw()
{
	//��ʂ̍���ɓG�摜��\��
	DrawExtendGraphF(x_, y_,
		x_ + ENEMY_IMAGE_WIDTH, y_ + ENEMY_IMAGE_HEIGHT,
		hImage_, TRUE);
}

//EnemyBeam* Enemy::GetActiveBeam()
//{
//	return nullptr;
//}

//void Enemy::Shoot()
//{
//	EnemyBeam* beam = GetActiveBeam();
//	if (beam != nullptr) {
//		beam->SetPos(x_, y_);
//		beam->SetFired(true);
//	}
//}
//
//EnemyBeam* Enemy::GetActiveBeam()
//{
//	for (auto& itr : beams_)
//	{
//		if (!itr->IsFired())
//		{
//			return itr; // ���˂���Ă��Ȃ��e��Ԃ�
//		}
//	}
//	return nullptr;
//}
