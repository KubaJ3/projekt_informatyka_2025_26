#pragma once
#include <SFML/Graphics.hpp>
#include "paletka.h"
#include "pilka.h"
#include "klocki.h"
#include <vector>
#include <fstream>

enum class GameState {
	Menu,
	Playing,
	GameOver,
	Paused,
	Win
};

struct BlockData {
	float x, y;
	int hp;
};

class GameData {
private:
	sf::Vector2f paddlePosition;
	sf::Vector2f ballPosition;
	sf::Vector2f ballVelocity;
	std::vector<BlockData> klocki;
public:
	void capture(const Paletka& paletka, const Pilka& pilka, const std::vector<Klocki>& klocek) {
		paddlePosition = paletka.getPosition();
		ballPosition = pilka.getPosition();
		ballVelocity = pilka.getVelocity();
		klocki.clear();
		klocki.reserve(klocek.size());

		for (const auto& k : klocek) {
			BlockData data;
			data.x = k.getPosition().x;
			data.y = k.getPosition().y;
			data.hp = k.getHP();
			klocki.push_back(data);
		}
	}

	bool SaveToFile(const std::string& filename) {
		std::ofstream file(filename);
		if (!file.is_open()) {
			return false;
		}
		file << paddlePosition.x << " " << paddlePosition.y << "\n";
		file << ballPosition.x << " " << ballPosition.y << "\n";
		file << ballVelocity.x << " " << ballVelocity.y << "\n";
		file << klocki.size() << "\n";
		for (const auto& k : klocki) {
			file << k.x << " " << k.y << " " << k.hp << "\n";
		}
		file.close();
		return true;
	}

	bool LoadFromFile(const std::string& filename, Paletka& paletka, Pilka& pilka, std::vector<Klocki>& gameKlocki) {
		std::ifstream file(filename);
		if (!file.is_open()) return false;

		float px, py, bx, by, bvx, bvy;
		size_t numBlocks;

		file >> px >> py;
		file >> bx >> by;
		file >> bvx >> bvy;
		file >> numBlocks;

		paddlePosition = { px, py };
		ballPosition = { bx, by };
		ballVelocity = { bvx, bvy };

		klocki.clear();  
		for (size_t i = 0; i < numBlocks; ++i) {
			BlockData data;
			file >> data.x >> data.y >> data.hp;
			klocki.push_back(data);  
		}
		file.close();

		paletka = Paletka(paddlePosition.x, paddlePosition.y, paletka.getSzerokosc(), paletka.getWysokosc(), 8.f);
		pilka = Pilka(ballPosition.x, ballPosition.y, pilka.getRadius(), ballVelocity.x, ballVelocity.y);

		gameKlocki.clear();
		for (const auto& b : klocki) {
			gameKlocki.emplace_back(b.x, b.y, 50.f, 20.f, b.hp);
		}

		return true;
	}

	const sf::Vector2f& getPaddlePosition() const { return paddlePosition; }
	const sf::Vector2f& getBallPosition() const { return ballPosition; }
	const sf::Vector2f& getBallVelocity() const { return ballVelocity; }
	const std::vector<BlockData>& getBlocks() const { return klocki; }
};