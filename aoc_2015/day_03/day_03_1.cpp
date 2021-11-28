/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-28
 *  Modified:           2021-11-28
 *
 *
 *
 *  Input is directions to houses where Santa will be
 *  delivering presents.
 *
 *  '^' = North,
 *  'v' = South,
 *  '>' = East,
 *  '<' = West.
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
    int x = 0;
    int y = 0;
    
    visitedHouseLocations.insert({ 0, 0 });
    
    for (auto ch : input)
    {
        switch (ch)
        {
            case '^': y--; break;
            case 'v': y++; break;
            case '>': x++; break;
            case '<': x--; break;
        }
        
        // If house has not yet been visited
        if (visitedHouseLocations.insert({ x, y }).second)
            visitedHouseCount++;
    }
    
    std::cout << visitedHouseCount << " houses receive at least one present." << std::endl;
    
    return 0;
}
