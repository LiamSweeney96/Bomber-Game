#include "move.h"

void Move::fire(Cave& c, string userCommand)
{
    string s = tail(userCommand);

    int newTomX = c.getTom()->getX(),  newTomY = c.getTom()->getY();

    // Altered if statements to check entire string rather than first letter. Ensures more accuracy.
    // Additional "else if's" added here to ensure east and south movement functionality.
    // Checks string to determine direction.
    if (s == "west")
        newTomX--;
    else if  (s == "north")
        newTomY--;
    else if (s == "east")
        newTomX++;
    else if (s == "south")
        newTomY++;
    else
    {
        cerr << "tom can't \"" << s << "\"" << endl;
        return;
    }


    if (newTomX < 0 || newTomY < 0 || newTomX >= c.getHeight() ||newTomY >= c.getHeight())
    {
        cerr << "can't walk into the void" << endl;
        return;
    }
    else if ( c.getMap()[newTomX][newTomY] -> isBlocking() )
    {
        cerr << "something is blocking the way" << endl;
        return;
    }
    else if (newTomX != c.getTom()->getX() || newTomY != c.getTom()->getY())
    {
        c.getTom() -> setLocation (&c, newTomX, newTomY);
        cerr << "tom shuffles through the dank cave" << endl;
        return;
    }
}
