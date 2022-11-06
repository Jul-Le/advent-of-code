/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-11-06
 *  Modified:           2022-11-06
 *
 *
 *
 *  Input is a list of strings. Strings may contain escape
 *  sequences: Backlashes (\\), lone double quotes (\") and
 *  hexadecimals (\x followed by two hexadecimal characters,
 *  for example \x27). Each of these sequences represent
 *  a single ascii character. In addition, each string is
 *  surrounded by double quotes, which don't count towards
 *  the characters in memory.
 *
 *  Disregarding the whitespace in the file, what is the number
 *  of characters of code for string literals minus the number
 *  of characters in memory for the values of the strings in
 *  total for the entire file?
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

bool isHexadecimal(char c)
{
    return (c >= '0' && c <= '9') ||
           (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}

int stringCharCount(std::string s)
{
    return s.length();
}

int memoryCharCount(std::string s)
{
    // Remove the double quotes around the string
    int len = s.length() - 2;

    const std::string backslash = "\\\\";
    const std::string doubleQuote = "\\\"";
    const std::string hexadecimal = "\\x";
    size_t nPos;

    // Find backslashes
    nPos = s.find(backslash, 0);
    while (nPos != std::string::npos)
    {
        // Make sure backslash is not preceded by another backslash to avoid counting overlaps, such as "\\\"
        // If backslash is preceded by double backslash, it shall be counted
        // Note: This will parse properly up to 4 backslashes in a row. The input data doesn't happen to contain more than 4 in a row.
        if (s[nPos-1] != '\\' || (s[nPos-1] == '\\' && s[nPos-2] == '\\'))
            len--;

        nPos = s.find(backslash, nPos + 1);
    }

    // Find double quotes
    nPos = s.find(doubleQuote, 0);
    while (nPos != std::string::npos)
    {
        // Don't count if terminating double quote is preceded with backslash
        if (nPos != s.length() - 2)
            len--;
        nPos = s.find(doubleQuote, nPos + 1);
    }

    // Find hexadecimal characters
    nPos = s.find(hexadecimal, 0);
    while (nPos != std::string::npos)
    {
        // Make sure we won't go out of bounds, then check if
        // characters following "\x" are hexadecimals
        if (nPos + 3 < s.length() &&
            isHexadecimal(s[nPos+2]) &&
            isHexadecimal(s[nPos+3]))
        {
            len -= 3;
        }

        nPos = s.find(hexadecimal, nPos + 1);
    }

    return len;
}

/**
 *  @brief Test functions
 *  @return Number of failed tests, zero if all were successful
 */
int doTests()
{
    int failedTests = 0;

    const std::vector<std::string> testStrings =
    {
        "\"\"",             // ""
        "\"abc\"",          // "abc"
        "\"aaa\\\"aaa\"",   // "aaa\"aaa"
        "\"\\x27\"",        // "\x27"
        "\"qwe\\xrty\"",    // "qwe\xrty" <- This is added because input data might contain "\x" which is not followed by hexadecimal characters
        "\"\\\\\\\\q\"",    // "\\\\q" <- This is added to make sure this counts as four backslashes
        "\"hhqe\\\\\""      // "hhqe\\" <- This is added in case the terminating double quote is preceded by escaped backslash
    };
    const std::vector<int> expectedStringChars = { 2, 5, 10, 6, 10, 7, 8 };
    const std::vector<int> expectedMemoryChars = { 0, 3, 7, 1, 8, 3, 5 };
    const int expectedTotalStringChars = 23 + 10 + 7 + 8;
    const int expectedTotalMemoryChars = 11 + 8 + 3 + 5;

    int totalStringChars = 0;
    int totalMemoryChars = 0;

    for (int i = 0; i < (int)testStrings.size(); i++)
    {
        int result = stringCharCount(testStrings[i]);
        int expected = expectedStringChars[i];

        totalStringChars += result;

        if (result != expected)
        {
            std::cout << testStrings[i] << " stringCharCount: Expected " << expected << ", got " << result << std::endl;
            failedTests++;
        }

        result = memoryCharCount(testStrings[i]);
        expected = expectedMemoryChars[i];

        totalMemoryChars += result;

        if (result != expected)
        {
            std::cout << testStrings[i] << " memoryCharCount: Expected " << expected << ", got " << result << std::endl;
            failedTests++;
        }
    }

    if (totalStringChars != expectedTotalStringChars)
    {
        std::cout << "Total string char count: Expected " << expectedTotalStringChars << ", got " << totalStringChars << std::endl;
        failedTests++;
    }

    if (totalMemoryChars != expectedTotalMemoryChars)
    {
        std::cout << "Total memory char count: Expected " << expectedTotalMemoryChars << ", got " << totalMemoryChars << std::endl;
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
    long long stringLength = 0;
    long long memoryLength = 0;

    for (auto line : input)
    {
        stringLength += stringCharCount(line);
        memoryLength += memoryCharCount(line);
    }

    std::cout << stringLength - memoryLength << std::endl;

    return 0;
}
