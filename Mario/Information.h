#pragma once
#include"GameGlobal.h"
class Information
{
private:
	int world_id;
	int timeGame;
	int scorePoint;
	int money;
	int life;
	STATEOBJECT card_1;
	STATEOBJECT card_2;
	STATEOBJECT card_3;
	int countCard;
	int scene_id;
	int gate_id;
public:
	Information() {
		world_id = 1;
		timeGame = 300;
		scorePoint = 0;
		money = 0;
		life = 4;
		card_1 = card_2 = card_3 = CARD_EMPTY;
		countCard = 0;
		scene_id = 0;
		gate_id = 0;
	}
	int GetWoldId() { return world_id; }
	void SetWorldId(int id) { world_id = id; }
	int GetSceneId() { return scene_id; }
	void SetSceneId(int id) { scene_id = id; }
	int GetGateId() { return gate_id; }
	void SetGateId(int id) { gate_id = id; }
	int GetGameTime() { return timeGame; }
	void CalcTimeGame(int time) { timeGame += time; }
	void SetGameTime(int time) { timeGame = time; }
	void MoneyEarn(int money) { this->money += money; }
	int GetMoney() { return money; }
	void ScoreEarn(int scorepoint) { scorePoint += scorepoint; }
	int GetScorePoint() { return scorePoint; }
	void LifeEarn(int lifec) { life += lifec; }
	int GetLife() { return life; }
	void AddCard(STATEOBJECT typeCard) {

		switch (countCard)
		{
		case 0:
			card_1 = typeCard;
			break;
		case 1:
			card_2 = typeCard;
			break;
		case 2:
			card_3 = typeCard;

			break;
		default:
			DebugOut(L"Cannot Add Card\n");
			break;
		}
		if (countCard >= 2) {
			CalsCard();
			ResetListCard();
		}
		else {
			countCard++;
		}
	}
	void ResetListCard() {
		card_1 = card_2 = card_3 = CARD_EMPTY;
		countCard = 0;
	}
	STATEOBJECT GetCard(int id) {
		switch (id)
		{
		case 1:
			return card_1;
			break;
		case 2:
			return card_2;
			break;
		case 3:
			return card_3;
			break;
		}
	}
	void CalsCard() {
		if (card_1 != card_2 || card_1 != card_3 || card_2 != card_3) {
			LifeEarn(1);
		}
		else if (card_1 == card_2 && card_1 == card_3 && card_1 == CARD_MUSHROOM) {
			LifeEarn(2);
		}
		else if (card_1 == card_2 && card_1 == card_3 && card_1 == CARD_FLOWER) {
			LifeEarn(3);
		}
		else if (card_1 == card_2 && card_1 == card_3 && card_1 == CARD_STAR) {
			LifeEarn(5);
		}
	}
};

