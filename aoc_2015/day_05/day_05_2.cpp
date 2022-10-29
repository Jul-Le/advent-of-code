/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-10-29
 *  Modified:           2022-10-29
 *
 *
 *
 *  Part 2: A nice string has all of the following properties:
 *  It contains a pair of any two letters that appears at least
 *  twice in the string without overlapping.
 *  It contains at least one letter which repeats with exactly
 *  one letter between them.
 *
 *  How many strings are nice?
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
 *  @brief Check if string contains pair of two letters
 *  @param String
 *  @return True if argument contains pair of two letters
 *  @details Identical pair of letters exist in at least two
 *           different positions within the string
 */
bool containsPairOfTwoLetters(const std::string &str)
{
    const int len = str.length();
    
    for (int i = 0; i < len - 3; i++)
    {
        for (int j = i+2; j < len - 1; j++)
        {
            if (str[i] == str[j] && str[i+1] == str[j+1])
                return true;
        }
    }
    
    return false;
}

/**
 *  @brief Check if string contains double letter with one
 *         letter between
 *  @param String
 *  @return True if argument contains double letter
 *  @details Double letter means that two characters in indexes
 *           [n] and [n+2] are the same
 *  @note Characters could be anything, not just letters.
 */
bool containsLetterRepeatingWithOneLetterBetween(const std::string &str)
{
    for (int i = 0; i < str.length() - 2; i++)
    {
        // If two characters with index difference of 2 are the same
        if (str[i] == str[i+2])
            return true;
    }

    return false;
}

bool isNice(const std::string &str)
{
    return containsPairOfTwoLetters(str)
        && containsLetterRepeatingWithOneLetterBetween(str);
}

/**
 *  @brief Use examples to test functions
 *  @return True if all tests pass
 */
bool testsPass()
{
    bool pass = true;

    // "qjhvhtzxzqqjkmpb" should be nice
    if (!isNice("qjhvhtzxzqqjkmpb"))
    {
        pass = false;
        std::cout << "isNice(\"qjhvhtzxzqqjkmpb\") returned false" << std::endl;
    }

    // "xxyxx" should be nice
    if (!isNice("xxyxx"))
    {
        pass = false;
        std::cout << "isNice(\"xxyxx\") returned false" << std::endl;
    }

    // "uurcxstgmygtbstg" should not be nice
    if (isNice("uurcxstgmygtbstg"))
    {
        pass = false;
        std::cout << "isNice(\"uurcxstgmygtbstg\") returned true" << std::endl;
    }

    // "ieodomkazucvgmuy" should not be nice
    if (isNice("ieodomkazucvgmuy"))
    {
        pass = false;
        std::cout << "isNice(\"ieodomkazucvgmuy\") returned true" << std::endl;
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
