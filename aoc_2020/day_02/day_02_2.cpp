/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            5.12.2020
 *  Modified:           5.12.2020
 *
 *  
 *
 *  Input is a list of passwords and password policies, that are
 *  different for each password.
 *
 *  Example: "1-3 a: abcde"
 *
 *  Password is valid, if it contains the letter 'a' as a first
 *  or third letter but not both.
 *
 *  Question is, how many passwords are valid?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

class Password
{
public:
    Password(int min, int max, char letter, std::string text)
        : m_min(min), m_max(max), m_letter(letter), m_text(text)
    {
        
    }
    
    void print()
    {
        std::cout << m_min << " " << m_max << " " << m_letter << " " << m_text << std::endl;
    }
    
    bool isValid()
    {
        // Look for the letter from these indexes
        int i1 = m_min - 1;
        int i2 = m_max - 1;
        
        // How many times the m_letter occurs in i1 or i2 position of m_text
        int count = 0;
        
        if (m_text.at(i1) == m_letter)
            count++;
        
        if (m_text.at(i2) == m_letter)
            count++;
        
        return (count == 1);
    }
    
private:
    int m_min; // Minimum number of required characters
    int m_max; // Maximum number of required characters
    char m_letter; // Required character
    std::string m_text; // Password
};

int main()
{
    std::string line;
    std::ifstream file;
    std::list<Password> pwList;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    // Read data from file
    while (getline(file, line))
    {
        int min, max;
        char ch;
        char str[32];
        
        // Split line to min, max, letter, password text
        sscanf(line.c_str(), "%d-%d %c: %s\n", &min, &max, &ch, str);
        
        // Create password object
        Password pw = Password(min, max, ch, str);
        
        // Add to pasword list
        pwList.push_back(pw);
    }
    
    file.close();
    
    // Number of valid passwords
    int validCount = 0;
    
    // Count valid passwords
    for (auto pw : pwList)
    {
        if (pw.isValid())
            validCount++;
    }
    
    std::cout << validCount << std::endl;
    
    return 0;
}
