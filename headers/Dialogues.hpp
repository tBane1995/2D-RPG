#ifndef Dialogues_hpp
#define Dialogues_hpp

class DialogueOption {
public:
	std::wstring text;
	int nextDialogueID;

	DialogueOption(int nextDialogueID, std::wstring text) {
		this->nextDialogueID = nextDialogueID;
		this->text = text;
	}
};

class Dialogue {
public:
	int id;
	std::wstring text;
	std::vector < DialogueOption > options;

	Dialogue(int id, std::wstring text) {
		this->id = id;
		this->text = text;
	}
};

std::vector < Dialogue* > dialogues;
Dialogue* currentDialogue;
enum class dialogueStates { dialogue, choose };
dialogueStates dialogueState;
int chooseOption = 0;

Dialogue* getDialogue(int id) {
	for (auto& d : dialogues)
		if (d->id == id)
			return d;

	cout << "incorrect dialog id\n";
	return nullptr;
}


// variables used to render dialogues
float characterSize = 24;

float lineHeight = 24;
float padding = 10.0f;
sf::Vector2f dialogSize = sf::Vector2f(600, 160);
sf::Vector2f textPosition;
int countOfLines = 0;
int page = 0;
std::vector < wstring > lines;
std::vector < wstring > wrappedText;
std::vector < DialogueOption > availableOptions;
int dialogScroll;


void setTextToDialogBox(std::wstring text) {

	float maxWidth = dialogSize.x - 2.0f * padding;

	wrappedText = wrapText(text, characterSize, maxWidth);
	countOfLines = wrappedText.size();
}

void drawDialogBox(sf::RenderWindow* window, int currentPage = 0) {

	page = currentPage;	// global variable "page"

	sf::Texture dialogBoxTexture;
	if (!dialogBoxTexture.loadFromFile("assets/GUI/infoPanel.png")) {
		return;
	}

	sf::Sprite background;
	background.setTexture(dialogBoxTexture);
	background.setOrigin(dialogSize.x / 2.0f, dialogSize.y / 2.0f);
	background.setPosition(cam->position.x, cam->position.y + screenHeight / 2.0f - dialogSize.y / 2.0f);
	window->draw(background);

	for (int i = 0; i < 5; i++) {
		if (i + 5 * page >= wrappedText.size())
			break;

		sf::Text text = sf::Text(wrappedText[i + 5 * page], dialogBoxFont, characterSize);
		text.setFillColor(textColor);
		textPosition.x = background.getPosition().x - dialogSize.x / 2.f + padding;
		textPosition.y = background.getPosition().y - dialogSize.y / 2.f + float(i) * lineHeight + padding;
		text.setPosition(textPosition);

		window->draw(text);
	}

}

bool scriptResult(std::wstring text) {

	return true;

}

void drawChooseBox(sf::RenderWindow* window) {
	sf::Texture dialogBoxTexture;
	if (!dialogBoxTexture.loadFromFile("assets/GUI/infoPanel.png")) {
		return;
	}

	sf::Sprite background;
	background.setTexture(dialogBoxTexture);
	background.setOrigin(dialogSize.x / 2.0f, dialogSize.y / 2.0f);
	background.setPosition(cam->position.x, cam->position.y + screenHeight / 2.0f - dialogSize.y / 2.0f);
	window->draw(background);


	availableOptions.clear();
	for (auto& o : currentDialogue->options) {

		availableOptions.push_back(o);
	}

	for (int i = 0; i < 5; i++) {

		if (i + dialogScroll >= availableOptions.size())
			return;

		sf::Text text = sf::Text(availableOptions[i + dialogScroll].text, dialogBoxFont, characterSize);
		if (i == chooseOption)
			text.setFillColor(textActiveColor);
		else
			text.setFillColor(textColor);
		textPosition.x = background.getPosition().x - dialogSize.x / 2.f + padding;
		textPosition.y = background.getPosition().y - dialogSize.y / 2.f + float(i) * lineHeight + padding;
		text.setPosition(textPosition);

		window->draw(text);

	}


}

void loadDialogue(int dialogID) {

	string textID = to_string(dialogID);

	while (textID.size() < 3)
		textID = "0" + textID;

	string filename = "dialogues/" + textID + ".txt";

	ifstream file(filename);
	if (!file.is_open()) {
		cout << "cant open dialogue " << filename << "\n";
		return;
	}

	string lineUTF8;
	getline(file, lineUTF8);
	std::istringstream lineStream(lineUTF8);

	cout << "\n";
	string textPart;
	lineStream >> std::quoted(textPart);

	std::cout << '\n';

	// stworzenie dialogu
	Dialogue* dial = new Dialogue(dialogID, ConvertUtf8ToWide(textPart));

	int id = -1;
	char comma;

	// wczytanie odpowiedzi do dialogu
	while (std::getline(file, lineUTF8)) {

		std::istringstream lineStream(lineUTF8);
		lineStream >> id >> comma;
		lineStream >> quoted(textPart);	// wczytywanie between cudzysłowami " "
		dial->options.push_back(DialogueOption(id, ConvertUtf8ToWide(textPart)));
	}

	// dodanie dialogu do listy wszystkich dialogow
	dialogues.push_back(dial);

	file.close();
}

void setDialogue(int id) {

	gameState = gameStates::dialogue;
	dialogueState = dialogueStates::dialogue;
	currentDialogue = getDialogue(id);
	page = 0;
}

void setDialogue(Dialogue* dial) {

	gameState = gameStates::dialogue;
	dialogueState = dialogueStates::dialogue;
	currentDialogue = dial;
	page = 0;
}

void loadDialogues() {
	dialogues.clear();

	// LOADING THE DIALOGUES FROM FILES

	loadDialogue(0);	// WELCOME DIALOG

	loadDialogue(1);
	loadDialogue(2);
	loadDialogue(3);

	loadDialogue(4);
	loadDialogue(12);

	loadDialogue(5);
	loadDialogue(6);
	loadDialogue(7);
	loadDialogue(8);
	loadDialogue(9);
	loadDialogue(10);
	loadDialogue(11);
	loadDialogue(12);

	loadDialogue(13);
	loadDialogue(14);
	loadDialogue(15);

}
#endif