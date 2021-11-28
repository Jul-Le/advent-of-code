/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-28
 *  Modified:           2021-11-28
 *
 *
 *
 *  Santa and Robo-Santa take turns and Santa follows first,
 *  third, fifth, ... instruction and Robo-Santa follows
 *  second, fourth, ... instruction.
 *
 *  How many houses receive at least one present?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>

std::string parseInput()
{
    std::ifstream file;
    std::string line;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    getline(file, line);
    
    file.close();
    
    return line;
}

int main()
{
    std::string input = parseInput();
    std::set<std::pair<int, int>> visitedHouseLocations;
    
    int visitedHouseCount = 1; // Starting location counts as one
    int santa_x = 0;
    int santa_y = 0;
    int robo_x = 0;
    int robo_y = 0;
    int i = 0;
    
    visitedHouseLocations.insert({ 0, 0 });
    
    for (auto ch : input)
    {
        // Santa
        if (i % 2 == 0)
        {
            switch (ch)
            {
                case '^': santa_y--; break;
                case 'v': santa_y++; break;
                case '>': santa_x++; break;
                case '<': santa_x--; break;
            }
            // If house has not yet been visited
            if (visitedHouseLocations.insert({ santa_x, santa_y }).second)
                visitedHouseCount++;
        }
        // Robo-Santa
        else
        {
            switch (ch)
            {
                case '^': robo_y--; break;
                case 'v': robo_y++; break;
                case '>': robo_x++; break;
                case '<': robo_x--; break;
            }
            
            // If house has not yet been visited
            if (visitedHouseLocations.insert({ robo_x, robo_y }).second)
                visitedHouseCount++;
        }
        i++;
    }
    
    std::cout << visitedHouseCount << " houses receive at least one present." << std::endl;
    
    return 0;
}
