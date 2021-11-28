/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-28
 *  Modified:           2021-11-28
 *
 *
 *
 *  Ribbon required for each present is equivalent to smallest
 *  perimeter of any face plus the volume of the present.
 *
 *  How much ribbon is required?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Cuboid
{
public:
    Cuboid(int w, int h, int l)
        : m_width(w), m_height(h), m_length(l)
    {
        
    }
    
    int smallestFacePerimeter()
    {
        int p1 = 2 * m_width + 2 * m_height;
        int p2 = 2 * m_width + 2 * m_length;
        int p3 = 2 * m_height + 2 * m_length;
        
        return p1 < p2 ? p1 < p3 ? p1 : p3 : p2 < p3 ? p2 : p3;
    }
    
    int volume()
    {
        return m_width * m_height * m_length;
    }
    
    int requiredRibbon()
    {
        return smallestFacePerimeter() + volume();
    }
    
private:
    int m_width;
    int m_height;
    int m_length;
};

std::vector<Cuboid> parseInput()
{
    std::ifstream file;
    std::string line;
    std::vector<Cuboid> boxes;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    while (getline(file, line))
    {
        int w, h, l;
        sscanf(line.c_str(), "%dx%dx%d", &w, &h, &l);
        boxes.push_back(Cuboid(w, h, l));
    }
    
    file.close();
    
    return boxes;
}

int main()
{
    std::vector<Cuboid> boxes = parseInput();
    
    int totalRibbon = 0;
    
    for (auto box : boxes)
        totalRibbon += box.requiredRibbon();
    
    std::cout << "Total of " << totalRibbon << " feet of ribbon is required" << std::endl;
    
    return 0;
}
