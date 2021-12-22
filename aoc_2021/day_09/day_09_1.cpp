/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-22
 *  Modified:           2021-12-22
 *
 *
 *
 *  Each number corresponds to the height of a particular location, where 9 is
 *  the highest and 0 is the lowest a location can be. Goal is to find the low
 *  points - the locations that are lower than any of its adjacent locations.
 *  Diagonal locations do not count as adjacent.
 *
 *  The risk level of a low point is 1 plus its height.
 *
 *  What is the sum of the risk levels of all low points on your heightmap?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
    const size_t rows = input.size();
    const size_t len = input[0].length();
        
    int totalRiskLevel = 0;
    
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < len; x++)
        {
            const int num = input[y][x] - '0';
            
            // If value is 9, it can't be less than any adjacent
            if (num == 9)
                continue;
            
            // If not leftmost column
            if (x > 0)
            {
                const int left = input[y][x-1] - '0';
                
                if (num >= left)
                    continue;
            }
                
            // If not rightmost column
            if (x < len - 1)
            {
                const int right = input[y][x+1] - '0';
                
                if (num >= right)
                    continue;
            }
            
            // If not top row
            if (y > 0)
            {
                const int above = input[y-1][x] - '0';
                
                if (num >= above)
                    continue;
            }
            
            // If not bottom row
            if (y < rows - 1)
            {
                const int below = input[y+1][x] - '0';
                
                if (num >= below)
                    continue;
            }
            
            totalRiskLevel += num + 1;
        }
    }
    
    std::cout << "Sum of the risk levels is " << totalRiskLevel << std::endl;
    
    return 0;
}
