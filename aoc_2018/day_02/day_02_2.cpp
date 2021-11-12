/*
 *  Contributor(s):     Julius L.
 *
 *  Created:            2021-11-12
 *  Modified:           2021-11-12
 *
 *  
 *
 *  There are two IDs that differ by exactly one character; all
 *  the other characters are identical and in the same
 *  positions.
 *  
 *  What is the character string that remains, when the one
 *  differing character is removed from the string?
 */

#include <iostream>
#include <fstream>
#include <vector>

/**
 *  @brief Compare two strings and try to find single character that differs
 *  @param a First string
 *  @param b Seconds string
 *  @return If single mismatching character, return index of that character, else return -1
 */
int compareStrings (std::string a, std::string b)
{
    // Index of mismatching character
    int mismatch = -1;
    
    // We just take for granted that the strings are equal length
    for (int i = 0; i < a.length(); i++)
    {
        // If characters match
        if (a.at(i) == b.at(i))
            continue;
        // If first mismatch found
        else if (mismatch == -1)
        {
            mismatch = i;
        }
        // If multiple mismatchs found
        else
            return -1;
    }
    return mismatch;
}

int main()
{
    std::string line;
    std::ifstream file;
    
    std::vector<std::string> ids;
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    while (getline(file, line))
    {
        // Store IDs to vector
        ids.push_back(line);
    }
    
    file.close();
    
    int index = -1;
    std::string correctString = "";
    
    for (int i = 0; i < ids.size() - 1; i++)
    {
        for (int j = 1; j < ids.size(); j++)
        {
            index = compareStrings(ids.at(i), ids.at(j));
            
            if (index != -1)
                break;
        }
        if (index != -1)
        {
            correctString = ids.at(i);
            break;
        }
    }
    
    correctString.erase(index, 1);
    
    std::cout << correctString << std::endl;
    
    return 0;
}
