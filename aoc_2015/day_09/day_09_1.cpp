/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-11-12
 *  Modified:           2022-11-12
 *
 *  
 *
 *  Input is distances between locations.
 *
 *  For example, given the following distances:
 *
 *  London to Dublin = 464
 *  London to Belfast = 518
 *  Dublin to Belfast = 141
 *  
 *  The possible routes are therefore:
 *  
 *  Dublin -> London -> Belfast = 982
 *  London -> Dublin -> Belfast = 605
 *  London -> Belfast -> Dublin = 659
 *  Dublin -> Belfast -> London = 659
 *  Belfast -> Dublin -> London = 605
 *  Belfast -> London -> Dublin = 982
 *  
 *  The shortest of these is London -> Dublin -> Belfast = 605, and so the answer is 605 in this example.
 *  
 *  What is the distance of the shortest route?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Location
{
public:
    Location()
    {
        
    }
    
    int distance(const std::string &l) const
    {
        return m_distances[l];
    }
    
    void addDistance(std::string l, int dist)
    {
        m_distances[l] = dist;
    }
    
private:
    std::map<std::string, int> m_distances;
};

std::vector<std::string> parseInput()
{
    std::ifstream file;
    std::vector<std::string> data;
    std::string line;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    while (getline(file, line))
    {
        char location1[32];
        char location2[32];
        int dist;
        
        sscanf(line.c_str(), "%s to %s = %d", location1, location2, &dist);
        
        data.push_back(line);
    }
        
    file.close();
    
    return data;
}

bool isHello(const std::string &str)
{
    return str == "Hello world";
}

/**
 *  @brief Test functions
 *  @return Number of failed tests, zero if all were successful
 */
int doTests()
{
    int failedTests = 0;

    // "Hello world" should return true
    if (!isHello("Hello world"))
    {
        failedTests++;
        std::cout << "myFunc(\"Hello world\") returned false" << std::endl;
    }
    
    return failedTests;
}

int main()
{
    int failedTests = doTests();
    
    if (failedTests != 0)
    {
        std::cout << failedTests << " test(s) failed" << std::endl;
        return 1;
    }
    
    std::vector<std::string> input = parseInput();
    
    for (auto line : input)
        std::cout << line << std::endl;
    
    return 0;
}
