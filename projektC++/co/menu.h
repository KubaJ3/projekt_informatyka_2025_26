#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class Menu {
private:
	sf::Font font;
	sf::Text tytul;
	std::vector<sf::Text> options;
	float m_width;
	float m_height;
	int selected = 0;

	void centerText(sf::Text& t, float x, float y) {
		sf::FloatRect b = t.getLocalBounds();
		t.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
		t.setPosition(x, y);
	}

	void updateOptionColors() {
		for (size_t i = 0; i < options.size(); ++i) {
			if (static_cast<int>(i) == selected)
				options[i].setFillColor(sf::Color::Yellow);
			else
				options[i].setFillColor(sf::Color::White);
		}
	}

public:
	Menu(float width, float height) : m_width(width), m_height(height) {
		if (!font.loadFromFile("ARIAL.TTF")) {
			std::cout << "ERROR: Nie mozna wczytaæ ARIAL.TTF!" << std::endl;
		}

		tytul.setFont(font);
		tytul.setString("Super Gra");
		tytul.setCharacterSize(50);
		tytul.setFillColor(sf::Color::White);
		centerText(tytul, width / 2.f, height / 2.f - 120.f);

		options.resize(3);

		options[0].setFont(font);
		options[0].setString("START");
		options[0].setCharacterSize(30);
		centerText(options[0], width / 2.f, height / 2.f - 20.f);

		options[1].setFont(font);
		options[1].setString("WCZYTAJ GRE");
		options[1].setCharacterSize(30);
		centerText(options[1], width / 2.f, height / 2.f + 20.f);

		options[2].setFont(font);
		options[2].setString("EXIT");
		options[2].setCharacterSize(30);
		centerText(options[2], width / 2.f, height / 2.f + 60.f);

		updateOptionColors();
	}

	void moveUp() {
		if (selected > 0) --selected;
		updateOptionColors();
	}

	void moveDown() {
		if (selected + 1 < static_cast<int>(options.size())) ++selected;
		updateOptionColors();
	}

	int getSelectedIndex() const {
		return selected;
	}

	void setInfo(const std::string& s) {
		tytul.setString(s);
		centerText(tytul, m_width / 2.f, m_height / 2.f - 120.f);
	}

	void render(sf::RenderWindow& window) {
		window.draw(tytul);
		for (auto& o : options) window.draw(o);
	}
};