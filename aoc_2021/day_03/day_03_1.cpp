/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-03
 *  Modified:           2021-12-04
 *
 *
 *
 *  The diagnostic report (your puzzle input) consists of a list
 *  of binary numbers which, when decoded properly, can tell you
 *  many useful things about the conditions of the submarine.
 *  The first parameter to check is the power consumption.
 *
 *  You need to use the binary numbers in the diagnostic report
 *  to generate two new binary numbers (called the gamma rate
 *  and the epsilon rate). The power consumption can then be
 *  found by multiplying the gamma rate by the epsilon rate.
 *
 *  Each bit in the gamma rate can be determined by finding the
 *  most common bit in the corresponding position of all numbers
 *  in the diagnostic report.
 *
 *  Epsilon is the complement of gamma.
 *
 *  What is the power consumption? (epsilon * gamma)
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

std::vector<std::string> parseInput()
{
    std::ifstream file;
    std::string line;
    std::vector<std::string> data;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    while (getline(file, line))
    {
        data.push_back(line);
    }
    
    file.close();
    
    return data;
}

int main()
{
    std::vector<std::string> input = parseInput();
    
    uint16_t gamma = 0;
    uint16_t epsilon = 0;
    
    const size_t len = input[0].length();
    
    // Loop through each digit
    for (int i = 0; i < len; i++)
    {
        int ones = 0;
        int zeros = 0;
        
        // Loop through each row
        for (auto str : input)
        {
            if (str[i] == '0')
                zeros++;
            else ones++;
        }
        
        if (ones > zeros)
        {
            const unsigned bit = len - i - 1;
            gamma |= (1 << bit);
        }
    }
    
    // Epsilon is complement of gamma, but when complement
    // is taken, all leading zeros will be converted to ones.
    // Mask will be used to zero those leading bits.
    uint16_t mask = 0x0000;
    
    // Set n least significant bits to ones
    for (int i = 0; i < len; i++)
        mask |= (1 << i);
    
    epsilon = ~gamma;
    epsilon &= mask;
    
    std::cout << "The power consumption is " << gamma * epsilon << std::endl;
    
    return 0;
}
