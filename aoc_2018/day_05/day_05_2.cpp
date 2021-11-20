/*
 *  Contributor(s):     Julius L.
 *
 *  Created:            2021-11-20
 *  Modified:           2021-11-20
 *
 *
 *
 *  If all characters 'a' and 'A' are removed and then the
 *  reactions are run like part 1, the remaining string has
 *  some length. With what characters of same type and
 *  different case removed, the remaining string lenght is the
 *  smallest?
 */

#include <iostream>
#include <fstream>
#include <vector>

#include <boost/algorithm/string.hpp>

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
    
    std::string original, polymer;
    
    getline(file, original);
    file.close();
    
    std::vector<int> polymerLengths;
    
    for (char ch = 'A'; ch <= 'Z'; ch++)
    {
        polymer = original;
        
        std::string lower = "";
        std::string upper = "";
        
        lower += (char)(ch + 32);
        upper += ch;
        
        boost::erase_all(polymer, lower);
        boost::erase_all(polymer, upper);
        
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
        
        polymerLengths.push_back(polymer.length());
    }
    
    int shortestPolymer = original.length();
    
    for (auto i : polymerLengths)
    {
        if (shortestPolymer > i)
            shortestPolymer = i;
    }
    
    std::cout << "Shortest polymer has " << shortestPolymer
              << " units." << std::endl;
    
    return 0;
}
