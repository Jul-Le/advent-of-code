/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-22
 *  Modified:           2021-12-22
 *
 *
 *
 *  A basin is all locations that eventually flow downward to a single low
 *  point. Therefore, every low point has a basin, although some basins are very
 *  small. Locations of height 9 do not count as being in any basin, and all
 *  other locations will always be part of exactly one basin.
 *
 *  The size of a basin is the number of locations within the basin, including
 *  the low point.
 *
 *  What is the product of the sizes of three largest basins?
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
    
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < len; x++)
        {
            const int num = input[y][x] - '0';
        }
    }
    
    std::cout << std::endl;
    
    return 0;
}
