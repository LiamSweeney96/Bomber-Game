#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <string>

#include "cave.h"
#include "throw.h"
#include "rock.h"
#include "thing.h"
#include "location.h"
#include "move.h"
#include "place.h"
#include "explode.h"

using namespace std;

Cave::Cave(int w, int h) : width(w), height(h) // width and height of the cave
{

    map = new Location**[width];

    // Condensed 2 original nested loops into one nested loop. Altered values to accept user input as size of the cave.
    for (int x = 0; x < width; x++)
    {
        Location** column = new Location*[height];
        map[x] = column;
        for (int y = 0; y < height; y++)
        {
            column[y] = new Location();
            if ( x == 0 || y == 0 || x == width - 1 || y == height - 1 )
                 map[x][y] -> add( new Rock() );
        }
    }
    tom = new Tom();
    // add tom to the middle of the map
    tom -> setLocation( this, width/2,height/2);
}

Cave::Cave(const Cave &copy) noexcept
{
    // Copy constructor. Copied variable values and created deep copies of dynamically allocated varibles.

    width = copy.width;
    height = copy.height;

    map = new Location**[width];

    for (int x = 0; x < width; x++)
    {
        Location** column = new Location*[height];
         map[x] = column;
        for (int y = 0; y < height; y++)
        {
            column[y] = new Location();
            if ( x == 0 || y == 0 || x == width - 1 || y == height - 1 )
                 map[x][y] -> add( new Rock() );
        }
    }
    tom = new Tom();
    // add tom to the middle of the map
    tom -> setLocation( this, width/2,height/2);

}

Cave::~Cave()
{
    // Nested loop to delete all locations in 'map' array the same way it was constructed. Map array is then deleted.
    // 'Tom' doesn't require deleting as Tom gets added as a thing to the map, so is deleted with the map.

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            delete map[i][j];
        }
    }
    delete[] map;
}

void Cave::command (string userCommand)
{
    if (Move().triggersOn(userCommand))
        Move().fire(*this, userCommand);
    else if (Place().triggersOn(userCommand))
        Place().fire(*this, userCommand);

    // Throw command added to run the throw class. Triggered when first word of input is "throw".
    else if (Throw().triggersOn(userCommand))
         Throw().fire(*this, userCommand);
    // Explode command added to run the explode class. Triggered when first word of input is "explode"
    else if (Explode().triggersOn(userCommand))
        Explode().fire(*this, userCommand);

    else
        cerr << "tom doesn't know how to "+userCommand << endl;;
}

void Cave::show()
{
    vector<Thing*>* thingsWithTom = map[tom -> getX()][tom -> getY()] -> getThings();

    // Altered loop conditions to accept user input values as size of the cave.
    for (int y = 0; y < height; y++)
    { // for all rows
        for (int x = 0; x < width; x++) // for all columns
            cout << map[x][y] -> show(); // output whatever we find there

        cout << "  "; // list the things at this location
        if (y <  (int) thingsWithTom -> size())
            cout << (*thingsWithTom)[y] -> getName();

        cout << endl;
    }

    cout << endl;
}
