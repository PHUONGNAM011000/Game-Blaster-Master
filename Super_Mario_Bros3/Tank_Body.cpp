#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "TANK_BODY.h"
#include "Game.h"

#include "Eyelet.h"
#include "Interrupt.h"
#include "Portal.h"

CTank_Body::CTank_Body(float x, float y) : CGameObject()
{
	untouchable = 0;
	SetState(TANK_BODY_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}

void CTank_Body::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += TANK_BODY_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != TANK_BODY_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > TANK_BODY_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
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

		// how to push back TANK_BODY if collides with a moving objects, what if TANK_BODY is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CInterrupt*>(e->obj)) // if e->obj is Goomba 
			{
				CInterrupt* goomba = dynamic_cast<CInterrupt*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->nx != 0|| e->ny != 0)
				{
					if (goomba->GetState() != INTERRUPT_STATE_DIE)
					{
						goomba->SetState(INTERRUPT_STATE_DIE);
						//goomba->x = 999999;
						//vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
			}
			if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CTank_Body::Render()
{

	int ani = -1;
	if (state == TANK_BODY_STATE_DIE)
		ani = TANK_BODY_ANI_DIE;
	else
	{
		if (vx == 0)
		{
			if (nx > 0) ani = TANK_BODY_ANI_BIG_IDLE_RIGHT;
			else ani = TANK_BODY_ANI_BIG_IDLE_LEFT;
		}
		else if (vx > 0)
			ani = TANK_BODY_ANI_BIG_WALKING_RIGHT;
		else ani = TANK_BODY_ANI_BIG_WALKING_LEFT;

	}
	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	//RenderBoundingBox();
}

void CTank_Body::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case TANK_BODY_STATE_WALKING_DOWN:
		vy = TANK_BODY_WALKING_SPEED;
		break;
	case TANK_BODY_STATE_WALKING_UP:
		vy = -TANK_BODY_WALKING_SPEED;
		break;
	case TANK_BODY_STATE_WALKING_RIGHT:
		vx = TANK_BODY_WALKING_SPEED;
		nx = 1;
		break;
	case TANK_BODY_STATE_WALKING_LEFT:
		vx = -TANK_BODY_WALKING_SPEED;
		nx = -1;
		break;
	case TANK_BODY_STATE_JUMP:
		// TODO: need to check if TANK_BODY is *current* on a platform before allowing to jump again
		vy = -TANK_BODY_JUMP_SPEED_Y;
		break;
	case TANK_BODY_STATE_IDLE:
		vx = 0;
		//vy = 0;
		break;
	case TANK_BODY_STATE_DIE:
		vy = TANK_BODY_DIE_DEFLECT_SPEED;
		break;
	}
}

void CTank_Body::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x-10;
	top = y-3;

	right = x + TANK_BODY_BIG_BBOX_WIDTH ;
	bottom = y + TANK_BODY_BIG_BBOX_HEIGHT;

	DebugOut(L"L T R B %f %f %f %f  \n", left, top, right, bottom);
}

/*
	Reset TANK_BODY status to the beginning state of a scene
*/
void CTank_Body::Reset()
{
	SetState(TANK_BODY_STATE_IDLE);
	SetLevel(TANK_BODY_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CTank_Body::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	vector <LPCOLLISIONEVENT> collisionEvents;
	CTank_Body* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (dynamic_cast<CTank_Bullet*>(e->obj))
		{
			continue;
		}

		if (e->t > 0 && e->t <= 1.0f)
			collisionEvents.push_back(e);
		else
			delete e;
	}

	std::sort(collisionEvents.begin(), collisionEvents.end(), CCollisionEvent::compare);

	for (UINT i = 0; i < collisionEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(collisionEvents[i]->obj);
		if (e->t > 0 && e->t <= 1.0f)
		{
			coEvents.push_back(e);
		}
		else
			delete e;
	}
}

