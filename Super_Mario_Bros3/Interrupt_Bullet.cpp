#include "Interrupt_Bullet.h"
#include <algorithm>
#include "PlayScene.h"
#include "Brick.h"

CInterrup_Bullet::CInterrup_Bullet()
{
	SetState(CINTERRUPT_BULLET_STATE_IDLE);
	nx = 0;
}

void CInterrup_Bullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CINTERRUPT_BULLET_BBOX_WIDTH;

	if (state == CINTERRUPT_BULLET_STATE_DIE)
		y = y + CINTERRUPT_BULLET_BBOX_HEIGHT;
	else bottom = y + CINTERRUPT_BULLET_BBOX_HEIGHT;
}

void CInterrup_Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* playscene = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene());
	CGameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != CINTERRUPT_BULLET_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	else
	{
		isUsed = false;
		x = STORING_LOCATION;
		y = STORING_LOCATION;
		SetState(CINTERRUPT_BULLET_STATE_DIE);
	}
	if (isUsed == false)
	{
		if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->CheckCInterrupt_FiringList())
		{
			this->SetPosition(playscene->GetCInterrupt_FiringList()->getInterrupt_FiringPoisitionX(), playscene->GetCInterrupt_FiringList()->getInterrupt_FiringPoisitionY());
			playscene->DeleteCInterrupt_FiringList();
			isUsed = true;
			SetState(CINTERRUPT_BULLET_STATE_IDLE);
		}
	}
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba
			{
				SetState(CINTERRUPT_BULLET_STATE_DIE);
				playscene->AddWormSpamMng(this->x, this->y);
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		if (x <= 0)
			if (vx < 0)
				vx = -vx;
	}
}

void CInterrup_Bullet::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));
		if (!dynamic_cast<CBrick*>(e->obj))
		{
			continue;
		}
		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}
	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CInterrup_Bullet::Render()
{
	int ani = 0;

	switch (state)
	{
	case CINTERRUPT_BULLET_STATE_IDLE:
		ani = CINTERRUPT_BULLET_ANI_IDLE;
		break;
	case CINTERRUPT_BULLET_STATE_DIE:
		return;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CInterrup_Bullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CINTERRUPT_BULLET_STATE_IDLE:
		vy = CINTERRUPT_BULLET_SPEED;
		break;

	}

}