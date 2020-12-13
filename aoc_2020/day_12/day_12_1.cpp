/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            13.12.2020
 *  Modified:           13.12.2020
 *
 *  
 *
 *  Input is a list of navigation instructions.
 *
 *
 *  Action N means to move north by the given value.
 *  Action S means to move south by the given value.
 *  Action E means to move east by the given value.
 *  Action W means to move west by the given value.
 *  Action L means to turn left the given number of degrees.
 *  Action R means to turn right the given number of degrees.
 *  Action F means to move forward by the given value in the
 *  direction the ship is currently facing.
 *
 *  The ship starts by facing east.
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum Direction
{
    North,
    South,
    East,
    West
};

struct Point
{
    int x;
    int y;
};

class Ship
{
public:
    Ship()
    {
        m_direction = East;
        m_coordinates.x = 0;
        m_coordinates.y = 0;
    }
    
    // Get manhattan distance from starting point
    int getManhattanDistance()
    {
        return abs(m_coordinates.x) + abs(m_coordinates.y);
    }
    
    void move(Direction dir, int val)
    {
        switch (dir)
        {
            case North:
                m_coordinates.y += val;
                break;
            case South:
                m_coordinates.y -= val;
                break;
            case East:
                m_coordinates.x -= val;
                break;
            case West:
                m_coordinates.x += val;
                break;
        }
    }
    
    /**
     *  @brief Move ship to given direction by certain amount
     *  @param dir Direction to move the ship
     *  @param val How much to move or rotate
     *  @details If dir is 'N', 'S', 'E' or 'W', move ship to
     *           North, South, East or West respectively, val
     *           specifies how far to move
     *           If dir is 'L' or 'R', turn the ship left or
     *           right (change m_direction member), val is
     *           number of degrees to turn.
     *           If dir is 'F', move to the m_direction
     *           direction.
     *  @note If dir is 'L' or 'R', val is assumed to be
     *        multiple of 90. If it isn't, message will be
     *        printed.
     */
    void move(char dir, int val)
    {
        switch (dir)
        {
            case 'N': move(North, val); break;
            case 'S': move(South, val); break;
            case 'E': move(East, val); break;
            case 'W': move(West, val); break;
            case 'L':
            case 'R':
            {
                val = dir == 'L' ? -val : val;
                switch (val % 360)
                {
                    case -270:
                    case 90:
                    {
                        // Turn right 90 degrees
                        switch (m_direction)
                        {
                            case North: m_direction = East; break;
                            case South: m_direction = West; break;
                            case East: m_direction = South; break;
                            case West: m_direction = North; break;
                        }
                        break;
                    }
                    case -180:
                    case 180:
                    {
                        // Turn around
                        switch (m_direction)
                        {
                            case North: m_direction = South; break;
                            case South: m_direction = North; break;
                            case East: m_direction = West; break;
                            case West: m_direction = East; break;
                        }
                        break;
                    }
                    case -90:
                    case 270:
                    {
                        // Turn left 90 degrees
                        switch (m_direction)
                        {
                            case North: m_direction = West; break;
                            case South: m_direction = East; break;
                            case East: m_direction = North; break;
                            case West: m_direction = South; break;
                        }
                        break;
                    }
                    case 0:
                    {
                        // Continue to same direction
                        break;
                    }
                    default:
                        std::cout << "Something went kaflooey" << std::endl
                                  << "Ship::move(char, int):" << __LINE__ << " val = " << val << std::endl;
                        break;
                }
                break;
            }
            case 'F':
            {
                move(m_direction, val);
                break;
            }
            default:
            {
                std::cout << "Input data is garbage or there's a bug" << std::endl
                          << "Ship::move(dir = " << dir << ", val = " << val << "):" << __LINE__ << std::endl;
                break;
            }
        }
    }
    
private:
    // Direction the ship is facing
    Direction m_direction;
    // Ship's location
    Point m_coordinates;
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
    
    std::vector<std::pair<char, int>> instructions;
    Ship ship;
    
    // Read data from file
    while (getline(file, line))
    {
        char dir;
        int val;
        
        // Parse line
        sscanf(line.c_str(), "%c%d", &dir, &val);
        
        // Add to container
        instructions.push_back(std::pair<char, int>(dir, val));
    }
    
    file.close();
    
    for (auto i : instructions)
    {
        ship.move(i.first, i.second);
    }
    
    int distance = ship.getManhattanDistance();
    
    std::cout << distance << std::endl;
    
    return 0;
}
