/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-27
 *  Modified:           2021-11-27
 *
 *
 *
 *  Find the sum of all digits that match the next digit in the input data.
 *
 *  Example: 11222 => 1+2+2 = 5
 */

#include <iostream>
#include <fstream>
#include <string>

std::string parseInput()
{
    std::ifstream file;
    std::string line;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    getline(file, line);
    file.close();
    
    return line;
}

int main()
{
    std::string digits = parseInput();
    int sum = 0;
    
    for (int i = 0; i < digits.length() - 1; i++)
    {
        int first = digits.at(i) - '0';
        int second = digits.at(i+1) - '0';
        
        if (first == second)
            sum += first;
    }
    
    int first = digits.back() - '0';
    int second = digits.front() - '0';
    
    if (first == second)
        sum += first;
    
    std::cout << "Sum: " << sum << std::endl;
    
    return 0;
}
