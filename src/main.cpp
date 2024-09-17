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
    testChar();
    testSetGet();
    
    sf::RenderWindow window (sf::VideoMode(800,600), "MyFirstTactics");
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
//        sf::Time deltaTime = clock.restart();
//        float dt = deltaTime.asSeconds();
        
        
        window.clear(sf::Color::Black);
        //call everything visual in between these two
        
        
        Character testGuy = Character(100,23,255,200,5);
        sf::CircleShape displayTestGuy = testGuy.render();
        
        
        
        
        window.draw(displayTestGuy);
        
        // TODO TRIGGER PLAYER
        
        // TODO TRIGGER BATTLE PHASE (based on speed check)
        
        
        
        
        
        
        
        window.display();
    }
    return 0;
}
