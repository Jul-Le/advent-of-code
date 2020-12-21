/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            20.12.2020
 *  Modified:           21.12.2020
 *
 *  
 *
 *  Input is a list of tiles. When tiles are flipped and
 *  oriented correctly and they line up, what is the product
 *  of the IDs of the corner tiles?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const int TILE_X_SIZE = 10;
const int TILE_Y_SIZE = 10;
const int MAX_X_INDEX = TILE_X_SIZE - 1;
const int MAX_Y_INDEX = TILE_Y_SIZE - 1;

enum Side
{
    Top,
    Bottom,
    Left,
    Right
};

enum Orientation
{
    Undefined,
    Normal,
    Rotated_Right,
    Rotated_180,
    Rotated_Left,
    Flipped,
    Flipped_Rotated_Right,
    Flipped_Rotated_180,
    Flipped_Rotated_Left
};

class Tile
{
public:
    Tile() {}
    Tile(int id, const std::vector<std::vector<char>> &data) : m_id(id)
    {
        for (int y = 0; y < TILE_Y_SIZE; y++)
        {
            for (int x = 0; x < TILE_X_SIZE; x++)
            {
                m_data[y][x] = data[y][x];
            }
        }
        
        m_orientation = Normal;
    }
    
    /**
     *  @brief Get side id of tile
     *  @param side Side to get id from
     *  @param reverse Whether the side should be flipped or not
     *  @return side id
     *  @note When this function is called, value of m_orientation
     *        is not considered, the orientation is always Normal
     *  @see getEdge
     */
    unsigned int edge(Side side, bool reverse = false) const
    {
        unsigned int id = 0;
        
        switch (side)
        {
            case Top:
            {
                // Convert top row to binary
                for (unsigned int bit = 0; bit < TILE_X_SIZE; bit++)
                {
                    if (m_data[0][MAX_X_INDEX - bit] == '#')
                        id |= (1 << bit);
                }
                break;
            }
            case Bottom:
            {
                // Convert bottom row to binary
                for (unsigned int bit = 0; bit < TILE_X_SIZE; bit++)
                {
                    if (m_data[MAX_Y_INDEX][MAX_X_INDEX - bit] == '#')
                        id |= (1 << bit);
                }
                break;
            }
            case Left:
            {
                // Convert left to binary
                for (unsigned int bit = 0; bit < TILE_Y_SIZE; bit++)
                {
                    if (m_data[MAX_Y_INDEX - bit][0] == '#')
                        id |= (1 << bit);
                }
                break;
            }
            case Right:
            {
                // Convert right to binary
                for (unsigned int bit = 0; bit < TILE_Y_SIZE; bit++)
                {
                    if (m_data[MAX_Y_INDEX - bit][MAX_X_INDEX] == '#')
                        id |= (1 << bit);
                }
                break;
            }
            default:
                std::cout << "Bug<noun>: (chiefly computing and engineering "
                          << "jargon) A problem that needs fixing." << std::endl;
        }
        if (reverse)
            id = reverseEdge(id);
        
        return id;
    }
    
    /**
     *  @brief Reverse side ID
     *  @param id Side id
     *  @return Side id, but the TILE_X_SIZE lowest bits are reversed
     *  @note This function only works if tiles are squares
     */
    unsigned int reverseEdge(unsigned int id) const
    {
        unsigned int temp = 0;
        
        // Assume square tiles
        for (int i = 0; i < TILE_X_SIZE; i++)
        {
            const unsigned int msb = MAX_X_INDEX;
            
            bool one = (id & (1 << i));
            if (one)
                temp |= (1 << (msb-i));
        }
        return temp;
    }
    
    /**
     *  @brief Check whether a side is symmetrical
     *  @param id Side id
     *  @return True if side is symmetrical
     *  @details Side is symmetrical if the value stays the
     *           same when the bits are reversed
     */
    bool isSymmetrical(unsigned int id) const
    {
        return reverseEdge(id) == id;
    }
    
    /**
     *  @brief Get side id of tile
     *  @param side Side to get id from
     *  @return side id
     *  @note The side depends on m_orientation
     *  @see edge
     */
    unsigned int getEdge(Side side) const
    {
        // For readability
        const bool reversed = true;
        
        switch (m_orientation)
        {
            case Normal:
                return edge(side);
            case Rotated_Right:
                switch (side)
                {
                    case Top:
                        return edge(Left, reversed);
                    case Bottom:
                        return edge(Right, reversed);
                    case Left:
                        return edge(Bottom);
                    case Right:
                        return edge(Top);
                }
            case Rotated_180:
                switch (side)
                {
                    case Top:
                        return edge(Bottom, reversed);
                    case Bottom:
                        return edge(Top, reversed);
                    case Left:
                        return edge(Right, reversed);
                    case Right:
                        return edge(Left, reversed);
                }
            case Rotated_Left:
                switch (side)
                {
                    case Top:
                        return edge(Right);
                    case Bottom:
                        return edge(Left);
                    case Left:
                        return edge(Top, reversed);
                    case Right:
                        return edge(Bottom, reversed);
                }
            case Flipped:
                switch (side)
                {
                    case Top:
                        return edge(Top, reversed);
                    case Bottom:
                        return edge(Bottom, reversed);
                    case Left:
                        return edge(Right);
                    case Right:
                        return edge(Left);
                }
            case Flipped_Rotated_Right:
                switch (side)
                {
                    case Top:
                        return edge(Right, reversed);
                    case Bottom:
                        return edge(Left, reversed);
                    case Left:
                        return edge(Bottom, reversed);
                    case Right:
                        return edge(Top, reversed);
                }
            case Flipped_Rotated_180:
                switch (side)
                {
                    case Top:
                        return edge(Bottom);
                    case Bottom:
                        return edge(Top);
                    case Left:
                        return edge(Left, reversed);
                    case Right:
                        return edge(Right, reversed);
                }
            case Flipped_Rotated_Left:
                switch (side)
                {
                    case Top:
                        return edge(Left);
                    case Bottom:
                        return edge(Right);
                    case Left:
                        return edge(Top);
                    case Right:
                        return edge(Bottom);
                }
            default:
                std::cout << "How tf did this happen? Line " << __LINE__ << " Tile: " << this->m_id << std::endl;
                return 0;
        }
    }
    
    /**
     *  @brief Check if any of the 8 orientations produces a side that matches the argument
     *  @param sideID side id
     *  @return True if any orientation matches
     */
    bool anyOrientationMatches(unsigned int sideID) const
    {
        return this->edge(Top) == sideID || this->edge(Bottom) == sideID ||
               this->edge(Left) == sideID || this->edge(Right) == sideID ||
               this->edge(Top, true) == sideID || this->edge(Bottom, true) == sideID ||
               this->edge(Left, true) == sideID || this->edge(Right, true) == sideID;
    }
    
    /**
     *  @brief Check if any orientation makes the given sides match with given ids.
     *  @param side1 Side
     *  @param side1_id Id side 1 has to match with
     *  @param side2 Another side
     *  @param side2_id Id side 2 has to match with
     *  @return Orientation where the sides match, Undefined if no
     *          matching orientation found
     *  @details If matching orientation is found, tile is set to that orientation.
     *           If not found, tile stays in the same orientation.
     */
    Orientation matchOrientation(Side side1, unsigned int side1_id,
                                 Side side2, unsigned int side2_id)
    {
        // Save current orientation
        Orientation startingOrientation = m_orientation;
        
        // Check that there is orientation that matches one side at a time
        if (!anyOrientationMatches(side1_id) || !anyOrientationMatches(side2_id))
            return Undefined;
        
        // Set one of the required sides to match
        setOrientation(side1, side1_id);
        
        // Save orientation where one side matches
        Orientation temp = m_orientation;
        
        // Make second side match as well, if it matches in the same orientation
        // as the first one, return that orientation
        setOrientation(side2, side2_id);
        
        if (m_orientation == temp)
            return m_orientation;
        else
        {
            // If side1 is symmetrical, flip and rotate the
            // tile and try to match side2 again
            if (isSymmetrical(side1_id))
            {
                // Reset orientation so that side1 matches again
                setOrientation(side1, side1_id);
                
                // Flip and rotate so that side1 matches but is reversed
                if (side1 == Top || side1 == Bottom)
                {
                    switch (m_orientation)
                    {
                        case Normal:                m_orientation = Flipped; break;
                        case Rotated_Right:         m_orientation = Flipped_Rotated_Left; break;
                        case Rotated_180:           m_orientation = Flipped_Rotated_180; break;
                        case Rotated_Left:          m_orientation = Flipped_Rotated_Right; break;
                        case Flipped:               m_orientation = Normal; break;
                        case Flipped_Rotated_Right: m_orientation = Rotated_Left; break;
                        case Flipped_Rotated_180:   m_orientation = Rotated_180; break;
                        case Flipped_Rotated_Left:  m_orientation = Rotated_Right; break;
                        default:
                            std::cout << "This is not the case you are looking for: Line " << __LINE__ << std::endl;
                            break;
                    }
                }
                else // side1 == Left || side1 == Right
                {
                    switch (m_orientation)
                    {
                        case Normal:                m_orientation = Flipped_Rotated_180; break;
                        case Rotated_Right:         m_orientation = Flipped_Rotated_Right; break;
                        case Rotated_180:           m_orientation = Flipped; break;
                        case Rotated_Left:          m_orientation = Flipped_Rotated_Left; break;
                        case Flipped:               m_orientation = Rotated_180; break;
                        case Flipped_Rotated_Right: m_orientation = Rotated_Right; break;
                        case Flipped_Rotated_180:   m_orientation = Normal; break;
                        case Flipped_Rotated_Left:  m_orientation = Rotated_Left; break;
                        default:
                            std::cout << "This is not the case you are looking for: Line " << __LINE__ << std::endl;
                            break;
                    }
                }
                // side2 should match now, if it doesn't, this tile won't fit
                if (getEdge(side2) == side2_id)
                {
                    return m_orientation;
                }
                else
                {
                    m_orientation = startingOrientation;
                    return Undefined;
                }
            }
            // side1 is not symmetrical and side2 doesn't match,
            // this tile won't fit in any orientation
            m_orientation = startingOrientation;
            return Undefined;
        }
    }
    
    /**
     *  @brief Set orientation such that the given side matches with given id
     *  @param side Side
     *  @param id ID side has to match with
     *  @return true if orientation was found
     *
     *  @todo Handle symmetrical sides?
     */
    bool setOrientation(Side side, unsigned int id)
    {
        // Sanity check
        if (!anyOrientationMatches(id))
            return false;
        
        m_orientation = Normal;
        if (getEdge(side) == id)
            return true;
        
        m_orientation = Rotated_Right;
        if (getEdge(side) == id)
            return true;
        
        m_orientation = Rotated_180;
        if (getEdge(side) == id)
            return true;
        
        m_orientation = Rotated_Left;
        if (getEdge(side) == id)
            return true;
        
        m_orientation = Flipped;
        if (getEdge(side) == id)
            return true;
        
        m_orientation = Flipped_Rotated_Right;
        if (getEdge(side) == id)
            return true;
        
        m_orientation = Flipped_Rotated_180;
        if (getEdge(side) == id)
            return true;
        
        m_orientation = Flipped_Rotated_Left;
        if (getEdge(side) == id)
            return true;
        
        std::cout << "bool setOrientation(): No matching orientation found line: " << __LINE__ << std::endl;
        
        return false;
    }
    
    /**
     *  @brief Add information about tiles that match this tile's given side
     *  @param side Side the given tile has a matching side with
     *  @param t Pointer to tile that matches with given side
     *  @details The side corresponds to side of this tile in Normal orientation
     */
    void addMatchingTile(Side side, Tile *t)
    {
        m_matchesWith[side].push_back(t);
    }
    
    /**
     *  @brief Get list of tiles that match with given side
     *  @param side Side for which we want to get all matching tiles
     *  @return Vector containing pointers to tiles that match with the
     *          given side, returns an empty vector if no such tiles exist
     */
    std::vector<Tile*> getMatchingTiles(Side side)
    {
        return m_matchesWith[side];
    }
    
    // Debugging
    void print() const
    {
        std::cout << "Tile " << m_id << ":" << std::endl;
        
        for (int y = 0; y < TILE_Y_SIZE; y++)
        {
            for (int x = 0; x < TILE_X_SIZE; x++)
                std::cout << m_data[y][x];
            std::cout << std::endl;
        }
    }
    
    // Debugging
    void printOrientation() const
    {
        switch (m_orientation)
        {
            case Undefined: std::cout << "Undefined" << std::endl; break;
            case Normal: std::cout << "Normal" << std::endl; break;
            case Rotated_Right: std::cout << "Rotated_Right" << std::endl; break;
            case Rotated_180: std::cout << "Rotated_180" << std::endl; break;
            case Rotated_Left: std::cout << "Rotated_Left" << std::endl; break;
            case Flipped: std::cout << "Flipped" << std::endl; break;
            case Flipped_Rotated_Right: std::cout << "Flipped_Rotated_Right" << std::endl; break;
            case Flipped_Rotated_180: std::cout << "Flipped_Rotated_180" << std::endl; break;
            case Flipped_Rotated_Left: std::cout << "Flipped_Rotated_Left" << std::endl; break;
        }
    }
    
    // Getter for m_id
    int id() const { return m_id; }
    
private:
    int m_id;
    Orientation m_orientation;
    char m_data[TILE_Y_SIZE][TILE_X_SIZE];
    
    /* 
     * Map containing four sides as keys, and vector of
     * Tile pointers as values. Each tile pointer corresponds
     * to tile that given side matches with.
     */
    std::map<Side, std::vector<Tile*>> m_matchesWith;
};

/**
 *  @brief Check if a tile has a side that matches the given side of another tile
 *  @param t1 First tile
 *  @param side Side of the first tile that we are looking for a match
 *  @param t2 Second tile, which will be checked if it has a side that
 *         matches the side parameter in any orientation
 *  @return True if matching edge was found
 */
bool tileHasMatchingEdge(Tile *t1, Side side, Tile *t2)
{
    return t2->anyOrientationMatches(t1->edge(side));
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
    
    // Container for tiles
    std::vector<Tile> tiles;
    
    int parsedTileCount = 0;
    int id;
    std::vector<std::vector<char>> data;
    
    while (getline(file, line))
    {
        int y = 0;
        
        if (line != "")
        {
            // Parse tile ID
            if (line[0] == 'T')
            {
                sscanf(line.c_str(), "%*s %d:", &id);
                parsedTileCount++;
            }
            // Parse tile data
            else
            {
                std::vector<char> temp;
                for (int x = 0; x < TILE_X_SIZE; x++)
                {
                    temp.push_back(line[x]);
                }
                data.push_back(temp);
                y++;
            }
        }
        // Blank line, create tile object
        else
        {
            tiles.push_back(Tile(id, data));
            data.clear();
        }
    }
    
    // Make sure we get the last tile as well
    if (tiles.size() < parsedTileCount)
        tiles.push_back(Tile(id, data));
    
    file.close();
    
    // Find tiles for every tile that match given edge
    for (int i = 0; i < tiles.size(); i++)
    {
        Tile *curTile = &tiles[i];
        
        for (int j = 0; j < tiles.size(); j++)
        {
            Tile *t = &tiles[j];
            
            // If current tile
            if (t == curTile)
                continue;
            
            if (tileHasMatchingEdge(curTile, Top, t))
                curTile->addMatchingTile(Top, t);
            if (tileHasMatchingEdge(curTile, Bottom, t))
                curTile->addMatchingTile(Bottom, t);
            if (tileHasMatchingEdge(curTile, Left, t))
                curTile->addMatchingTile(Left, t);
            if (tileHasMatchingEdge(curTile, Right, t))
                curTile->addMatchingTile(Right, t);
        }
    }
    
    int countOfTilesThatHaveExactlyTwoOtherTilesThatMatchTheirSides = 0;
    unsigned long long result = 1;
    
    for (Tile t : tiles)
    {
        int sumOfMatchingTiles = t.getMatchingTiles(Top).size() + 
                                 t.getMatchingTiles(Bottom).size() + 
                                 t.getMatchingTiles(Left).size() + 
                                 t.getMatchingTiles(Right).size();
        if (sumOfMatchingTiles == 2)
        {
            if (countOfTilesThatHaveExactlyTwoOtherTilesThatMatchTheirSides < 4)
                result *= t.id();
            
            countOfTilesThatHaveExactlyTwoOtherTilesThatMatchTheirSides++;
            
            std::cout << "Tile " << t.id() << " has total of " << sumOfMatchingTiles
                    << " other tiles that match with any of it's sides: ";
            
            // Print matching tile's ids
            {
                std::vector<Tile*> matches = t.getMatchingTiles(Top);
                for (Tile *tilePtr : matches)
                {
                    std::cout << tilePtr->id() << " ";
                }
            }
            {
                std::vector<Tile*> matches = t.getMatchingTiles(Bottom);
                for (Tile *tilePtr : matches)
                {
                    std::cout << tilePtr->id() << " ";
                }
            }
            {
                std::vector<Tile*> matches = t.getMatchingTiles(Left);
                for (Tile *tilePtr : matches)
                {
                    std::cout << tilePtr->id() << " ";
                }
            }
            {
                std::vector<Tile*> matches = t.getMatchingTiles(Right);
                for (Tile *tilePtr : matches)
                {
                    std::cout << tilePtr->id() << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    
    // If there are exactly four tiles that have maximum of two
    // other tiles that match with them, they must all be corner tiles
    if (countOfTilesThatHaveExactlyTwoOtherTilesThatMatchTheirSides == 4)
        std::cout << result << std::endl;

    return 0;
}
