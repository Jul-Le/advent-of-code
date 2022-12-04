/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-12-04
 *  Modified:           2022-12-04
 *
 *
 *
 *  Input is rock-paper-scissors strategy guide. Every line
 *  consists of opponent's move (A, B, or C) and your move
 *  (X, Y, or Z).
 *
 *  A == X == Rock
 *  B == Y == Paper
 *  C == Z == Scissors
 *
 *  Your total score is the sum of your scores for each round.
 *  The score for a single round is the score for the shape you
 *  selected (1 for Rock, 2 for Paper, and 3 for Scissors) plus
 *  the score for the outcome of the round (0 if you lost, 3 if
 *  the round was a draw, and 6 if you won).
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
    const int myChoice = str[2] - 'X';

    int score = 0;

    // Add 6 points if win
    if ((opponentChoice + 1) % 3 == myChoice)
        score += 6;
    // Add 3 points if draw
    else if (opponentChoice == myChoice)
        score += 3;
    // Add 0 points if loss

    // Add 1 for rock, 2 for paper, 3 for scissors
    return score + myChoice + 1;
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

    std::vector<int> expectedScores = { 8, 1, 6 };

    int totalScore = 0;
    const int expectedTotalScore = 15;

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
