/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            24.12.2020
 *  Modified:           24.12.2020
 *
 *  
 *
 *  Input specifies list of hexagonal tiles that will be
 *  flipped. Input line consists of coordinates, which
 *  specify offsets from a reference tile. All tiles start with
 *  the white side facing up.
 *
 *  After flipping the tiles, how many tiles have the black side
 *  facing up?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum Direction
{
    NorthWest = 0,
    West,
    SouthWest,
    SouthEast,
    East,
    NorthEast
};

struct Point
{
    int x;
    int y;
};

class Tile
{
public:
    // Default constructor for reference tile
    Tile()
    {
        m_coordinates.x = 0;
        m_coordinates.y = 0;
        m_isBlack = false;
    }
    
    /**
     *  @brief Tile constructor
     *  @param dir Direction of child with respect to parent
     *  @param parent Pointer to adjacent tile
     */
    Tile(Direction dir, Tile *parent)
    {
        // Set coordinates to parent coordinates
        // and update them
        m_coordinates = parent->coordinates();
        this->updateCoordinates(dir);
        
        m_isBlack = false;
    }
    
    /**
     *  @brief Get new coordinates after moving to specified direction
     *  @param dir Direction to move to
     */
    void updateCoordinates(Direction dir)
    {
        switch (dir)
        {
            case NorthWest:
                m_coordinates.y--;
                break;
            case West:
                m_coordinates.x--;
                break;
            case SouthWest:
                m_coordinates.x--;
                m_coordinates.y++;
                break;
            case SouthEast:
                m_coordinates.y++;
                break;
            case East:
                m_coordinates.x++;
                break;
            case NorthEast:
                m_coordinates.x++;
                m_coordinates.y--;                
                break;
        }
    }
    
    void flip()
    {
        m_isBlack = !m_isBlack;
    }
    
    Point coordinates() const { return m_coordinates; }
    bool isBlack() const { return m_isBlack; }
    
private:
    Point m_coordinates;
    bool m_isBlack;
};

Direction charToDir(char ch1, char ch2 = '\0')
{
    if (ch1 == 'e' || ch1 == 'w')
        return ch1 == 'e' ? East : West;
    
    if (ch1 == 'n')
        return ch2 == 'e' ? NorthEast : NorthWest;
    
    else if (ch1 == 's')
        return ch2 == 'e' ? SouthEast : SouthWest;
    
    std::cout << "Something went wrong at line " << __LINE__ << std::endl;
    return NorthWest;
}

/**
 *  @brief Check if tile exists in a given direction of parent tile
 *  @param dir Direction to check from
 *  @param parent Pointer to parent tile
 *  @param tiles Vector containing pointers to all tiles
 *  @return Pointer to tile if found, nullptr if tile doesn't exist
 */
Tile *tileExists(Direction dir, Tile *parent, const std::vector<Tile*> &tiles)
{
    Tile temp(dir, parent);
    Point childCoord = temp.coordinates();
    
    // Check if tile exists at childCoord
    for (Tile* t : tiles)
    {
        Point tileCoord = t->coordinates();
        if (tileCoord.x == childCoord.x &&
            tileCoord.y == childCoord.y)
            return t;
    }
    return nullptr;
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
    
    std::vector< std::vector<Direction> > dirs;
    
    while (getline(file, line))
    {
        std::vector<Direction> dirVect;
        
        for (int i = 0; i < line.length(); i++)
        {
            Direction dir;
            
            // Don't pass the next character if we are at the end of the string
            if (i < line.length() - 1)
                dir = charToDir(line[i], line[i+1]);
            else
                dir = charToDir(line[i]);
            
            // If dir consisted of two characters, move ahead
            if (dir != East && dir != West)
                i++;
            
            dirVect.push_back(dir);
        }
        dirs.push_back(dirVect);
    }
    file.close();
    
    // Create tile container and add reference tile to it
    std::vector<Tile*> tiles;
    Tile *referenceTile = new Tile();
    tiles.push_back(referenceTile);
    
    // Navigate to destination tile and flip it
    for (std::vector<Direction> dirVect : dirs)
    {
        Tile *parentTile = referenceTile;
        Tile *t = nullptr;
        
        for (Direction dir : dirVect)
        {
            // Check if tile exists in tiles vector
            // in direction dir of parentTile
            t = tileExists(dir, parentTile, tiles);
            
            // If tile doesn't exist, create it
            if (!t)
            {
                t = new Tile(dir, parentTile);
                tiles.push_back(t);
            }
            
            parentTile = t;
        }
        
        // Last tile is the destination tile, flip it
        t->flip();
    }
    
    int blackTileCount = 0;
    
    for (Tile *t : tiles)
    {
        if (t->isBlack())
            blackTileCount++;
        
        delete t;
    }
    
    std::cout << blackTileCount << " tiles are black" << std::endl;
    
    return 0;
}
