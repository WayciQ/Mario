#include "GameObject.h"
#include "PlayerState.h"
#include "Information.h"
class Mario : public GameObject 
{
private:
	static Mario* __instance;
public:

	bool immortal;
	float currentLocationY;
	PlayerState* state;
	TYPE level;
	TYPE WorldMapScene;
	float  gravity;
	bool untouchable;
	DWORD untouchableTime,FreezeTime;
	float speedJump;
	int stateBoundingBox;
	int alpha, beta;
	bool isShooting;
	bool canShoot;
	int countShoot;


	bool isSitting;

	bool isJumping;
	bool isFalling;

	bool isJumpDone;
	DWORD startJumping;
	DWORD startTimeFly;
	bool isWavingTail;
	bool isWhipping;
	bool canWhip;
	
	bool isRunning;

	bool isOnSky;

	bool isFlying;
	bool isFlyingPush;

	bool isPicking;
	bool canPicking;

	int startWalkingComplete;
	int walkingDirection;
	bool isWalkingComplete;
	bool isWaittingPressBtn;

	bool IsChangeTrigger;
	bool IsChangeScene;
	int gateScene;

	bool IsTouchTrigger;
	int moveToTrigger;
	bool IsTouchPort;

	DWORD countRealTime;
	Information* infor;
	bool isFreezeTime;
	Animation* CurAnimation;
	unordered_map<STATEPLAYER, bool> Allow;
	static Mario* GetInstance();
	Mario();
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void startWalkingDone() { startWalkingComplete = GetTickCount(); }
	void startJump() { startJumping = GetTickCount(); isJumpDone = false; }
	STATEPLAYER GetState() { return state->stateName; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void CollisionAtCreate(LPGAMEOBJECT object);
	void UpdateWithEnemy(LPCOLLISIONEVENT colliable_objects);
	void UpdateWithGround(LPCOLLISIONEVENT colliable_objects);
	void UpdateWithItem(LPCOLLISIONEVENT colliable_objects);
	void UpdateWithGate(LPCOLLISIONEVENT colliable_objects);
	void SetLevel(TYPE level) { this->level = level; }
	void OnKeyUp(int key);
	void OnKeyDown(int key);
	void ChangeState(PlayerState* newState);
	void Revival(float x, float y, int isInScene);
	void startTimeChangeState() { untouchableTime = GetTickCount(); untouchable = true; }
	void startTimeFreeze() { FreezeTime = GetTickCount(); isFreezeTime = true; }
	void StartTimeFly() { startTimeFly = GetTickCount(); isFlying = true; }
};