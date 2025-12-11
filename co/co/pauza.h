#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "gamestate.h"
#include "gra.h"
#include "menu.h"

class Gra;
class Menu;

class Pauza {
public:
	Pauza(const std::string& fontFile = "ARIAL.TTF");

	void setCenter(float x, float y);
	void setMessage(const std::string& s);

	bool isLoaded() const;
	const sf::Font& getFont() const;

	void render(sf::RenderTarget& target) const;

	void processEvent(GameState& currentState, const sf::Event& event, Gra& gra, Menu& menu);

private:
	void updateOrigin();

	sf::Font font_;
	sf::Text text_;
	sf::Vector2f center_;
	bool loaded_;
};

Pauza::Pauza(const std::string& fontFile) : center_{ 0.f, 0.f }, loaded_{ false } {
	loaded_ = font_.loadFromFile(fontFile);
	if (!loaded_) {
		std::cout << "Nie dziala tekst" << std::endl;
	}
	else {
		text_.setFont(font_);
		text_.setString("PAUZA\nnacisnij P, aby wznowic\nnacisnij O, aby zapisac");
		text_.setCharacterSize(28);
		text_.setFillColor(sf::Color::White);
		updateOrigin();
	}
}

void Pauza::setCenter(float x, float y) {
	center_.x = x;
	center_.y = y;
	updateOrigin();
}

void Pauza::setMessage(const std::string& s) {
	text_.setString(s);
	updateOrigin();
}

bool Pauza::isLoaded() const {
	return loaded_;
}

const sf::Font& Pauza::getFont() const {
	return font_;
}

void Pauza::render(sf::RenderTarget& target) const {
	if (loaded_) {
		target.draw(text_);
	}
}

void Pauza::processEvent(GameState& currentState, const sf::Event& event, Gra& gra, Menu& menu) {
	if (event.type != sf::Event::KeyPressed) return;

	using Key = sf::Keyboard;

	if (currentState == GameState::Playing) {
		if (event.key.code == Key::P) {
			currentState = GameState::Paused;
			menu.setInfo("PAUZA");
		}
		else if (event.key.code == Key::Escape) {
			currentState = GameState::Menu;
		}
	}
	else if (currentState == GameState::Paused) {
		if (event.key.code == Key::P) {
			currentState = GameState::Playing;
		}
		else if (event.key.code == Key::Escape) {
			currentState = GameState::Menu;
		}
		else if (event.key.code == Key::O) {
			GameData snapshot;
			snapshot.capture(gra.getPaletka(), gra.getPilka(), gra.getKlocki());
			if (snapshot.SaveToFile("zapiski.txt"))
				std::cout << "Save\n";
			else
				std::cout << "Blad\n";
		}
	}
}
void Pauza::updateOrigin() {
	sf::FloatRect b = text_.getLocalBounds();
	text_.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
	text_.setPosition(center_);
}

