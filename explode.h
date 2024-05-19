#ifndef EXPLODE_H
#define EXPLODE_H

#include "coin.h"
#include "command.h"
#include "mushroom.h"
#include "rock.h"
#include "bomb.h"
#include <iostream>

/*
 *
 * This class is used to explode the bombs under and adjacent to Tom using the command
 * "explode" to trigger it. Also creates a chain of eplosions if bombs are next to
 * another bomb.
 *
*/

using namespace std;

class Explode : public Command
{
public:
    Explode() : Command("explode") {};
    void fire(Cave& c, string userCommand);
    void destroyNonTom(Cave& c, int x, int y);
    bool checkBomb(Cave& c, int x, int y);

};

#endif // EXPLODE_H
