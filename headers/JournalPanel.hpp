#ifndef JournalPanel_hpp
#define JournalPanel_hpp

class JournalPanel {
public:

	sf::Sprite panel;
	std::vector < sf::Text > titles;
	sf::Text description;

	JournalPanel() {
		panel = sf::Sprite();
		panel.setTexture(*getTexture("GUI/journalTexture")->texture);
		panel.setOrigin(300, 200);

		titles.clear();
		for (int i = 0; i < 18; i++) {
			titles.emplace_back();
			titles[i].setFont(basicFont);
			titles[i].setFillColor(sf::Color::White);
			titles[i].setCharacterSize(20);
			titles[i].setString(L"test title");
			if (i < quests.size())
				titles[i].setString(quests[i]->name);

		}

		description = sf::Text();
		description.setFont(basicFont);
		description.setFillColor(sf::Color::White);
		description.setCharacterSize(20);
		if(quests[0]->state == questState::actual)
			description.setString(quests[0]->steps[quests[0]->currentStep]->text);
	}

	void update() {

		panel.setPosition(cam->position);

		int i=0;
		float w, h;
		for (auto& title : titles) {
			w = title.getLocalBounds().getSize().x;
			h = title.getLocalBounds().getSize().y;
			title.setOrigin(w/2.0f, h/2.0f);
			title.setPosition(cam->position.x-250, cam->position.y + (20 * i++) - 180);
		}
			
		description.setPosition(cam->position);
	}

	void draw() {

		window->draw(panel);

		for (auto& title : titles)
			window->draw(title);

		window->draw(description);
	}

};

JournalPanel* journal = nullptr;

#endif