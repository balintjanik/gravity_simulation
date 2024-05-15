#ifndef SETUPTYPE_H
#define SETUPTYPE_H

enum class PlacementType
{
    Fullscreen,
    Circular
};

// max radius of circle in case of circular setup
const int R = 300;

const float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

enum class SpeedType
{
    RandSpeed,
    AngularSpeed,
    NoSpeed
};

#endif
