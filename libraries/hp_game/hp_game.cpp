

#include "hp_game.h"

hp_game::hp_game()
{
}

void hp_game::begin()
{
    _challenges = BEGIN_GAME;
    _color = (struct Color) { 0, 0, 0 };
    _colorType = 0;

    _taps = 0;

    _GRYFFINDOR = (Color) { 0x99, 0x33, 0x33 };
    _HUFFLEPUFF = (Color) { 0x99, 0x99, 0x33 };
    _RAVENCLAW  = (Color) { 0x33, 0x33, 0x99 };
    _SLYTHERIN  = (Color) { 0x33, 0x99, 0x33 };
}

void hp_game::updatePotentiometer(uint32_t value)
{
    // broygbpvw
    int NUM_THINGS = 9;
    int spaces = 255.0/NUM_THINGS;
    value = 255.0 * value / MAX_POTENTIOMETER;

    if (value <= spaces*1) {                        // Black
        _color = (struct Color) {0x00, 0x00, 0x00};
    } else if (value <= spaces*2) {                 // Red
        _color = (struct Color) {0xff, 0x00, 0x00};
    } else if (value <= spaces*3) {                 // Orange
        _color = (struct Color) {0x99, 0x33, 0x00};
    } else if (value <= spaces*4) {                 // Yellow
        _color = (struct Color) {0x9A, 0x9A, 0x00};
    } else if (value <= spaces*5) {                 // Green
        _color = (struct Color) {0x00, 0xff, 0x00};
    } else if (value <= spaces*6) {                 // Blue
        _color = (struct Color) {0x00, 0x00, 0xff};
    } else if (value <= spaces*7) {                 // Pink
        _color = (struct Color) {0x99, 0x00, 0x33};
    } else if (value <= spaces*8) {                 // Violet
        _color = (struct Color) {0x99, 0x00, 0x99};
    } else if (value <= spaces*9) {                 // White
        _color = (struct Color) {0xff, 0xff, 0xff};
    }
}

/*
 Private
 */
void hp_game::matchesHouse()
{
    if (_color.r > _HUFFLEPUFF.r && _color.g > _HUFFLEPUFF.g && _color.b < _HUFFLEPUFF.b) {
        _challenges = _challenges | 0x000002;
    } else if (_color.r > _GRYFFINDOR.r && _color.g < _GRYFFINDOR.g && _color.b < _GRYFFINDOR.b) {
        _challenges = _challenges | 0x000001;
    } else if (_color.r < _RAVENCLAW.r && _color.g < _RAVENCLAW.g && _color.b > _RAVENCLAW.b) {
        _challenges = _challenges | 0x000004;
    } else if (_color.r < _SLYTHERIN.r && _color.g > _SLYTHERIN.g && _color.b < _SLYTHERIN.b) {
        _challenges = _challenges | 0x000008;
    }

    // TODO - Print name to screen
}
