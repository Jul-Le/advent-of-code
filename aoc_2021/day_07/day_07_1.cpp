/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-10
 *  Modified:           2021-12-10
 *
 *
 *
 *  Given a list of horizontal positions of crab submarines and that a change of
 *  horizontal position costs 1 unit of fuel, what is the minimum fuel
 *  consumption when all crabs are moved to same horizontal position?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <set>

std::multiset<int> parseInput()
{
    std::ifstream file;
    std::string line;
    std::multiset<int> data;
    
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
        data.insert(val);
        token = strtok(NULL, ",");
    }
    
    file.close();
    
    return data;
}

int main()
{
    std::multiset<int> input = parseInput();
    const size_t size = input.size();
    int count = 0;
    int i = -1;
    
    // Get median
    while (count < size / 2)
    {
        i++;
        count += input.count(i);
    }
    
    const int median = i;
    int fuelSpent = 0;
    
    for (auto hpos : input)
        fuelSpent += abs(hpos - median);
    
    std::cout << "Minimum fuel required is " << fuelSpent << " units, "
              << "when moving to position " << median << std::endl;
    
    return 0;
}
