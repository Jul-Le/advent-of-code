/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-10-29
 *  Modified:           2022-10-29
 *
 *
 *
 *  A nice string is one with all of the following properties:
 *  It contains at least three vowels (aeiou only).
 *  It contains at least one letter that appears twice in a row.
 *  It does not contain the strings ab, cd, pq, or xy.
 *
 *  How many strings are nice?
 */

#include <algorithm> // std::count
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
 *  @brief Check if string has at least 3 vowels
 *  @param String
 *  @return True if argument contains at least 3 vowels
 *  @details Vowels are 'a', 'e', 'i', 'o' and 'u'.
 */
bool containsThreeVowels(const std::string &str)
{
    int vowels = 0;

    vowels += std::count(str.begin(), str.end(), 'a');
    vowels += std::count(str.begin(), str.end(), 'e');
    vowels += std::count(str.begin(), str.end(), 'i');
    vowels += std::count(str.begin(), str.end(), 'o');
    vowels += std::count(str.begin(), str.end(), 'u');

    return vowels >= 3;
}

/**
 *  @brief Check if string contains double letter
 *  @param String
 *  @return True if argument contains double letter
 *  @details Double letter means that two consecutive
 *           characters are the same.
 *  @note Characters could be anything, not just letters.
 */
bool containsDoubleLetter(const std::string &str)
{
    for (int i = 0; i < str.length() - 1; i++)
    {
        // If two consecutive characters are the same
        if (str[i] == str[i+1])
            return true;
    }

    return false;
}

/**
 *  @brief Check if string contains forbidden substring
 *  @param String
 *  @return True if argument contains forbidden substring
 *  @details Forbidden substrings are "ab", "cd", "pq", "xy"
 */
bool containsForbiddenString(const std::string &str)
{
    const std::vector<std::string> forbiddenStrings { "ab", "cd", "pq", "xy" };

    for (auto s : forbiddenStrings)
    {
        // Check if s exists withing str
        bool found = str.find(s) != std::string::npos;

        if (found)
            return true;
    }

    return false;
}

bool isNice(const std::string &str)
{
    return containsThreeVowels(str)
        && containsDoubleLetter(str)
        && !containsForbiddenString(str);
}

/**
 *  @brief Use examples to test functions
 *  @return True if all tests pass
 */
bool testsPass()
{
    bool pass = true;

    // "ugknbfddgicrmopn" should be nice
    if (!isNice("ugknbfddgicrmopn"))
    {
        pass = false;
        std::cout << "isNice(\"ugknbfddgicrmopn\") returned false" << std::endl;
    }

    // "aaa"              should be nice
    if (!isNice("aaa"))
    {
        pass = false;
        std::cout << "isNice(\"aaa\") returned false" << std::endl;
    }

    // "jchzalrnumimnmhp" should not be nice
    if (isNice("jchzalrnumimnmhp"))
    {
        pass = false;
        std::cout << "isNice(\"jchzalrnumimnmhp\") returned true" << std::endl;
    }

    // "haegwjzuvuyypxyu" should not be nice
    if (isNice("haegwjzuvuyypxyu"))
    {
        pass = false;
        std::cout << "isNice(\"haegwjzuvuyypxyu\") returned true" << std::endl;
    }

    // "dvszwmarrgswjxmb" should not be nice
    if (isNice("dvszwmarrgswjxmb"))
    {
        pass = false;
        std::cout << "isNice(\"dvszwmarrgswjxmb\") returned true" << std::endl;
    }

    return pass;
}

int main()
{
    if (!testsPass())
    {
        std::cout << "One or more tests failed" << std::endl;
        return 1;
    }

    std::vector<std::string> input = parseInput();
    int niceStringCount = 0;

    for (auto line : input)
        if (isNice(line))
            niceStringCount++;

    std::cout << niceStringCount << " strings are nice" << std::endl;
    return 0;
}
