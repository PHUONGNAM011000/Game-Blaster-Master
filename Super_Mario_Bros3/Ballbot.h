#pragma once
#include "GameObject.h"

#define BALLBOT_WALKING_SPEED	0.03f;

#define BALLBOT_BBOX_WIDTH 18
#define BALLBOT_BBOX_HEIGHT 17
#define BALLBOT_BBOX_HEIGHT_DIE	16

#define BALLBOT_STATE_WALKING_LEFT 100	
#define BALLBOT_STATE_WALKING_RIGHT 200
#define BALLBOT_STATE_IDLE 300
#define BALLBOT_STATE_DIE 500

#define BALLBOT_ANI_WALKING_LEFT	0
#define BALLBOT_ANI_WALKING_RIGHT	1
#define BALLBOT_ANI_IDLE		2
#define BALLCARRY_ANI_DIE		3

#define TOP_LIMIT 84
#define BOTTOM_LIMIT 134
#define LEFT_LIMIT 0
#define RIGHT_LIMIT	448



class CBallbot : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CBallbot();
	virtual void SetState(int state);
};

