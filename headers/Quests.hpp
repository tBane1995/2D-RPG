#ifndef Quests_hpp
#define Quests_hpp

enum class questCondition { currentHP, showDialogue, haveArmor, haveHelmet, havePants, position_x, position_y };
enum class questState { unstarted, actual, ended };

class Step {
public:
	questCondition condition;
	string value;
	std::wstring text;

	Step(questCondition condition, string value, std::wstring text) {
		this->condition = condition;
		this->value = value;
		this->text = text;
	}

	bool check() {

		if (condition == questCondition::currentHP) {
			if(player->HP >= atoi(value.c_str()))
				return true;
		}

		if (condition == questCondition::showDialogue) {
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
	std::wstring name;
	questState state;
	std::vector < Step* > steps;
	int currentStep;

	Quest(int id, std::wstring name) {
		
		this->id = id;
		this->name = name;
		steps.clear();
		state = questState::unstarted;
		currentStep = 0;

	}
	
	void addStep(questCondition condition, string value, std::wstring text) {
		Step* step = new Step(condition, value, text);
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

	Quest* quest1 = new Quest(0, L"Zjedz coś.");
	quest1->addStep(questCondition::currentHP, "40", L"jestem głodny, powinienem coś zjeść");
	quest1->addStep(questCondition::showDialogue, "13", L"już się najadłem. Powinienem poszukać jakichś ubrań");
	quest1->addStep(questCondition::haveArmor, "true", L"powinienem ubrać koszule");
	quest1->addStep(questCondition::haveHelmet, "true", L"powinienem założyć czapkę");
	quest1->addStep(questCondition::havePants, "true", L"powiniene ubrać spodnie");
	quest1->addStep(questCondition::showDialogue, "14", L"ubralem się");
	quest1->addStep(questCondition::position_x, "2750", L"powinienem dojść na pozycję x");
	quest1->addStep(questCondition::position_y, "340", L"powinienem dojść na pozycję y ");
	quest1->addStep(questCondition::showDialogue, "15", L"ścieżka się skończyła, nie wiem co robić dalej.");
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