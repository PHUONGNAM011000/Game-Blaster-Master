#include "Eyelet.h"
CEyelet::CEyelet()
{
	SetState(EYELET_STATE_WALKING_RIGHT);
	SetState(EYELET_STATE_WALKING_DOWN);
}

void CEyelet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + EYELET_BBOX_WIDTH;

	if (state == EYELET_STATE_DIE)
		bottom = y + EYELET_BBOX_HEIGHT_DIE;
	else
		bottom = y + EYELET_BBOX_HEIGHT;
}

void CEyelet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	/*x += dx;
	y += dy;

	if (x <= LEFT_LIMIT && vx < 0) {
		SetState(EYELET_STATE_WALKING_RIGHT);
	}
	else if (x >= RIGHT_LIMIT && vx > 0) {
		SetState(EYELET_STATE_WALKING_LEFT);
	}

	else if (y <= TOP_LIMIT && vy < 0) {
		SetState(EYELET_STATE_WALKING_DOWN);
	}
	else if (y >= BOTTOM_LIMIT && vy > 0) {
		SetState(EYELET_STATE_WALKING_UP);
	}*/
}

void CEyelet::Render()
{
	int ani;
	if (vx > 0)
		ani = EYELET_ANI_WALKING_RIGHT;
	else if (vx < 0)
		ani = EYELET_ANI_WALKING_LEFT;
	else ani = EYELET_ANI_DIE;

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CEyelet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case EYELET_STATE_DIE:
		y += EYELET_BBOX_HEIGHT - EYELET_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case EYELET_STATE_WALKING_RIGHT:
		vx = EYELET_WALKING_SPEED;

		break;
	case EYELET_STATE_WALKING_LEFT:
		vx = -EYELET_WALKING_SPEED;

		break;
	case EYELET_STATE_WALKING_UP:
		vy = -EYELET_WALKING_SPEED;

		break;
	case EYELET_STATE_WALKING_DOWN:

		vy = EYELET_WALKING_SPEED;
	}
}
