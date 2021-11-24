#include "Ballbot.h"

CBallbot::CBallbot()
{
	SetState(BALLBOT_STATE_IDLE);
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
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	x += dx;

	if (x <= LEFT_LIMIT && vx < 0) {
		SetState(BALLBOT_STATE_WALKING_RIGHT);
	}
	else if (x >= RIGHT_LIMIT && vx > 0) {
		SetState(BALLBOT_STATE_WALKING_LEFT);
	}



}

void CBallbot::Render()
{
	int ani = BALLBOT_ANI_IDLE;
	if (state == BALLBOT_STATE_DIE) {
		ani = BALLCARRY_ANI_DIE;
	}
	else if (state == BALLBOT_STATE_WALKING_LEFT)
		ani = BALLBOT_ANI_WALKING_LEFT;
	else if (state == BALLBOT_STATE_WALKING_RIGHT)
		ani = BALLBOT_ANI_WALKING_RIGHT;
	else if (state == BALLBOT_STATE_IDLE)
		ani = BALLBOT_ANI_IDLE;



	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CBallbot::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BALLBOT_STATE_DIE:
		y += BALLBOT_BBOX_HEIGHT - BALLBOT_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case BALLBOT_STATE_WALKING_LEFT:
		vx = -BALLBOT_WALKING_SPEED;
		break;
	case BALLBOT_STATE_WALKING_RIGHT:
		vx = BALLBOT_WALKING_SPEED;
		break;
	case BALLBOT_STATE_IDLE:
		break;
	}

}


