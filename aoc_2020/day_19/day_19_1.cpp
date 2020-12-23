/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            19.12.2020
 *  Modified:           19.12.2020
 *
 *  
 *
 *  Description
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Rule
{
public:
    Rule(char ch = '\0')
        : m_char(ch)
    {
        
    }
    
private:
    std::vector<Rule*> m_rules;
    std::vector<Rule*> m_altRules
    char m_char;
}

int main()
{
    std::string line;
    std::ifstream file;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    while(getline(file, line))
    {
        std::cout << line << std::endl;
    }
    
    file.close();
    
    return 0;
}
