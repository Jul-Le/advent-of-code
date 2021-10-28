/*
 *  Contributor(s):     Julius L.
 *
 *  Created:            2021-10-28
 *  Modified:           2021-10-28
 *
 *  
 *
 *  What is the sum of the numbers in the input file?
 */

#include <iostream>
#include <fstream>

int main()
{
    std::string line;
    std::ifstream file;
    int sum = 0;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    while (getline(file, line))
    {
        sum += std::stoi(line);
    }
    
    file.close();
    
    std::cout << sum << std::endl;
    
    return 0;
}
