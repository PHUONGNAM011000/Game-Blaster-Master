#include "LaserGuard.h"
CLaserGuard::CLaserGuard()
{
	SetState(STATE_IDLE);
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

	x += dx;
	y += dy;
}

void CLaserGuard::Render()
{
	if (state != STATE_DIE)
	{
		int ani = LASERGUARD_ANI;

		animation_set->at(ani)->Render(x, y);

		//RenderBoundingBox();
	}
}

void CLaserGuard::SetState(int state)
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
