#pragma once
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "gra.h"
#include "gamestate.h"
#include <iostream>

void Sterowanie(sf::Event& event, GameState& state, Menu& menu, Gra& gra, sf::RenderWindow& window) {
    if (event.type == sf::Event::Closed) {
        window.close();
        return; 
    }

    if (state == GameState::Menu && event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::W:
            menu.moveUp();
            break;
        case sf::Keyboard::S:
            menu.moveDown();
            break;
        case sf::Keyboard::Enter:
            switch (menu.getSelectedIndex()) {
            case 0: 
                gra = Gra();
                state = GameState::Playing;
                break;
            case 1: { 
                GameData snapshot;
                if (snapshot.LoadFromFile("zapiski.txt", gra.getPaletka(), gra.getPilka(), gra.getKlocki())) {
                    gra.LoadState(snapshot);
                    if (!gra.getKlocki().empty()) {
                        state = GameState::Playing;
                        std::cout << "Gra wczytana\n";
                    }
                    else {
                        std::cout << "Blad wczytywania\n";
                    }
                }
                else {
                    std::cout << "Blad wczytywania\n";
                }
                break;
            }
            case 2: 
                window.close();
                break;
            }
            break;
        }
    }

    else if (state == GameState::Playing && event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P)
            state = GameState::Paused;
    }

    else if (state == GameState::Paused && event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P)
            state = GameState::Playing;
        else if (event.key.code == sf::Keyboard::Escape)
            state = GameState::Menu;
        else if (event.key.code == sf::Keyboard::O) {
            GameData snapshot;
            snapshot.capture(gra.getPaletka(), gra.getPilka(), gra.getKlocki());
            if (snapshot.SaveToFile("zapiski.txt"))
                std::cout << "Zapis sie udal\n";
            else
                std::cout << "Zapis sie nie udal\n";
        }
    }

    else if ((state == GameState::GameOver || state == GameState::Win) && event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            gra = Gra();
            state = GameState::Playing;
        }
        else if (event.key.code == sf::Keyboard::Escape) {
            state = GameState::Menu;
        }
    }
}
