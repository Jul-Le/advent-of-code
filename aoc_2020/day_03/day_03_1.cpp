/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            5.12.2020
 *  Modified:           5.12.2020
 *
 *  
 *
 *  Input is a map containing open squares '.' and trees '#'.
 *  The map repeats itself in horizontal direction, if you move
 *  over the right edge you appear at the left edge.
 *
 *  Question is, starting from top left of the map and moving
 *  3 steps right, one step down until the bottom is reached,
 *  how many trees will be encountered?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// How many steps to the right will be taken every update
#define STEP_R 3
// How many steps down will be taken every update
#define STEP_D 1

int main()
{
    std::string line;
    std::ifstream file;
    std::vector<std::string> map;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    // Read data from file
    while (getline(file, line))
    {
        map.push_back(line);
    }
    
    file.close();
    
    // Current x coordinate on the map.
    // 0 == leftmost column.
    int x = 0;
    
    // Current y coordinate on the map.
    // 0 == top row
    int y = 0;
    
    // Map width
    const int width = map.at(0).length();
    
    // Map height
    const int height = map.size();
    
    // How many trees ('#') have been encountered
    int countTrees = 0;
    
    for (;;)
    {
        x += STEP_R; // Move right
        y += STEP_D; // Move down
        
        // Check whether bottom is reached
        if (y >= height)
            break;
        
        // Map repeats in x direction
        x %= width;
        
        // Check for tree encounter
        if (map.at(y).at(x) == '#')
        {
            countTrees++;
        }
    }
    
    std::cout << countTrees << std::endl;
    
    return 0;
}
