#include "Ballbot.h"
CBallbot::CBallbot()
{
	SetState(STATE_IDLE);
}

void CBallbot::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BALLBOT_BBOX_WIDTH;

	if (state == BALLBOT_STATE_DIE)
		bottom = y + BALLBOT_BBOX_HEIGHT_DIE;
	else
		bottom = y + BALLBOT_BBOX_HEIGHT;
}

void CBallbot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;
}

void CBallbot::Render()
{
	if (state != STATE_DIE)
	{
		int ani = BALLBOT_ANI;

		animation_set->at(ani)->Render(x, y);

		//RenderBoundingBox();
	}
}

void CBallbot::SetState(int state)
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
