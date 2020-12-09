/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            9.12.2020
 *  Modified:           9.12.2020
 *
 *  
 *
 *  Numbers in the input list are valid, if they are a sum of
 *  two previous 25 numbers.
 *
 *  What is the first invalid number in the list?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int PREAMBLE = 25;

/**
 *  @brief Find the first invalid number in the container
 *  @param numbers Number container
 *  @return Value of the invalid number
 *  @details
 *      Start from the n + PREAMBLEth number in the list.
 *      Subtract nth number from n+PREAMBLEth number, and
 *      try to find the result somewhere between n+1 and
 *      n + PREAMBLE - 1, includive.
 *      If not found, subtract n+1th number from n+PREAMBLEth
 *      and try to find the result between n+2 and
 *      n + PREAMBLE - 1.
 *      If match is found, number is valid and repeat the
 *      process for the n + PREAMBLE + 1th number.
 */
int findInvalidNumber(std::vector<int> numbers)
{
    int i = PREAMBLE;
    bool found = false; // Whether invalid number is found
    
    while (i < numbers.size())
    {
        found = true;
        for (int j = 0; j < PREAMBLE; j++)
        {
            int a = numbers.at(i - PREAMBLE + j);
            
            auto it = std::find(numbers.begin() + i - PREAMBLE + j,
                                numbers.begin() + i,
                                numbers.at(i) - a);
            
            if (it != numbers.begin() + i)
            {
                found = false;
                break;
            }
        }
        if (!found)
            i++;
        else break;
    }
    return numbers.at(i);
}

int main()
{
    std::string line;
    std::ifstream file;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    std::vector<int> numbers;
    
    // Read data from file
    while (getline(file, line))
    {        
        int val;
        
        // Parse line
        sscanf(line.c_str(), "%d", &val);
        
        // Add to numbers container
        numbers.push_back(val);
    }
    
    file.close();
    
    int invalid = findInvalidNumber(numbers);
    
    std::cout << invalid << std::endl;
    
    return 0;
}
