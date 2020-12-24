/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            24.12.2020
 *  Modified:           24.12.2020
 *
 *  
 *
 *  After each day, black tiles with zero or more than 2
 *  adjacent black tiles are flipped to white.
 *
 *  White tiles with exactly two black tiles adjacent to them
 *  are flipped to black.
 *
 *  How many tiles are black after 100 days?
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

/**
 *  @brief Check if two tiles are adjacent
 *  @param t1 Pointer to Tile
 *  @param t2 Pointer to Tile
 *  @return true if tiles are adjacent
 *  @details Tiles are adjacent if their x coordinates are the same
 *           and y coordinate differs by one or y coordinates are
 *           the same and x coordinate differs by one, or x
 *           coordinate is +1 and y -1 or x is -1 and y +1.
 *           Tiles are not adjacent if both x and y differ by one
 *           in the same direction.
 */
bool tilesAreAdjacent(Tile *t1, Tile *t2)
{
    Point p1 = t1->coordinates();
    Point p2 = t2->coordinates();
    
    // If x coordinate is the same
    if (p1.x == p2.x)
    {
        // If y differs by one
        if (abs(p1.y - p2.y) == 1)
            return true;
    }
    // If y coordinate is the same
    if (p1.y == p2.y)
    {
        // If x differs by one
        if (abs(p1.x - p2.x) == 1)
            return true;
    }
    // If x and y both differ by one in different directions
    if ((p1.x == p2.x + 1 && p1.y == p2.y - 1) ||
        (p1.x == p2.x - 1 && p1.y == p2.y + 1))
        return true;
    
    return false;
}

/**
 *  @brief Check how many adjacent tiles are black
 *  @param midTile Tile of which the adjacent tiles will be checked
 *  @param tiles Vector containing pointers to all tiles
 *  @return Count of adjacent black tiles (0-6)
 */
int adjacentBlackTileCount(Tile *midTile, const std::vector<Tile*> &tiles)
{
    int blackTileCount = 0;
    Point midTileCoord = midTile->coordinates();
    
    for (Tile *adjTile : tiles)
    {
        // Midtile exists in container, skip it
        if (midTile == adjTile)
            continue;
        
        if (adjTile->isBlack() && tilesAreAdjacent(midTile, adjTile))
            blackTileCount++;
    }
    return blackTileCount;
}

/**
 *  @brief Add adjacent tiles to list
 *  @param tile Tile of which the adjacent tiles will be checked
 *  @param tiles Vector containing pointers to all tiles
 */
void addAdjacentTilesToList(Tile *tile, std::vector<Tile*> &tiles)
{
    for (int i = 0; i < 6; i++)
    {
        Direction dir = (Direction)i;
        
        if (!tileExists(dir, tile, tiles))
            tiles.push_back(new Tile(dir, tile));
    }
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
            
            // Don't pass the next character if we
            // are at the end of the string
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
    
    for (int daysPassed = 0; daysPassed < 100; daysPassed++)
    {
        // All tiles adjacent to black tiles will be added to tiles vector
        for (Tile *tile : tiles)
            if (tile->isBlack())
                addAdjacentTilesToList(tile, tiles);
        
        // Vector containing information about whether Tile in
        // tiles vectorwith matching index should be flipped
        // at the end of day
        std::vector<bool> shouldFlip;
        
        for (Tile *tile : tiles)
        {
            int adjBlackTiles = adjacentBlackTileCount(tile, tiles);
            
            if (tile->isBlack())
            {
                switch (adjBlackTiles)
                {
                    case 0:
                        shouldFlip.push_back(true);
                        break;
                    case 1:
                    case 2:
                        shouldFlip.push_back(false);
                        break;
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        shouldFlip.push_back(true);
                        break;
                    default:
                        std::cout << "You're not supposed to be here " << __LINE__ << std::endl;
                }
            }
            else // White tile
            {
                switch (adjBlackTiles)
                {
                    case 0:
                    case 1:
                        shouldFlip.push_back(false);
                        break;
                    case 2:
                        shouldFlip.push_back(true);
                        break;
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        shouldFlip.push_back(false);
                        break;
                    default:
                        std::cout << "You're not supposed to be here " << __LINE__ << std::endl;
                }
            }
        }
        // Sanity check
        if (tiles.size() != shouldFlip.size())
            std::cout << "Something went kaflooey" << std::endl;
        
        // Flip tiles that need flipping
        for (int i = 0; i < tiles.size(); i++)
        {
            if (shouldFlip[i])
                tiles[i]->flip();
        }
        
        int day = daysPassed+1;
        int blackTileCount = 0;
        
        for (auto t : tiles)
            if (t->isBlack())
                blackTileCount++;
        
        std::cout << "Day " << day << ": " << blackTileCount << std::endl;
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
