#include "explode.h"
#include "thing.h"

// Function to destroy anything in the current location except for Tom
void Explode::destroyNonTom(Cave& c, int x, int y)
{
    // Declare vector containing all things at the current location
    vector<Thing*>* th = c.getMap()[x][y]->getThings();

    // Loop through items at current location, removing anything that isn't tom
    for (Thing* t : *th)
    {
        if (t->getName() != "tom")
        {
            c.getMap()[x][y]->remove(t);
        }
    }
}

// Function to check whether a bomb is present at a location and explode it
bool Explode::checkBomb(Cave& c, int x, int y)
{
    Location* loc;
    // Check x & y values are valid and in bounds
    if (x < c.getWidth() && y < c.getHeight() && x > 0 && y > 0)
    {

    }
    else
    {
        cerr << "Out of bounds error" << endl;
        return false;
    }

    // Set location to current location specified by parameters
    loc = c.getMap()[x][y];

    // Declare vector containing all things in current location
    vector<Thing*>* th;
    th = loc->getThings();

    bool bombFound = false;

    // Loop through things in current location to check if a bomb is present and explode it
    for (Thing* t : *th)
    {
        // If a bomb is found, run function to "destroy"
        if (t->getName() == "bomb")
        {
            destroyNonTom(c, x, y);
            bombFound = true;
        }
    }
    return bombFound;
}

// Function to explode bombs in a chain starting from toms current location
// Run's until no bombs are left adjacent to be exploded
void Explode::fire(Cave& c, string userCommand)
{
    // Arrays to store x & y coordinates or each bomb
    int xCoord[c.getWidth()], yCoord[c.getHeight()];
    int index = 0, x = c.getTom()->getX(), y = c.getTom()->getY();
    bool checkFinished = false;

    // Check if there is a bomb in tom's location
    checkBomb(c, c.getTom()->getX(), c.getTom()->getY());

    // While there are still bombs adjacent or under tom, loop will continue running
    // Index is incremented on finding a bomb, and decremented on removing a bomb to get next bomb location to be exploded

    while (!checkFinished)
    {
        // If bomb check returns true, store location and increment index
        if (checkBomb(c, x, y-1))
        {
            xCoord[index] = x;
            yCoord[index] = y-1;
            index++;
        }
        if (checkBomb(c, x+1, y))
        {
            xCoord[index] = x+1;
            yCoord[index] = y;
            index++;
        }
        if (checkBomb(c, x, y+1))
        {
            xCoord[index] = x;
            yCoord[index] = y + 1;
            index++;
        }
        if (checkBomb(c, x-1, y))
        {
            xCoord[index] = x-1;
            yCoord[index] = y;
            index++;
        }
        // Loop ends when qSize is zero (all bombs exploded)
        if (index == 0)
        {
            checkFinished = true;
        }
        // Decrement index to get next bomb coordinates
        else
        {
            index--;
            x = xCoord[index];
            y = yCoord[index];
        }
    }
}
