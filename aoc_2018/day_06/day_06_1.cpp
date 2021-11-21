/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-21
 *  Modified:           2021-11-21
 *
 *
 *
 *  Using only the Manhattan distance, determine the area around
 *  each coordinate by counting the number of integer X,Y
 *  locations that are closest to that coordinate (and aren't
 *  tied in distance to any other coordinate).
 *  
 *  Goal is to find the size of the largest area that isn't
 *  infinite.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>

struct Point
{
    int x;
    int y;
    int area;
    bool inf;
};

int getDistance(Point *a, Point *b)
{
    int xDist = abs(a->x - b->x);
    int yDist = abs(a->y - b->y);
    
    return xDist + yDist;
}

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

Point *getClosest(const std::vector<Point*> &points, int x, int y)
{
    int closestDist = INT_MAX;
    Point *closestPoint = nullptr;
    bool equidistant = false;
    
    for (auto point : points)
    {
        int dist = getDistance(point, x, y);
        
        if (dist == closestDist)
            equidistant = true;
            
        else if (dist < closestDist)
        {
            closestDist = dist;
            closestPoint = point;
            equidistant = false;
        }
    }
    
    if (equidistant)
        return nullptr;
    else
        return closestPoint;
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
        p->area = 0;
        p->inf = false;
        points.push_back(p);
    }
    
    file.close();
    
    // Find out which points have infinite number of closest locations
    // Find the largest finite area
    int max_x = 0, max_y = 0;
    
    for (auto p : points)
    {
        max_x = greater(max_x, p->x);
        max_y = greater(max_y, p->y);
    }
    
    for (int y = 0; y <= max_y; y++)
    {
        for (int x = 0; x <= max_x; x++)
        {
            Point *closest = getClosest(points, x, y);
            
            // If two or more points are equidistant from given x,y coordinate
            // or if it has been determined that this point has infinite area, continue
            if (!closest || closest->inf)
                continue;
            
            // If point is closest to some cell at the edge of measured area,
            // it will have infinite area
            if (x == 0 || y == 0 || x == max_x || y == max_y)
            {
                closest->inf = true;
                continue;
            }
            
            // There is a single point that is closest to given coordinate, increment its area
            closest->area++;
        }
    }
    
    int largestArea = 0;
    
    for (auto p : points)
    {
        std::cout << "Point (" << p->x << ", " << p->y << ") has area of ";
                  
        if (p->inf)
            std::cout << "infinity";
        else
        {
            std::cout << p->area;
            largestArea = greater(largestArea, p->area);
        }
        
        std::cout << std::endl;
        
        delete p;
    }
    
    std::cout << "The largest finite area is " << largestArea << std::endl;
    
    return 0;
}
