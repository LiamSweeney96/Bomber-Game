#ifndef COMMAND_H
#define COMMAND_H

#include "cave.h"

#include <string>

using namespace std;

// superclass of all user commands.
class Command {

public:
    Command(string triggerWord) : trigger(triggerWord) {}

    virtual bool triggersOn (string userCommand)
    {
        string userTrigger = userCommand;
        int index = userCommand.find(' ');
        if (index > 0)
                userTrigger = userCommand.substr(0, userCommand.find(' '));
        return trigger.compare(userTrigger) == 0;
    }

    virtual void fire(Cave& c, string arguments) =0;



protected:

    string tail(string userCommand) {

            int pos = userCommand.find(' ');
            if (pos >= 0)
                return userCommand.substr(userCommand.find(' ')+1, userCommand.length());
            else
                return "";
        }

    // Added function to pull first string command out of the user input
    // Finds location of first space, then counts number of chars until next space to get given command
    string firstCommand(string userCommand) {

        int spaceCount = 0, loc = 0;

        for (int i = 0; i < int(userCommand.length()); i++)
        {
            if (userCommand.at(i) == ' ' && spaceCount == 0)
            {
                spaceCount++;
                loc = (i + 1);
                continue;
            }
            if (userCommand.at(i) == ' ' && spaceCount == 1)
            {
                return userCommand.substr(loc, i - loc);
            }
        }
        return "";
    }

    // Added function to pull second string command out of the user input
    // Finds location of second space, then creates substring from that location +1 to the end of userCommand
    string secondCommand(string userCommand) {

        int spaceCount = 0;

        for (int i = 0; i < int(userCommand.length()); i++)
        {
            if (userCommand.at(i) == ' ')
            {
                spaceCount++;
                if (spaceCount == 2)
                {
                    return userCommand.substr((i + 1), userCommand.length() - i);
                }
            }
        }
        return "";
    }


private:
    string trigger;
};

#endif // COMMAND_H
