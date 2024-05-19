#include "throw.h"
#include "thing.h"

// Function to throw an object one place adjacent to Tom's current location
void Throw::fire(Cave& c, string userCommand)
{
    // Calls functions which split the input and get the necessary words
    string s = firstCommand(userCommand);
    string d = secondCommand(userCommand);

    // Get current location of Tom
    Location* loc;
    int newTomX = c.getTom()->getX(),  newTomY = c.getTom()->getY();

    // Set location to updated location based on input
    if (d == "north")
    {
        loc = c.getMap()[c.getTom()->getX()][c.getTom()->getY()-1];
        newTomY++;
    }
    else if (d == "east")
    {
        loc = c.getMap()[c.getTom()->getX()+1][c.getTom()->getY()];
        newTomX++;
    }
    else if (d == "south")
    {
        loc = c.getMap()[c.getTom()->getX()][c.getTom()->getY()+1];
        newTomY--;
    }
    else if (d == "west")
    {
        loc = c.getMap()[c.getTom()->getX()-1][c.getTom()->getY()];
        newTomX--;
    }
    else
    {
        cerr << "Invalid direction" << endl;
        return;
    }

    // Check new location is in bounds
    if (newTomX < 0 || newTomY < 0 || newTomX >= c.getHeight() ||newTomY >= c.getHeight())
    {
        cerr << "can't throw object into the void" << endl;
        return;
    }

    // Check if anything is already in the location
    if ( c.getMap()[newTomX][newTomY] -> isBlocking() )
    {
        cerr << "something is blocking the way" << endl;
        return;
    }

    // Throw item
    if (s.compare("coin")==0)
        loc ->add(new Coin());
    else if (s.compare("mushroom")==0)
        loc ->add(new Mushroom());
    else
        cerr << "I don't know how to " << userCommand << endl;

}
