/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-12-10
 *  Modified:           2022-12-10
 *
 *
 *
 *  Input is a list of pairs, for example "2-4,6,8"
 *
 *  In how many pairs does one range fully contain the other?
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

bool rangeContainsAnother(const std::string &str)
{
    int a, b, c, d;

    sscanf(str.c_str(), "%d-%d,%d-%d", &a, &b, &c, &d);

    return ((a <= c) && (b >= d)) || ((a >= c) && (b <= d));
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
        "2-4,6-8",
        "2-3,4-5",
        "5-7,7-9",
        "2-8,3-7",
        "6-6,4-6",
        "2-6,4-8"
    };
    int totalContains = 0;

    const std::vector<bool> expectedResults = { false, false, false, true, true, false };
    const int expectedTotalContains = 2;

    for (int i = 0; i < (int)testData.size(); i++)
    {
        bool containsAnother = rangeContainsAnother(testData[i]);

        if (containsAnother)
            totalContains++;

        if (containsAnother != expectedResults[i])
        {
            std::cout << i << ": Expected " << expectedResults[i] << ", got " << containsAnother << std::endl;
            failedTests++;
        }
    }

    if (totalContains != expectedTotalContains)
    {
        std::cout << "Total: Expected " << expectedTotalContains << ", got " << totalContains << std::endl;
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
    int total = 0;

    for (auto line : input)
        if (rangeContainsAnother(line))
            total++;

    std::cout << "One range contains the other in " << total << " pairs" << std::endl;

    return 0;
}
