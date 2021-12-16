#include "Interrupt.h"


CInterrupt::CInterrupt()
{
	SetState(INTERRUPT_STATE_IDLE);
	//SetState(DRAP_STATE_WALKING_DOWN);
}

void CInterrupt::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + INTERRUPT_BBOX_WIDTH;

	if (state == INTERRUPT_STATE_DIE)
		bottom = y + INTERRUPT_BBOX_HEIGHT_DIE;
	else
		bottom = y + INTERRUPT_BBOX_HEIGHT;
}

void CInterrupt::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	
}

void CInterrupt::Render()
{
	int ani = INTERRUPT_ANI_IDLE;
	if (state == INTERRUPT_STATE_DIE) {
		ani = INTERRUPT_ANI_DIE;
	}
	else if(state == INTERRUPT_STATE_IDLE)
	{
		ani = INTERRUPT_ANI_IDLE;
	}else if(state = INTERRUPT_STATE_DROP)
		ani = INTERRUPT_ANI_DROP;

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CInterrupt::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case INTERRUPT_STATE_DIE:
		y += INTERRUPT_BBOX_HEIGHT - INTERRUPT_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case INTERRUPT_STATE_IDLE:
		break;
	case INTERRUPT_STATE_DROP:
		break;
	}
}

