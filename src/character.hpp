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
    sf::Font font;
    
public:
    Character(){                // Default Constructor
        HP = 1;
        ATK = 1;
        DEF = 1;
        SPD = 1;
        shapeClass = 1;
        font.loadFromFile("ProtestGuerrilla-Regular.ttf");
    }
    
    Character(int newHP, int newATK, int newDEF, int newSPD, int newShapeClass) {        // Param'd constructor
        HP = newHP;
        ATK = newATK;
        DEF = newDEF;
        SPD = newSPD;
        shapeClass = newShapeClass;
        font.loadFromFile("ProtestGuerrilla-Regular.ttf");
    }
    
    // Get methods for private stats
    int getHP() {return HP;}
    int getATK() {return ATK;}
    int getDEF() {return DEF;}
    int getSPD() {return SPD;}
    int getShapeClass() {return shapeClass;}
    sf::Font getFont() {return font;}
  
    // Set methods for private stats
    void setHP(int newHP) {HP = newHP;}
    void setATK(int newATK) {ATK = newATK;}
    void setDEF(int newDEF) {DEF = newDEF;}
    void setSPD(int newSPD) {SPD = newSPD;}
    void setShapeClass(int newShapeClass) {shapeClass = newShapeClass;}
    
    sf::CircleShape render();               // Define a shape to be drawn representing the character

    // TODO WINDOW FOR PLAYER SHAPE STATS
    sf::RectangleShape statsWindow(sf::RenderWindow &window) {
        // Create the rectangle
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(150, 100));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(3);
        rectangle.setPosition(800, 650);

        sf::Text HPLine;
        std::string HPString = std::to_string(getHP());
        HPLine.setFont(font); // Set the loaded font
        HPLine.setString("HP: " + HPString); // Set the string to display
        HPLine.setCharacterSize(20); // Set the text size
        HPLine.setFillColor(sf::Color::Black); // Set the text color
        HPLine.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 10); // Position inside the rectangle
        
        sf::Text ATKLine;
        std::string ATKString = std::to_string(getATK());
        ATKLine.setFont(font);
        ATKLine.setString("ATK: " + ATKString);
        ATKLine.setCharacterSize(20);
        ATKLine.setFillColor(sf::Color::Black);
        ATKLine.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 30);

        sf::Text DEFLine;
        std::string DEFString = std::to_string(getDEF());
        DEFLine.setFont(font);
        DEFLine.setString("DEF: " + DEFString);
        DEFLine.setCharacterSize(20);
        DEFLine.setFillColor(sf::Color::Black);
        DEFLine.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 50);
        
        sf::Text SPDLine;
        std::string SPDString = std::to_string(getSPD());
        SPDLine.setFont(font);
        SPDLine.setString("SPD: " + SPDString);
        SPDLine.setCharacterSize(20);
        SPDLine.setFillColor(sf::Color::Black);
        SPDLine.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 70);

        window.draw(rectangle);
        window.draw(HPLine);
        window.draw(ATKLine);
        window.draw(DEFLine);
        window.draw(SPDLine);
        return rectangle;
    }
    
    sf::RectangleShape actionWindow(sf::RenderWindow &window) {
        // Create the rectangle
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(150, 100));
        rectangle.setOutlineColor(sf::Color::Blue);
        rectangle.setOutlineThickness(3);
        rectangle.setPosition(425, 650);
        
        sf::Text attack;
        attack.setFont(font); // Set the loaded font
        attack.setString("1. Attack" ); // Set the string to display
        attack.setCharacterSize(20); // Set the text size
        attack.setFillColor(sf::Color::Black); // Set the text color
        attack.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 10); // Position inside the rectangle
        
        sf::Text capture;
        capture.setFont(font); // Set the loaded font
        capture.setString("2. Capture" ); // Set the string to display
        capture.setCharacterSize(20); // Set the text size
        capture.setFillColor(sf::Color::Black); // Set the text color
        capture.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 30); // Position inside the rectangle
        
        sf::Text debuff10;
        debuff10.setFont(font); // Set the loaded font
        debuff10.setString("3. Debuff 10%" ); // Set the string to display
        debuff10.setCharacterSize(20); // Set the text size
        debuff10.setFillColor(sf::Color::Black); // Set the text color
        debuff10.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 50); // Position inside the rectangle

        
        
        
        window.draw(rectangle);
        window.draw(attack);
        window.draw(capture);
        window.draw(debuff10);
        return rectangle;
    }
    
    
    
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
    void attack(Character &rhs){
        int damage = ATK - rhs.getDEF();
        if (damage <1){
            damage = 1;
        }
        rhs.setHP(rhs.getHP()-damage);
    }
    
    void capture(Character &rhs){
        int captureChance = (getHP()*getSPD()) / (rhs.getHP()*rhs.getSPD());
        if( captureChance > (rand() % 100)) {
            ATK += rhs.getATK();
            DEF += rhs.getDEF();
            SPD += rhs.getSPD();
            shapeClass += rhs.getShapeClass();
        }
    }
    
    void debuff10(Character &rhs){
        rhs.setATK(rhs.getATK()*.9);
        rhs.setDEF(rhs.getDEF()*.9);
        rhs.setSPD(rhs.getSPD()*.9);
    }
    
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
