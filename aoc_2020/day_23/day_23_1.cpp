/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            23.12.2020
 *  Modified:           23.12.2020
 *
 *  
 *
 *  Input values are placed in a circular buffer. After every
 *  turn, the three values after the current value are removed
 *  from the buffer, and new destination cup is chosen.
 *  
 *  Destination cup is the cup that has closest, smaller value
 *  than the current cup. If no smaller value exists,
 *  destination cup will be the cup with the largest value.
 *
 *  After destination cup is chosed, the three removed cups are
 *  placed after the destination cup, in the same order they
 *  were when they were removed.
 *
 *  After 100 rounds, what are the labels on the cups after
 *  cup 1?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

class Placeholder
{
public:
    Placeholder()
    {
        
    }
    
private:
    
};

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
    
    getline(file, line);
    file.close();
    
    // List of cup values
    std::list<int> cups;
    
    // Add values to list
    for (char ch : line)
    {
        int val = ch - '0';
        cups.push_back(val);
    }
    
    for (int val : cups)
        std::cout << val << std::endl;
    
    return 0;
}
