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
    
    sf::Texture background; // background sprite setup
    background.loadFromFile("background.jpg");
    sf::Sprite bg (background);
    
    int roundIncrementer = 0, playerAction = 0; // inits
    Character player = Character(1, fontPointer); // player initial generation
    Character enemy = Character(0.8, fontPointer); // enemy initial generation, .8 for initial weaker start to give player chance
    std::string combatLogString;

    
    sf::RenderWindow window (sf::VideoMode(1000,800), "Polymons");
    while (window.isOpen()) {
        window.clear(sf::Color::Black); // set black window
        window.draw(bg); // set bg
        
        roundWindow(window, roundIncrementer, fontPointer); // show round counter
        actionWindow(window, fontPointer); // render action window
        renderPlayer(player, window); // render player
        player.statsWindow(window,800,650); // render player stats
        renderEnemy(enemy, window); // render enemy
        enemy.statsWindow(window,10,10); // render enemy stat window

        sf::Event event;
        keystrokeListener(event, playerAction, window); // listen for keypress and set player action to non zero...
        battlePhase(enemy, fontPointer, player, playerAction, roundIncrementer, combatLogString);   // ... therefore triggering combat resolution

        gameOverCheck(fontPointer, playerAction, roundIncrementer, window); // triggered if playeraction is set to 4 by health check, IE player dead
        
        combatLog(combatLogString, fontPointer, window); // display latest combat log at bottom of screen
        window.display();
    }
    return 0;
}
