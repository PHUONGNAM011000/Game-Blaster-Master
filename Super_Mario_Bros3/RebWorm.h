#pragma once
#include "GameObject.h"
#define REDWORM_SPEED 0.075f;

#define REDWORM_BBOX_WIDTH	18
#define REDWORM_BBOX_HEIGHT 10

#define	REDWORM_STATE_DIE	200
#define REDWORM_STATE_WALKING 100

#define REDWORM_ANI_WALKING_RIGHT 1
#define REDWORM_ANI_WALKING_LEFT 0

#define REDWORM_GRAVITY	0.0008f
#define REDWORM_RESET_TIME 5000

#define STORING_LOCATION 5000


class CReDWorm : public CGameObject
{
	DWORD reset_start;
	bool isUsed = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void StartReset() { reset_start = (DWORD)GetTickCount64(); }

public:
	CReDWorm();
	void SetisUsed(bool value) { isUsed = value; }
	bool GetisUsed() { return isUsed; }
	virtual void SetState(int state);
};

