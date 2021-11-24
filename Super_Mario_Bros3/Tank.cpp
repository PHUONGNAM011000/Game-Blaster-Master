#include "Tank.h"
#include <algorithm>
#include "PlayScene.h"


Tank::Tank(int part)
{
	this->part = part;
}

void Tank::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + TANK_BBOX_WIDTH;
	if (state == TANK_STATE_DIE)
		y = y + TANK_BBOX_HEIGHT;
	else bottom = y + TANK_BBOX_HEIGHT;
}

void Tank::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != TANK_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	CTank_Body* TANK_BODY = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (part)
	{
	case TANK_LEFT_WHEEL:
		x = TANK_BODY->x - TANK_WHEEL_DISTANT_X;
		break;
	case TANK_RIGHT_WHEEL:
		x = TANK_BODY->x + TANK_WHEEL_DISTANT_X;
		break;
	case TANK_TURRET:
		x = TANK_BODY->x - TANK_TURRET_DISTANT_X;
		break;
	}
	if (part == TANK_TURRET)
		y = TANK_BODY->y - TANK_TURRET_DISTANT_Y;
	else
		y = TANK_BODY->y + TANK_WHEEL_DISTANT_Y;

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
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Tank::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));
		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}
	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void Tank::Render()
{
	CTank_Body* TANK_BODY = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int ani = 0;
	if (TANK_BODY->vx > 0)
	{
		switch (part)
		{
		case TANK_TURRET:
			ani = TURRET_ANI_IDLE_RIGHT;
			pre_ani = ani;
			break;
		case TANK_RIGHT_WHEEL:
			ani = WHEELING_ANI_RIGHT;
			break;
		case TANK_LEFT_WHEEL:
			ani = WHEELING_ANI_RIGHT;
			break;
		}
	}
	else if (TANK_BODY->vx < 0)
	{
		switch (part)
		{
		case TANK_TURRET:
			ani = TURRET_ANI_IDLE_LEFT;
			pre_ani = ani;
			break;
		case TANK_RIGHT_WHEEL:
			ani = WHEELING_ANI_LEFT;
			break;
		case TANK_LEFT_WHEEL:
			ani = WHEELING_ANI_LEFT;
			break;
		}
	}
	else if (TANK_BODY->vx == 0)
	{
		if (part != TANK_TURRET)
			ani = WHEELING_ANI_IDLE;
		else
			ani = pre_ani;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Tank::SetState(int state)
{
	CGameObject::SetState(state);
	//switch (state)
	//{
	//case TankParts_STATE_DIE:
	//	vx = FIRE_BALL_STATE_DIE_VX;
	//	vy = FIRE_BALLSTATE_DIE_VY;
	//	break;

	//}

}
