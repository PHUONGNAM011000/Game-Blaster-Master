#include "Tank_Wheel.h"
#include <algorithm>
#include "PlayScene.h"


Tank_Wheel::Tank_Wheel(int part)
{
	this->part = part;
}

void Tank_Wheel::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void Tank_Wheel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);

	CSoPhia* SOPHIA = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (part)
	{
	case TANKWHEEL_LEFT_WHEEL:
		x = SOPHIA->x + TANKWHEEL_WHEEL_DISTANT_X_1;
		break;
	case TANKWHEEL_RIGHT_WHEEL:
		x = SOPHIA->x + TANKWHEEL_WHEEL_DISTANT_X_2;
		break;
	}
	y = SOPHIA->y + TANKWHEEL_WHEEL_DISTANT_Y;

	x += dx;
	y += dy;

}


void Tank_Wheel::Render()
{
	CSoPhia* SOPHIA = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	int ani = 0;

	if (SOPHIA->vx > 0)
	{
		switch (part)
		{
		case TANKWHEEL_TURRET:
			ani = TURRET_ANI_IDLE_RIGHT;
			pre_ani = ani;
			break;
		case TANKWHEEL_RIGHT_WHEEL:
			ani = WHEELING_ANI_RIGHT;
			break;
		case TANKWHEEL_LEFT_WHEEL:
			ani = WHEELING_ANI_RIGHT;
			break;
		}
	}

	else if (SOPHIA->vx < 0)
	{
		switch (part)
		{
		case TANKWHEEL_TURRET:
			ani = TURRET_ANI_IDLE_LEFT;
			pre_ani = ani;
			break;
		case TANKWHEEL_RIGHT_WHEEL:
			ani = WHEELING_ANI_LEFT;
			break;
		case TANKWHEEL_LEFT_WHEEL:
			ani = WHEELING_ANI_LEFT;
			break;
		}
	}

	else if (SOPHIA->vx == 0)
	{
		if (part != TANKWHEEL_TURRET)
			ani = WHEELING_ANI_IDLE;
		else
			ani = pre_ani;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Tank_Wheel::SetState(int state)
{
	CGameObject::SetState(state);
	//switch (state)
	//{
	//case TANKWHEEL_STATE_DIE:
	//	vx = FIRE_BALL_STATE_DIE_VX;
	//	vy = FIRE_BALLSTATE_DIE_VY;
	//	break;

	//}

}
