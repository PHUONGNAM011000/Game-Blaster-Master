#pragma once
#pragma once
#include "GameObject.h"
#include "algorithm"

#define GX680S_WALKING_SPEED 0.05f;

#define GX680S_BBOX_WIDTH 18
#define GX680S_BBOX_HEIGHT 17
#define GX680S_BBOX_HEIGHT_DIE 9

#define GX680S_STATE_WALKING_RIGHT 1000
#define GX680S_STATE_WALKING_LEFT 1001
#define GX680S_STATE_WALKING_UP 1002
#define GX680S_STATE_WALKING_DOWN 1003
#define GX680S_STATE_DIE 200
#define GX680S_STATE_IDLE 100

#define GX680S_ANI 0






class CGX_680S : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(vector<LPCOLLISIONEVENT>& coEvents, vector<LPCOLLISIONEVENT>& coEventsResult, float& min_tx, float& min_ty, float& nx, float& ny, float& rdx, float& rdy);
	virtual void Render();

public:
	CGX_680S();
	virtual void SetState(int state);
};