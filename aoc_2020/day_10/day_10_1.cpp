/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            9.12.2020
 *  Modified:           9.12.2020
 *
 *  
 *
 *  Input is a list of adapter joltages. Outlet joltage is 3
 *  and device joltage is max adapter joltage + 3.
 *
 *  What is the product of 1-jolt differences and 3-jolt
 *  differences between all joltages?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 *  @brief Return vector containing differences between
 *         consecutive values of the input vector
 *  @param numbers Integer vector, sorted ascending
 *  @return Vector, size is input vector size - 1
 */
std::vector<int> diff(std::vector<int> &numbers)
{
    std::vector<int> differences;
    
    for (int i = 0; i < numbers.size() - 1; i++)
    {
        int a = numbers.at(i);
        int b = numbers.at(i+1);
        
        differences.push_back(b-a);
    }
    return differences;
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
    
    std::vector<int> joltages;
    
    // Read data from file
    while (getline(file, line))
    {        
        int jolt;
        
        // Parse line
        sscanf(line.c_str(), "%d", &jolt);
        
        // Add to container
        joltages.push_back(jolt);
    }
    
    file.close();
    
    // Add outlet
    int outletJoltage = 0;
    joltages.push_back(outletJoltage);
    
    std::sort(joltages.begin(), joltages.end());
    
    // Add device
    int largestJoltage = joltages.at(joltages.size() - 1);
    int deviceJoltage = largestJoltage + 3;
    joltages.push_back(deviceJoltage);
    
    std::vector<int> joltDiffs = diff(joltages);
    
    int ones = std::count(joltDiffs.begin(), joltDiffs.end(), 1);
    int threes = std::count(joltDiffs.begin(), joltDiffs.end(), 3);
    
    std::cout << ones << " * " << threes << " = " << ones * threes << std::endl;
    
    return 0;
}
