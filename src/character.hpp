//
//  character.hpp
//  MyFirstTactics
//
//  Created by Nathan Johnston on 9/16/24.
//

#ifndef character_hpp
#define character_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Character {
    public:
    int HP;
    int ATK;
    int DEF;
    int SPD;
    
public:
    sf::CircleShape render();
    Character(){
        HP = 99;
        ATK = 1;
        DEF = 1;
        SPD = 1;
    }
    
};



sf::CircleShape Character::render() {
sf::CircleShape shape(50.f);
shape.setFillColor(sf::Color(100,250,50));
    return shape;
   // sf::Rectangle visualCharacter(100,100);
}
#endif /* character_hpp */
