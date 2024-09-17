//
//  testing.cpp
//  MyFirstTactics
//
//  Created by Nathan Johnston on 9/16/24.
//

#include "testing.hpp"
        
void runTests() {
    Character defaultMon = Character();
    Character negativeMon = Character(-99,-99,-99,-99,-99);
    Character zeroMon = Character(0,0,0,0,0);
    
    // Test get methods
    assert(defaultMon.getHP() == 1);
    assert(defaultMon.getATK() == 1);
    assert(defaultMon.getDEF() == 1);
    assert(defaultMon.getSPD() == 1);
    assert(defaultMon.getShapeClass() == 1);
}
