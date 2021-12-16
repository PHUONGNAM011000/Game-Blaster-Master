#pragma once
#pragma once
#include "GameObject.h"

#define LASERGUARD_WALKING_SPEED	0.03f;

#define LASERGUARD_BBOX_WIDTH 17
#define LASERGUARD_BBOX_HEIGHT 18
#define LASERGUARD_BBOX_HEIGHT_DIE	16

#define LASERGUARD_STATE_WALKING_LEFT 100	
#define LASERGUARD_STATE_WALKING_RIGHT 200
#define LASERGUARD_STATE_WALKING_UP 300
#define LASERGUARD_STATE_WALKING_DOWN 400
#define LASERGUARD_STATE_DIE 500

#define LASERGUARD_ANI_WALKING	0
#define LASERGUARD_ANI_DIE		1

#define TOP_LIMIT 84
#define BOTTOM_LIMIT 134
#define LEFT_LIMIT 0
#define RIGHT_LIMIT	448



class CLaserGuard : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CLaserGuard();
	virtual void SetState(int state);
};
