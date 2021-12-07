/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-07
 *  Modified:           2021-12-07
 *
 *
 *
 *  Considering vertical, horizontal and diagonal lines, at how many points do
 *  two or more lines intersect?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct HydroVent
{
    HydroVent(int x0, int y0, int x1, int y1)
    {
        this->x0 = x0;
        this->y0 = y0;
        this->x1 = x1;
        this->y1 = y1;
    }
    
    int x0;
    int y0;
    int x1;
    int y1;
};

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

bool horizontal(HydroVent v)
{
    return v.y0 == v.y1;
}

bool vertical(HydroVent v)
{
    return v.x0 == v.x1;
}

int smaller(int a, int b)
{
    return a < b ? a : b;
}

int greater(int a, int b)
{
    return a > b ? a : b;
}

void addVent(const HydroVent vent, std::vector<std::vector<int>> &oceanFloor)
{
    if (horizontal(vent))
    {
        const int y      = vent.y0;
        const int start  = smaller(vent.x0, vent.x1);
        const int finish = greater(vent.x0, vent.x1);
        
        for (int x = start; x <= finish; x++)
            oceanFloor[y][x]++;
    }
    else if (vertical(vent))
    {
        const int x      = vent.x0;
        const int start  = smaller(vent.y0, vent.y1);
        const int finish = greater(vent.y0, vent.y1);
        
        for (int y = start; y <= finish; y++)
            oceanFloor[y][x]++;
    }
    else // Diagonal
    {
        const int x0 = vent.x0;
        const int x1 = vent.x1;
        const int y0 = vent.y0;
        const int y1 = vent.y1;
        
        const int x_increment = x1 > x0 ? 1 : -1;
        const int y_increment = y1 > y0 ? 1 : -1;
        
        int x = x0;
        int y = y0;
        
        while (x != x1 + x_increment)
        {
            oceanFloor[y][x]++;
            
            x += x_increment;
            y += y_increment;
        }
    }
}

int main()
{
    std::vector<std::string> input = parseInput();
    std::vector<std::vector<int>> oceanFloor;
    std::vector<HydroVent> hydroVents;
    
    int x0, y0, x1, y1, overlapPoints = 0;
    
    oceanFloor.resize(1024);
    for (auto &x : oceanFloor)
        x.resize(1024);
        
    for (auto str : input)
    {
        sscanf(str.c_str(), "%d,%d -> %d,%d", &x0, &y0, &x1, &y1);
        
        hydroVents.push_back(HydroVent(x0, y0, x1, y1));
    }
    
    for (auto vent : hydroVents)
    {
        addVent(vent, oceanFloor);
    }
    
    for (int y = 0; y < 1024; y++)
        for (int x = 0; x < 1024; x++)
            if (oceanFloor[y][x] > 1)
                overlapPoints++;
    
    std::cout << "Two or more lines overlap on " << overlapPoints << " points." << std::endl;
    
    return 0;
}
