/*
 *  Contributor(s):     Julius L.
 *
 *  Created:            2021-11-20
 *  Modified:           2021-11-20
 *
 *
 *
 *  Input is a string. If two of the same character that are
 *  different case follow one another, they will be removed.
 *  After removing all occurences, what is the length of
 *  remaining string?
 */

#include <iostream>
#include <fstream>
#include <vector>

bool react(char a, char b)
{
    return abs(a-b) == 32;
}

int main()
{
    std::ifstream file;
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    std::string polymer;
    
    getline(file, polymer);
    file.close();
    
    int i = 0;
    
    for (;;)
    {
        // If polymers react
        if (react(polymer.at(i), polymer.at(i+1)))
        {
            // Remove them
            polymer.erase(i, 2);
            
            // Go back one step, in case removal causes new reaction
            if (i > 0)
                i--;
        }
        else // If no reaction, go forward
            i++;
        
        // Iterate until end is reached
        if (i + 1 == polymer.length())
            break;
    }
    
    std::cout << "After all reactions, " << polymer.length()
              << " units remain." << std::endl;
    
    return 0;
}
