/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-01
 *  Modified:           2021-12-01
 *
 *
 *
 *  Spreadsheet checksum is the sum of the difference between
 *  the largest and smallest value on each row.
 *
 *  What is the checksum value?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

std::vector<std::vector<int>> parseInput()
{
    std::ifstream file;
    std::string line;
    std::vector<std::vector<int>> data;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    while (getline(file, line))
    {
        char *token = strtok((char*)line.c_str(), "\t");
        std::vector<int> row;
        
        while (token)
        {
            row.push_back(atoi(token));
            token = strtok(NULL, "\t");
        }
        data.push_back(row);
    }
    
    file.close();
    
    return data;
}

int main()
{
    std::vector<std::vector<int>> input = parseInput();
    int checksum = 0;
    
    for (auto row : input)
    {
        int smallest = row[0];
        int largest = row[0];
        
        for (auto i : row)
        {
            if (i > largest)
                largest = i;
            
            if (i < smallest)
                smallest = i;
        }
        
        int diff = largest - smallest;
        checksum += diff;
    }
    
    std::cout << "Checksum for the spreadsheet is " << checksum << std::endl;
    
    return 0;
}
