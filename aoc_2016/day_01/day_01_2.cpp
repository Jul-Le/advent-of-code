/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-27
 *  Modified:           2021-11-27
 *
 *
 *
 *  What is the Manhattan distance to the first point you visit
 *  twice?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <set>

enum Direction
{
    North, South, East, West
};

struct Instruction
{
    char turn;
    int dist;
};

std::vector<Instruction> parseInput()
{
    std::ifstream file;
    std::string line;
    std::vector<Instruction> instructions;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    getline(file, line);
    file.close();
    
    char *token = strtok((char*)line.c_str(), ", ");
    
    while (token)
    {
        Instruction instruction;
        char turn;
        int dist;
        
        sscanf(token, "%c%d", &turn, &dist);
        
        instruction.turn = turn;
        instruction.dist = dist;
        
        instructions.push_back(instruction);
        
        token = strtok(NULL, ", ");
    }
    
    return instructions;
}

Direction updateDir(Direction dir, char turn)
{
    switch (dir)
    {
        case North: return turn == 'R' ? East : West;
        case South: return turn == 'R' ? West : East;
        case East:  return turn == 'R' ? South : North;
        case West:  return turn == 'R' ? North : South;
        default:
            std::cout << "The destination is in another castle" << std::endl;
            return dir;
    }
}

int main()
{
    std::vector<Instruction> instructions = parseInput();
    
    // Starting position
    int x = 0;
    int y = 0;
    Direction dir = North;
    
    std::set<std::pair<int, int>> visitedLocations;
    visitedLocations.insert({ 0, 0 });
        
    for (auto instruction : instructions)
    {
        dir = updateDir(dir, instruction.turn);
        
        for (int i = 0; i < instruction.dist; i++)
        {
            switch (dir)
            {
                case North: y--; break;
                case South: y++; break;
                case East:  x++; break;
                case West:  x--; break;
            }
            // If location already visited
            if (!visitedLocations.insert({ x, y }).second)
                goto finish;
        }
    }
    
finish:
    std::cout << "First location you visit twice is at (" << x << ", " << y << "), "
              << abs(x) + abs(y) << " blocks away." << std::endl;
    
    return 0;
}
