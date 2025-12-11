#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "paletka.h"
#include "klocki.h"

class Pilka {
private:
	float x, y;
	float vx, vy;
	float radius;
	sf::CircleShape shape;

public:
	Pilka(float xS, float yS, float radiusS, float vxS, float vyS) :
		x(xS), y(yS), vx(vxS), vy(vyS), radius(radiusS)
	{
		shape.setRadius(radius);
		shape.setOrigin(radius, radius);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::White);
	}

	void move() {
		x += vx;
		y += vy;
		shape.setPosition(x, y);
	}

	void bounceX() {
		vx = -vx;
	}

	void bounceY() {
		vy = -vy;
	}

	void collideWalls(float width, float height) {
		if (x - radius <= 0) {
			bounceX();
		}
		if (x + radius >= width) {
			bounceX();
		}
		if (y - radius <= 0) {
			bounceY();
		}
	}

	bool collidePaddle(const Paletka& p) {
		float px = p.getX();
		float py = p.getY();
		float pw = p.getSzerokosc();
		float ph = p.getWysokosc();
		float left = px - pw / 2;
		float right = px + pw / 2;
		float top = py - ph / 2;
		float bottom = py + ph / 2;
		if (x + radius >= left &&
			x - radius <= right &&
			y + radius >= top &&
			y - radius <= bottom)
		{
			return true;    
		}
		return false;
	}

	void draw(sf::RenderTarget& target) {
		target.draw(shape);
	};

	float getX() const {
		return x;
	};
	float getY() const {
		return y;
	};
	float getVX() const {
		return vx;
	};
	float getVY() const {
		return vy;
	};
	float getRadius() const {
		return radius;
	};

	sf::Vector2f getPosition() const {
		return { x, y };
	}
	sf::Vector2f getVelocity() const {
		return { vx, vy };
	}
};