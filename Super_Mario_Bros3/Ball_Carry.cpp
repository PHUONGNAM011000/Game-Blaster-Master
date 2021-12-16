#include "Ball_Carry.h"

CBall_Carry::CBall_Carry()
{
	SetState(BALLCARRY_STATE_WALKING_RIGHT);
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
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	/*x += dx;

	if (x <= LEFT_LIMIT && vx < 0) {
		SetState(BALLCARRY_STATE_WALKING_RIGHT);
	}
	else if (x >= RIGHT_LIMIT && vx > 0) {
		SetState(BALLCARRY_STATE_WALKING_LEFT);
	}*/



}

void CBall_Carry::Render()
{
	int ani = BALLCARRY_ANI_IDLE;
	if (state == BALLCARRY_STATE_DIE) {
		ani = BALLCARRY_ANI_DIE;
	}
	else if (state == BALLCARRY_STATE_WALKING_LEFT)
		ani = BALLCARRY_ANI_WALKING_LEFT;
	else if (state == BALLCARRY_STATE_WALKING_RIGHT)
		ani = BALLCARRY_ANI_WALKING_RIGHT;
	else if (state == BALLCARRY_STATE_IDLE)
		ani = BALLCARRY_ANI_IDLE;
	else if (state == BALLCARRY_STATE_DROP)
		ani = BALLCARRY_ANI_DROP;


	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CBall_Carry::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BALLCARRY_STATE_DIE:
		y += BALLCARRY_BBOX_HEIGHT - BALLCARRY_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case BALLCARRY_STATE_WALKING_LEFT:
		vx = -BALLCARRY_WALKING_SPEED;
		break;
	case BALLCARRY_STATE_WALKING_RIGHT:
		vx = BALLCARRY_WALKING_SPEED;
		break;
	case BALLCARRY_STATE_IDLE:
		break;
	case BALLCARRY_STATE_DROP:
		break;
	}

}


