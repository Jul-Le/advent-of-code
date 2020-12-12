/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            12.12.2020
 *  Modified:           12.12.2020
 *
 *  
 *
 *  In part 2, seat is considered adjacent if it can be seen.
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum Direction
{
    NorthWest = 0,
    North,
    NorthEast,
    West,
    East,
    SouthWest,
    South,
    SouthEast
};

class SeatLayout
{
public:
    SeatLayout()
    {
        // By default, seat layout is assumed to be unstable
        m_isStable = false;
    }
    
    SeatLayout(const SeatLayout &s)
    {
        this->m_rows = s.m_rows;
    }
        
    void addRow(std::string str)
    {
        std::vector<char> row;
        
        for (auto ch : str)
        {
            row.push_back(ch);
        }
        m_rows.push_back(row);
    }
    
    // Debugging
    void printLayout()
    {
        for (auto row : m_rows)
        {
            for (auto ch : row)
            {
                std::cout << ch;
            }
            std::cout << std::endl;
        }
    }
    
    // Apply rules
    void advance()
    {
        // Create copy of seat layout
        SeatLayout oldLayout = *this;
        
        // Layout is stable, unless any seat changes
        m_isStable = true;
        
        for (int row = 0; row < m_rows.size(); row++)
        {
            for (int column = 0; column < m_rows.at(0).size(); column++)
            {
                if (this->seatExists(row, column))
                {
                    if (this->isOccupied(row, column))
                    {
                        // Seat is occupied, check if it becomes unoccupied
                        if (oldLayout.getAdjacentOccupied(row, column) >= 5)
                        {
                            this->setUnOccupied(row, column);
                            m_isStable = false;
                        }
                    }
                    else
                    {
                        // Seat is not occupied, check if it becomes occupied
                        if (oldLayout.getAdjacentOccupied(row, column) == 0)
                        {
                            this->setOccupied(row, column);
                            m_isStable = false;
                        }
                    }
                }
            }
        }
    }
    
    // Get number of adjacent occupied seats
    // (Seats that are visible to current seat)
    int getAdjacentOccupied(int row, int column)
    {
        int occupiedSeats = 0;
        
        if (occupiedSeatVisible(NorthWest, row, column))
            occupiedSeats++;
        if (occupiedSeatVisible(North, row, column))
            occupiedSeats++;
        if (occupiedSeatVisible(NorthEast, row, column))
            occupiedSeats++;
        if (occupiedSeatVisible(West, row, column))
            occupiedSeats++;
        if (occupiedSeatVisible(East, row, column))
            occupiedSeats++;
        if (occupiedSeatVisible(SouthWest, row, column))
            occupiedSeats++;
        if (occupiedSeatVisible(South, row, column))
            occupiedSeats++;
        if (occupiedSeatVisible(SouthEast, row, column))
            occupiedSeats++;
        
        return occupiedSeats;
    }
    
    int countOccupied()
    {
        int count = 0;
        for (auto row : m_rows)
        {
            // Count occupied seats within row
            count += std::count(row.begin(), row.end(), '#');
        }
        return count;
    }
    
    void setOccupied(int row, int column)
    {
        m_rows.at(row).at(column) = '#';
    }
    
    void setUnOccupied(int row, int column)
    {
        m_rows.at(row).at(column) = 'L';
    }
    
    bool isOccupied(int row, int column)
    {
        return isOccupied(m_rows.at(row).at(column));
    }
    
    bool isOccupied(char seat)
    {
        return seat == '#';
    }
    
    bool seatExists(int row, int column)
    {
        return seatExists(m_rows.at(row).at(column));
    }
    
    bool seatExists(char seat)
    {
        return seat != '.';
    }
    
    bool outOfBounds(int row, int column)
    {
        return !((row >= 0) &&
                 (row < m_rows.size()) &&
                 (column >= 0) &&
                 (column < m_rows.at(0).size()));
    }
    
    bool occupiedSeatVisible(Direction dir, int row, int column)
    {
        int tempRow, tempCol;
        
        switch (dir)
        {
            case NorthWest:
            {
                tempRow = row - 1;
                tempCol = column - 1;
                
                while (!outOfBounds(tempRow, tempCol))
                {
                    if (isOccupied(tempRow, tempCol))
                        return true;
                    else if (seatExists(tempRow, tempCol))
                        return false;
                    
                    // Continue until a seat is found or we go out of bounds
                    tempRow--;
                    tempCol--;
                }
                // Out of bounds, no seat visible
                return false;
            }
            case North:
            {
                tempRow = row - 1;
                tempCol = column;
                
                while (!outOfBounds(tempRow, tempCol))
                {
                    if (isOccupied(tempRow, tempCol))
                        return true;
                    else if (seatExists(tempRow, tempCol))
                        return false;
                    
                    // Continue until a seat is found or we go out of bounds
                    tempRow--;
                }
                // Out of bounds, no seat visible
                return false;
            }
            case NorthEast:
            {
                tempRow = row - 1;
                tempCol = column + 1;
                
                while (!outOfBounds(tempRow, tempCol))
                {
                    if (isOccupied(tempRow, tempCol))
                        return true;
                    else if (seatExists(tempRow, tempCol))
                        return false;
                    
                    // Continue until a seat is found or we go out of bounds
                    tempRow--;
                    tempCol++;
                }
                // Out of bounds, no seat visible
                return false;
            }
            case West:
            {
                tempRow = row;
                tempCol = column - 1;
                
                while (!outOfBounds(tempRow, tempCol))
                {
                    if (isOccupied(tempRow, tempCol))
                        return true;
                    else if (seatExists(tempRow, tempCol))
                        return false;
                    
                    // Continue until a seat is found or we go out of bounds
                    tempRow;
                    tempCol--;
                }
                // Out of bounds, no seat visible
                return false;
            }
            case East:
            {
                tempRow = row;
                tempCol = column + 1;
                
                while (!outOfBounds(tempRow, tempCol))
                {
                    if (isOccupied(tempRow, tempCol))
                        return true;
                    else if (seatExists(tempRow, tempCol))
                        return false;
                    
                    // Continue until a seat is found or we go out of bounds
                    tempRow;
                    tempCol++;
                }
                // Out of bounds, no seat visible
                return false;
            }
            case SouthWest:
            {
                tempRow = row + 1;
                tempCol = column - 1;
                
                while (!outOfBounds(tempRow, tempCol))
                {
                    if (isOccupied(tempRow, tempCol))
                        return true;
                    else if (seatExists(tempRow, tempCol))
                        return false;
                    
                    // Continue until a seat is found or we go out of bounds
                    tempRow++;
                    tempCol--;
                }
                // Out of bounds, no seat visible
                return false;
            }
            case South:
            {
                tempRow = row + 1;
                tempCol = column;
                
                while (!outOfBounds(tempRow, tempCol))
                {
                    if (isOccupied(tempRow, tempCol))
                        return true;
                    else if (seatExists(tempRow, tempCol))
                        return false;
                    
                    // Continue until a seat is found or we go out of bounds
                    tempRow++;
                    tempCol;
                }
                // Out of bounds, no seat visible
                return false;
            }
            case SouthEast:
            {
                tempRow = row + 1;
                tempCol = column + 1;
                
                while (!outOfBounds(tempRow, tempCol))
                {
                    if (isOccupied(tempRow, tempCol))
                        return true;
                    else if (seatExists(tempRow, tempCol))
                        return false;
                    
                    // Continue until a seat is found or we go out of bounds
                    tempRow++;
                    tempCol++;
                }
                // Out of bounds, no seat visible
                return false;
            }
        }
        return false;
    }
    
    bool isStable() { return m_isStable; };
    
private:
    std::vector<std::vector<char>> m_rows;
    bool m_isStable;
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
    
    SeatLayout seats;
    
    // Read data from file
    while (getline(file, line))
    {
        seats.addRow(line);
    }
    
    file.close();
        
    int iterations = 0;
    
    // Update seats until system stabilizes
    while (true)
    {
        // Update seats
        seats.advance();
        
        // If seats didn't change when updating, we're done
        if (seats.isStable())
            break;
        
        iterations++;
        //std::cout << std::endl << "After " << iterations << " iterations:" << std::endl;
        //seats.printLayout();
    }
    
    int occupiedSeats = seats.countOccupied();
    
    std::cout << "After " << iterations << " iterations, "
              << occupiedSeats << " seats are occupied." << std::endl;
    
    return 0;
}
