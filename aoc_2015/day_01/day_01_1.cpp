/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-28
 *  Modified:           2021-11-28
 *
 *
 *
 *  The directions consist of opening and closing parenthesis.
 *  '(' means to go 1 floor up, ')' means go 1 floor down.
 *
 *  What floor does Santa end up after following the
 *  instructions?
 */

#include <iostream>
#include <fstream>
#include <string>

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
    
    int floor = 0;
    
    for (auto ch : input)
    {
        if (ch == '(')
            floor++;
        else if (ch == ')')
            floor--;
        else
            std::cout << "The program has encountered an oopsie: '" << ch << '\'' << std::endl;
    }
    
    std::cout << "Santa ends up on floor " << floor << std::endl;
    
    return 0;
}
