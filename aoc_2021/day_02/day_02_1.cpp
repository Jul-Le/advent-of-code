/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-02
 *  Modified:           2021-12-02
 *
 *
 *
 *  Input is a list of instructions how to move the submarine:
 *  up, down or forward plus the distance how much to move.
 *
 *  After executing all the instructions, what is the product of
 *  the horizontal position and the depth?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> parseInput()
{
    std::ifstream file;
    std::string line;
    std::vector<std::string> data;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    while (getline(file, line))
    {
        data.push_back(line);
    }
    
    file.close();
    
    return data;
}

int main()
{
    std::vector<std::string> input = parseInput();
    
    int hpos = 0;
    int depth = 0;
    
    for (auto str : input)
    {
        // Only first character is required to parse the command
        char cmd;
        int dist;
        
        sscanf(str.c_str(), "%c%*s %d", &cmd, &dist);
        
        switch (cmd)
        {
            case 'f':
                hpos += dist;
                break;
            case 'd':
                depth += dist;
                break;
            case 'u':
                depth -= dist;
                break;
        }
    }
    
    std::cout << "hpos = " << hpos << ", depth = " << depth << std::endl
              << hpos << " * " << depth << " = " << hpos * depth << std::endl;
    
    return 0;
}
