#include "Player.h"
#include "DxLib.h"
#include "Globals.h"
#include "Input.h"

namespace 
{
	const float PLAYER_INIT_SPEED = 5.0f; // プレイヤーの初期移動速度
	const int PLAYER_IMAGE_WIDTH = 48; // プレイヤーの画像の幅
	const int PLAYER_IMAGE_HEIGHT = 48; // プレイヤーの画像の高さ
	const int PLAYER_BASE_MARGIN = 32; // プレイヤーの基準マージン

	const float PLAYER_INIT_X = WIN_WIDTH / 2 - PLAYER_IMAGE_WIDTH / 2; // プレイヤーの初期X座標
	const float PLAYER_INIT_Y = WIN_HEIGHT - PLAYER_IMAGE_HEIGHT - PLAYER_BASE_MARGIN; // プレイヤーの初期Y座標
}

Player::Player()
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0)
{
	hImage_ = LoadGraph("Assets\\tiny_ship5.png"); // プレイヤーの画像を読み込む
	if (hImage_ == -1) {
		// 画像の読み込みに失敗した場合のエラーハンドリング
		// エラーを返してゲーム終了
	}
	x_ = PLAYER_INIT_X; // 初期座標
	y_ = PLAYER_INIT_Y; // 初期座標
	speed_ = PLAYER_INIT_SPEED; // 移動速度
}

Player::~Player()
{
}

void Player::Update()
{
	float dt = GetDeltaTime(); // フレーム間の時間差を取得
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT)) {
		x_ -= speed_ * dt; // 左に移動
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT)) {
		x_ += speed_ * dt; // 右に移動
	}
}

void Player::Draw()
{
	// プレイヤーの画像を描画(画像の原点は左上)
	DrawExtendGraph(x_, y_, x_ + PLAYER_IMAGE_WIDTH, y_ + PLAYER_IMAGE_HEIGHT, hImage_, TRUE);
}
