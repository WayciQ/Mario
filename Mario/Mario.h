#include "GameObject.h"
#include "PlayerState.h"
#define MARIO_ANI_IDLE_RIGHT		0
#define MARIO_ANI_IDLE_LEFT			1
#define MARIO_ANI_WALKING_RIGHT		2
#define MARIO_ANI_WALKING_LEFT		3
#define MARIO_ANI_JUMP_RIGHT		4	
#define MARIO_ANI_FALL_RIGHT		5
#define MARIO_ANI_JUMP_LEFT			6
#define MARIO_ANI_FALL_LEFT			7
#define MARIO_ANI_SIT_RIGHT			8
#define MARIO_ANI_SIT_LEFT			9
#define MARIO_ANI_FIGHT_RIGHT		10
#define MARIO_ANI_FIGHT_LEFT		11
#define MARIO_ANI_DIE				12

class PlayerState;
class GameObject;
class Whip;
class Mario : public GameObject 
{
private:
	static Mario* __instance;
public:
	float ax; //inertia
	float speedPush;
	Mario();
	Whip* whip;
	PlayerState* state;
	int level;
	int untouchable;
	DWORD untouchableTime;
	int stateBoundingBox;
	int alpha;
	bool isSitting;
	bool isJumping;
	bool isWhipping;
	bool isShooting;
	int startWalkingComplete;
	int walkingDirection;
	bool isWalkingComplete;
	bool isWaittingPress;
	Animation* CurAnimation;
	std::unordered_map<STATENAME, bool> allow;
	static Mario* GetInstance();
	STATENAME GetState() { return state->stateName; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void startWalkingDone() { startWalkingComplete = GetTickCount(); }
	void HandleObject(LPGAMEOBJECT object);
	void OnKeyUp(int key);
	void OnKeyDown(int key);
	void SetLevel(int level) { this->level = level; }
	void ChangeAnimation(PlayerState* newState);

};