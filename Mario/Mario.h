#include "GameObject.h"
#include "PlayerState.h"


class Mario : public GameObject 
{
private:
	static Mario* __instance;
public:
	Mario();
	PlayerState* state;
	TYPE level;
	int untouchable;
	DWORD untouchableTime;
	float speedJump;
	int stateBoundingBox;
	int alpha;

	bool isKicking;

	bool isShooting;
	bool canShoot;
	int countShoot;

	bool isSitting;
	bool isJumping;
	bool isJumpDone;

	bool canShortJump;
	bool canFallJump;

	bool isWhipping;
	bool canWhip;

	bool isRunning;
	bool isOnSky;
	bool canFly;
	bool isFlying;

	int startWalkingComplete;
	int startJumping;
	int walkingDirection;
	bool isWalkingComplete;
	bool isWaittingPressBtn;

	Animation* CurAnimation;
	unordered_map<STATENAME, bool> Allow;
	static Mario* GetInstance();
	STATENAME GetState() { return state->stateName; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void startWalkingDone() { startWalkingComplete = GetTickCount(); }
	void startJump() { startJumping = GetTickCount(); isJumpDone = false; }
	void SetLevel(TYPE level) { this->level = level; }
	void OnKeyUp(int key);
	void OnKeyDown(int key);
	void ChangeAnimation(PlayerState* newState);
	void Revival(float x, float y);

};