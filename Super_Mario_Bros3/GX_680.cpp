#include "GX_680.h"

CGX_680::CGX_680()
{
	SetState(GX680_STATE_WALKING_UP);
}

void CGX_680::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GX680_BBOX_WIDTH;

	if (state == GX680_STATE_DIE)
		bottom = y + GX680_BBOX_HEIGHT_DIE;
	else
		bottom = y + GX680_BBOX_HEIGHT;
}

void CGX_680::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	/*x += dx;
	y += dy;

	if (x <= LEFT_LIMIT && vx < 0) {
		SetState(GX680_STATE_WALKING_RIGHT);
	}
	else if (x >= RIGHT_LIMIT && vx > 0) {
		SetState(GX680_STATE_WALKING_LEFT);
	}
	else if (y <= TOP_LIMIT && vy < 0) {
		SetState(GX680_STATE_WALKING_DOWN);
	}
	else if (y >= BOTTOM_LIMIT && vy > 0) {
		SetState(GX680_STATE_WALKING_UP);
	}*/



}

void CGX_680::Render()
{
	int ani = GX680_ANI_WALKING;
	if (state == GX680_STATE_DIE) {
		ani = GX680_ANI_DIE;
	}
	else
		ani = GX680_ANI_WALKING;



	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CGX_680::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GX680_STATE_DIE:
		y += GX680_BBOX_HEIGHT - GX680_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case GX680_STATE_WALKING_LEFT:
		vx = -GX680_WALKING_SPEED;
		break;
	case GX680_STATE_WALKING_RIGHT:
		vx = GX680_WALKING_SPEED;
		break;
	case GX680_STATE_WALKING_UP:
		vy = -GX680_WALKING_SPEED;
		break;
	case GX680_STATE_WALKING_DOWN:
		vy = GX680_WALKING_SPEED;
		break;
	}

}


