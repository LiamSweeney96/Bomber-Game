//
// Do not change this file
//

#include "tom.h"
#include "cave.h"
#include <stdio.h>
#include <string>
#include <iostream>

void Tom::setLocation(Cave* c, int new_x, int new_y)
{
    if (location[0] >= 0 && location[1] >= 0)  // if we've set the location before, remove tom from old position
        c -> getMap()[location[0]][location[1]]->remove(this);
    string str = "";


    location[0] = new_x;
    location[1] = new_y;


    c -> getMap()[location[0]][location[1]]->add(this);
}
