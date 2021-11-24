#include "Drap.h"

CDrap::CDrap()
{
	SetState(DRAP_STATE_WALKING_RIGHT);
	//SetState(DRAP_STATE_WALKING_DOWN);
}

void CDrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DRAP_BBOX_WIDTH;

	if (state == DRAP_STATE_DIE)
		bottom = y + DRAP_BBOX_HEIGHT_DIE;
	else
		bottom = y + DRAP_BBOX_HEIGHT;
}

void CDrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (x <= LEFT_LIMIT && vx < 0) {
		SetState(DRAP_STATE_WALKING_RIGHT);
	}
	else if (x >= RIGHT_LIMIT && vx > 0) {
		SetState(DRAP_STATE_WALKING_LEFT);
	}

	else if (y <= TOP_LIMIT && vy < 0) {
		SetState(DRAP_STATE_WALKING_DOWN);
	}
	else if (y >= BOTTOM_LIMIT && vy > 0) {
		SetState(DRAP_STATE_WALKING_UP);
	}
}

void CDrap::Render()
{
	int ani = DRAP_ANI_WALKING;
	if (state == DRAP_STATE_DIE) {
		ani = DRAP_ANI_DIE;
	}
	else
		ani = DRAP_ANI_WALKING;

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CDrap::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DRAP_STATE_DIE:
		y += DRAP_BBOX_HEIGHT - DRAP_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case DRAP_STATE_WALKING_RIGHT:
		vx = DRAP_WALKING_SPEED;

		break;
	case DRAP_STATE_WALKING_LEFT:
		vx = -DRAP_WALKING_SPEED;

		break;
	case DRAP_STATE_WALKING_UP:
		vy = -DRAP_WALKING_SPEED;

		break;
	case DRAP_STATE_WALKING_DOWN:

		vy = DRAP_WALKING_SPEED;
	}
}

