/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2023-12-16
 *  Modified:           2023-12-16
 *
 *
 *
 *  Description
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

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
    
    getline(file, line);
        
    char *token = strtok((char*)line.c_str(), ",");
    
    while (token)
    {
        data.push_back(token);
        token = strtok(NULL, ",");
    }
    
    file.close();
    
    return data;
}

// Determine the ASCII code for the current character of the string.
// Increase the current value by the ASCII code you just determined.
// Set the current value to itself multiplied by 17.
// Set the current value to the remainder of dividing itself by 256.
int hash(std::string s)
{
    int currentValue = 0;
    
    for (auto ch : s)
    {
        currentValue += (int)ch;
        currentValue *= 17;
        currentValue %= 256;
    }
    
    return currentValue;
}

int main()
{
    std::vector<std::string> input = parseInput();
    
    int sum = 0;
    
    for (auto &str : input)
        sum += hash(str);
    
    std::cout << "Result: " << sum << std::endl;
    
    return 0;
}
