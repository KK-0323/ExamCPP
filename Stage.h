#pragma once
#include "GameObject.h"
#include <vector>

class Player; // �O���錾
class Enemy; // �O���錾
class Effect; // �O���錾

class Stage :
	public GameObject
{
private:
	Player* player_; // �v���C���[�I�u�W�F�N�g
	std::vector<Enemy*> enemy_; // �G�I�u�W�F�N�g
	int hBackground;

	bool playerIsDead_;		// �v���C���[�����S�������ǂ���
	bool effectsFinished_;	// �v���C���[�����S���̃G�t�F�N�g���I���������ǂ���
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	Player* GetPlayer() const { return player_; }

	// �Q�[���I�[�o�[�Ɉڍs���鏀�����ł��Ă邩�̊֐�
	bool IsGameOverReady() const { return playerIsDead_ && effectsFinished_; }
};