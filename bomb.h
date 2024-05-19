#ifndef BOMB_H
#define BOMB_H

#include "thing.h"
#include <string>

// a giant bolder that stops tom from walking through this location
class Bomb: public Thing
{
public:
    Bomb(){};
    ~Bomb(){};
    string getName()
    {
        return "bomb";
    }
};

#endif // BOMB_H
