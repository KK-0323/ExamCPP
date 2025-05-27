#pragma once
#include "GameObject.h"
#include "Globals.h"


enum ETYPE
{
	ZAKO, MID, KNIGHT, BOSS, MAX_ETYPE
};


class Enemy :
	public GameObject
{
	int hImage_;  //“G‚Ì‰æ‘œƒnƒ“ƒhƒ‹
	float x_, y_; //“G‚ÌÀ•W
	float speed_; //“G‚ÌˆÚ“®‘¬“x

	int ID_; //“G‚ÌID
	ETYPE type_; //“G‚Ìí—Ş
public:
	Enemy(int id, ETYPE type);
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
	void SetPos(float x, float y) { x_ = x; y_ = y; } //“G‚ÌÀ•W‚ğİ’è
	Rect GetRect() const { return { x_,y_,ENEMY_IMAGE_WIDTH,ENEMY_IMAGE_HEIGHT }; } // “G‚Ì‹éŒ`‚ğæ“¾
	//void SetID(int id) { ID_ = id; } //“G‚ÌID‚ğİ’è
};