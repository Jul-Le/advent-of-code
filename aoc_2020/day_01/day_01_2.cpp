/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            2.12.2020
 *  Modified:           2.12.2020
 *
 *  
 *
 *  Goal is to find three numbers that sum up to 2020.
 *  
 *  The first and last number in the list will be added
 *  together, and if the sum is greater than 2020, first and
 *  second last will be added.
 *
 *  If sum is less than 2020, try to find a number from the
 *  list that would make the sum equal to 2020.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

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
        
    std::list<int>::iterator a = numbers.begin();
    std::list<int>::reverse_iterator b = numbers.rbegin();
    std::list<int>::iterator c;
    int answer = 0;
    
    while (answer == 0 && a != numbers.end())
    {
        b = numbers.rbegin();
        
        while (*b != *a)
        {
            int sum = *a + *b;
            std::cout << (*a) << " + " << (*b) << " = " << sum << std::endl;
            
            if (sum < 2020)
            {
                c = std::find(numbers.begin(), numbers.end(), 2020 - sum);
                if (c != numbers.end())
                {
                    answer = (*a) * (*b) * (*c);
                    std::cout << (*a) << " + "
                              << (*b) << " + "
                              << (*c) << " = "
                              << (*a)+(*b)+(*c) << std::endl;
                    break;
                }
            }
            b++;
        }
        a++;
    }
    
    std::cout << answer << std::endl;
    
    return 0;
}
