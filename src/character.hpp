//
//  character.hpp
//  MyFirstTactics
//
//  Created by Nathan Johnston and Lloyd Livengood on 9/16/24.
//
// TODO WINDOW FOR PLAYER ACTIONS ** COMPLETED
// TODO WINDOW FOR ENEMY SHAPE STATS ** COMPLETED
// TODO ENEMY GENERATOR, calculate stats based on duration of "run", higher randomized stats based on run duration ** COMPLETED
// TODO ATTACK ACTION ** COMPLETED
// TODO Victory / Defeat Checks and screens
        // if player HP = 0, game over
            //TODO GAME OVER SCREEN
        // if enemy hp = 0, Victory screen
// TODO DEBUFF ACTION ** COMPLETED
// TODO CAPTURE ACTION ** COMPLETED
// TODO BUMP MOTION FOR ATTACKS
// TODO FLICKER FOR TAKING DAMAGE
// TODO PLAYER PHASE ** COMPLETED
// TODO BATTLE PHASE ** COMPLETED

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
    std::shared_ptr<sf::Font> font;
public:
    Character(int newHP, int newATK, int newDEF, int newSPD, int newShapeClass, std::shared_ptr<sf::Font> newFont) {        // Param'd constructor
        HP = newHP;
        ATK = newATK;
        DEF = newDEF;
        SPD = newSPD;
        shapeClass = newShapeClass;
        font = newFont;
    }
    
    Character(double roundIncrementer, std::shared_ptr<sf::Font> newFont) { // Constructor for randGen
        int distributionTotal = 100 * roundIncrementer; // total number of points to be distributed, 10% higher each round
        
        int distribution = distributionTotal - (rand() % distributionTotal);
        HP = 10 + distribution;
        distributionTotal -= distribution;
        distributionTotal++;
  
        distribution = distributionTotal - (rand() % (distributionTotal));
        ATK = 9 + distribution;
        distributionTotal -= distribution;
        distributionTotal++;
        
        distribution = distributionTotal - (rand() % (distributionTotal));
        DEF = 9 + distribution;
        distributionTotal -= distribution;
        distributionTotal++;
        
        SPD = distributionTotal;                            // remainder get sent to spd
        
        shapeClass = 3 + (rand() % 4);                      // random shape
        font = newFont;                                     // req'd font
    }
    
    // Get methods for private stats
    int getHP() {return HP;}
    int getATK() {return ATK;}
    int getDEF() {return DEF;}
    int getSPD() {return SPD;}
    int getShapeClass() {return shapeClass;}
    std::shared_ptr<sf::Font> getFont() {return font;}
  
    // Set methods for private stats
    void setHP(int newHP) {HP = newHP;}
    void setATK(int newATK) {ATK = newATK;}
    void setDEF(int newDEF) {DEF = newDEF;}
    void setSPD(int newSPD) {SPD = newSPD;}
    void setShapeClass(int newShapeClass) {shapeClass = newShapeClass;}
    
    // Define a shape to be drawn representing the character
    sf::CircleShape render() {
        double radius = 100; // 100 pixel max radius
        radius *= (getHP() / radius);
        if (radius > 100)
            radius = 100;                           // TODO REWRITE TO BE MORE BETTER AND DYNAMIC
        sf::CircleShape shape(radius, getShapeClass());
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(5);
        
        double totalStats = getATK() + getDEF() + getSPD();
        int red = 255 * (getATK() / totalStats); // RBG R proportional
        int blue = 255 * (getDEF() / totalStats); // RBG B proportional
        int green = 255 * (getSPD() / totalStats); // RBG G proportional
        shape.setFillColor(sf::Color(red, blue, green));
        
        return shape;
    }

    void statsWindow(sf::RenderWindow &window, int positionX, int positionY) {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(150, 100));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(3);
        rectangle.setPosition(positionX, positionY);

        sf::Text HPLine;
        std::string HPString = std::to_string(getHP());
        HPLine.setFont(*font); // Set the loaded font
        HPLine.setString("HP: " + HPString); // Set the string to display
        HPLine.setCharacterSize(20); // Set the text size
        HPLine.setFillColor(sf::Color::Black); // Set the text color
        HPLine.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 10); // Position inside the rectangle
        
        sf::Text ATKLine;
        std::string ATKString = std::to_string(getATK());
        ATKLine.setFont(*font);
        ATKLine.setString("ATK: " + ATKString);
        ATKLine.setCharacterSize(20);
        ATKLine.setFillColor(sf::Color::Black);
        ATKLine.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 30);

        sf::Text DEFLine;
        std::string DEFString = std::to_string(getDEF());
        DEFLine.setFont(*font);
        DEFLine.setString("DEF: " + DEFString);
        DEFLine.setCharacterSize(20);
        DEFLine.setFillColor(sf::Color::Black);
        DEFLine.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 50);
        
        sf::Text SPDLine;
        std::string SPDString = std::to_string(getSPD());
        SPDLine.setFont(*font);
        SPDLine.setString("SPD: " + SPDString);
        SPDLine.setCharacterSize(20);
        SPDLine.setFillColor(sf::Color::Black);
        SPDLine.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 70);

        window.draw(rectangle);
        window.draw(HPLine);
        window.draw(ATKLine);
        window.draw(DEFLine);
        window.draw(SPDLine);
    }
    
    void attack(Character &rhs, std::string &combatLogString){
        int damage = ATK - rhs.getDEF(); // atk - def damage calc
        if (damage <1){
            damage = 1; // damage minimum of 1 point for chip damage
        }
        rhs.setHP(rhs.getHP()-damage);
        combatLogString += ("Damage dealt: " + std::to_string(damage) + " ");
    }
    
    void capture(Character &rhs, std::string &combatLogString){
        int captureChance = 50 - (rhs.getHP() - getHP() + rhs.getSPD() - getSPD()); // 50/50 odds at parity, modified by stats
        
        if( captureChance > (rand() % 100)) {  // capture chance against random roll
            ATK += (rhs.getATK()*.2) + 1; // add portion of stat aggregate, +1 for int rounding
            DEF += (rhs.getDEF()*.2) + 1;
            SPD += (rhs.getSPD()*.2) + 1;
            shapeClass += 1;
            rhs.setHP(0); // 'kill' the enemy, and trigger new randgen
            combatLogString +=  "Polymon captured! Stats Stolen! Next enemy...";
        } else {
            combatLogString += "Capture failed.";
        }
    }
    
    void debuff10(Character &rhs,  std::string &combatLogString){
        rhs.setATK(rhs.getATK()*.9);
        rhs.setDEF(rhs.getDEF()*.9);
        rhs.setSPD(rhs.getSPD()*.9);
        combatLogString += "Enemy stats debuffed.";
    }
    
    bool alive() {
        return (getHP() > 0);
    }
};

void actionWindow(sf::RenderWindow &window, std::shared_ptr<sf::Font> newFont) {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(150, 100));
    rectangle.setOutlineColor(sf::Color::Blue);
    rectangle.setOutlineThickness(3);
    rectangle.setPosition(425, 650);
    
    sf::Text attack;
    attack.setFont(*newFont);
    attack.setString("1. Attack" );
    attack.setCharacterSize(20);
    attack.setFillColor(sf::Color::Black);
    attack.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 10);
    
    sf::Text capture;
    capture.setFont(*newFont);
    capture.setString("2. Capture" );
    capture.setCharacterSize(20);
    capture.setFillColor(sf::Color::Black);
    capture.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 30);
    
    sf::Text debuff10;
    debuff10.setFont(*newFont);
    debuff10.setString("3. Debuff 10%" );
    debuff10.setCharacterSize(20);
    debuff10.setFillColor(sf::Color::Black);
    debuff10.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 50);

    window.draw(rectangle);
    window.draw(attack);
    window.draw(capture);
    window.draw(debuff10);
}

static void roundWindow(sf::RenderWindow &window, int roundIncrementer, std::shared_ptr<sf::Font> newFont) {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(80, 40));
    rectangle.setOutlineColor(sf::Color::Green);
    rectangle.setOutlineThickness(3);
    rectangle.setPosition(460, 10);
    
    sf::Text roundLine;
    std::string roundString = std::to_string(roundIncrementer + 1);
    roundLine.setFont(*newFont);
    roundLine.setString("Round: " + roundString);
    roundLine.setCharacterSize(15);
    roundLine.setFillColor(sf::Color::Black);
    roundLine.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 10); 
  
    window.draw(rectangle);
    window.draw(roundLine);
}

static void renderPlayer(Character &player, sf::RenderWindow &window) {
    sf::CircleShape displayPlayer = player.render();
    displayPlayer.setPosition(130, 550);
    window.draw(displayPlayer);
}

static void renderEnemy(Character &enemy, sf::RenderWindow &window) {
    sf::CircleShape displayEnemy = enemy.render();
    displayEnemy.setPosition(650, 60);
    window.draw(displayEnemy);
}

inline void enemyHealthCheck(Character &enemy, const std::shared_ptr<sf::Font> &fontPointer, Character &player, int &roundIncrementer) {
    if(!enemy.alive()) { // if the enemy is slain/capt
        std::cout << "Enemy defeated!" << std::endl;
        roundIncrementer++; //increment next round
        enemy = Character(.8 + pow(roundIncrementer,roundIncrementer)*.05, fontPointer);
        player.setHP((player.getHP()*1.2) + 15); // player regains 20% HP, with 15hp min
    }
}

inline void playerAct(Character &enemy, Character &player, int &playerAction, std::string &combatLogString) {
    switch (playerAction) {
        case 1:
            player.attack(enemy, combatLogString);
            break;
        case 2:
            player.capture(enemy, combatLogString);
            break;
        case 3:
            player.debuff10(enemy, combatLogString);
            break;
    }
}

static void battlePhase(Character &enemy, const std::shared_ptr<sf::Font> &fontPointer, Character &player, int &playerAction, int &roundIncrementer, std::string &combatLogString) {
    if (playerAction != 0){  // Battle resolution triggered if action is not zero IE a button is pressed
        if(player.getSPD() - enemy.getSPD() >= 0){ // if the player is faster, they attack first
            combatLogString = "Player acts! ";
            playerAct(enemy, player, playerAction, combatLogString);
            enemyHealthCheck(enemy, fontPointer, player, roundIncrementer); // check enemy health after action
            
            enemy.attack(player, combatLogString); // enemy attacks
            combatLogString +=  "Enemy attacks! ";
            if(!player.alive()){
                playerAction = 4;
                return;
            }
        } else {
            combatLogString = "Enemy attacks! ";
            enemy.attack(player, combatLogString); // the enemy is faster and attacks first
            if(!player.alive()){
                playerAction = 4;
                return;
            }
            combatLogString +=  "Player acts! ";
            playerAct(enemy, player, playerAction, combatLogString);
            enemyHealthCheck(enemy, fontPointer, player, roundIncrementer);
        }
    }
    playerAction=0; // reset player action to resume "listening" for next keystroke
}

static void keystrokeListener(sf::Event &event, int &playerAction, sf::RenderWindow &window) {
    while (window.pollEvent(event)) { // listening to key presses
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1 ) {
            playerAction = 1;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
            playerAction = 2;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {
            playerAction = 3;
        }
    }
}

static std::shared_ptr<sf::Font> fontLoader() { // font loader
    sf::Font* font = new sf::Font();
    std::shared_ptr<sf::Font> fontPointer(font);
    sf::Font& fontRef = *fontPointer;
    (*fontPointer).loadFromFile("ProtestGuerrilla-Regular.ttf");
    return fontPointer;
}

sf::RectangleShape gameOverWindow(int roundIncrementer, std::shared_ptr<sf::Font> newFont) {
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(1000, 800));
  rectangle.setFillColor(sf::Color(255, 0, 0));
  sf::Text roundLine;
  std::string roundString = std::to_string(roundIncrementer + 1);
  roundLine.setFont(*newFont);
  roundLine.setString("Round: " + roundString);
  roundLine.setCharacterSize(15);
  roundLine.setFillColor(sf::Color::Black);
  roundLine.setPosition(rectangle.getPosition().x + 10, rectangle.getPosition().y + 10);
  return rectangle;
}

sf::Text gameOverText(int roundIncrementer, std::shared_ptr<sf::Font> newFont) {
  sf::Text gameOverLine;
  gameOverLine.setString("Game Over at Round: " + std::to_string(roundIncrementer+1));
  gameOverLine.setCharacterSize(80);
  gameOverLine.setFont(*newFont);
  gameOverLine.setPosition(100, 300);
  gameOverLine.setFillColor(sf::Color(0, 0, 0));
  return gameOverLine;
}

static void gameOverCheck(const std::shared_ptr<sf::Font> &fontPointer, int playerAction, int roundIncrementer, sf::RenderWindow &window) {
    if (playerAction == 4){                 // if player is dead
        sf::RectangleShape gameOver = gameOverWindow(roundIncrementer, fontPointer);
        sf::Text gameOverLine = gameOverText(roundIncrementer, fontPointer);
        window.draw(gameOver);
        window.draw(gameOverLine);
    }
}

static void combatLog(const std::string &combatLogString, const std::shared_ptr<sf::Font> &fontPointer, sf::RenderWindow &window) {
    sf::RectangleShape combatLog;
    combatLog.setSize(sf::Vector2f(1000, 40));
    combatLog.setFillColor(sf::Color(0, 0, 0));
    combatLog.setFillColor(sf::Color::Black);
    combatLog.setPosition(0, 760);
    window.draw(combatLog);
    
    sf::Text combatLogText;
    combatLogText.setString(combatLogString);
    combatLogText.setCharacterSize(20);
    combatLogText.setFont(*fontPointer);
    combatLogText.setPosition(10, 762);
    combatLogText.setFillColor(sf::Color::White);
    window.draw(combatLogText);
}

#endif /* character_hpp */
