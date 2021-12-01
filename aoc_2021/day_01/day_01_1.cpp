/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-01
 *  Modified:           2021-12-01
 *
 *
 *
 *  Each line of input is a measurement of sea floor depth.
 *
 *  How many times the depth measurement incrases from the
 *  previous measurement?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<int> parseInput()
{
    std::ifstream file;
    std::string line;
    std::vector<int> data;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    while (getline(file, line))
    {
        data.push_back(std::stoi(line));
    }
    
    file.close();
    
    return data;
}

int main()
{
    std::vector<int> input = parseInput();
    
    int answer = 0;
    
    for (int i = 0; i < input.size() - 1; i++)
    {
        if (input[i+1] > input[i])
            answer++;
    }
    
    std::cout << answer << " measurements are larger than the previous measurement." << std::endl;
    
    return 0;
}
