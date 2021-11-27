/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-27
 *  Modified:           2021-11-27
 *
 *
 *
 *  Input is a list of instructions to navigate a city. Each
 *  instruction consists of direction and distance. First, turn
 *  left or right and then proceed forward given number of
 *  steps.
 *  
 *  After all the steps are completed, what is the Manhattan
 *  distance from starting point to finish point?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

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
    
    for (auto instruction : instructions)
    {
        dir = updateDir(dir, instruction.turn);
        
        switch (dir)
        {
            case North: y -= instruction.dist; break;
            case South: y += instruction.dist; break;
            case East:  x += instruction.dist; break;
            case West:  x -= instruction.dist; break;
        }
    }
    
    std::cout << "Easter Bunny HQ is at (" << x << ", " << y << "), "
              << abs(x) + abs(y) << " blocks away." << std::endl;
    
    return 0;
}
