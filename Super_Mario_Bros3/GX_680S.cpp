#include "GX_680S.h"
CGX_680S::CGX_680S()
{
	SetState(STATE_IDLE);
}

void CGX_680S::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GX680S_BBOX_WIDTH;

	if (state == GX680S_STATE_DIE)
		bottom = y + GX680S_BBOX_HEIGHT_DIE;
	else
		bottom = y + GX680S_BBOX_HEIGHT;
}

void CGX_680S::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;
}

void CGX_680S::Render()
{
	if (state != STATE_DIE)
	{
		int ani = GX680S_ANI;

		animation_set->at(ani)->Render(x, y);

		//RenderBoundingBox();
	}
}

void CGX_680S::SetState(int state)
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
