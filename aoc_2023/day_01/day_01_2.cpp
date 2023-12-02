/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2023-12-01
 *  Modified:           2023-12-02
 *
 *
 *
 *  In part 2, numbers spelled as words also count as numbers.
 *
 *  What is the sum of all calibration values?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::vector<std::string> numbers =
{
    "zero", "one", "two", "three", "four",
    "five", "six", "seven", "eight", "nine"
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
        data.push_back(line);
        
    file.close();
    
    return data;
}

bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

// Get first digit spelled as word
// Returns the current number digit (n) if earlier digit as string is not found
// Arguments:
//      s   The calibration string
//      n   Position of first digit
int getFirstDigitString(const std::string &s, int n)
{
    int ret = -1;
    
    for (int i = 0; i < 10; i++)
    {
        std::size_t foundAt = s.find(numbers[i]);
        
        // If not found
        if (foundAt == std::string::npos)
            continue;
        
        if ((int)foundAt < n)
        {
            n = foundAt;
            // The index in numbers vector matches with the string
            ret = i;
        }
    }
    
    return ret;
}

// Get last digit spelled as word
// Returns the current number digit (n) if later digit as string is not found
// Arguments:
//      s   The calibration string
//      n   Position of last digit, start looking after this
int getLastDigitString(const std::string &s, int n)
{
    int ret = -1;
    int lastIndex = n;
    
    for (int i = 0; i < 10; i++)
    {
        std::size_t foundAt = s.find(numbers[i], n);
        
        // If not found
        if (foundAt == std::string::npos)
            continue;
        
        // Check if same number occurs multiple times (this is quite an abomination)
        std::size_t foundAt2 = foundAt; // Index of subsequent number if found
        bool foundAnother;
        
        do
        {
            foundAt2 = s.find(numbers[i], foundAt2 + 1);  // Look for another occurrence after latest
            foundAnother = foundAt2 != std::string::npos; // Check if found
            if (foundAnother)                             // If found, update index
                foundAt = foundAt2;
        }
        while (foundAnother);                             // Repeat until no more is found
        
        if ((int)foundAt > lastIndex)
        {
            lastIndex = foundAt;
            
            ret = i;
        }
    }
    
    return ret;
}

int getFirstDigit(const std::string &s)
{
    char digitCh = '0';
    int digitIndex = 999;
    
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (isDigit(s[i]))
        {
            digitCh = s[i];
            digitIndex = i;
            // stop after first occurrence
            break;
        }
    }
    
    int val = (int)(digitCh - '0');
    
    int strNumberFound = getFirstDigitString(s, digitIndex);
    
    if (strNumberFound != -1)
        return strNumberFound;
    
    return val;
}

int getLastDigit(const std::string &s)
{
    char digitCh = '0';
    int digitIndex = 0;
    
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (isDigit(s[i]))
        {
            digitCh = s[i];
            digitIndex = i;
        }
    }
    
    int val = (int)(digitCh - '0');
    
    int strNumberFound = getLastDigitString(s, digitIndex);
    
    if (strNumberFound != -1)
        return strNumberFound;
    
    return val;
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
