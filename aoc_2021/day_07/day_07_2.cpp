/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-10
 *  Modified:           2021-12-11
 *
 *
 *
 *  Each change of 1 step in horizontal position costs 1 more unit of fuel than
 *  the last: the first step costs 1, the second step costs 2, the third step
 *  costs 3, and so on.
 *
 *  What is the minimum fuel consumption when all crabs are moved to same
 *  horizontal position?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

std::vector<int> parseInput()
{
    std::ifstream file;
    std::string line;
    std::vector<int> data;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    getline(file, line);
    
    char *token = strtok((char*)line.c_str(), ",");
    
    while (token)
    {
        int val;    
        sscanf(token, "%d", &val);
        data.push_back(val);
        token = strtok(NULL, ",");
    }
    
    file.close();
    
    return data;
}

int getTriangularNumber(int n)
{
    if (n < 1) return 0;
    
    static std::vector<int> results(1, 0);
    int triangular = 0;
    
    // If already calculated, return cached value
    if (n < results.size())
    {
        triangular = results[n];
    }
    // Calculate numbers before current one
    else
    {
        while (results.size() < n)
            getTriangularNumber(results.size());
        
        triangular += results[n-1] + n;
        results.push_back(triangular);
    }
    return triangular;
}

int main()
{
    std::vector<int> input = parseInput();
    
    int total = 0;
    
    for (auto i : input)
        total += i;
    
    const size_t count = input.size();
    double avg;
    
    avg = (double)total / count;
    
    int avgInt = (int)avg;
    int fuelSpent = 0;
    
    for (auto hpos : input)
        fuelSpent += getTriangularNumber(abs(hpos - avgInt));
    
    std::cout << "Minimum fuel required is " << fuelSpent << " units, "
              << "when moving to position " << avgInt << std::endl;
    
    return 0;
}
