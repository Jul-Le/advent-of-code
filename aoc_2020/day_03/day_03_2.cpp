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
 *  x steps right, y steps down until the bottom is reached,
 *  how many trees will be encountered?
 *
 *  Chect the number of encounters for multiple values of x
 *  and y, and multiply the encounters to get the answer.
 *
 *  List of x (right) and y (down) values:
 *  
 *  Right 1, down 1.
 *  Right 3, down 1.
 *  Right 5, down 1.
 *  Right 7, down 1.
 *  Right 1, down 2.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// How many steps to the right will be taken every update
const int STEP_R[5] = { 1, 3, 5, 7, 1 };
// How many steps down will be taken every update
const int STEP_D[5] = { 1, 1, 1, 1, 2 };

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
    int countTrees[5] = { 0 };
        
    for (int i = 0; i < 5; i++)
    {
        // Move to start
        x = 0;
        y = 0;
        
        for (;;)
        {
            x += STEP_R[i]; // Move right
            y += STEP_D[i]; // Move down
            
            // Check whether bottom is reached
            if (y >= height)
                break;
            
            // Map repeats in x direction
            x %= width;
            
            // Check for tree encounter
            if (map.at(y).at(x) == '#')
            {
                countTrees[i]++;
            }
        }
    }
    
    // Initialize to 1, because all countTrees values will
    // be multiplied together, so first value is just
    // multiplied by 1
    long long answer = 1;
    
    for (int i : countTrees)
    {
        answer *= i;
    }
    
    std::cout << answer << std::endl;
    
    return 0;
}
