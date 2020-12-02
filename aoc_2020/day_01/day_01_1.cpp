/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            1.12.2020
 *  Modified:           2.12.2020
 *
 *  
 *
 *  Input is a list of numbers, the goal is to find two numbers
 *  that sum up to 2020.
 *  Numbers will be stored to std::list, which will be sorted.
 *
 *  The first and last number in the list will be added
 *  together, and if the sum is greater than 2020, first and
 *  second last will be added.
 *
 *  If sum is less than 2020, second number on the list will be
 *  added instead of first.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <list>

int main()
{
    std::string line;
    std::ifstream file;
    std::list<int> numbers;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    // Read data from file
    while (getline(file, line))
    {
        // Add to list
        numbers.push_back(std::stoi(line));
    }
    
    file.close();
    
    numbers.sort();
        
    /*
        Quick way: O(n^2)
        Iterate through the list, add every number to the first
        number using two nested loops. If no sum of 2020 is
        found, add second number on the list to every number
        after it.
        
        Efficient way: O(n)
        Iterate through the list, one iterator starting from the
        first element forwards and another from the last element
        backwards.
        Add the numbers together. If sum is more than 2020, move
        the reverse iterator forward. If sum is less than
        2020, move the forward iterator. Repeat until correct 
        answer is found.
        
        1) Set iterator a to beginning of the list.
        2) Set iterator b to end of the list.
        3) If sum of values is more than 2020:
            Move iterator b back
           If sum of values is less than 2020:
            Move iterator a forward
           If sum of values is equal to 2020:
            multiply the values
    */
    
    std::list<int>::iterator a = numbers.begin();
    std::list<int>::reverse_iterator b = numbers.rbegin();
    int answer = 0;
    
    while (answer == 0 && a != numbers.end())
    {
        while (b != numbers.rend())
        {
            int sum = *a + *b;
            std::cout << (*a) << " + " << (*b) << " = " << sum << std::endl;
            
            if (sum > 2020)
            {
                b++;
                continue;
            }
            else if (sum < 2020)
            {
                a++;
                break;
            }
            else
            {
                answer = (*a) * (*b);
                break;
            }
        }
    }
    
    std::cout << answer << std::endl;
    
    
    return 0;
}
