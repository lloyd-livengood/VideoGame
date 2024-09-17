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
    //Stats that define a character
    int HP;
    int ATK;
    int DEF;
    int SPD;
    int shapeClass;
    
public:
    
    // Default Constructor
    Character(){
        HP = 1;
        ATK = 1;
        DEF = 1;
        SPD = 1;
        shapeClass = 1;
    }
    
    // Constructor
    Character(int newHP, int newATK, int newDEF, int newSPD, int newShapeClass){
        HP = newHP;
        ATK = newATK;
        DEF = newDEF;
        SPD = newSPD;
        shapeClass = newShapeClass;
    }
    
    // Get methods for private stats
    int getHP() {return HP;}
    int getATK() {return ATK;}
    int getDEF() {return DEF;}
    int getSPD() {return SPD;}
    int getShapeClass() {return shapeClass;}
  
    // Set methods for private stats
    void setHP(int newHP) {HP = newHP;}
    void setATK(int newATK) {ATK = newATK;}
    void setDEF(int newDEF) {DEF = newDEF;}
    void setSPD(int newSPD) {SPD = newSPD;}
    void setShapeClass(int newShapeClass) {shapeClass = newShapeClass;}
    
    // Define a shape to be drawn representing the character
    sf::CircleShape render();
};



sf::CircleShape Character::render() {
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(100,250,50));
    return shape;
}




#endif /* character_hpp */
