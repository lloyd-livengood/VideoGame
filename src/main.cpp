//
//  main.hpp
//  MyFirstTactics
//
//  Created by Nathan Johnston and Lloyd Livengood on 9/16/24.
//

#include <iostream>
#include "character.hpp"

int main() {
    sf::RenderWindow window (sf::VideoMode(800,600), "MyFirstTactics");
    
    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::Black);
        //call everything visual in between these two
        
        
        Character testGuy = Character();
        sf::CircleShape displayTestGuy = testGuy.render();
        
        window.draw(displayTestGuy);
        
        window.display();
    }
    
    return 0;
}
