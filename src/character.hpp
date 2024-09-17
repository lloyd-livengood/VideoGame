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
#include <SFML/Window.hpp>
#include <vector>

class Character {
private:
    int HP;
    int ATK;
    int DEF;
    int SPD;
    int shapeClass;
    
public:
    Character(){                // Default Constructor
        HP = 1;
        ATK = 1;
        DEF = 1;
        SPD = 1;
        shapeClass = 1;
    }
    
    Character(int newHP, int newATK, int newDEF, int newSPD, int newShapeClass){        // Param'd constructor
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
    
    sf::CircleShape render();               // Define a shape to be drawn representing the character

    // TODO WINDOW FOR PLAYER SHAPE STATS
    // TODO WINDOW FOR PLAYER ACTIONS
    // TODO WINDOW FOR ENEMY SHAPE STATS
    // TODO ENEMY GENERATOR, calculate stats based on duration of "run", higher randomized stats based on run duration
    // TODO ATTACK ACTION
    // RELATED TODO, HEALTH CHECK after any damage dealt
            // if player HP = 0, game over
                //TODO GAME OVER SCREEN
            // if enemy hp = 0, Victory screen, then generate new enemy
    // TODO BUFF ACTION
    // TODO DEBUFF ACTION
    // TODO CAPTURE ACTION
    // TODO BUMP MOTION FOR ATTACKS
    // TODO FLICKER FOR TAKING DAMAGE
    // TODO PLAYER PHASE
    // TODO BATTLE PHASE
    
    // potential TODO of "resolution" depending on boolean states set by player/enemy hp
    
};



sf::CircleShape Character::render() {
    sf::CircleShape shape(getHP(), getShapeClass());
    shape.setFillColor(sf::Color(getATK(),getDEF(),getSPD()));
    return shape;
}

void renderObjects(const std::vector<sf::Drawable*> & objects, sf::RenderWindow & window){
    for (auto object: objects){
        
    }
}

static void testChar() {
    Character testGet = Character(1,2,3,4,5);
    assert(testGet.getHP() == 1);
    assert(testGet.getATK() == 2);
    assert(testGet.getDEF() == 3);
    assert(testGet.getSPD() == 4);
    assert(testGet.getShapeClass() == 5);
}

static void testSetGet() {
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
}


#endif /* character_hpp */
