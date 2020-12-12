/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            12.12.2020
 *  Modified:           12.12.2020
 *
 *  
 *
 *  Input is a map of seats. At start, every seat is occupied.
 *  A seat becomes unoccupied, if >= 4 adjacent seats are
 *  occupied.
 *  An empty seat becomes occupied, if 0 adjacent seats are
 *  occupied.
 *
 *  After the system stabilizes, how many seats are occupied?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
                        if (oldLayout.getAdjacentOccupied(row, column) >= 4)
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
    int getAdjacentOccupied(int row, int column)
    {
        bool isTop, isBottom, isLeftmost, isRightmost;
        int occupiedSeats = 0;
        
        isTop = (row == 0);
        isBottom = (row == (m_rows.size() - 1));
        isLeftmost = (column == 0);
        isRightmost = (column == (m_rows.at(0).size() - 1));
        
        // Above row
        if (!isTop)
        {
            // Top left
            if (!isLeftmost)
            {
                if (isOccupied(m_rows.at(row-1).at(column-1)))
                    occupiedSeats++;
            }
            // Above
            if (isOccupied(m_rows.at(row-1).at(column)))
                occupiedSeats++;
            // Top right
            if (!isRightmost)
            {
                if (isOccupied(m_rows.at(row-1).at(column+1)))
                    occupiedSeats++;
            }
        }
        // Same row
        // Left
        if (!isLeftmost)
        {
            if (isOccupied(m_rows.at(row).at(column-1)))
                occupiedSeats++;
        }
        // Right
        if (!isRightmost)
        {
            if (isOccupied(m_rows.at(row).at(column+1)))
                occupiedSeats++;
        }
        // Below row
        if (!isBottom)
        {
            // Bottom left
            if (!isLeftmost)
            {
                if (isOccupied(m_rows.at(row+1).at(column-1)))
                    occupiedSeats++;
            }
            // Below
            if (isOccupied(m_rows.at(row+1).at(column)))
                occupiedSeats++;
            // Bottom right
            if (!isRightmost)
            {
                if (isOccupied(m_rows.at(row+1).at(column+1)))
                    occupiedSeats++;
            }
        }
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
