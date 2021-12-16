#pragma once
#include "GameObject.h"
#include "DefinePlayer.h"

class Tank_Wheel : public CGameObject
{
	int part = 0;
	int pre_ani = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);

public:
	float upBoudary;
	Tank_Wheel(int part);
	virtual void SetState(int state);
};
