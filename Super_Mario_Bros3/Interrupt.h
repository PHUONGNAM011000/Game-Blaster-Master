#pragma once
#include "GameObject.h"

#define INTERRUPT_WALKING_SPEED	0.03f;

#define INTERRUPT_BBOX_WIDTH 22
#define INTERRUPT_BBOX_HEIGHT 18
#define INTERRUPT_BBOX_HEIGHT_DIE	16

#define INTERRUPT_STATE_IDLE 100	
#define INTERRUPT_STATE_DROP 200
#define INTERRUPT_STATE_DIE 500

#define INTERRUPT_ANI_IDLE	0
#define INTERRUPT_ANI_DROP	1
#define INTERRUPT_ANI_DIE	2

#define TOP_LIMIT 84
#define BOTTOM_LIMIT 134
#define LEFT_LIMIT 0
#define RIGHT_LIMIT	448



class CInterrupt : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CInterrupt();
	virtual void SetState(int state);
};
