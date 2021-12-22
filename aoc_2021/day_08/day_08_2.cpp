/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-11
 *  Modified:           2021-12-20
 *
 *
 *
 *  What is the sum of all output values?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cstring>

enum Segment
{
    Segment_Undefined = '\0',
    Segment_A = 'a',
    Segment_B,
    Segment_C,
    Segment_D,
    Segment_E,
    Segment_F,
    Segment_G
}

// TODO no class needed for digit, just std::string
class Digit
{
public:
    Digit(std::string s) { }
    
private:
};

/**
 *  @brief Display class
 *  @details Contains information about possible connections between inputs and
 *           segments
 */
class Display
{
public:
    Display()
    {
        // Initialize connections
        for (char ch = 'a'; ch <= 'g'; ch++)
        {
            m_wiring[ch] = Segment_Undefined;
            
            for (char s = 'a'; s <= 'g'; s++)
                m_possibleConnections[ch].insert(s);
        }
    }
    
    void addDigit(std::string str)
    {
        const size_t len = str.length();
        
        switch (str.length())
        {
            case 2:
                m_digits.push_back(str, 1);
                break;
            case 3:
                m_digits.push_back(str, 7);
                break;
            case 4:
                m_digits.push_back(str, 4);
                break;
            case 7:
                m_digits.push_back(str, 8);
                break;
            default:
                m_digits.push_back(str, -1);
                break;
        }
    }
    
    void updatePossibleConnections()
    {
        // TODO
    }
    
private:
    std::vector<std::pair<std::string, int>> m_digits;
    std::map<char, Segment> m_wiring;
    std::map<char, std::set<Segment>> m_possibleConnections;
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
        
    int answer = 0;
    
    // Count how many times digits 1, 4, 7 or 8 appear
    for (auto str : input)
    {
        char *token = strtok((char*)str.c_str(), " ");
        
        // First ten digits
        while (strcmp(token, "|"))
        {
            switch (strlen(token))
            {
                case 2: // n == 1
                case 3: // n == 7
                case 4: // n == 4
                case 5: // n == 2 || n == 3 || n == 5
                case 6: // n == 6 || n == 9
                case 7: // n == 8
            }
            
            token = strtok(NULL, " ");
        }
        
        // Discard delimiter "|"
        token = strtok(NULL, " ");
        
        // Output digits
        while (token)
        {
            const size_t len = strlen(token);
            
            if (len == 2 || len == 3 || len == 4 || len == 7)
                answer++;
            
            token = strtok(NULL, " ");
        }
    }
    
    std::cout << "Digits 1, 4, 7 and 8 appear on the output values " << answer << " times." << std::endl;
    
    return 0;
}
