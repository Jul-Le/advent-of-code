/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            5.12.2020
 *  Modified:           5.12.2020
 *
 *  
 *
 *  Your seat isn't at the very front or back; the seats with
 *  IDs +1 and -1 from yours will be in the list.
 *
 *  What is the ID of your seat?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

int getRow(std::string str)
{
    // B == 1
    // F == 0
    
    int row = 0;
    
    for (int i = 0; i < 7; i++)
        row |= ((str.at(i) == 'B') << 6-i);
        
    return row;
}

int getCol(std::string str)
{
    // R == 1
    // L == 0
    
    int col = 0;
    
    for (int i = 0; i < 3; i++)
        col |= ((str.at(i+7) == 'R') << 2-i);
    
    return col;
}

int getSeatID(int row, int col)
{
    return row * 8 + col;
}

int main()
{
    std::string line;
    std::ifstream file;
    std::list<int> seats;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    int largestSeatID = 0;
    
    // Read data from file
    while (getline(file, line))
    {
        int row = 0;
        int col = 0;
        int sID = 0; // Seat ID
        
        row = getRow(line);
        col = getCol(line);
        sID = getSeatID(row, col);
        
        seats.push_back(sID);
    }
    
    file.close();
    
    int mySeatID = 0;
    
    for (auto s : seats)
    {
        // Check if there are 2 occupied seats with 1 in between
        auto it = std::find(seats.begin(), seats.end(), s + 2);
        
        if (it != seats.end())
        {
            // Check that the seat between occupied ones is empty
            it = std::find(seats.begin(), seats.end(), s+1);
            if (it == seats.end())
            {
                mySeatID = s + 1;
                break;
            }
        }
    }
    
    std::cout << mySeatID << std::endl;
    
    return 0;
}
