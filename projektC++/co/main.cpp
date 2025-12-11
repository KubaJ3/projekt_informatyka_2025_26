#include <SFML/Graphics.hpp>
#include "gra.h"
#include "menu.h"
#include "gamestate.h"
#include "sterowanie.h"
#include "stop.h"
#include "stanislaw.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Super Gra");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Gra gra;
    GameState currentState = GameState::Menu;

    PauseScreen pauseScreen;
    GameOverScreen gameOverScreen;
	WinScreen winScreen;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            Sterowanie(event, currentState, menu, gra, window);
        }

        if (currentState == GameState::Playing) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                gra.getPaletka().moveL();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                gra.getPaletka().moveR();

            gra.getPaletka().ClampToBounds(window.getSize().x);
            gra.update(dt);

            const Pilka& pilka = gra.getPilka();
            if (pilka.getY() - pilka.getRadius() > static_cast<float>(window.getSize().y))
                currentState = GameState::GameOver;
           
            if (gra.getKlocki().empty()) 
                currentState = GameState::Win;
        }

        window.clear(sf::Color::Black);

        switch (currentState) {
        case GameState::Menu:
            menu.render(window);
            break;
        case GameState::Playing:
            gra.render(window);
            break;
        case GameState::Paused:
            gra.render(window);
            pauseScreen.rysuj(window);
            break;
        case GameState::GameOver:
            gra.render(window);
            gameOverScreen.rysuj(window);
            break;
        case GameState::Win:
            gra.render(window);
            winScreen.rysuj(window);
            break;
        }
        window.display();
    }
    return 0;
}
