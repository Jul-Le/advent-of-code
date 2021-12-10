/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-10
 *  Modified:           2021-12-10
 *
 *
 *
 *  Input is a list of timers until a lanternfish creates a new fish. When timer
 *  goes to zero, next day the timer will be reset to 6 and new lanternfish with
 *  timer value of 8 will be created.
 *
 *  How many lanternfish are there after 80 days?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

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

void printStatus(const int day, const std::vector<int> &timers)
{
    std::cout << "After ";
    if (day < 10)
        std::cout << " ";
    std::cout << day;
    if (day == 1)
        std::cout << " day:  ";
    else
        std::cout << " days: ";
    std::cout << timers[0];
    for (int i = 1; i < timers.size(); i++)
        std::cout << "," << timers[i];
    std::cout << std::endl;
}

int main()
{
    std::vector<int> timers = parseInput();
    const int totalDays = 80;
    
    //std::cout << "Initial state: " << timers[0];
    //for (int i = 1; i < timers.size(); i++)
    //    std::cout << "," << timers[i];
    //std::cout << std::endl;
    
    for (int day = 1; day <= totalDays; day++)
    {
        // Decrement every timer
        for (auto &val : timers)
        {
            val--;
        }
        
        const size_t size = timers.size();
        
        // If timer reaches zero, reset and add new
        for (int i = 0; i < size; i++)
        {
            if (timers[i] == -1)
            {
                timers[i] = 6;
                timers.push_back(8);
            }
        }
        
        //printStatus(day, timers);
    }
    
    std::cout << "After " << totalDays << " days, there are a total of " << timers.size() << " fish." << std::endl;
    
    return 0;
}
