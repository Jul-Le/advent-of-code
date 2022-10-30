/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-10-30
 *  Modified:           2022-10-30
 *
 *  
 *
 *  Each wire has an identifier (some lowercase letters) and can
 *  carry a 16-bit signal.
 *
 *  For example:
 *
 *  "123 -> x" means that the signal 123 is provided to wire x.
 *
 *  "x AND y -> z" means that the bitwise AND of wire x and wire
 *  y is provided to wire z.
 *
 *  "p LSHIFT 2 -> q" means that the value from wire p is
 *  left-shifted by 2 and then provided to wire q.
 *
 *  "NOT e -> f" means that the bitwise complement of the value
 *  from wire e is provided to wire f.
 *
 *  Operators: AND (&), OR (|), LSHIFT (<<), RSHIFT(>>), NOT (~)
 *
 *  What signal is ultimately provided to wire "a"?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

enum class Operator
{
    AND,
    OR,
    LSHIFT,
    RSHIFT,
    NOT
};

class Wire
{
public:
    Wire()
    {
        
    }
    
private:
    std::string m_identifier;
    uint16_t m_signal;
    Operator m_operator;
};

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

bool isNumber(const std::string &str)
{
    if (str.empty())
        return false;
    
    const char firstChar = str[0];
    
    return firstChar >= '0' && firstChar <= '9';
}

// TODO this function is not required because operators are always in specific part of the instruction
bool isOperator(const std::string &str)
{
    return str == "AND" || str == "OR" || str == "LSHIFT" || str == "RSHIFT" || str == "NOT";
}

/*
 *  Every instruction has the arrow "->" right before the last element.
 *  Last element is always the wire that the values are being assigned to.
 *
 *  If instruction contains 3 substrings, first is always either signal or wire.
 *
 *  If instruction contains 4 substrings, first is always NOT and second is a signal/wire
 *
 *  If instruction contains 5 substrings, first and third are signals/wires,
 *  while second is always an operator.
 *
 *  The second last substring is always "->".
 *
 *  +-----------------+-------------+-------------+-------------+-------------+-------------+
 *  | # of substrings | [0]         | [1]         | [2]         | [3]         | [4]         |
 *  +-----------------+-------------+-------------+-------------+-------------+-------------+
 *  | 3               | signal/wire | "->"        | wire        | N/A         | N/A         |
 *  | 4               | "NOT"       | signal/wire | "->"        | wire        | N/A         |
 *  | 5               | signal/wire | operator    | signal/wire | "->"        | wire        |
 *  +-----------------+-------------+-------------+-------------+-------------+-------------+
 */

bool testsPass()
{
    bool pass = true;
    
    const std::vector<std::string> testData =
    {
        "123 -> x",
        "456 -> y",
        "x AND y -> d",
        "x OR y -> e",
        "x LSHIFT 2 -> f",
        "y RSHIFT 2 -> g",
        "NOT x -> h",
        "NOT y -> i"
    };

    std::map<std::string, uint16_t> wires;

    // TODO tests
    if (true)
    {
        pass = false;
        //std::cout << "isHello(\"Hello world\") returned false" << std::endl;
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
    
    for (auto line : input)
        std::cout << line << std::endl;
    
    return 0;
}
