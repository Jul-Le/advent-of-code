/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-28
 *  Modified:           2021-11-28
 *
 *
 *
 *  Input is a list of box dimensions. For each box, required
 *  amount of wrapping paper is the area of the box plus area
 *  of the smallest side.
 *
 *  How much wrapping paper is required in total?
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
    
    int smallestFaceArea()
    {
        int _ = m_width * m_height;
        int __ = m_width * m_length;
        int ___ = m_height * m_length;
        
        // https://www.ioccc.org/
        return _<__?_<___?_:___:__<___?__:___;
    }
    
    int area()
    {
        return 2 * m_width * m_height +
               2 * m_width * m_length +
               2 * m_height * m_length;
    }
    
    int requiredPaper()
    {
        return area() + smallestFaceArea();
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
    
    int totalArea = 0;
    
    for (auto box : boxes)
        totalArea += box.requiredPaper();
    
    std::cout << "Total of " << totalArea << " square feet of paper is required" << std::endl;
    
    return 0;
}
