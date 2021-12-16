#include "LaserGuard.h"

CLaserGuard::CLaserGuard()
{
	SetState(LASERGUARD_STATE_WALKING_RIGHT);
	//SetState(DRAP_STATE_WALKING_DOWN);
}

void CLaserGuard::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + LASERGUARD_BBOX_WIDTH;

	if (state == LASERGUARD_STATE_DIE)
		bottom = y + LASERGUARD_BBOX_HEIGHT_DIE;
	else
		bottom = y + LASERGUARD_BBOX_HEIGHT;
}

void CLaserGuard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	/*x += dx;
	y += dy;

	if (x <= LEFT_LIMIT && vx < 0) {
		SetState(LASERGUARD_STATE_WALKING_RIGHT);
	}
	else if (x >= RIGHT_LIMIT && vx > 0) {
		SetState(LASERGUARD_STATE_WALKING_LEFT);
	}

	else if (y <= TOP_LIMIT && vy < 0) {
		SetState(LASERGUARD_STATE_WALKING_DOWN);
	}
	else if (y >= BOTTOM_LIMIT && vy > 0) {
		SetState(LASERGUARD_STATE_WALKING_UP);
	}*/
}

void CLaserGuard::Render()
{
	int ani = LASERGUARD_ANI_WALKING;
	if (state == LASERGUARD_STATE_DIE) {
		ani = LASERGUARD_ANI_DIE;
	}
	else
		ani = LASERGUARD_ANI_WALKING;

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CLaserGuard::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LASERGUARD_STATE_DIE:
		y += LASERGUARD_BBOX_HEIGHT - LASERGUARD_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case LASERGUARD_STATE_WALKING_RIGHT:
		vx = LASERGUARD_WALKING_SPEED;

		break;
	case LASERGUARD_STATE_WALKING_LEFT:
		vx = -LASERGUARD_WALKING_SPEED;

		break;
	case LASERGUARD_STATE_WALKING_UP:
		vy = -LASERGUARD_WALKING_SPEED;

		break;
	case LASERGUARD_STATE_WALKING_DOWN:

		vy = LASERGUARD_WALKING_SPEED;
	}
}

