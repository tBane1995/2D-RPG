#ifndef Quests_hpp
#define Quests_hpp

enum class questCondition { currentHP, dialogue, haveArmor, haveHelmet, havePants, position_x, position_y };
enum class questState { unstarted, actual, ended };

class Step {
public:
	questCondition condition;
	string value;

	Step(questCondition condition, string value) {
		this->condition = condition;
		this->value = value;
	}

	bool check() {

		if (condition == questCondition::currentHP) {
			if(player->HP >= atoi(value.c_str()))
				return true;
		}

		if (condition == questCondition::dialogue) {
			setDialogue(atoi(value.c_str()));
			return true;
		}

		if (condition == questCondition::haveArmor) {
			if (value == "true") {
				if (player->armor != nullptr)
					return true;
			}

			if (value == "false") {
				if (player->armor == nullptr)
					return true;
			}
		}

		if (condition == questCondition::haveHelmet) {
			if (value == "true") {
				if (player->helmet != nullptr)
					return true;
			}

			if (value == "false") {
				if (player->helmet == nullptr)
					return true;
			}
		}

		if (condition == questCondition::havePants) {
			if (value == "true") {
				if (player->pants != nullptr)
					return true;
			}

			if (value == "false") {
				if (player->pants == nullptr)
					return true;
			}
		}

		if (condition == questCondition::position_x)
		{
			if (abs(player->position.x - atoi(value.c_str())) < 50) {
				return true;
			}
		}

		if (condition == questCondition::position_y)
		{
			if (abs(player->position.y - atoi(value.c_str())) < 50) {
				return true;
			}
		}

		return false;
	}

};

class Quest {
public:
	int id;
	string name;
	questState state;
	std::vector < Step* > steps;
	int currentStep;

	Quest(int id, string name) {
		
		this->id = id;
		this->name = name;
		steps.clear();
		state = questState::unstarted;
		currentStep = 0;

	}
	
	void addStep(questCondition condition, string value) {
		Step* step = new Step(condition, value);
		steps.push_back(step);
	}

	void check() {

		if (currentStep >= steps.size() - 1)
			state = questState::ended;

		if (steps[currentStep]->check())
			currentStep++;
		
	}


};

std::vector < Quest* > quests;

void loadQuests() {
	quests.clear();

	Quest* quest1 = new Quest(0, "Zjedz coś, ubierz się a potem pójdź w wyznaczone miejsce");
	quest1->addStep(questCondition::currentHP, "80");
	quest1->addStep(questCondition::dialogue, "13");
	quest1->addStep(questCondition::haveArmor, "true");
	quest1->addStep(questCondition::haveHelmet, "true");
	quest1->addStep(questCondition::havePants, "true");
	quest1->addStep(questCondition::dialogue, "14");
	quest1->addStep(questCondition::position_x, "2750");
	quest1->addStep(questCondition::position_y, "340");
	quest1->addStep(questCondition::dialogue, "15");
	quest1->state = questState::actual;
	quests.push_back(quest1);



}

void checkQuests() {

	for (auto& quest : quests) {

		if (quest->state == questState::actual) {
			quest->check();

		}

	}

}


#endif