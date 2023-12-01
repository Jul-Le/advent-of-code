/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2023-12-01
 *  Modified:           2023-12-01
 *
 *
 *
 *  Input is lines of text containing calibration values.
 *  Calibration value can be found by combining the first and last digit
 *  from each line, to form a 2-digit number.
 *
 *  What is the sum of all calibration values?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
        data.push_back(line);
        
    file.close();
    
    return data;
}

bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

int getFirstDigit(const std::string &s)
{
    char digitCh = '0';
    
    for (auto ch : s)
    {
        if (isDigit(ch))
        {
            digitCh = ch;
            // stop after first occurrence
            break;
        }
    }
    return (int)(digitCh - '0');
}

int getLastDigit(const std::string &s)
{
    char digitCh = '0';
    
    for (auto ch : s)
    {
        if (isDigit(ch))
        {
            digitCh = ch;
        }
    }
    return (int)(digitCh - '0');
}

int getCalibrationValue(const std::string &s)
{
    int firstDigit = getFirstDigit(s);
    int lastDigit = getLastDigit(s);
    
    return firstDigit * 10 + lastDigit;
}

int main()
{
    std::vector<std::string> input = parseInput();
    
    int sum = 0;
    
    for (const auto &s : input)
    {
        sum += getCalibrationValue(s);
    }
    
    std::cout << "The sum of calibration values is " << sum << std::endl;
    
    return 0;
}
