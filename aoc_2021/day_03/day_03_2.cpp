/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-04
 *  Modified:           2021-12-06
 *
 *
 *
 *  Next, you should verify the life support rating, which can
 *  be determined by multiplying the oxygen generator rating by
 *  the CO2 scrubber rating.
 *
 *  Both the oxygen generator rating and the CO2 scrubber rating
 *  are values that can be found in your diagnostic report -
 *  finding them is the tricky part. Both values are located
 *  using a similar process that involves filtering out values
 *  until only one remains. Before searching for either rating
 *  value, start with the full list of binary numbers from your
 *  diagnostic report and consider just the first bit of those
 *  numbers. Then:
 *
 *  Keep only numbers selected by the bit criteria for the type
 *  of rating value for which you are searching. Discard numbers
 *  which do not match the bit criteria.
 *
 *  If you only have one number left, stop; this is the rating
 *  value for which you are searching.
 *
 *  Otherwise, repeat the process, considering the next bit to
 *  the right.
 *
 *  The bit criteria depends on which type of rating value you
 *  want to find:
 *
 *  To find oxygen generator rating, determine the most common
 *  value (0 or 1) in the current bit position, and keep only
 *  numbers with that bit in that position. If 0 and 1 are
 *  equally common, keep values with a 1 in the position being
 *  considered.
 *
 *  To find CO2 scrubber rating, determine the least common
 *  value (0 or 1) in the current bit position, and keep only
 *  numbers with that bit in that position. If 0 and 1 are
 *  equally common, keep values with a 0 in the position being
 *  considered.
 *
 *  What is the life support rating of the submarine? (Oxygen
 *  generator rating multiplied by CO2 scrubber rating)
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

struct Number
{
    Number(std::string s, bool b)
        : digits(s), discarded(b)
    {
        
    }
    
    std::string digits;
    bool discarded;
};

std::vector<std::string> parseInput()
{
    std::ifstream file;
    std::string line;
    std::vector<std::string> data;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    while (getline(file, line))
    {
        data.push_back(line);
    }
    
    file.close();
    
    return data;
}

uint16_t binaryStrToInt(std::string s)
{
    unsigned bit = 0;
    uint16_t bin = 0;
    
    // Loop through string in reverse
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if (s[i] == '1')
            bin |= (1 << bit);
        bit++;
    }
    
    return bin;
}

uint16_t calcOxygenRating(std::vector<Number> numbers)
{
    const size_t len = numbers[0].digits.length();
    int discardedCount = 0;
    
    // Loop through each digit
    for (int i = 0; i < len; i++)
    {
        // Number of ones and zeros in current digit position
        int ones = 0;
        int zeros = 0;
        
        // Loop through each row
        for (auto num : numbers)
        {
            // Count the bits
            if (!num.discarded)
            {
                if (num.digits[i] == '0')
                    zeros++;
                else ones++;
            }
        }
        
        const uint16_t bit = len - i - 1;
        
        // Discard numbers according to rules...
        for (auto &num : numbers)
        {
            if (num.discarded)
                continue;
            
            const uint16_t currentNum = binaryStrToInt(num.digits);
            
            if (ones >= zeros)
            {
                // If bit in current position is 0, discard
                if (!(currentNum & (1 << bit)))
                {
                    num.discarded = true;
                    discardedCount++;
                }
            }
            else // more zeros
            {
                // If bit in current position is 1, discard
                if (currentNum & (1 << bit))
                {
                    num.discarded = true;
                    discardedCount++;
                }
            }
        }
        
        // If all but 1 numbers are discarded
        if (discardedCount == numbers.size() - 1)
        {
            for (auto num : numbers)
            {
                if (!num.discarded)
                    return binaryStrToInt(num.digits);
            }
        }
    }
    
    return 0;
}

uint16_t calcCarbonRating(std::vector<Number> numbers)
{
    const size_t len = numbers[0].digits.length();
    int discardedCount = 0;
    
    // Loop through each digit
    for (int i = 0; i < len; i++)
    {
        // Number of ones and zeros in current digit position
        int ones = 0;
        int zeros = 0;
        
        // Loop through each row
        for (auto num : numbers)
        {
            // Count the bits
            if (!num.discarded)
            {
                if (num.digits[i] == '0')
                    zeros++;
                else ones++;
            }
        }
        
        const uint16_t bit = len - i - 1;
        
        // Discard numbers according to rules...
        for (auto &num : numbers)
        {
            if (num.discarded)
                continue;
            
            const uint16_t currentNum = binaryStrToInt(num.digits);
            
            if (zeros > ones)
            {
                // If bit in current position is 0, discard
                if (!(currentNum & (1 << bit)))
                {
                    num.discarded = true;
                    discardedCount++;
                }
            }
            else // more zeros
            {
                // If bit in current position is 1, discard
                if (currentNum & (1 << bit))
                {
                    num.discarded = true;
                    discardedCount++;
                }
            }
        }
        
        // If all but 1 numbers are discarded
        if (discardedCount == numbers.size() - 1)
        {
            for (auto num : numbers)
            {
                if (!num.discarded)
                    return binaryStrToInt(num.digits);
            }
        }
    }
    
    return 0;
}

int main()
{
    std::vector<std::string> input = parseInput();
    std::vector<Number> numbers;
    
    for (auto str : input)
        numbers.push_back(Number(str, false));
    
    uint16_t oxygenRating = calcOxygenRating(numbers);
    uint16_t carbonRating = calcCarbonRating(numbers);
    
    std::cout << "The oxygen generator rating is " << oxygenRating << std::endl
              << "The CO2 scrubber rating is " << carbonRating << std::endl
              << "The answer is " << oxygenRating * carbonRating << std::endl;
    
    return 0;
}
