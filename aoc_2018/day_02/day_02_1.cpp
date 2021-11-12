/*
 *  Contributor(s):     Julius L.
 *
 *  Created:            2021-11-12
 *  Modified:           2021-11-12
 *
 *  
 *
 *  What is the product of times an id contains exactly two of
 *  any letter and times an id contains exactly three of any
 *  letter?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

int main()
{
    std::string line;
    std::ifstream file;
    
    std::vector<std::string> ids;
    std::map<char, int> letterCounts;
    
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
    
    // Insert every letter and initialize count to zero
    for (char ch = 'a'; ch <= 'z'; ch++)
    {
        letterCounts.insert(std::pair<char, int>(ch, 0));
    }
    
    // Get count of times a letter appears exactly twice in an id
    // Get count of times a letter appears exactly three times in an id
    // Multiple letters can appear twice (or thrice) in same id but they only count once
    
    int twoTimes = 0;
    int threeTimes = 0;
    
    // For every id...
    for (auto id : ids)
    {
        // For every char in id...
        for (char ch : id)
        {
            // Count letter occurences
            letterCounts.at(ch)++;
        }
        
        int temp2 = 0;
        int temp3 = 0;
        
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            // If some letter occurs two times
            if (letterCounts.at(ch) == 2)
                temp2 = 1;
            // If some letter occurs three times
            else if (letterCounts.at(ch) == 3)
                temp3 = 1;
            
            // Clear letter counts for next id
            letterCounts.at(ch) = 0;
        }
        
        twoTimes += temp2;
        threeTimes += temp3;   
    }
    
    std::cout << twoTimes << " * " << threeTimes << " = " << twoTimes * threeTimes << std::endl;
    
    return 0;
}
