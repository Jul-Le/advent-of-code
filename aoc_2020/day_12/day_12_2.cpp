/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            13.12.2020
 *  Modified:           13.12.2020
 *
 *  
 *
 *  Action N means to move waypoint north by the given value.
 *  Action S means to move waypoint south by the given value.
 *  Action E means to move waypoint east by the given value.
 *  Action W means to move waypoint west by the given value.
 *  Action L means to turn rotate waypoint counterclockwise
 *  given number of degrees.
 *  Action R means to turn rotate waypoint clockwise
 *  given number of degrees.
 *  Action F means move towards the waypoint times the given
 *  value.
 *
 *  What is the manhattan distance to the starting position
 *  after executing all of the instructions?
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

class Waypoint
{
public:
    Waypoint()
    {
        // Waypoint starts 10 units east and 1 unit north
        m_relativePos.x = 10;
        m_relativePos.y = 1;
    };
    
    void move(Direction dir, int val)
    {
        switch (dir)
        {
            case North:
                m_relativePos.y += val;
                break;
            case South:
                m_relativePos.y -= val;
                break;
            case East:
                m_relativePos.x += val;
                break;
            case West:
                m_relativePos.x -= val;
                break;
        }
    }
    
    void rotate(char dir, int val)
    {
        val = dir == 'L' ? -val : val;
        
        int currentX = m_relativePos.x;
        int currentY = m_relativePos.y;
        
        switch (val % 360)
        {
            case -270:
            case 90:
            {
                // Rotate waypoint right 90 degrees
                m_relativePos.x = currentY;
                m_relativePos.y = -currentX;
                break;
            }
            case -180:
            case 180:
            {
                // Rotate waypoint 180 degrees
                m_relativePos.x = -currentX;
                m_relativePos.y = -currentY;
                break;
            }
            case -90:
            case 270:
            {
                // Rotate waypoint left 90 degrees
                m_relativePos.x = -currentY;
                m_relativePos.y = currentX;
                break;
            }
            case 0:
            {
                // Waypoint doesn't move
                break;
            }
            default:
                std::cout << "Something went kaflooey" << std::endl
                        << "Ship::move(char, int):" << __LINE__ << " val = " << val << std::endl;
                break;
        }
    }
    
    Point relativePos() { return m_relativePos; };
    
private:
    // The waypoint position relative to the ship
    Point m_relativePos;
};

class Ship
{
public:
    Ship()
    {
        m_coordinates.x = 0;
        m_coordinates.y = 0;
    }
    
    // Get manhattan distance from starting point
    int getManhattanDistance()
    {
        return abs(m_coordinates.x) + abs(m_coordinates.y);
    }
    
    /**
     *  @brief Move ship towards the waypoint
     *  @param times How many times the ship moves towards
     *               the waypoint
     */
    void move(int times)
    {
        Point waypointPos = m_waypoint.relativePos();
        
        m_coordinates.x += waypointPos.x * times;
        m_coordinates.y += waypointPos.y * times;
    }
    
    /**
     *  @brief Move ship or waypoint
     *  @param dir Direction to move the ship/waypoint
     *  @param val How much to move or rotate
     *  @details If dir is 'N', 'S', 'E' or 'W', move waypoint
     *           to North, South, East or West respectively, val
     *           specifies how far to move
     *           If dir is 'L' or 'R', rotate the waypoint left
     *           or right val is number of degrees to rotate.
     *           If dir is 'F', move ship towards the waypoint
     *           val times.
     */
    void move(char dir, int val)
    {
        switch (dir)
        {
            case 'N': m_waypoint.move(North, val); break;
            case 'S': m_waypoint.move(South, val); break;
            case 'E': m_waypoint.move(East, val); break;
            case 'W': m_waypoint.move(West, val); break;
            case 'L':
            case 'R': m_waypoint.rotate(dir, val); break;
            case 'F':
            {
                move(val);
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
    // Ship's location
    Point m_coordinates;
    // Waypoint
    Waypoint m_waypoint;
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
