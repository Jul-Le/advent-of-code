/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            17.12.2020
 *  Modified:           17.12.2020
 *
 *  
 *
 *  Description
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Point
{
    int x;
    int y;
    int z;
};

class Cube
{
    Cube();
    
    bool isActive();
    
    bool m_active;
};

bool cubesIntersect(const Cube &a, const Cube &b);
bool pointWithinCube(const Point &p, const cube &c);

int main()
{
    std::string line;
    std::ifstream file;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    while(getline(file, line))
    {
        std::cout << line << std::endl;
    }
    
    file.close();
    
    return 0;
}
