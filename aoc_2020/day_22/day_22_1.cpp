/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            22.12.2020
 *  Modified:           22.12.2020
 *
 *  
 *
 *  Each of two players has a deck. On each turn, both players
 *  draw a card from the deck. The player who has larger card,
 *  inserts both cards to bottom of their deck, larger one
 *  first.
 *
 *  Once the game ends, you can calculate the winning player's
 *  score. The bottom card in their deck is worth the value of
 *  the card multiplied by 1, the second-from-the-bottom card is
 *  worth the value of the card multiplied by 2, and so on.
 *
 *  What is the winning player's score?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

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
    
    
    std::queue<int> deck_1;
    std::queue<int> deck_2;
    std::queue<int> temp;
    
    std::queue<int> *deck = &deck_1;
    
    while (getline(file, line))
    {
        // Skip player names
        if (line[0] == 'P')
            continue;
        
        // Blank line
        if (line.length() == 0)
        {
            // Values in temp queue are in wrong order,
            // move them to other queue to fix the order
            while (!temp.empty())
            {
                int val = temp.front();
                temp.pop();
                deck_1.push(val);
            }
            continue;
        }
        
        int value;
        
        sscanf(line.c_str(), "%d", &value);
        
        // Add to temporary queue
        temp.push(value);
    }
    
    file.close();
    
    while (!temp.empty())
    {
        int val = temp.front();
        temp.pop();
        deck_2.push(val);
    }
    
    while (!deck_1.empty() && !deck_2.empty())
    {
        int a = deck_1.front();
        int b = deck_2.front();
        
        deck_1.pop();
        deck_2.pop();
        
        if (a > b)
        {
            deck_1.push(a);
            deck_1.push(b);
        }
        else // b > a
        {
            deck_2.push(b);
            deck_2.push(a);
        }
    }
    
    if (deck_2.empty())
        deck = &deck_1;
    else
        deck = &deck_2;
    
    int result = 0;
    
    for (int i = deck->size() ; i > 0; i--)
    {
        std::cout << deck->front() << " * " << i << std::endl;
        result += deck->front() * i;
        deck->pop();
    }
    
    std::cout << result << std::endl;
    
    return 0;
}
