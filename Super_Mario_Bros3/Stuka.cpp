#include "Stuka.h"

CStuka::CStuka()
{
	SetState(STUKA_STATE_WALKING_RIGHT);
}

void CStuka::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + STUKA_BBOX_WIDTH;

	if (state == STUKA_STATE_DIE)
		bottom = y + STUKA_BBOX_HEIGHT_DIE;
	else
		bottom = y + STUKA_BBOX_HEIGHT;
}

void CStuka::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (x <= LEFT_LIMIT && vx < 0) {
		SetState(STUKA_STATE_WALKING_RIGHT);
	}
	else if (x >= RIGHT_LIMIT && vx > 0) {
		SetState(STUKA_STATE_WALKING_LEFT);
	}

	else if (y <= TOP_LIMIT && vy < 0) {
		SetState(STUKA_STATE_WALKING_DOWN);
	}
	else if (y >= BOTTOM_LIMIT && vy > 0) {
		SetState(STUKA_STATE_WALKING_UP);
	}
}

void CStuka::Render()
{
	int ani = STUKA_ANI_WALKING;
	if (state == STUKA_STATE_DIE) {
		ani = STUKA_ANI_DIE;
	}
	else ani = STUKA_ANI_WALKING;

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CStuka::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STUKA_STATE_DIE:
		y += STUKA_BBOX_HEIGHT - STUKA_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case STUKA_STATE_WALKING_LEFT:
		vx = -STUKA_WALKING_SPEED;
		break;
	case STUKA_STATE_WALKING_RIGHT:
		vx = STUKA_WALKING_SPEED;
		break;
	case STUKA_STATE_WALKING_UP:
		vy = -STUKA_WALKING_SPEED;
		break;
	case STUKA_STATE_WALKING_DOWN:
		vy = STUKA_WALKING_SPEED;
		break;
	}

}

