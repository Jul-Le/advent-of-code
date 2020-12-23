/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            13.12.2020
 *  Modified:           13.12.2020
 *
 *  
 *
 *  What is the earliest timestamp such that all of the
 *  listed bus IDs depart at offsets matching their
 *  positions in the list?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

class Bus
{
public:
    Bus(uint64_t i, uint64_t p) : m_id(i), m_position(p)
    {
        
    }
        
    uint64_t id() { return m_id; }
    uint64_t position() { return m_position; }
    
private:
    uint64_t m_id;
    uint64_t m_position;
};

/**
 *  @brief Calculate answer to part 2 question
 *  @details
 *  n[i] = (n[0] * x[0] + i) / x[i]
 *
 *  x[] = bus id:s
 *  n[] = nth time the bus leaves
 *  i   = container index
 *
 *  x[] values are given in input file.
 *  i is the iteration index.
 *  n[] is unknown.
 *  By trying different values for n[0], there must be a value
 *  for n[0] such that all values n[i] are integers.
 *  When such value for n[0] is found, answer is n[0] * x[0].
 *
 *  @todo O(n) takes too much time, O(log n) or O(1) required
 */
uint64_t calcTimeStamp(std::vector<Bus> buses)
{
    uint64_t x0 = buses[0].id();
    uint64_t n0 = 0;
    bool solved = false;
    
    uint64_t maxID = 0;
    
    for (Bus b : buses)
        maxID = b.id() > maxID ? b.id() : maxID;
    std::cout << maxID << std::endl;
    getchar();
    
    //const unsigned long long LCM = 1390548191579807;
    uint64_t counter = 0;
    uint64_t temp = 1;
    uint64_t i = 1;
    while (!solved)
    {
        while (n0*x0 < maxID * i)
            n0++;
        //std::cout << n0 << "*" << x0 << " >= " << maxID << " * " << i << std::endl;
        //getchar();
        n0--;
        i++;
        solved = true;
        
        for (uint64_t i = 0; i < buses.size(); i++)
        {
            if ((n0*x0+buses[i].position()) % buses[i].id() == 0)
                continue;
            else
            {
                solved = false;
                break;
            }
        }
        counter++;
        if (counter == temp)
        {
            std::cout << n0*x0 << std::endl;
            temp *= 2;
        }
    }
    return n0 * x0;
}

/**
 *  The bus depart offsets match at regular interval.
 *  The lowest common multiple between the bus IDs is
 *  that interval.
 *
 */
uint64_t calcTimeStamp(std::vector<Bus> buses)
{
    
}

int main()
{
    std::string line;
    std::ifstream file;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    std::vector<Bus> buses;
    
    // Departure time not relevant in part 2
    getline(file, line);
    
    // Parse bus IDs
    getline(file, line);
    file.close();
    
    // Separate by comma
    boost::char_separator<char> sep(",");
    tokenizer tokens(line, sep);
    
    uint64_t i = 0;
    
    // Loop handling comma separated values within line
    BOOST_FOREACH(std::string const& token, tokens)
    {
        int id;
        
        if (token != "x")
        {
            sscanf(token.c_str(), "%d", &id);
            buses.push_back(Bus(id, i));
        }
        i++;
    }
    
    uint64_t timestamp = calcTimeStamp(buses);
    
    std::cout << timestamp << std::endl;
    
    return 0;
}
