/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-27
 *  Modified:           2021-11-27
 *
 *
 *
 *  In part 2, the keypad layout is different:
 *
 *      1
 *    2 3 4
 *  5 6 7 8 9
 *    A B C
 *      D
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Keypad
{
public:
    Keypad() : m_chosenButton('5')
    {
        
    }
    
    void move(char ch)
    {
        switch (ch)
        {
            case 'U':
            {
                switch (m_chosenButton)
                {
                    case '1': break;
                    case '2': break;
                    case '3': m_chosenButton = '1'; break;
                    case '4': break;
                    case '5': break;
                    case '6': m_chosenButton = '2'; break;
                    case '7': m_chosenButton = '3'; break;
                    case '8': m_chosenButton = '4'; break;
                    case '9': break;
                    case 'A': m_chosenButton = '6'; break;
                    case 'B': m_chosenButton = '7'; break;
                    case 'C': m_chosenButton = '8'; break;
                    case 'D': m_chosenButton = 'B'; break;
                }
                break;
            }
            case 'D':
            {
                switch (m_chosenButton)
                {
                    case '1': m_chosenButton = '3'; break;
                    case '2': m_chosenButton = '6'; break;
                    case '3': m_chosenButton = '7'; break;
                    case '4': m_chosenButton = '8'; break;
                    case '5': break;
                    case '6': m_chosenButton = 'A'; break;
                    case '7': m_chosenButton = 'B'; break;
                    case '8': m_chosenButton = 'C'; break;
                    case '9': break;
                    case 'A': break;
                    case 'B': m_chosenButton = 'D'; break;
                    case 'C': break;
                    case 'D': break;
                }
                break;
            }
            case 'R':
            {
                switch (m_chosenButton)
                {
                    case '1': break;
                    case '2': m_chosenButton = '3'; break;
                    case '3': m_chosenButton = '4'; break;
                    case '4': break;
                    case '5': m_chosenButton = '6'; break;
                    case '6': m_chosenButton = '7'; break;
                    case '7': m_chosenButton = '8'; break;
                    case '8': m_chosenButton = '9'; break;
                    case '9': break;
                    case 'A': m_chosenButton = 'B'; break;
                    case 'B': m_chosenButton = 'C'; break;
                    case 'C': break;
                    case 'D': break;
                }
                break;
            }
            case 'L':
            {
                switch (m_chosenButton)
                {
                    case '1': break;
                    case '2': break;
                    case '3': m_chosenButton = '2'; break;
                    case '4': m_chosenButton = '3'; break;
                    case '5': break;
                    case '6': m_chosenButton = '5'; break;
                    case '7': m_chosenButton = '6'; break;
                    case '8': m_chosenButton = '7'; break;
                    case '9': m_chosenButton = '8'; break;
                    case 'A': break;
                    case 'B': m_chosenButton = 'A'; break;
                    case 'C': m_chosenButton = 'B'; break;
                    case 'D': break;
                }
                break;
            }
            default:
                std::cout << "Something something at line " << __LINE__ << std::endl;
                break;
        }
    }
    
    char button() const { return m_chosenButton; }
    
private:
    char m_chosenButton;
};

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
    std::string code;
    
    Keypad keypad;
    
    for (auto str : input)
    {
        for (auto ch : str)
        {
            keypad.move(ch);
        }
        code += keypad.button();
    }
    
    std::cout << "The passcode is " << code << std::endl;
    
    return 0;
}
