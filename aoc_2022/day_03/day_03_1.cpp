/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-12-03
 *  Modified:           2022-12-03
 *
 *
 *
 *  Input is a list of rucksack contents (strings). Rucksacks
 *  are divided into 2 compartments (1st half of the string
 *  = 1st compartment, 2nd half of the string = 2nd
 *  compartment). Strings have even number of characters.
 *
 *  Characters have priorities:
 *  'a' through 'z' have priorities 1...26.
 *  'A' through 'Z' have priorities 27...52.
 *
 *  Find the item type (char) that appears in both compartments
 *  (halves) of each rucksack (string). What is the sum of the
 *  priorities of those item types?
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
 *  @brief Find character that exists both in first and second
 *         half of string
 *  @param str String
 *  @return Character that occurs in first and second half
 *  @details Returns first occurence of duplicate character. If
 *           input string length is odd number, undefined
 *           behaviour. If no duplicate found, return null char.
 */
char getItem(std::string str)
{
    const int len = str.length();

    for (int i = 0; i < len/2; i++)
    {
        for (int j = len/2; j < len; j++)
        {
            if (str[i] == str[j])
                return str[i];
        }
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

    const std::vector<char> expectedItems = { 'p', 'L', 'P', 'v', 't', 's' };
    const std::vector<int> expectedPriorities = { 16, 38, 42, 22, 20, 19 };
    const int expectedTotalPriorities = 157;

    std::vector<char> items;
    std::vector<int> priorities;
    int totalPriorities = 0;

    // Get items & priorities for each input line
    for (auto str : testData)
    {
        char item = getItem(str);
        int priority = getPriority(item);

        items.push_back(item);
        priorities.push_back(priority);
        totalPriorities += priority;


    }

    // Test all items and priorities
    for (int i = 0; i < testData.size(); i++)
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

    for (auto line : input)
        totalPriorities += getPriority(getItem(line));

    std::cout << "Sum of priorities is " << totalPriorities << std::endl;

    return 0;
}
