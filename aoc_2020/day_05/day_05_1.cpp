/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            5.12.2020
 *  Modified:           5.12.2020
 *
 *  
 *
 *  Input is lines of text, which specify position of a seat
 *  in an airplane. A seat might be specified like FBFBBFFRLR,
 *  where F means "front", B means "back", L means "left",
 *  and R means "right".
 *
 *  The first 7 characters will either be F or B; these specify
 *  exactly one of the 128 rows on the plane (numbered 0 through
 *  127). Each letter tells you which half of a region the given
 *  seat is in. Start with the whole list of rows; the first
 *  letter indicates whether the seat is in the front (0 through
 *  63) or the back (64 through 127). The next letter indicates
 *  which half of that region the seat is in, and so on until
 *  you're left with exactly one row.
 *
 *  The last three characters will be either L or R; these
 *  specify exactly one of the 8 columns of seats on the plane
 *  (numbered 0 through 7).
 *
 *  Every seat has a unique seat ID: multiply the row by 8, then
 *  add the column.
 *
 *  What is the highest seat id in the input data?
 */

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
        
        if (sID > largestSeatID)
            largestSeatID = sID;
    }
    
    file.close();
    
    std::cout << largestSeatID << std::endl;
    
    return 0;
}
