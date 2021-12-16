#include "Tank_Body.h"
#include <algorithm>
#include "PlayScene.h"
#include "DefinePlayer.h"


Tank_Body::Tank_Body()
{
}

void Tank_Body::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void Tank_Body::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);

	CSoPhia* SOPHIA = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	x = SOPHIA->x + BODY_DISTANT_X;

	y = SOPHIA->y + BODY_DISTANT_Y;

	x += dx;
	y += dy;

}


void Tank_Body::Render()
{
	CSoPhia* SOPHIA = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	int ani = 0;

	ani = TANKBODY_ANI_IDLE;

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Tank_Body::SetState(int state)
{
	CGameObject::SetState(state);
	//switch (state)
	//{
	//case TANKBODY_STATE_DIE:
	//	vx = FIRE_BALL_STATE_DIE_VX;
	//	vy = FIRE_BALLSTATE_DIE_VY;
	//	break;

	//}

}
