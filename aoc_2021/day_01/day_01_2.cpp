/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-01
 *  Modified:           2021-12-01
 *
 *
 *
 *  This time, consider sum of three consecutive measurements
 *  [0]+[1]+[2] and [1]+[2]+[3]...
 *
 *  How many times the sum increases from the previous
 *  measurement?
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
    
    for (int i = 0; i < input.size() - 3; i++)
    {
        int sum1 = input[i+0] + input[i+1] + input[i+2];
        int sum2 = input[i+1] + input[i+2] + input[i+3];
        
        if (sum2 > sum1)
            answer++;
    }
    
    std::cout << answer << " measurements are larger than the previous measurement." << std::endl;
    
    return 0;
}
