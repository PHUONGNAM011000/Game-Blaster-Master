#include "Tank_Turret.h"
#include <algorithm>
#include "PlayScene.h"
#include "DefinePlayer.h"


Tank_Turret::Tank_Turret()
{
}

void Tank_Turret::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void Tank_Turret::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);

	CSoPhia* SOPHIA = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	x = SOPHIA->x + TURRET_DISTANT_X;

	y = SOPHIA->y + TURRET_DISTANT_Y;

	x += dx;
	y += dy;

}


void Tank_Turret::Render()
{
	CSoPhia* SOPHIA = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	int ani = pre_ani;

	if (SOPHIA->vx > 0)
	{
		ani = TURRET_ANI_IDLE_RIGHT;
		pre_ani = ani;
	}
	else if (SOPHIA->vx < 0) {
		ani = TURRET_ANI_IDLE_LEFT;
		pre_ani = ani;
	}

	else ani = pre_ani;

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Tank_Turret::SetState(int state)
{
	CGameObject::SetState(state);
	//switch (state)
	//{
	//case TANKTURRET_STATE_DIE:
	//	vx = FIRE_BALL_STATE_DIE_VX;
	//	vy = FIRE_BALLSTATE_DIE_VY;
	//	break;

	//}

}
