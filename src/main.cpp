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
    
    Character testGet = Character(1,2,3,4,5);
    assert(testGet.getHP() == 1);
    assert(testGet.getATK() == 2);
    assert(testGet.getDEF() == 3);
    assert(testGet.getSPD() == 4);
    assert(testGet.getShapeClass() == 5);
    
    Character testSet = Character();
    testSet.setHP(999);
    assert(testSet.getHP() == 999);
    testSet.setATK(888);
    assert(testSet.getATK() == 888);
    testSet.setDEF(77);
    assert(testSet.getDEF() == 77);
    testSet.setSPD(-1);
    assert(testSet.getSPD() == -1);
    testSet.setShapeClass(66666);
    assert(testSet.getShapeClass() == 66666);

    
    sf::RenderWindow window (sf::VideoMode(800,600), "MyFirstTactics");
    
    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::Black);
        //call everything visual in between these two
        
        
        Character testGuy = Character(100,23,255,200,5);
        sf::CircleShape displayTestGuy = testGuy.render();
        
        window.draw(displayTestGuy);
        
        window.display();
    }
    
    return 0;
}
