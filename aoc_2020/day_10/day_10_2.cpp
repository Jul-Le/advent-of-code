/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            11.12.2020
 *  Modified:           11.12.2020
 *
 *  
 *
 *  How many different ways it is possible to arrange the
 *  adapters, such that the difference between connected
 *  adapter is 1-3 jolts?
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

// Returns number of possible distinct ways adapters can be
// connected, where x is the number of consecutive 1-jolt
// differences between adapters
int f(int x)
{
    if (x < 0)
        return 0;
    if (x == 0 || x == 1)
        return 1;
    
    int a = f(x-1);
    int b = f(x-2);
    int c = f(x-3);
    
    return a + b + c;
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
        
    // Number of distinct ways the adapters can be connected
    long long combinations = 1;
    // Temp var for number of consecutive adapters with 1 jolt difference
    int ones = 0;
    
    for (int i = 0; i < joltDiffs.size(); i++)
    {
        if (joltDiffs.at(i) == 1)
        {
            i++;
            ones = 1;
            while (joltDiffs.at(i) == 1)
            {
                ones++;
                i++;
            }
            combinations *= f(ones);
            ones = 0;
        }
    }
    
    std::cout << combinations << std::endl;
        
    return 0;
}
