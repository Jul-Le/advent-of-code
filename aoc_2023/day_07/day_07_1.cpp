/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2023-12-07
 *  Modified:           2023-12-09
 *
 *
 *
 *  Description
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Hand
{
public:
    Hand(const std::string &str)
    {
        m_rank = parseRank(str);
        m_bid = parseBid(str);
    }
    
    int rank();
    int bid();
    
private:
    int m_rank;
    int m_bid;
    
    int parseRank(const std::string &str)
    {
        char[5] hand;
        std::string handStr;
        
        sscanf(s.c_str(), "%c%c%c%c%c %d", hand[0], hand[1], hand[2], hand[3], hand[4], &value);
        handStr = hand;
        // TODO need to parse the kicker
        // maybe use a variable
    }
    
    int parseBid(const std::string &str)
    {
        
    }
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

int getHandRank(const std::string &str)
{
    // If all characters are the same
    
    // If 4 of the same character
    
    // If only 2 different characters
    
    // If 3 of the same characters
    
    // If only 3 different characters
    
    // If only 4 different characters
}

void func()
{
    
    
}

int main()
{
    std::vector<std::string> input = parseInput();
    
    for (auto line : input)
        process(line);
    
    return 0;
}
