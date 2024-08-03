#ifndef Fonts_hpp
#define Fonts_hpp


sf::Font basicFont;
sf::Font dialogBoxFont;

sf::Color textDialogueColor = sf::Color(234, 224, 175);
sf::Color textNameColor = sf::Color::White;
sf::Color titleColor = sf::Color::White;

void loadFonts() {
	basicFont = sf::Font();
	basicFont.loadFromFile("assets/fonts/arial.ttf");

	dialogBoxFont = sf::Font();
	dialogBoxFont.loadFromFile("assets/fonts/CascadiaCode.ttf");

}


std::wstring ConvertUtf8ToWide(const std::string& utf8Str) {
    // TO-DO
    int wideCharCount = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), utf8Str.size(), nullptr, 0);
    if (wideCharCount == 0) {
        throw std::runtime_error("Error in MultiByteToWideChar");
    }

    std::wstring wideStr(wideCharCount, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), utf8Str.size(), &wideStr[0], wideCharCount);
    return wideStr;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Zmieniamy start_pos o długość "to" aby uniknąć zapętlenia
    }
}

std::vector < std::wstring > wrapText(std::wstring text, int characterSize, int maxWidth) {
    
    std::vector < std::wstring > wrappedText;

    wrappedText.clear();

	std::wistringstream wordsStream(text);
	std::wstring word;
	std::wstring currentLine;

	while (wordsStream >> word) {
		
		std::wstring testLine = currentLine.empty() ? word : currentLine + L" " + word;
		sf::Text testText(testLine, dialogBoxFont, characterSize);
		
		if (testText.getLocalBounds().width > maxWidth) {
			wrappedText.push_back(currentLine);
			currentLine = word;
		}
		else {
			currentLine = testLine;
		}
	}

	if (!currentLine.empty()) {
		wrappedText.push_back(currentLine);
	}

	return wrappedText;
}

#endif