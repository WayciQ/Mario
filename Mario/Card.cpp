#include "Card.h"
#define TIME_CHANGE 2000
Card::Card() {
	getCard = 0;
	widthBBox = heightBBox = 32;
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