#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Paletka
{
private:
	float x;
	float y;
	float szerokosc;
	float wysokosc;
	float v;
	sf::RectangleShape shape;

public:
	Paletka(float xS, float yS, float szerokoscS, float wysokoscS, float vS) :
		x(xS), y(yS), szerokosc(szerokoscS), wysokosc(wysokoscS), v(vS)
	{
		shape.setSize({ szerokosc, wysokosc });
		shape.setOrigin({ szerokosc / 2, wysokosc / 2 });
		shape.setPosition({ x, y });
		shape.setFillColor(sf::Color::Blue);
	}
	void moveL() {
		x -= v;
		shape.setPosition(x, y);
	}
	void moveR() {
		x += v;
		shape.setPosition(x, y);
	}
	void ClampToBounds(float width) {
		if (x - szerokosc / 2 <= 0) {
			x = szerokosc / 2;
			shape.setPosition(x, y);
		}
		if (x + szerokosc / 2 >= width) {
			x = width - szerokosc / 2;
			shape.setPosition(x, y);
		}
	}

	void draw(sf::RenderTarget& target) {
		target.draw(shape);
	};

	float getX() const {
		return x;
	}
	float getY() const {
		return y;
	}
	float getSzerokosc() const {
		return szerokosc;
	}
	float getWysokosc() const {
		return wysokosc;
	}

	sf::Vector2f getPosition() const {
		return sf::Vector2f(x, y);
	}
};
