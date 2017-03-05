/*
    hp_game.h

    Author: David Soller

    Harry Potter Game
*/

#ifndef __HP_GAME_H__
#define __HP_GAME_H__

#include <inttypes.h>
#include "Print.h"

// game states
/*
    Ones to 32's digit:

    GRYFFINDOR Color
    HUFFLEPUFF Color
    RAVENCLAW Color
    SLYTHERIN Color

    hitSound
    hitLight
    hitDoublePress
    hitTemperature

*/
#define BEGIN_GAME  0x000000
#define WIN_GAME    0x0000ff


// colors
struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// numbers
#define MAX_POTENTIOMETER   1023.0

class hp_game
{

public:
    hp_game();

    void begin();

    bool isWinner() {
        return _challenges == WIN_GAME;
    }
    uint32_t getState() {
        return _challenges;
    }
    struct Color getColor() {
        return _color;
    }

    void updatePotentiometer(uint32_t);
    void clickButton() {
        matchesHouse();
    }

    // Hits
    void hitSound() { _challenges = _challenges | 0x000010; }
    void hitLight() { _challenges = _challenges | 0x000020; }
    void hitDoublePress() { _challenges = _challenges | 0x000040; }
    void hitTemperature() { _challenges = _challenges | 0x000080; }

private:
    void matchesHouse();

    struct Color _color;
    uint8_t _colorType;

    uint32_t _challenges;

    struct Color _GRYFFINDOR;
    struct Color _HUFFLEPUFF;
    struct Color _RAVENCLAW;
    struct Color _SLYTHERIN;

};


#endif