/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-12-04
 *  Modified:           2022-12-04
 *
 *
 *
 *  This time the second column says how the round needs to end:
 *  X means you need to lose, Y means you need to end the round
 *  in a draw, and Z means you need to win.
 *
 *  What would your total score be if everything goes exactly
 *  according to your strategy guide?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

int getScore(std::string str)
{
    // Convert choices into values 0, 1, or 2
    const int opponentChoice = str[0] - 'A';
    const int result = str[2];

    int score = 0;

    // When winning, my choice will be opponent choice + 1.
    // When draw, my choice will be equal to opponent choice.
    // When losing, my choice will be opponent choice - 1
    switch (result)
    {
        case 'X':
            // Add 1-3 points, depending on choice
            score += (opponentChoice + 2) % 3 + 1;
            break;
        case 'Y':
            // Add 1-3 points, depending on choice
            score += opponentChoice + 1;
            score += 3; // Add draw score
            break;
        case 'Z':
            // Add 1-3 points, depending on choice
            score += (opponentChoice + 1) % 3 + 1;
            score += 6; // Add win score
            break;
    }

    return score;
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
        "A Y",
        "B X",
        "C Z"
    };

    std::vector<int> expectedScores = { 4, 1, 7 };

    int totalScore = 0;
    const int expectedTotalScore = 12;

    for (int i = 0; i < 3; i++)
    {
        int score = getScore(testData[i]);
        int expectedScore = expectedScores[i];

        totalScore += score;

        if (score != expectedScore)
        {
            failedTests++;
            std::cout << "Round " << i << " score: Expected " << expectedScore << ", got " << score << std::endl;
        }
    }

    if (totalScore != expectedTotalScore)
    {
        failedTests++;
        std::cout << "Total score: Expected " << expectedTotalScore << ", got " << totalScore << std::endl;
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
    int totalScore = 0;

    for (auto line : input)
        totalScore += getScore(line);

    std::cout << "The total score is " << totalScore << std::endl;

    return 0;
}
