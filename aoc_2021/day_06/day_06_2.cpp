/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-10
 *  Modified:           2021-12-10
 *
 *
 *
 *  How many lanternfish are there after 256 days?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <map>

std::vector<int> parseInput()
{
    std::ifstream file;
    std::string line;
    std::vector<int> data;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    getline(file, line);
    
    char *token = strtok((char*)line.c_str(), ",");
    
    while (token)
    {
        int val;    
        sscanf(token, "%d", &val);
        data.push_back(val);
        token = strtok(NULL, ",");
    }
    
    file.close();
    
    return data;
}

int main()
{
    std::vector<int> input = parseInput();
    std::map<int, long long> timers;
    const int totalDays = 256;
    
    // Part 1 solution is too complex for 256 iterations.
    // In this solution, number of fish is stored as integers rather than adding
    // an element into a container. Thus, the execution time only depends from
    // the number of days, amount of fish doesn't matter.
    
    // Fish have timer values 0...8
    for (auto val : input)
        timers[val]++;
    
    for (int day = 1; day <= totalDays; day++)
    {
        // Values at beginning of day
        std::map<int, long long> startOfDay = timers;
        
        // Update all...
        for (int i = 0; i < 8; i++)
            timers[i] = startOfDay[i+1];
        
        timers[6] += startOfDay[0];
        timers[8] = startOfDay[0];
    }
    
    // The final answer is about 400 times larger than INT32_MAX
    long long totalFish = 0;
    
    for (int i = 0; i <= 8; i++)
        totalFish += timers[i];
    
    std::cout << "After " << totalDays << " days, there are a total of " << totalFish << " fish." << std::endl;
    
    return 0;
}
