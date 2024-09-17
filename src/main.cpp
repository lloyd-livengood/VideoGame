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
//    testChar();
//    testSetGet();
    sf::RenderWindow window (sf::VideoMode(1000,800), "Polymons");
    int playerAction = 0;
    std::srand(static_cast<unsigned>( int(time(nullptr))));
    
    Character player = Character(100,23,255,200,5);
    Character enemy = Character(100,255,150,200,5);
    
    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {               // listening to key presses
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1 ) {
                std::cout << "player action 1" << std::endl;
                playerAction = 1;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
                std::cout << "player action 2" << std::endl;
                playerAction = 2;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {
                std::cout << "player action 3" << std::endl;
                playerAction = 3;
            }
         }
        
        window.clear(sf::Color::Black);                              // set black window

        // TODO create player char on first, carry over on victory
        sf::CircleShape displayPlayer = player.render();
        displayPlayer.setPosition(20, 550);
        window.draw(displayPlayer);
        player.statsWindow(window);
        player.actionWindow(window);
        
        
        // generate enemy, use incremental random params for future rounds
        sf::CircleShape displayEnemy = enemy.render();
        displayEnemy.setPosition(600, 20);
        window.draw(displayEnemy);
            
        if (playerAction != 0){                                     // Battle resolution
            if(player.getSPD() - enemy.getSPD() >= 0){              // if the player is faster
                switch (playerAction) {
                    case 1:
                        player.attack(enemy);
                        std::cout << "HIYAAAAAAAAAAAAAAAA" << std::endl;
                        break;
                    case 2:
                        player.capture(enemy);
                        break;
                    case 3:
                        player.debuff10(enemy);
                        break;
                }
                enemy.attack(player);
            } else {                                                // the enemy is faster
                enemy.attack(player);
                switch (playerAction) {
                    case 1:
                        player.attack(enemy);
                        std::cout << "HIYAAAAAAAAAAAAAAAA" << std::endl;
                        break;
                    case 2:
                        player.capture(enemy);
                        break;
                    case 3:
                        player.debuff10(enemy);
                        break;
                }
            }
            playerAction=0;
        }
        
        
        
        
        window.display();
    }
    return 0;
}
