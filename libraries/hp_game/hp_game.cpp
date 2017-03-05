

#include "hp_game.h"

hp_game::hp_game()
{
}

void hp_game::begin()
{
    _challenges = BEGIN_GAME;
    _color = (struct Color) { 0, 0, 0 };
    _colorType = 0;

    _GRYFFINDOR = (Color) { 0x99, 0x33, 0x33 };
    _HUFFLEPUFF = (Color) { 0x99, 0x99, 0x33 };
    _RAVENCLAW  = (Color) { 0x33, 0x33, 0x99 };
    _SLYTHERIN  = (Color) { 0x33, 0x99, 0x33 };
}

void hp_game::updatePotentiometer(uint32_t value)
{
    value = 256.0 * value / MAX_POTENTIOMETER;

    switch(_colorType) {
        case 0: // Red
            _color.r = value;
            break;
        case 1: // Green
            _color.g = value;
            break;
        case 2: // Blue
            _color.b = value;
            break;
        default:

            _colorType = 0;
            _color.r = value;
            break;
    }

    hp_game::matchesHouse();
}

/*
 Private
 */
void hp_game::matchesHouse()
{
    if (_color.r >= _HUFFLEPUFF.r && _color.g >= _HUFFLEPUFF.g && _color.b <= _HUFFLEPUFF.b) {
        _challenges = _challenges | 0x000002;
    } else if (_color.r >= _GRYFFINDOR.r && _color.g <= _GRYFFINDOR.g && _color.b <= _GRYFFINDOR.b) {
        _challenges = _challenges | 0x000001;
    } else if (_color.r <= _RAVENCLAW.r && _color.g <= _RAVENCLAW.g && _color.b >= _RAVENCLAW.b) {
        _challenges = _challenges | 0x000004;
    } else if (_color.r <= _SLYTHERIN.r && _color.g >= _SLYTHERIN.g && _color.b <= _SLYTHERIN.b) {
        _challenges = _challenges | 0x000008;
    }

    // TODO - Print name to screen
}
