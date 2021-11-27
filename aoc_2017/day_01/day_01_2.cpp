/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-27
 *  Modified:           2021-11-27
 *
 *
 *
 *  Find the sum of all digits that match the digit halfway
 *  around the circular list
 *  (current_digit_index + input_length / 2)
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
    int len = digits.length();
    
    for (int i = 0; i < len; i++)
    {
        int first = digits.at(i) - '0';
        int second = digits.at((i + len / 2) % len) - '0';
        
        if (first == second)
            sum += first;
    }
        
    std::cout << "Sum: " << sum << std::endl;
    
    return 0;
}
