#include "Stuka.h"
CStuka::CStuka()
{
	SetState(STATE_IDLE);
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
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;
}

void CStuka::Render()
{
	if (state != STATE_DIE)
	{
		int ani = STUKA_ANI;

		animation_set->at(ani)->Render(x, y);

		//RenderBoundingBox();
	}
}

void CStuka::SetState(int state)
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
