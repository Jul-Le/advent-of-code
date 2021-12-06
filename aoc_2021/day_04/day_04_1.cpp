/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-12-06
 *  Modified:           2021-12-06
 *
 *
 *
 *  First line of input is bingo numbers, followed by some bingo boards.
 *
 *  Find the board that is going to find first. Only rows and columns count,
 *  diagonals don't.
 *
 *  What is the sum of the unmarked numbers multiplied my value of the number
 *  that was marked last?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

class BingoBoard
{
public:
    BingoBoard() { }
    BingoBoard(std::vector<std::vector<int>> n)
        : m_numbers(n)
    {
        for (int x = 0; x < 5; x++)
            m_marked.push_back({ 0,0,0,0,0 });
    }
    
    BingoBoard(const BingoBoard &b)
    {
        this->m_numbers = b.m_numbers;
        this->m_marked = b.m_marked;
    }
    
    void mark(int num)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (m_numbers[i][j] == num)
                {
                    m_marked[i][j] = true;
                    return;
                }
            }
        }
    }
    
    bool win()
    {
        for (int i = 0; i < 5; i++)
        {
            int marked = 0;
            
            for (int j = 0; j < 5; j++)
            {
                if (m_marked[i][j])
                    marked++;
                else break;
            }
            
            if (marked == 5)
                return true;
            
            marked = 0;
            
            for (int j = 0; j < 5; j++)
            {
                if (m_marked[j][i])
                    marked++;
                else break;
            }
            
            if (marked == 5)
                return true;
        }
        
        return false;
    }
    
    int unmarkedSum()
    {
        int sum = 0;
        
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (!m_marked[i][j])
                    sum += m_numbers[i][j];
            }
        }
        
        return sum;
    }
    
private:
    std::vector<std::vector<int>> m_numbers;
    std::vector<std::vector<bool>> m_marked;
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

std::vector<int> getNumbers(std::string s)
{
    std::vector<int> nums;
    
    char *token = strtok((char*)s.c_str(), ",");
    
    while (token)
    {
        nums.push_back(std::atoi(token));
        
        token = strtok(NULL, ",");
    }
    
    return nums;
}

int main()
{
    std::vector<std::string> input = parseInput();
    std::vector<int> numbers = getNumbers(input[0]);
    std::vector<BingoBoard> boards;
    
    // First row contains numbers, second row is blank so start from 3th
    for (int i = 2; i < input.size(); i++)
    {
        std::string str = input[i];
        
        if (str == "")
            continue;
        
        std::vector<std::vector<int>> numbers;
        int a, b, c, d, e;
        
        for (int j = i; j < i+5; j++)
        {
            str = input[j];
            sscanf(str.c_str(), "%d %d %d %d %d", &a, &b, &c, &d, &e);
            numbers.push_back({ a, b, c, d, e });
        }
        
        boards.push_back(BingoBoard(numbers));
        i += 5;
    }
    
    BingoBoard winningBoard;
    int lastNum;
    
    for (auto num : numbers)
    {
        for (auto &board : boards)
        {
            board.mark(num);
            if (board.win())
            {
                lastNum = num;
                winningBoard = board;
                goto print_result;
            }
        }
    }
    
print_result:
    std::cout << "Sum of unmarked numbers is " << winningBoard.unmarkedSum() << std::endl
              << "The last number was " << lastNum << std::endl
              << "The result is " << winningBoard.unmarkedSum() * lastNum << std::endl;
    return 0;
}
