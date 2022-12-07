/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-12-07
 *  Modified:           2022-12-07
 *
 *
 *
 *  Split the rucksacks into groups of three. Find the item type
 *  that appears in all three rucksacks in a group. What is the
 *  sum of the priorities of those item types?
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

/**
 *  @brief Get priority of char
 *  @param ch Char
 *  @return 'a' ... 'z' mapped to 1 ... 26, 'A' ... 'Z' mapped
 *          to 27 ... 52, otherwise return 0
 */
int getPriority(char ch)
{
    int priority = 0;

    if (ch >= 'a' && ch <= 'z')
    {
        priority = ch - 'a' + 1;
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
        priority = ch - 'A' + 27;
    }
    return priority;
}

/**
 *  @brief Find item that exists in 3 consecutive rucksacks
 *  @param rucksacks Vector of strings
 *  @param index Vector index which to start from
 *  @return Character that occurs in 3 consecutive strings
 *  @details Returns first occurence of duplicate character.
             Element at given index, index+1 and index+2 are
             accessed. Index needs to be vector size-3 or less.
             No OOB check is done.
 */
char getItem(const std::vector<std::string> &rucksacks, int index)
{
    const std::string sack1 = rucksacks[index];
    const std::string sack2 = rucksacks[index+1];
    const std::string sack3 = rucksacks[index+2];
    const int len1 = sack1.length();

    for (int i = 0; i < len1; i++)
    {
        char ch = sack1[i];

        if (sack2.find(ch) != std::string::npos && sack3.find(ch) != std::string::npos)
            return ch;
    }
    return '\0';
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
        "vJrwpWtwJgWrhcsFMMfFFhFp",
        "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
        "PmmdzqPrVvPwwTWBwg",
        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
        "ttgJtRGJQctTZtZT",
        "CrZsJsPPZsGzwwsLwLmpwMDw"
    };

    const std::vector<char> expectedItems = { 'r', 'Z' };
    const std::vector<int> expectedPriorities = { 18, 52 };
    const int expectedTotalPriorities = 70;

    std::vector<char> items;
    std::vector<int> priorities;
    int totalPriorities = 0;

    for (int i = 0; i < (int)testData.size(); i += 3)
    {
        char item = getItem(testData, i);
        int priority = getPriority(item);

        items.push_back(item);
        priorities.push_back(priority);
        totalPriorities += priority;
    }

    // Test all items and priorities
    for (int i = 0; i < (int)items.size(); i++)
    {
        if (items[i] != expectedItems[i])
        {
            failedTests++;
            std::cout << "Item " << i << ": Expected \'" << expectedItems[i] << "\', got \'" << items[i] << "\'" << std::endl;
        }
        if (priorities[i] != expectedPriorities[i])
        {
            failedTests++;
            std::cout << "Priority " << i << ": Expected " << expectedPriorities[i] << ", got " << priorities[i] << std::endl;
        }
    }

    // Test total priorities
    if (totalPriorities != expectedTotalPriorities)
    {
        failedTests++;
        std::cout << "Total priorities: Expected " << expectedTotalPriorities << ", got " << totalPriorities << std::endl;
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
    int totalPriorities = 0;

    for (int i = 0; i < (int)input.size(); i += 3)
        totalPriorities += getPriority(getItem(input, i));

    std::cout << "Sum of priorities is " << totalPriorities << std::endl;

    return 0;
}
