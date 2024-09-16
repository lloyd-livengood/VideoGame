//
//  character.hpp
//  MyFirstTactics
//
//  Created by Nathan Johnston and Lloyd Livengood on 9/16/24.
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
    int shapeClass;
    
public:
    sf::CircleShape render();
    Character(){
        HP = 99;
        ATK = 1;
        DEF = 1;
        SPD = 1;
        shapeClass = 1;
    }
    Character(int newHP, int newATK, int newDEF, int newSPD, int newShapeClass){
        HP = newHP;
        ATK = newATK;
        DEF = newDEF;
        SPD = newSPD;
        shapeClass = newShapeClass;
    }
};



sf::CircleShape Character::render() {
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(100,250,50));
    return shape;
}




#endif /* character_hpp */
