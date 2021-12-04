/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-02
 *  Modified:           2021-12-02
 *
 *
 *
 *  Up/down commands decrease or increase the aim respectively.
 *  When moving forward, horizontal position increases by the
 *  amount specified in the command, and the depth change is aim
 *  multiplied by distance specified in forward command.
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
    int aim = 0;
    
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
                depth += aim * dist;
                break;
            case 'd':
                aim += dist;
                break;
            case 'u':
                aim -= dist;
                break;
        }
    }
    
    std::cout << "hpos = " << hpos << ", depth = " << depth << std::endl
              << hpos << " * " << depth << " = " << (long long)hpos * depth << std::endl;
    
    return 0;
}
