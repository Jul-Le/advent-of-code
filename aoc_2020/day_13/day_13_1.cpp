/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            13.12.2020
 *  Modified:           13.12.2020
 *
 *  
 *
 *  Input is departure time and departure intervals (IDs)
 *  of buses.
 *
 *  Find the bus that leaves first after your departure time.
 *
 *  What is the product of id of that bus and the time you have
 *  to wait?
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
    Bus(int i) : m_id(i)
    {
        
    }
    
    getNextDepartureTime(int curTime)
    {
        int lastDeparture, nextDeparture;
        /*
         *  Example:
         *    Bus leaves every 10 mins.
         *    Time is now 15 min.
         *    Last departure was:
         *      ((curTime-1) / m_id) * m_id
         *      ((   15-1  ) / 10  ) * 10  
         *      (14 / 10) * 10
         *      ( 1 ) * 10
         *      10
         *    Next departure:
         *      10 + 10 = 20
         */
        lastDeparture = ((curTime-1) / m_id) * m_id;
        nextDeparture = lastDeparture + m_id;
        
        return nextDeparture;
    }
    
    int id() { return m_id; }
    
private:
    int m_id;
};

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
    
    int departureTime;
    std::vector<Bus> buses;
    
    // Parse departure time
    getline(file, line);
    sscanf(line.c_str(), "%d", &departureTime);
    
    // Parse bus IDs
    getline(file, line);
    file.close();
    
    // Separate by comma
    boost::char_separator<char> sep(",");
    tokenizer tokens(line, sep);
    
    // Loop handling comma separated values within line
    BOOST_FOREACH(std::string const& token, tokens)
    {
        int id;
        
        if (token != "x")
        {
            sscanf(token.c_str(), "%d", &id);
            buses.push_back(Bus(id));
        }
    }
    
    // Time when next bus leaves
    int earliestNextDeparture = buses.at(0).getNextDepartureTime(departureTime);
    int id = buses.at(0).id(); // id of bus that leaves next
    
    // First bus in the vector gets checked twice, whatever
    for (auto bus : buses)
    {
        int nextDep = bus.getNextDepartureTime(departureTime);
        if (nextDep < earliestNextDeparture)
        {
            earliestNextDeparture = nextDep;
            id = bus.id();
        }
    }
    
    // Shorten variable names
    int d = departureTime;
    int e = earliestNextDeparture;
    int w = e-d; // Waiting time
    
    std::cout << "Time is now " << d << "." << std::endl
              << "Next bus (" << id << ") leaves at " << e << "." << std::endl
              << "You have to wait for " << w << " minutes." << std::endl
              << "Answer: " << id << " * " << w << " = " << id * w << std::endl;
    
    return 0;
}
