/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2020-12-11
 *  Modified:           2020-12-11
 *
 *
 *
 *  When moving multiple crates, the crates are moved at once
 *  instead of one at a time.
 *
 *  After completing the instructions, what crate ends up on top
 *  of each stack?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

std::vector<std::string> parseInput()
{
    std::ifstream file;
    std::vector<std::string> data;
    std::string line;

    file.open("input.txt");

    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }

    while (getline(file, line))
        data.push_back(line);

    file.close();

    return data;
}

std::vector<std::stack<char>> getStacks(const std::vector<std::string> &data)
{
    const int len = data[0].length();

    // Every stack is "[n]", where n is a character.
    // Every stack is 3 characters in the string.
    // Stacks are separated with space, so widths are:
    // 1 stack: 3
    // 2 stacks: 3 + 1 + 3 == 7
    // 3 stacks: 3 + 1 + 3 + 1 + 3 == 11
    // ...
    // Therefore, string length + 1 div 4 equals stack count
    const int stackCount = (len + 1) / 4;

    std::vector<std::stack<char>> stacks;

    for (int i = 0; i < stackCount; i++)
        stacks.push_back(std::stack<char>());

    int i = 0;

    while (i < (int)data.size())
    {
        // Find the line which has the stack numbers
        if (data[i][1] != '1')
        {
            i++;
            continue;
        }

        // Go up one line, to the 'floor' level
        i--;
        break;
    }

    // Start from bottom of the stack, going up
    while (i >= 0)
    {
        for (int stackNumber = 0; stackNumber < stackCount; stackNumber++)
        {
            char ch = data[i][stackNumber * 4 + 1];

            if (ch != ' ')
                stacks[stackNumber].push(ch);
        }
        i--;
    }
    return stacks;
}

void moveCrates(std::vector<std::stack<char>> &stacks, const std::vector<std::string> &instructions)
{
    int i = 0;

    // Find first instruction
    while (instructions[i][0] != 'm')
        i++;

    while (i < (int)instructions.size())
    {
        int howMany, fromStack, toStack;
        std::stack<char> tempStack;

        sscanf(instructions[i].c_str(), "move %d from %d to %d", &howMany, &fromStack, &toStack);

        // Move items to temp stack
        for (int j = 0; j < howMany; j++)
        {
            // Get item
            char crate = stacks[fromStack-1].top();
            // Remove item
            stacks[fromStack-1].pop();
            // Add to temp stack
            tempStack.push(crate);
        }

        // Move from temp stack to destination stack
        while (!tempStack.empty())
        {
            char crate = tempStack.top();
            tempStack.pop();
            stacks[toStack-1].push(crate);
        }

        i++;
    }
}

/**
 *  @brief Test functions
 *  @return Number of failed tests, zero if all were successful
 */
int doTests()
{
    int failedTests = 0;

    std::vector<std::string> testData =
    {
        "    [D]    ",
        "[N] [C]    ",
        "[Z] [M] [P]",
        " 1   2   3 ",
        "",
        "move 1 from 2 to 1",
        "move 3 from 1 to 3",
        "move 2 from 2 to 1",
        "move 1 from 1 to 2"
    };

    std::string message = "";
    std::string expectedMessage = "MCD";

    std::vector<std::stack<char>> stacks = getStacks(testData);

    moveCrates(stacks, testData);

    for (auto s : stacks)
        message += s.top();

    for (int i = 0; i < (int)expectedMessage.length(); i++)
    {
        if (message[i] != expectedMessage[i])
        {
            std::cout << "Stack " << i << ": Expected " << expectedMessage[i] << ", got " << message[i] << std::endl;
            failedTests++;
        }
    }

    if (message != expectedMessage)
    {
        std::cout << "Message: Expected \"" << expectedMessage << "\", got \"" << message << "\"" << std::endl;
        failedTests++;
    }

    return failedTests;
}

int main()
{
    int failedTests = doTests();

    if (failedTests != 0)
    {
        std::cout << failedTests << " test(s) failed" << std::endl;
        return 1;
    }

    std::vector<std::string> input = parseInput();
    std::vector<std::stack<char>> stacks = getStacks(input);

    moveCrates(stacks, input);

    std::string message = "";

    for (auto s : stacks)
        message += s.top();

    std::cout << "The items ending up at each stack are " << message << std::endl;

    return 0;
}
