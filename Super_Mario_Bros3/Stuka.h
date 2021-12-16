#pragma once
#pragma once
#include "GameObject.h"
#include "algorithm"

#define STUKA_WALKING_SPEED 0.05f;

#define STUKA_BBOX_WIDTH 18
#define STUKA_BBOX_HEIGHT 18
#define STUKA_BBOX_HEIGHT_DIE 9

#define STUKA_STATE_WALKING_RIGHT 1000
#define STUKA_STATE_WALKING_LEFT 1001
#define STUKA_STATE_WALKING_UP 1002
#define STUKA_STATE_WALKING_DOWN 1003

#define STUKA_ANI 0

#define STUKA_STATE_IDLE 100
#define STUKA_STATE_DIE 200
#define STUKA_STATE_WALKING 300



class CStuka : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(vector<LPCOLLISIONEVENT>& coEvents, vector<LPCOLLISIONEVENT>& coEventsResult, float& min_tx, float& min_ty, float& nx, float& ny, float& rdx, float& rdy);
	virtual void Render();

public:
	CStuka();
	virtual void SetState(int state);
};