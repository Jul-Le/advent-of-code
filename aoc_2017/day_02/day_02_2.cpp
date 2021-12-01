/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-01
 *  Modified:           2021-12-01
 *
 *
 *
 *  On each row, there are two values that divide evenly. Divide
 *  them and add together to get the checksum.
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
        for (int i = 0 ; i < row.size() - 1; i++)
        {
            int a = row[i];
            
            for (int j = i+1; j < row.size(); j++)
            {
                int b = row[j];
                
                if (a % b == 0)
                {
                    checksum += a / b;
                    goto next;
                }
                else if (b % a == 0)
                {
                    checksum += b / a;
                    goto next;
                }
            }
        }
        
    next:
        continue;
    }
    
    std::cout << "Checksum for the spreadsheet is " << checksum << std::endl;
    
    return 0;
}
