/*
 *  Contributor(s):     Julius L.
 *
 *  Created:            2021-11-14
 *  Modified:           2021-11-19
 *
 *
 *
 *  What is the ID of the only rectangle that does not overlap
 *  with any other rectangle?
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
        sscanf(s.c_str(), "#%d @ %d,%d: %dx%d", &m_id, &m_xPos, &m_yPos, &m_width, &m_height);
        m_overlaps = false;
    }
    
    bool overlapsWith(Rect *b) const
    {
        const Rect *a = this;
        
        return (((a->x() <= b->x() && a->x() + a->width() >= b->x()) ||
                 (a->x() >= b->x() && a->x() <= b->x() + b->width())) &&
                ((a->y() <= b->y() && a->y() + a->height() >= b->y()) ||
                 (a->y() >= b->y() && a->y() <= b->y() + b->height())));
    }
    
    int id() const { return m_id; };
    int x() const { return m_xPos; };
    int y() const { return m_yPos; };
    int width() const { return m_width; };
    int height() const { return m_height; };
    bool overlaps() const { return m_overlaps; };
    
    void setOverlap(bool o)
    {
        m_overlaps = o;
    }
    
private:
    int m_id;
    int m_xPos;
    int m_yPos;
    int m_width;
    int m_height;
    
    bool m_overlaps;
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
    
    // Construct Rect objects
    for (std::string str : input)
    {
        rects.push_back(new Rect(str));
    }
    
    // Check for overlaps
    for (int i = 0; i < rects.size() - 1; i++)
    {
        Rect *a = rects.at(i);
        
        for (int j = i + 1; j < rects.size(); j++)
        {
            Rect *b = rects.at(j);
            
            // If both rectangles overlap with any other, no need to check for more overlaps
            if (a->overlaps() && b->overlaps())
                continue;
            
            if (a->overlapsWith(b))
            {
                a->setOverlap(true);
                b->setOverlap(true);
            }
        }
    }
    
    for (Rect *r : rects)
    {
        if (!r->overlaps())
            std::cout << "ID " << r->id() << " doesn't overlap with anything." << std::endl;
        
        delete r;
    }
    
    return 0;
}
