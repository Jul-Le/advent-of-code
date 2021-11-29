/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-29
 *  Modified:           2021-11-29
 *
 *
 *
 *  Each room consists of an encrypted name (lowercase letters
 *  separated by dashes) followed by a dash, a sector ID, and a
 *  checksum in square brackets.
 *
 *  A room is real (not a decoy) if the checksum is the five
 *  most common letters in the encrypted name, in order, with
 *  ties broken by alphabetization.
 *
 *  What is the sum of the sector IDs of the real rooms?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <map>

class RoomName
{
public:
    RoomName(std::vector<std::string> name, int id, std::string chk)
        : m_encryptedName(name), m_sectorID(id), m_checksum(chk)
    {
        
    }
    
    bool isReal()
    {
        std::vector<char> mostCommonLetters;
        std::map<char, int> letterCounts;
        
        for (auto str : m_encryptedName)
        {
            for (auto ch : str)
            {
                letterCounts[ch]++;
            }
        }
        // "What is "real"? How do you define "real"?" -Morpheus
        
    }
    
    int id() const { return m_sectorID; }
    
private:
    std::vector<std::string> m_encryptedName;
    int m_sectorID;
    std::string m_checksum;
};

std::vector<std::string> parseInput()
{
    std::ifstream file;
    std::string line;
    std::vector<std::string> data;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    while (getline(file, line))
    {
        data.push_back(line);
    }
    
    file.close();
    
    return data;
}

std::vector<RoomName> getRooms(const std::vector<std::string> &input)
{
    std::vector<RoomName> roomNames;
    
    for (auto str : input)
    {
        std::vector<std::string> splitInput;
        char *token = strtok((char*)str.c_str(), "-");
        
        std::vector<std::string> encryptedNames;
        int id;
        std::string checksum;
        
        // Split by '-'
        while (token)
        {
            splitInput.push_back(std::string(token));
            
            token = strtok(NULL, "-");
        }
        
        // Parse encrypted names
        for (int i = 0; i < splitInput.size() - 1; i++)
        {
            encryptedNames.push_back(splitInput.at(i));
        }
        
        char temp[32];
        
        // Parse id and checksum
        sscanf(splitInput.back().c_str(), "%d%s", &id, temp);
        
        checksum = std::string(temp);
        // remove '[', ']'
        checksum.erase(checksum.length() - 1, 1);
        checksum.erase(0, 1);
        
        // Create RoomName object
        roomNames.push_back(RoomName(encryptedNames, id, checksum));
    }
    return roomNames;
}

int main()
{
    std::vector<std::string> input = parseInput();
    std::vector<RoomName> roomNames = getRooms(input);
    int sum = 0;
    
    for (auto room : roomNames)
    {
        if (room.isReal())
            sum += room.id();
    }
    
    std::cout << "The sum of real rooms' IDs is " << sum << std::endl;
    
    return 0;
}
