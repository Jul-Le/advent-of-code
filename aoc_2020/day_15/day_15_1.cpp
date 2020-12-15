/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            15.12.2020
 *  Modified:           15.12.2020
 *
 *  
 *
 *  Memory game: Two players take turns saying numbers. There's
 *  a list of starting numbers (input), first players take
 *  turns saying those.
 *
 *  After that, if last number that the other player said has
 *  not been said before, players will say 0. If the number
 *  that other player said has been said before, the players
 *  will say how many turns apart the last two occurences of
 *  the numbers are.
 *
 *  What will be the 2020th number spoken?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Game
{
public:
    Game(std::vector<int> sn, int snc = 6)
        : m_startNums(sn), m_startNumCount(snc)
    {
        m_turns = 0;
    }
    
    /**
     *  @brief Advance game by one turn
     *  @return The number spoken on that round
     */
    int nextTurn()
    {
        int nextNum;
        
        if (startNumsNotSpokenYet())
        {
            int num = m_startNums.at(m_turns);
            speak(num);
            m_spokenNumbers[num] = m_turns+1;
        }
        else
        {
            nextNum = numberSpoken(m_lastNumberSpoken);
            
            speak(nextNum);
        }
        
        m_turns++;
        
        return m_lastNumberSpoken;
    }
    
    void speak(int num)
    {
        m_lastNumberSpoken = num;
    }
    
    /**
     *  @brief Check if number has been spoken before
     *  @param num The number to check
     *  @return 0 if not spoken before, how many turns apart
     *          number was before previously spoken if found
     */
    int numberSpoken(int num)
    {
        auto search = m_spokenNumbers.find(num);
        
        // If found
        if (search != m_spokenNumbers.end())
        {
            int lastSaid = m_spokenNumbers[num];
            m_spokenNumbers[num] = m_turns;
            return m_turns - lastSaid;
        }
        else
        {
            m_spokenNumbers[num] = m_turns;
            return 0; 
        }
    }
    
    bool startNumsNotSpokenYet()
    {
        return m_turns < m_startNumCount;
    }
    
private:
    std::vector<int> m_startNums;
    int m_startNumCount;
    int m_turns; // How many turns have been completed
    int m_lastNumberSpoken;
    
    std::map<int, int> m_spokenNumbers;
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
    
    // Input is a single line
    getline(file, line);
    file.close();
    
    // Parse starting numbers
    // There are 3 values in the example input,
    // and 6 values in the actual input
    std::vector<int> numList;
    int startNums[6] { 0 };
    int countNums = 0;
    
    countNums = sscanf(line.c_str(), "%d,%d,%d,%d,%d,%d",
                    &startNums[0], &startNums[1], &startNums[2],
                    &startNums[3], &startNums[4], &startNums[5]);
    
    if (countNums == 6 || countNums == 3)
        std::cout << countNums << " input values parsed" << std::endl;
    else
    {
        std::cout << countNums << " input values parsed, expected 3 or 6, exiting..." << std::endl;
        return 1;
    }
    
    for (int i = 0; i < countNums; i++)
        numList.push_back(startNums[i]);
    
    Game game(numList, countNums);
    
    // Run game for 2019 turns
    for (int turn = 1; turn < 2020; turn++)
    {
        game.nextTurn();
    }
    
    // 2020th turn
    int theNumber = game.nextTurn();
    
    std::cout << theNumber << std::endl;
    
    return 0;
}
