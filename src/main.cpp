//
//  main.hpp
//  MyFirstTactics
//
//  Created by Nathan Johnston and Lloyd Livengood on 9/16/24.
//

#include <iostream>
#include <cassert>
#include "character.hpp"

int main() {
    std::shared_ptr<sf::Font> fontPointer = fontLoader(); //Load font once;
    std::srand(static_cast<unsigned>( int(time(nullptr)))); // random seed for random purposes
    int roundIncrementer = 0, playerAction = 0; // inits
    Character player = Character(1, fontPointer); // player initial generation
    Character enemy = Character(0.8, fontPointer); // enemy initial generation, .8 for initial weaker start to give player chance
    
    sf::RenderWindow window (sf::VideoMode(1000,800), "Polymons");
    while (window.isOpen()) {
        window.clear(sf::Color::Black); // set black window

        sf::Event event;
        keystrokeListener(event, playerAction, window);
        
        sf::RectangleShape round = roundWindow(window, roundIncrementer, fontPointer); // show round counter
        renderPlayer(player, window); // render player
        renderEnemy(enemy, window); // render enemy
            
        battlePhase(enemy, fontPointer, player, playerAction, roundIncrementer);
        window.display();
    }
    return 0;
}
