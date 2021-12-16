#include "Ball_Carry.h"
CBall_Carry::CBall_Carry()
{
	SetState(STATE_IDLE);
}

void CBall_Carry::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BALLCARRY_BBOX_WIDTH;

	if (state == BALLCARRY_STATE_DIE)
		bottom = y + BALLCARRY_BBOX_HEIGHT_DIE;
	else
		bottom = y + BALLCARRY_BBOX_HEIGHT;
}

void CBall_Carry::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	//


	x += dx;
	y += dy;
}

void CBall_Carry::Render()
{
	if (state != STATE_DIE)
	{
		int ani = BALLCARRY_ANI;

		animation_set->at(ani)->Render(x, y);

		//RenderBoundingBox();
	}
}

void CBall_Carry::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case STATE_DIE:
		vy = DIE_PULL;
		break;
	}
}
