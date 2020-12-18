#include "GameObject.h"
#include "PlayerState.h"
#include "Information.h"
class Mario : public GameObject 
{
private:
	static Mario* __instance;
public:
	float curY;
	PlayerState* state;
	
	TYPE level;
	TYPE typeScene;
	float  gravity;
	bool untouchable;
	DWORD untouchableTime;
	float speedJump;
	int stateBoundingBox;
	int alpha, beta;

	bool isKicking;
	bool isShooting;
	bool canShoot;
	int countShoot;

	float maxSpeedX;

	bool isSitting;

	bool isJumping;
	bool isJumpingShort;

	bool isJumpDone;
	int startJumping;

	bool canFallJump;

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
	bool IsTelePort;
	int scene_id = 1;
	int scene_trigger;
	bool IsTouchTrigger;
	int moveToTrigger;
	bool IsTouchPort;
	DWORD countTime;
	Information* infor;
	bool freeze;
	Animation* CurAnimation;
	unordered_map<STATEPLAYER, bool> Allow;
	static Mario* GetInstance();
	STATEPLAYER GetState() { return state->stateName; }
	Mario();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void ChangeScene(int Port);
	void startWalkingDone() { startWalkingComplete = GetTickCount(); }
	void startJump() { startJumping = GetTickCount(); isJumpDone = false; }
	void UpdateWithEnemy(LPCOLLISIONEVENT colliable_objects);
	void UpdateWithGround(LPCOLLISIONEVENT colliable_objects);
	void UpdateWithItem(LPCOLLISIONEVENT colliable_objects);
	void UpdateWithPortal(LPCOLLISIONEVENT colliable_objects);
	void SetLevel(TYPE level) { this->level = level; }
	void OnKeyUp(int key);
	void OnKeyDown(int key);
	void ChangeAnimation(PlayerState* newState);
	void Revival(float x, float y, int isInScene);
	void startTimeDead() { untouchableTime = GetTickCount(); untouchable = true; }
};