/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2023-12-02
 *  Modified:           2023-12-06
 *
 *
 *
 *  Input is list of games, where cubes are taken out of a bag, and then put
 *  back, repeated several times (separated by ';').
 *
 *  How many of the games would be possible with a bag that contains
 *  12 red, 13 green and 14 blue cubes?
 */

#include <iostream>
#include <fstream>
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
    
    while (getline(file, line))
        data.push_back(line);
        
    file.close();
    
    return data;
}

std::vector<int> getNumbers(std::string s)
{
    std::vector<int> nums;
    
    char *token = strtok((char*)s.c_str(), ",");
    
    while (token)
    {
        nums.push_back(std::atoi(token));
        
        token = strtok(NULL, ",");
    }
    
    return nums;
}

// If number of cubes taken from the bag is:
// - greater than 14: game is impossible
// - less than 13: game is possible
// - between 13 and 14: depends on the color
//
// Every time less than 13 cubes of one color are taken out, it can be ignored
// If more than 14 are taken out, game is impossible
// Only cases with 13-14 cubes require some ifs
void findNumbers(const std::string &str)
{
    "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
    "Game 1", " 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
        " 3 blue, 4 red",
        " 1 red, 2 green, 6 blue",
        " 2 green"
            {
                " 3 blue",
                " 4 red"
            },
            {
                " 1 red",
                " 2 green",
                " 6 blue"
            },
            {
                " 2 green"
            }
    //          " %d %s"
    //          " %d %c"
    
    
    
    int len = (int)str.length();
    
    for (int i = 0; i < len; i++)
    {
        // Plan is to just iterate and find integers
        // problem is 2-digit numbers
        // need to parse it properly...
    }
    
    for (auto cubes : game)
    {
        if (cubes.count() > 14)
            // Not possible
        else if (cubes.count() == 14 && (cubes.color() == Color::red || cubes.color() == Color::green))
            // Not possible if red or green
        else if (cubes.count() == 13 && cubes.color() == Color::red)
            // Not possible if red
        else
            // Otherwise possible
    }
}

void tbd()
{
    std::string takesStr = getTakesStr();
    std::vector<std::string> takes = getTakes(takesStr);
    std::vector<std::string> cubes = getCubes(takes);
    
    int count;
    char color;
    
    for (auto &s : cubes)
    {
        // get "%d %c"
        sscanf(s, "%d %c", &count, &color);
        
        // If more than 14, impossible
        // If 14 and not blue, impossible
        // If 13 and red, impossible
        if ((count >  14) ||
            (count == 14 && color != 'b') ||
            (count == 13 && color == 'r'))
        {
            isPossible = false;
            break;
        }
        // Less than 13 always possible
        else continue;
    }
}

int main()
{
    std::vector<std::string> input = parseInput();
    
    
    
    return 0;
}
