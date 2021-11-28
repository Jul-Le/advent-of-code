/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-28
 *  Modified:           2021-11-28
 *
 *
 *
 *  What is the position of character that causes the floor to
 *  be negative for the first time? First character is position
 *  1.
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
    int pos = 1;
    
    for (auto ch : input)
    {
        if (ch == '(')
            floor++;
        else if (ch == ')')
            floor--;
        else
            std::cout << "The program has encountered an oopsie: '" << ch << '\'' << std::endl;
        
        if (floor < 0)
            break;
        pos++;
    }
    
    std::cout << "Santa enters basement at character position " << pos << std::endl;
    
    return 0;
}
