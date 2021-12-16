#pragma once
#include "GameObject.h"

#define BALLCARRY_WALKING_SPEED	0.03f;

#define BALLCARRY_BBOX_WIDTH 18
#define BALLCARRY_BBOX_HEIGHT 17
#define BALLCARRY_BBOX_HEIGHT_DIE	16

#define BALLCARRY_STATE_WALKING_LEFT 100	
#define BALLCARRY_STATE_WALKING_RIGHT 200
#define BALLCARRY_STATE_IDLE 300
#define BALLCARRY_STATE_DROP 400
#define BALLCARRY_STATE_DIE 500

#define BALLCARRY_ANI_WALKING_LEFT	0
#define BALLCARRY_ANI_WALKING_RIGHT	1
#define BALLCARRY_ANI_IDLE		2
#define BALLCARRY_ANI_DROP		3
#define BALLCARRY_ANI_DIE		4

#define TOP_LIMIT 84
#define BOTTOM_LIMIT 134
#define LEFT_LIMIT 0
#define RIGHT_LIMIT	448
class CBall_Carry : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CBall_Carry();
	virtual void SetState(int state);
};

