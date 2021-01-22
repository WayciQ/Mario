#include "Card.h"
#include "Grid.h"
#include "Alert.h"
#define TIME_CHANGE 2000
#define BBOX 2 * UNIT_GAME
Card::Card() {
	getCard = 0;

	SetBBox(BBOX, BBOX);
	this->type = CARD;
	timeChange = GetTickCount();
	animation_set = animationsSets->Get(type);
}

void Card::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (GetTickCount() - timeChange > TIME_CHANGE) {
		timeChange = GetTickCount();
		if (getCard >= 2) {
			getCard = 0;
		}
		else {
			getCard++;
		}
		DebugOut(L"card: %d\n", getCard);
	}

	switch (getCard)
	{
	case 0:
		typeCard = CARD_MUSHROOM;
		break;
	case 1:
		typeCard = CARD_FLOWER;
		break;
	case 2:
		typeCard = CARD_STAR;
		break;
	}
	CurAnimation = animation_set->Get(typeCard);
	
}