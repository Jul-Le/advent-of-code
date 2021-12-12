/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-11
 *  Modified:           2021-12-12
 *
 *
 *
 *  Input is a list of seven-segment signal patterns. The signal wires are
 *  connected to the segments randomly. Every line in input has the same
 *  connections. First, there are ten unique signal patterns then a "|"
 *  followed by four-digit output value.
 *
 *  How many times do digits 1, 4, 7 or 8 appear on the output value?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

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
        
        // The first ten digits are irrelevant for part 1
        while (strcmp(token, "|"))
            token = strtok(NULL, " ");
        
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
