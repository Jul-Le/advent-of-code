/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-28
 *  Modified:           2021-11-28
 *
 *
 *
 *  Input is a list of dimensions for triangles. Only some of
 *  the inputs are possible triangles, for a triangle to be
 *  possible, sum of any of its two sides has to be greater than
 *  the remaining side.
 *
 *  How many triangles are possible?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Triangle
{
public:
    Triangle(int a, int b, int c)
        : m_a(a), m_b(b), m_c(c)
    {
        
    }
    
    // Check that lengths of any two sides are greater than the remaining side
    bool isPossible()
    {
        return m_a+m_b > m_c && m_a+m_c > m_b && m_b+m_c > m_a;
    }
    
private:
    int m_a;
    int m_b;
    int m_c;
};

std::vector<Triangle> parseInput()
{
    std::ifstream file;
    std::string line;
    std::vector<Triangle> triangles;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    while (getline(file, line))
    {
        int a, b, c;
        sscanf(line.c_str(), "%d %d %d", &a, &b, &c);
        
        triangles.push_back(Triangle(a, b, c));
    }
    
    file.close();
    
    return triangles;
}

int main()
{
    std::vector<Triangle> triangles = parseInput();
    
    int answer = 0;
    
    for (auto triangle : triangles)
    {
        if (triangle.isPossible())
            answer++;
    }
    
    std::cout << answer << " triangles are possible." << std::endl;
    
    return 0;
}
