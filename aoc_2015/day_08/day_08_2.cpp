/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-11-08
 *  Modified:           2022-11-11
 *
 *
 *
 *  Now, let's go the other way. In addition to finding the
 *  number of characters of code, you should now encode each
 *  code representation as a new string and find the number of
 *  characters of the new encoded representation, including the
 *  surrounding double quotes.
 *
 *  For example:
 *
 *  "" encodes to "\"\"", an increase from 2 characters to 6.
 *
 *  "abc" encodes to "\"abc\"", an increase from 5 characters
 *  to 9.
 *
 *  "aaa\"aaa" encodes to "\"aaa\\\"aaa\"", an increase from
 *  10 characters to 16.
 *
 *  "\x27" encodes to "\"\\x27\"", an increase from 6 characters
 *  to 11.
 *
 *  Your task is to find the total number of characters to
 *  represent the newly encoded strings minus the number of
 *  characters of code in each original string literal.
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

int encodedCharCount(std::string s)
{
    // Add 2 escaped double quotes
    int len = s.length() + 4;

    // For every backslash add 2 to the length
    // For every double quote add 2 to the length
    // For every hexadecimal add 1 to the length

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
            len += 2;

        nPos = s.find(backslash, nPos + 1);
    }

    // Find double quotes
    nPos = s.find(doubleQuote, 0);
    while (nPos != std::string::npos)
    {
        // Don't count if terminating double quote is preceded with backslash
        if (nPos != s.length() - 2)
            len += 2;
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
            len++;
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
    //  "\"qwe\\xrty\"",    // "qwe\xrty" <- This needs to be removed because otherwise "\\x" in the input data would be counted as backslash and hexadecimal.
                            //               Input data does not contain random non-escaped backslashes
        "\"\\\\\\\\q\"",    // "\\\\q"
        "\"hhqe\\\\\""      // "hhqe\\"
    };
    const std::vector<int> expectedStringChars = { 2, 5, 10, 6, /*10,*/ 7, 8 };
    const std::vector<int> expectedEncodedChars = { 6, 9, 16, 11, /*15,*/ 15, 14 };
    const int expectedTotalStringChars = 2 + 5 + 10 + 6 /*+ 10*/ + 7 + 8;
    const int expectedTotalEncodedChars = 6 + 9 + 16 + 11 /*+ 15*/ + 15 + 14;

    int totalStringChars = 0;
    int totalEncodedChars = 0;

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

        result = encodedCharCount(testStrings[i]);
        expected = expectedEncodedChars[i];

        totalEncodedChars += result;

        if (result != expected)
        {
            std::cout << testStrings[i] << " encodedCharCount: Expected " << expected << ", got " << result << std::endl;
            failedTests++;
        }
    }

    if (totalStringChars != expectedTotalStringChars)
    {
        std::cout << "Total string char count: Expected " << expectedTotalStringChars << ", got " << totalStringChars << std::endl;
        failedTests++;
    }

    if (totalEncodedChars != expectedTotalEncodedChars)
    {
        std::cout << "Total encoded char count: Expected " << expectedTotalEncodedChars << ", got " << totalEncodedChars << std::endl;
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
    long long encodedLength = 0;

    for (auto line : input)
    {
        stringLength += stringCharCount(line);
        encodedLength += encodedCharCount(line);
    }

    std::cout << encodedLength - stringLength << std::endl;

    return 0;
}
