/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-27
 *  Modified:           2021-11-27
 *
 *
 *
 *  Input describes movement on a keypad. After each line, a
 *  chosen key is pressed. Each line of input corresponds to one
 *  key press. Move is ignored if it would lead outside the
 *  keypad.
 *  
 *  What is the passcode (combination of key presses)?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Keypad
{
public:
    Keypad() : m_chosenButton(5)
    {
        
    }
    
    void move(char ch)
    {
        switch (ch)
        {
            case 'U':
            {
                if (m_chosenButton > 3)
                    m_chosenButton -= 3;
                break;
            }
            case 'D':
            {
                if (m_chosenButton < 7)
                    m_chosenButton += 3;
                break;
            }
            case 'R':
            {
                if (m_chosenButton % 3 != 0)
                    m_chosenButton ++;
                break;
            }
            case 'L':
            {
                if ((m_chosenButton - 1) % 3 != 0)
                    m_chosenButton--;
                break;
            }
            default:
                std::cout << "Something something at line " << __LINE__ << std::endl;
                break;
        }
    }
    
    int button() const { return m_chosenButton; }
    
private:
    int m_chosenButton;
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
    std::vector<int> code;
    
    Keypad keypad;
    
    for (auto str : input)
    {
        for (auto ch : str)
        {
            keypad.move(ch);
        }
        code.push_back(keypad.button());
    }
    
    std::cout << "The passcode is ";
    for (auto i : code)
        std::cout << i;
    
    std::cout << std::endl;
    
    return 0;
}
