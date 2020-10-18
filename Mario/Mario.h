#include "GameObject.h"
#include "PlayerState.h"

class PlayerState;
class GameObject;
class Whip;

class Mario : public GameObject 
{
private:
	static Mario* __instance;
public:
	Mario();
	Whip* whip;
	PlayerState* state;
	TYPE level;
	int untouchable;
	DWORD untouchableTime;
	float speedJump;
	int stateBoundingBox;
	int alpha;
	bool isSitting;
	bool isJumping;
	bool isWhipping;
	bool isRunning;
	bool isShooting;
	bool isSitWalk;
	int startWalkingComplete;
	int walkingDirection;
	bool isWalkingComplete;
	bool isWaittingPressBtn;
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
	void SetLevel(TYPE level) { this->level = level; }
	void ChangeAnimation(PlayerState* newState);
	void Reset(float x, float y);

};