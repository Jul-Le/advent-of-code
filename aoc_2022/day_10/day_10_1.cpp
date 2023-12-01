/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2023-11-18
 *  Modified:           2023-11-18
 *
 *  
 *
 *  Input is a set of instructions.
 *  addx 3      adds 3 to 'X' register, takes 2 clock cycles
 *  noop        does nothing, takes 1 clock cycle
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum class InstructionType
{
    addx,
    noop
};

class Instruction
{
public:
    Instruction(std::string s)
    {
        // Assign instruction type and value
    }
    
private:
    InstructionType m_type;
    int m_value;
};


std::vector<std::string> parseInput()
{
    std::ifstream file;
    std::vector<std::string> data;
    std::string line;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    while (getline(file, line))
        data.push_back(line);
        
    file.close();
    
    return data;
}

long compute(const std::vector<std::string> &instructions)
{
    for (auto cmd : instructions)
    {
        if (/* first 4 chars of cmd are "addx" */)
            ;
        else if (/* firest 4 chars of cmd are "noop" */)
            ;
        else
            // error msg
    }
}

int main()
{
    std::vector<std::string> input = parseInput();
    
    long x = compute(input);
    
    for (auto line : input)
        std::cout << line << std::endl;
    
    return 0;
}
