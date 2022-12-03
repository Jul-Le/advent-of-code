/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-12-03
 *  Modified:           2022-12-03
 *
 *
 *
 *  Input list represents calories of food carried by elves.
 *
 *  Find the top three elves carrying the most Calories. How
 *  many total Calories are those elves carrying?
 */

#include <algorithm>
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

std::vector<int> getCalories(const std::vector<std::string> data)
{
    std::vector<int> calories = { 0 };

    for (auto line : data)
    {
        // Blank line, move to next elf
        if (line == "")
        {
            calories.push_back(0);
            continue;
        }

        // Add calories
        calories[calories.size() - 1] += std::stoi(line);
    }
    return calories;
}

bool greater(int a, int b)
{
    return a > b;
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
        "1000",
        "2000",
        "3000",
        "",
        "4000",
        "",
        "5000",
        "6000",
        "",
        "7000",
        "8000",
        "9000",
        "",
        "10000"
    };

    std::vector<int> totalCalories = getCalories(testData);
    std::vector<int> expectedCalories = { 6000, 4000, 11000, 24000, 10000 };

    if (totalCalories.size() != 5)
    {
        failedTests++;
        std::cout << "totalCalories.size(): Expected " << expectedCalories.size()
                  << ", got " << totalCalories.size() << std::endl;
        // Skip other tests to avoid out of bounds errors
        return failedTests;
    }

    for (int i = 0; i < totalCalories.size(); i++)
    {
        if (totalCalories[i] != expectedCalories[i])
        {
            failedTests++;
            std::cout << "Total calories: Expected " << expectedCalories[i] << ", got " << totalCalories[i] << std::endl;
        }
    }
    // Get largest calorie amount
    int mostCalories = 0;

    // Sort descending
    std::sort(totalCalories.begin(), totalCalories.end(), greater);

    // Add up three largest
    for (int i = 0; i < 3; i++)
        mostCalories += totalCalories[i];

    if (mostCalories != 45000)
    {
        failedTests++;
        std::cout << "Most calories: Expected 45000, got " << mostCalories << std::endl;
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
    std::vector<int> calories = getCalories(input);
    int mostCalories = 0;

    std::sort(calories.begin(), calories.end(), greater);

    for (int i = 0; i < 3; i++)
        mostCalories += calories[i];

    std::cout << "The sum of top three calorie counts is " << mostCalories << std::endl;

    return 0;
}
