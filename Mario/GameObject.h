#pragma once
#include "Sprites.h"
#include "Animations.h"
using namespace std;

#define ID_TEX_BBOX -100		

class GameObject;
typedef GameObject* LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent* LPCOLLISIONEVENT;
struct CollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class GameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;
	int ny;

	STATEOBJECT state;
	TAG tag;
	TAG tagChange;
	TYPE type;			// type obj
	TYPE typeParent;	// type parent obj
	TYPE child;			// type child after destroy obj
	DWORD dt;

	bool isDead;
	bool canDel;
	bool isKicked;
	int TimeDead;
	bool canRespawn;

	bool isFlip;
	bool isShoot;
	bool canShoot;
	LPANIMATION_SET animation_set;

public:
	float widthBBox, heightBBox;
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	void SetWidthHeight(float w, float h) { this->widthBBox = w, this->heightBBox = h; }

	int GetState() { return this->state; }

	void RenderBoundingBox();
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);
	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }
	GameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(STATEOBJECT state) { this->state = state; }
	int GetNx() { return this->nx; }
	virtual void startTimeDead() { TimeDead = GetTickCount(); isDead = true; canRespawn = true; }
	bool IsCollisionAABB(RECT rect1, RECT rect2);
	RECT GetRect();
	~GameObject();
};

