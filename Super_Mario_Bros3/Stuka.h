#pragma once

#include "GameObject.h"

#define STUKA_WALKING_SPEED	0.03f;

#define STUKA_BBOX_WIDTH 18
#define STUKA_BBOX_HEIGHT 18
#define STUKA_BBOX_HEIGHT_DIE	16

#define STUKA_STATE_WALKING_LEFT 100	
#define STUKA_STATE_WALKING_RIGHT 200	
#define STUKA_STATE_WALKING_UP 300	
#define STUKA_STATE_WALKING_DOWN 400	
#define STUKA_STATE_DIE 500

#define STUKA_ANI_WALKING 0
#define STUKA_ANI_DIE 1

#define TOP_LIMIT 84
#define BOTTOM_LIMIT 134
#define LEFT_LIMIT 0
#define RIGHT_LIMIT	448

class CStuka : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CStuka();
	virtual void SetState(int state);
};