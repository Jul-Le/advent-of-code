/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-21
 *  Modified:           2021-11-21
 *
 *
 *
 *  How many coordinates exist, that have less than 10000
 *  combined distance to all locations?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>

struct Point
{
    int x;
    int y;
};

int getDistance(Point *a, int x, int y)
{
    int xDist = abs(a->x - x);
    int yDist = abs(a->y - y);
    
    return xDist + yDist;
}

int greater(int a, int b)
{
    return a > b ? a : b;
}

int getTotalDistance(const std::vector<Point*> &points, int x, int y)
{
    int total = 0;
    
    for (auto point : points)
        total += getDistance(point, x, y);
    
    return total;
}

int main()
{
    std::ifstream file;
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    std::string line;
    std::vector<Point*> points;
    
    while (getline(file, line))
    {
        int x, y;
        Point *p = new Point;
        
        sscanf(line.c_str(), "%d, %d", &x, &y);
        
        p->x = x;
        p->y = y;
        points.push_back(p);
    }
    
    file.close();
    
    int max_x = 0, max_y = 0;
    
    for (auto p : points)
    {
        max_x = greater(max_x, p->x);
        max_y = greater(max_y, p->y);
    }
    
    int answer = 0;
    
    for (int y = 0; y <= max_y; y++)
    {
        for (int x = 0; x <= max_x; x++)
        {
            if (getTotalDistance(points, x, y) < 10000)
                answer++;
        }
    }
    
    for (auto p : points)
    {
        delete p;
    }
    
    std::cout << "The answer is " << answer << std::endl;
    
    return 0;
}
