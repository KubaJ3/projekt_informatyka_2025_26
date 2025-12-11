#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "paletka.h"
#include "pilka.h"
#include "klocki.h"
#include <vector>
#include "gamestate.h"

class Gra {
private:
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Klocki> m_klocki;

public:
    Gra() :
        m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),
        m_pilka(320.f, 200.f, 6.f, 2.f, 8.f) 
    {
        float klockiSzer = 50.f, klockiWys = 20.f;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                m_klocki.emplace_back(j * (klockiSzer + 5.f) + 35.f, i * (klockiWys + 5.f) + 30.f, klockiSzer, klockiWys);
            }
        }
    }

    void update(sf::Time dt) {

        m_pilka.move();
        m_pilka.collideWalls(640.f, 480.f);

        if (m_pilka.collidePaddle(m_paletka))
            m_pilka.bounceY();

        for (auto& k : m_klocki) {
            if (!k.isAlive()) continue;

            float px = m_pilka.getX();
            float py = m_pilka.getY();
            float pr = m_pilka.getRadius();

            sf::FloatRect pRect(px - pr, py - pr, pr * 2, pr * 2);

            if (pRect.intersects(k.getGlobalBounds())) {
                k.hit();
                m_pilka.bounceY();
            }
        }

        m_klocki.erase(std::remove_if(m_klocki.begin(), m_klocki.end(),
            [](const Klocki& k) { return !k.isAlive(); }),
            m_klocki.end()
        );
    }

    Paletka& getPaletka() { return m_paletka; }
    Pilka& getPilka() { return m_pilka; }
    std::vector<Klocki>& getKlocki() { return m_klocki; }

    void render(sf::RenderTarget& target) {
        m_paletka.draw(target);
        m_pilka.draw(target);
        for (auto& k : m_klocki)
            k.draw(target);
    }
    void LoadState(const GameData& snapshot) {
        m_paletka = Paletka(snapshot.getPaddlePosition().x, snapshot.getPaddlePosition().y, m_paletka.getSzerokosc(), m_paletka.getWysokosc(), 8.f);
        m_pilka = Pilka(snapshot.getBallPosition().x, snapshot.getBallPosition().y, m_pilka.getRadius(), snapshot.getBallVelocity().x, snapshot.getBallVelocity().y);
        m_klocki.clear();
        for (const auto& b : snapshot.getBlocks()) {
            m_klocki.emplace_back(b.x, b.y, 50.f, 20.f, b.hp);
        }
    }
};

