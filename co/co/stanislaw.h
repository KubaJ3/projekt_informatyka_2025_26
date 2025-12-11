#pragma once
#include <SFML/Graphics.hpp>

struct GameOverScreen {
    sf::Font font;
    sf::Text text;

    GameOverScreen() {
        font.loadFromFile("ARIAL.TTF");
        text.setFont(font);
        text.setString("GAME OVER\nENTER - restart\nESC - menu");
        text.setCharacterSize(28);
        text.setFillColor(sf::Color::White);
    }

    void ustawPozycje(sf::RenderWindow& win) {
        sf::FloatRect b = text.getLocalBounds();
        text.setOrigin(b.width / 2.f, b.height / 2.f);
        text.setPosition(win.getSize().x / 2.f, win.getSize().y / 2.f);
    }

    void rysuj(sf::RenderWindow& win) {
        ustawPozycje(win);
        win.draw(text);
    }
}; 

#pragma once
#include <SFML/Graphics.hpp>

struct WinScreen {
    sf::Font font;
    sf::Text text;

    WinScreen() {
        font.loadFromFile("ARIAL.TTF");
        text.setFont(font);
        text.setString("WYGRALES!\nENTER - restart\nESC - menu");
        text.setCharacterSize(28);
        text.setFillColor(sf::Color::Green);
    }

    void ustawPozycje(sf::RenderWindow& win) {
        sf::FloatRect b = text.getLocalBounds();
        text.setOrigin(b.width / 2.f, b.height / 2.f);
        text.setPosition(win.getSize().x / 2.f, win.getSize().y / 2.f);
    }

    void rysuj(sf::RenderWindow& win) {
        ustawPozycje(win);
        win.draw(text);
    }
};