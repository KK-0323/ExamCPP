#include "Enemy.h"
#include "DxLib.h"
#include <string>
#include "Effect.h"
#include "EnemyBeam.h"

namespace
{
	const int ENEMY_IMAGE_WIDTH = 48; // 敵の画像の幅;
	const int ENEMY_IMAGE_HEIGHT = 48; // 敵の画像の高さ;

	const float ENEMY_INIT_X = 100; // 敵の初期X座標;
	const float ENEMY_INIT_Y = 100; // 敵の初期Y座標;
	const float ENEMY_INIT_SPEED = 100.0f; // 敵の初期移動速度;
	const float ENEMY_BEAM_INTERVAL = 5.0f;
	const int ENEMY_BEAM_NUM = 5; // 敵が同時に発射する弾の数
}


Enemy::Enemy()
	:GameObject(),
	hImage_(-1),
	x_(0), y_(0),
	speed_(0),
	imageSize_({ ENEMY_IMAGE_WIDTH, ENEMY_IMAGE_HEIGHT })
{
	hImage_ = LoadGraph("Assets\\tiny_ship10.png"); // 敵の画像を読み込む
	if (hImage_ == -1) {
		// 画像の読み込みに失敗した場合のエラーハンドリング
		// エラーを返してゲーム終了
	}
	x_ = ENEMY_INIT_X; // 初期座標
	y_ = ENEMY_INIT_Y; // 初期座標
	speed_ = ENEMY_INIT_SPEED; // 移動速度
	//for (int i = 0; i < ENEMY_BEAM_NUM; i++)
	//{
	//	beams_.push_back(new EnemyBeam(-10, -10));
	//}
	//idとtypeを指定されなかったときのしょりをここに書かねば
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
	// 画像の読み込み
	std::string imagePath[MAX_ETYPE] = {
		"Assets\\tiny_ship10.png", // ZAKO
		"Assets\\tiny_ship18.png", // MID
		"Assets\\tiny_ship16.png", // KNIGHT
		"Assets\\tiny_ship9.png"   // BOSS
	};

	moveTime_ = 0.0f;
	hImage_ = LoadGraph(imagePath[type_].c_str()); // 敵の画像を読み込む
	if (hImage_ == -1) {
		// 画像の読み込みに失敗した場合のエラーハンドリング
		// エラーを返してゲーム終了
	}
	x_ = ENEMY_INIT_X; // 初期座標
	y_ = ENEMY_INIT_Y; // 初期座標
	speed_ = ENEMY_INIT_SPEED; // 移動速度
	//for (int i = 0; i < ENEMY_BEAM_NUM; i++) {
	//	beams_.push_back(new EnemyBeam(-10, -10)); // 弾のベクターを初期化
	//}
	AddGameObject(this); // 敵オブジェクトをゲームオブジェクトのベクターに追加
}

Enemy::~Enemy()
{
	new Effect({ x_, y_ });
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_); // 画像のハンドルを解放
	}
}

void Enemy::Update()
{
	static float beamTimer = 3.0f; // 弾の発射タイマー

	float period = 10.0f; // 1往復にかける時間（秒）
	float omega = 2.0f * 3.14159265f / period; // 角速度 ω = 2π / T
	moveTime_ = moveTime_ + GetDeltaTime();
	x_ = xorigin_ + xMoveMax_ / 2.0 * sinf(omega * moveTime_);
	y_ = y_;
	
	if (beamTimer < 0)
	{
		// 弾を発射
		//Shoot();
		new EnemyBeam(x_ + ENEMY_IMAGE_WIDTH / 2, y_ + ENEMY_IMAGE_HEIGHT);
		
		beamTimer = ENEMY_BEAM_INTERVAL;
	}
	beamTimer -= GetDeltaTime(); // タイマーを減少
}

void Enemy::Draw()
{
	//画面の左上に敵画像を表示
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
//			return itr; // 発射されていない弾を返す
//		}
//	}
//	return nullptr;
//}
