/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            9.12.2020
 *  Modified:           9.12.2020
 *
 *  
 *
 *  Numbers in the input list are valid, if they are a sum of
 *  two previous 25 numbers.
 *
 *  There is one contiguous set of at least two numbers which
 *  sum up to the number that was part 1's solution.
 *  What is the sum of the smallest and largest number in that
 *  set?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int PREAMBLE = 25;

/**
 *  @brief Find the first invalid number in the container
 *  @param numbers Number container
 *  @return Value of the invalid number
 *  @details
 *      Start from the n + PREAMBLEth number in the list.
 *      Subtract nth number from n+PREAMBLEth number, and
 *      try to find the result somewhere between n+1 and
 *      n + PREAMBLE - 1, inclusive.
 *      If not found, subtract n+1th number from n+PREAMBLEth
 *      and try to find the result between n+2 and
 *      n + PREAMBLE - 1.
 *      If match is found, number is valid and repeat the
 *      process for the n + PREAMBLE + 1th number.
 */
int findInvalidNumber(std::vector<int> numbers)
{
    int i = PREAMBLE;
    bool found = false; // Whether invalid number is found
    
    while (i < numbers.size())
    {
        found = true;
        for (int j = 0; j < PREAMBLE; j++)
        {
            int a = numbers.at(i - PREAMBLE + j);
            
            auto it = std::find(numbers.begin() + i - PREAMBLE + j,
                                numbers.begin() + i,
                                numbers.at(i) - a);
            
            if (it != numbers.begin() + i)
            {
                found = false;
                break;
            }
        }
        if (!found)
            i++;
        else break;
    }
    return numbers.at(i);
}

// Find smallest number from a vector within given index range
int findSmallest(std::vector<int> &numbers, int a, int b)
{
    int smallest = numbers.at(a);
    
    for (int i = a+1; i <= b; i++)
    {
        int temp = numbers.at(i);
        
        if (temp < smallest)
            smallest = temp;
    }
    return smallest;
}

// Find largest number from a vector within given index range
int findLargest(std::vector<int> &numbers, int a, int b)
{
    int largest = numbers.at(a);
    
    for (int i = a+1; i <= b; i++)
    {
        int temp = numbers.at(i);
        
        if (temp > largest)
            largest = temp;
    }
    return largest;
}

/**
 *  @brief Find the set of contiguous numbers that sum up to
 *         the given number
 *  @param numbers Number container
 *  @param targetNum Sum to look for
 *  @return Sum of smallest and largest numbers in the set
 *  @details
 *      Index a starts at the first element of the vector.
 *      Index b starts from the second element. If sum of the
 *      numbers between a and b (inclusive) is less than
 *      targetNum, add 1 to b. If sum is smaller, add 1 to a.
 *      Repeat until sum equals targetNum.
 */
int findSet(std::vector<int> &numbers, int targetNum)
{
    int a = 0;
    int b = 1;
    int sum = numbers.at(a) + numbers.at(b);
    
    while (sum != targetNum)
    {
        while (sum < targetNum)
        {
            b++;
            if (b >= numbers.size())
            {
                std::cout << "Index out or range" << std::endl;
                return 0;
            }
            sum += numbers.at(b);
        }
        while (sum > targetNum)
        {
            sum -= numbers.at(a);
            a++;
        }
    }
    
    return findSmallest(numbers, a, b) + findLargest(numbers, a, b);
}

int main()
{
    std::string line;
    std::ifstream file;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    std::vector<int> numbers;
    
    // Read data from file
    while (getline(file, line))
    {        
        int val;
        
        // Parse line
        sscanf(line.c_str(), "%d", &val);
        
        // Add to numbers container
        numbers.push_back(val);
    }
    
    file.close();
    
    int invalid = findInvalidNumber(numbers);
    int result = findSet(numbers, invalid);
    
    std::cout << result << std::endl;
    
    return 0;
}
