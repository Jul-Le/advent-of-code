/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-28
 *  Modified:           2021-11-28
 *
 *
 *
 *  Instead of every row containing data for triangle, data for
 *  one triangle is three consecutive values in the same column.
 *
 *  How many triangles are valid?
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
    
    int i = 0;
    std::string row1, row2, row3;
    
    while (getline(file, line))
    {
        switch (i % 3)
        {
            case 0: row1 = line; break;
            case 1: row2 = line; break;
            case 2:
            {
                row3 = line;
                
                int t1_a, t1_b, t1_c,
                    t2_a, t2_b, t2_c,
                    t3_a, t3_b, t3_c;
                
                sscanf(row1.c_str(), "%d %d %d", &t1_a, &t2_a, &t3_a);
                sscanf(row2.c_str(), "%d %d %d", &t1_b, &t2_b, &t3_b);
                sscanf(row3.c_str(), "%d %d %d", &t1_c, &t2_c, &t3_c);
                
                triangles.push_back(Triangle(t1_a, t1_b, t1_c));
                triangles.push_back(Triangle(t2_a, t2_b, t2_c));
                triangles.push_back(Triangle(t3_a, t3_b, t3_c));
                
                break;
            }
        }
        
        i++;
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
