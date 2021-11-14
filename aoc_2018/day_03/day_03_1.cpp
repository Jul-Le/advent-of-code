/*
 *  Contributor(s):     Julius L.
 *
 *  Created:            2021-11-12
 *  Modified:           2021-11-14
 *
 *  
 *
 *  Input is a list of rectangles.
 *
 *  What is the total number of squares where two or more
 *  rectangles overlap?
 */

#include <iostream>
#include <fstream>
#include <vector>

class Rect
{
public:
    Rect();
    
    Rect(std::string s)
    {
        sscanf(s.c_str(), "#%*d @ %d,%d: %dx%d", &m_xPos, &m_yPos, &m_width, &m_height);
    }
    
    int x() const { return m_xPos; };
    int y() const { return m_yPos; };
    int width() const { return m_width; };
    int height() const { return m_height; };
    
private:
    int m_xPos;
    int m_yPos;
    int m_width;
    int m_height;
};

int main()
{
    std::string line;
    std::ifstream file;
    
    std::vector<std::string> input;
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    while (getline(file, line))
    {
        input.push_back(line);
    }
    
    file.close();
    
    // Container for rectangles
    std::vector<Rect*> rects;
    
    for (std::string str : input)
    {
        rects.push_back(new Rect(str));
    }
    
    // Probably not the most efficient way...
    char grid[1024][1024] { 0 };
    
    for (Rect *r : rects)
    {
        for (int y = r->y(); y < r->y() + r->height(); y++)
        {
            for (int x = r->x(); x < r->x() + r->width(); x++)
            {
                grid[x][y] += 1;
            }
        }
    }
    
    int overlappingSquares = 0;
    
    for (int i = 0; i < 1024; i++)
    {
        for (int j = 0; j < 1024; j++)
        {
            // How many rectangles overlap in a square
            int val = grid[i][j];
            
            if (val > 1)
                overlappingSquares++;
        }
    }
    
    for (Rect *r : rects)
        delete r;
    
    std::cout << overlappingSquares << std::endl;
    
    return 0;
}
