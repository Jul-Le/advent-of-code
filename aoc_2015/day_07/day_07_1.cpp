/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2022-10-30
 *  Modified:           2022-11-06
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

/**
 *  @brief Check if given instruction has been processed
 *  @param instruction The instruction as a vector of strings
 *  @param wires Map of wires
 *  @return True if signal has been processed
 *  @details This function checks whether the last string in the 'instruction' vector
 *           exists as a key in the 'wires' map
 */
bool isProcessed(const std::vector<std::string> &instruction, std::map<std::string, uint16_t> &wires)
{
    const int substringCount = instruction.size();
    const std::string wire = instruction[substringCount - 1];
    std::map<std::string, uint16_t>::iterator it = wires.find(wire);

    // If wire was found from map, the instruction has been processed already
    return it != wires.end();
}

/**
 *  @brief Emulate given set of instructions and calculate values for every wire
 *  @param data Vector of instruction strings
 *  @return Wires mapped to their values
 */
std::map<std::string, uint16_t> emulate(const std::vector<std::string> &data)
{
    std::map<std::string, uint16_t> wires;

    // Whether all instructions have been processed
    bool done = false;

    while (!done)
    {
        // Set flag to true, if unprocessed instruction is found,
        // flag will be set to false within for loop
        done = true;

        for (auto str : data)
        {
            // Parse instruction
            char a[32], b[32], c[32], d[32], e[32];
            int substringCount = sscanf(str.c_str(), "%s %s %s %s %s", a, b, c, d, e);

            // Check instruction validity
            if (substringCount < 3 || substringCount > 5)
            {
                std::cout << "Invalid instruction" << std::endl;
                // Error handling is questionable here...
                // But if wires doesn't contain all the correct values, doTests() function will catch the error
                return wires;
            }

            // Instruction split into substrings
            std::vector<std::string> instruction;

            // Save instruction into vector of strings
            instruction.push_back(std::string(a));
            instruction.push_back(std::string(b));
            instruction.push_back(std::string(c));
            if (substringCount > 3)
                instruction.push_back(std::string(d));
            if (substringCount > 4)
                instruction.push_back(std::string(e));

            // If instruction has already been processed
            if (isProcessed(instruction, wires))
                continue;

            // When all instructions have been processed, this line won't be reached
            // so the while loop breaks
            done = false;

            /*
             *  Note: In the following section, instruction[n] is used countless times.
             *  Instead of indexes being magic numbers, enums would make this more readable
             *  and less error prone.
             */

            if (substringCount == 3)
            {
                // signal -> wire
                if (isNumber(instruction[0]))
                {
                    uint16_t signal = std::stoi(instruction[0]);
                    std::string wireTo = instruction[2];
                    wires[wireTo] = signal;
                }
                // wire -> wire
                else
                {
                    std::string wireFrom = instruction[0];

                    // Check if wireFrom exists
                    std::map<std::string, uint16_t>::iterator it = wires.find(wireFrom);
                    // If it doesn't exist
                    if (it == wires.end())
                    {
                        /*
                         *  Here we could either look for an instruction where wireFrom will be defined.
                         *  This would need to work recursively.
                         *
                         *  Another way would be to mark this instruction as unprocessed somehow
                         *  and do multiple passes on the instructions until everything is processed.
                         *  (this ended up being the solution)
                         */
                        continue;
                    }

                    std::string wireTo = instruction[2];
                    wires[wireTo] = wires[wireFrom];
                }
            }
            else if (substringCount == 4)
            {
                // NOT signal -> wire
                if (isNumber(instruction[1]))
                {
                    uint16_t signal = std::stoi(instruction[1]);
                    std::string wireTo = instruction[3];
                    wires[wireTo] = ~signal;
                }
                // NOT wire -> wire
                else
                {
                    std::string wireFrom = instruction[1];

                    // Check if wireFrom exists
                    std::map<std::string, uint16_t>::iterator it = wires.find(wireFrom);
                    // If it doesn't exist
                    if (it == wires.end())
                        continue;

                    std::string wireTo = instruction[3];
                    wires[wireTo] = ~wires[wireFrom];
                }
            }
            else // substringCount == 5
            {
                // wire/signal [op] wire/signal -> wire
                std::string op = instruction[1];
                std::string wireTo = instruction[4];

                uint16_t operand1, operand2;

                if (isNumber(instruction[0]))
                    operand1 = std::stoi(instruction[0]);
                else
                {
                    // Operand is a wire, check if it exists
                    std::string operand = instruction[0];
                    std::map<std::string, uint16_t>::iterator it = wires.find(operand);

                    if (it == wires.end())
                        continue;

                    operand1 = wires[operand];
                }

                if (isNumber(instruction[2]))
                    operand2 = std::stoi(instruction[2]);
                else
                {
                    // Operand is a wire, check if it exists
                    std::string operand = instruction[2];
                    std::map<std::string, uint16_t>::iterator it = wires.find(operand);

                    if (it == wires.end())
                        continue;

                    operand2 = wires[operand];
                }

                if (op == "AND")
                {
                    wires[wireTo] = operand1 & operand2;
                }
                else if (op == "OR")
                {
                    wires[wireTo] = operand1 | operand2;
                }
                else if (op == "LSHIFT")
                {
                    wires[wireTo] = operand1 << operand2;
                }
                else if (op == "RSHIFT")
                {
                    wires[wireTo] = operand1 >> operand2;
                }
                else // error
                {
                    std::cout << "Invalid operator: \"" << op << "\"" << std::endl;
                    return wires;
                }
            }
        }
    }

    return wires;
}

/**
 *  @brief Test functions
 *  @return Number of failed tests, zero if all were successful
 */
int doTests()
{
    int failedTests = 0;

     // Test data from AOC
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
    // Test data in reverse order
    const std::vector<std::string> testDataReverse =
    {
        "NOT y -> i",
        "NOT x -> h",
        "y RSHIFT 2 -> g",
        "x LSHIFT 2 -> f",
        "x OR y -> e",
        "x AND y -> d",
        "456 -> y",
        "123 -> x"
    };
    // Test data in random order
    const std::vector<std::string> testDataRandom =
    {
        "NOT x -> h",
        "x AND y -> d",
        "123 -> x",
        "NOT y -> i",
        "456 -> y",
        "y RSHIFT 2 -> g",
        "x LSHIFT 2 -> f",
        "x OR y -> e"
    };

    std::map<std::string, uint16_t> testWires = emulate(testData);
    std::map<std::string, uint16_t> testWiresReverse = emulate(testDataReverse);
    std::map<std::string, uint16_t> testWiresRandom = emulate(testDataRandom);

    if (testWires["d"] != 72)    { std::cout << "Line " << __LINE__ << ": d expected    72, got " << testWires["d"] << std::endl; failedTests++; }
    if (testWires["e"] != 507)   { std::cout << "Line " << __LINE__ << ": e expected   507, got " << testWires["e"] << std::endl; failedTests++; }
    if (testWires["f"] != 492)   { std::cout << "Line " << __LINE__ << ": f expected   492, got " << testWires["f"] << std::endl; failedTests++; }
    if (testWires["g"] != 114)   { std::cout << "Line " << __LINE__ << ": g expected   114, got " << testWires["g"] << std::endl; failedTests++; }
    if (testWires["h"] != 65412) { std::cout << "Line " << __LINE__ << ": h expected 65412, got " << testWires["h"] << std::endl; failedTests++; }
    if (testWires["i"] != 65079) { std::cout << "Line " << __LINE__ << ": i expected 65079, got " << testWires["i"] << std::endl; failedTests++; }
    if (testWires["x"] != 123)   { std::cout << "Line " << __LINE__ << ": x expected   123, got " << testWires["x"] << std::endl; failedTests++; }
    if (testWires["y"] != 456)   { std::cout << "Line " << __LINE__ << ": y expected   456, got " << testWires["y"] << std::endl; failedTests++; }

    if (testWiresReverse["d"] != 72)    { std::cout << "Line " << __LINE__ << ": d expected    72, got " << testWiresReverse["d"] << std::endl; failedTests++; }
    if (testWiresReverse["e"] != 507)   { std::cout << "Line " << __LINE__ << ": e expected   507, got " << testWiresReverse["e"] << std::endl; failedTests++; }
    if (testWiresReverse["f"] != 492)   { std::cout << "Line " << __LINE__ << ": f expected   492, got " << testWiresReverse["f"] << std::endl; failedTests++; }
    if (testWiresReverse["g"] != 114)   { std::cout << "Line " << __LINE__ << ": g expected   114, got " << testWiresReverse["g"] << std::endl; failedTests++; }
    if (testWiresReverse["h"] != 65412) { std::cout << "Line " << __LINE__ << ": h expected 65412, got " << testWiresReverse["h"] << std::endl; failedTests++; }
    if (testWiresReverse["i"] != 65079) { std::cout << "Line " << __LINE__ << ": i expected 65079, got " << testWiresReverse["i"] << std::endl; failedTests++; }
    if (testWiresReverse["x"] != 123)   { std::cout << "Line " << __LINE__ << ": x expected   123, got " << testWiresReverse["x"] << std::endl; failedTests++; }
    if (testWiresReverse["y"] != 456)   { std::cout << "Line " << __LINE__ << ": y expected   456, got " << testWiresReverse["y"] << std::endl; failedTests++; }

    if (testWiresRandom["d"] != 72)    { std::cout << "Line " << __LINE__ << ": d expected    72, got " << testWiresRandom["d"] << std::endl; failedTests++; }
    if (testWiresRandom["e"] != 507)   { std::cout << "Line " << __LINE__ << ": e expected   507, got " << testWiresRandom["e"] << std::endl; failedTests++; }
    if (testWiresRandom["f"] != 492)   { std::cout << "Line " << __LINE__ << ": f expected   492, got " << testWiresRandom["f"] << std::endl; failedTests++; }
    if (testWiresRandom["g"] != 114)   { std::cout << "Line " << __LINE__ << ": g expected   114, got " << testWiresRandom["g"] << std::endl; failedTests++; }
    if (testWiresRandom["h"] != 65412) { std::cout << "Line " << __LINE__ << ": h expected 65412, got " << testWiresRandom["h"] << std::endl; failedTests++; }
    if (testWiresRandom["i"] != 65079) { std::cout << "Line " << __LINE__ << ": i expected 65079, got " << testWiresRandom["i"] << std::endl; failedTests++; }
    if (testWiresRandom["x"] != 123)   { std::cout << "Line " << __LINE__ << ": x expected   123, got " << testWiresRandom["x"] << std::endl; failedTests++; }
    if (testWiresRandom["y"] != 456)   { std::cout << "Line " << __LINE__ << ": y expected   456, got " << testWiresRandom["y"] << std::endl; failedTests++; }

    return failedTests;
}

int main()
{
    int failedTests = doTests();

    if (failedTests)
    {
        std::cout << failedTests << " test(s) failed" << std::endl;
        return 1;
    }

    std::vector<std::string> input = parseInput();
    std::map<std::string, uint16_t> wires = emulate(input);

    std::cout << "Signal to wire \"a\" is " << wires["a"] << std::endl;

    return 0;
}
