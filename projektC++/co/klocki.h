#pragma once 
#include <iostream>
#include <SFML/Graphics.hpp>

class Klocki {
private:
	sf::RectangleShape rect;
	int hp;
	bool alive = true;
	void updateColor() {
		switch (hp) {
		case 3:
			rect.setFillColor(sf::Color::Green);
			break;
		case 2:
			rect.setFillColor(sf::Color::Yellow);
			break;
		case 1:
			rect.setFillColor(sf::Color::Red);
			break;
		default:
			rect.setFillColor(sf::Color::Transparent);
			break;
		}
	}

public:
	Klocki(float x, float y, float szerokosc, float wysokosc, int Shp = 3):
		hp(Shp), alive(true)
	{
		rect.setSize({ szerokosc, wysokosc });
		rect.setPosition({ x, y });
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(1.f);
		updateColor();
	}
	void draw(sf::RenderTarget& target) const {
		if (alive) {
			target.draw(rect);
		}
	};
	void hit() {
		if(hp > 0) {
			hp--;
			updateColor();
			if (hp == 0) {
				alive = false;
			}
		}
	}
	bool isAlive() const {
		return alive;
	}
	sf::FloatRect getGlobalBounds() const {
		return rect.getGlobalBounds();
	}

	int getHP() const {
		return hp;
	}
	sf::Vector2f getPosition() const {
		return rect.getPosition();
	}
};