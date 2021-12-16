#pragma once
#include "GameObject.h"

#define GX680_WALKING_SPEED	0.03f;

#define GX680_BBOX_WIDTH 18
#define GX680_BBOX_HEIGHT 17
#define GX680_BBOX_HEIGHT_DIE	16

#define GX680_STATE_WALKING_LEFT 100	
#define GX680_STATE_WALKING_RIGHT 200
#define GX680_STATE_WALKING_UP 300
#define GX680_STATE_WALKING_DOWN 400
#define GX680_STATE_DIE 500

#define GX680_ANI_WALKING	0
#define GX680_ANI_DIE		1

#define TOP_LIMIT 84
#define BOTTOM_LIMIT 134
#define LEFT_LIMIT 0
#define RIGHT_LIMIT	448




class CGX_680 : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CGX_680();
	virtual void SetState(int state);
};
