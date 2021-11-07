/*
 *  Contributor(s):     Julius L.
 *
 *  Created:            2021-10-28
 *  Modified:           2021-11-07
 *
 *  
 *
 *  After adding all the numbers in the input file,
 *  and looping it if necessary, what is the
 *  first sum that is reached twice?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

int main()
{
    std::string line;
    std::ifstream file;
    
    std::vector<int> numbers;
    std::set<int> sums;
    int sum = 0; // The latest sum
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    while (getline(file, line))
    {
        // Store values to vector
        numbers.push_back(std::stoi(line));
    }
    
    file.close();
    
    int i = 0;
    
    // Starting at zero
    sums.insert(0);
    
    // Just for funzies
    int inputDataLooped = 0;
    
    for (;;)
    {
        sum += numbers.at(i);
        
        // Save the new sum and check if it already exists
        // std::set returns std::pair<iterator, bool>,
        // where the bool is false when the insertion failed 
        if (!sums.insert(sum).second)
            break;
        
        i++;
        
        if (i == numbers.size())
        {
            i = 0;
            inputDataLooped++;
        }
    }
    
    std::cout << "The answer is " << sum << std::endl;
    std::cout << "The input data was looped " << inputDataLooped << " times." << std::endl;
    
    return 0;
}
