/*
 *  Contributor(s):     Julius L.
 *
 *  Created:            2021-11-20
 *  Modified:           2021-11-20
 *
 *
 *
 *  Input is a schedule of guard shift starts, fall asleep and
 *  wake up times.
 *  
 *  Find guard that is the most frequently asleep on the same
 *  minute.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>

enum Action
{
    Begin_Shift,
    Fall_Asleep,
    Wake_Up
};

class Record
{
public:
    Record();
    
    Record(std::string s)
    {
        char action[32];
        sscanf(s.c_str(), "[%d-%d-%d %d:%d] %s #%d", &m_year, &m_month, &m_day, &m_hour, &m_minute, &action, &m_guardID);
        
        if (strcmp(action, "Guard") == 0)
            m_action = Begin_Shift;
        else if (strcmp(action, "falls") == 0)
            m_action = Fall_Asleep;
        else if (strcmp(action, "wakes") == 0)
            m_action = Wake_Up;
        else
            std::cout << __LINE__ << ": Something went kaflooey" << std::endl;
    }
    
    
    // Combine all time data to single value
    long long datetime() const
    {
        long long ret = 0;
        ret += (long long)m_minute;
        ret += (long long)m_hour   * 100;
        ret += (long long)m_day    * 10000;
        ret += (long long)m_month  * 1000000;
        ret += (long long)m_year   * 100000000;
        
        return ret;
    }
    
    void print() const
    {
        std::cout << "[" << m_year << "-" << m_month << "-" << m_day << " " << m_hour << ":" << m_minute << "] ";
        
        if (m_action == Begin_Shift)
            std::cout << "Guard " << m_guardID << " begins shift";
        else if (m_action == Fall_Asleep)
            std::cout << "falls asleep";
        else if (m_action == Wake_Up)
            std::cout << "wakes up";
        else
            std::cout << "Something went wrong";
        
        std::cout << std::endl;
    }
    
    bool operator<(const Record &r) const
    {
        return this->datetime() < r.datetime();
    }
    
    int minute() const { return m_minute; }
    Action action() const { return m_action; }
    int guardID() const { return m_guardID; }
    
private:
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_minute;
    
    Action m_action;
    int m_guardID;
};

class Guard
{
public:
    Guard()
    {
        m_minutesAsleep = 0;
        
        for (int i = 0; i < 60; i++)
            m_timesAsleepEachMinute.push_back(0);
    }
    
    void addSleepMinutes(int startTime, int endTime)
    {
        for (int i = startTime; i < endTime; i++)
        {
            m_minutesAsleep++;
            m_timesAsleepEachMinute.at(i)++;
        }
    }
    
    // Get the minute guard was sleeping the most often
    // first: the minute
    // second: total time spent asleep on that minute
    std::pair<int, int> mostAsleepAt()
    {
        int mostAsleepAtMinute = 0;
        int mostAsleepTotalTime = 0;;
        
        for (int i = 0; i < 60; i++)
        {
            int mins = m_timesAsleepEachMinute.at(i);
            
            if (mins > mostAsleepTotalTime)
            {
                mostAsleepTotalTime = mins;
                mostAsleepAtMinute = i;
            }
        }
        
        return { mostAsleepAtMinute, mostAsleepTotalTime };
    }
        
    int minutesAsleep() const { return m_minutesAsleep; }
    
private:
    int m_minutesAsleep;
    std::vector<int> m_timesAsleepEachMinute;
};

// Compare two records, return true if a happened before b
bool comparePtr(Record *a, Record *b)
{
    return *a < *b;
}

int main()
{
    std::string line;
    std::ifstream file;
    
    std::vector<Record*> records;
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    while (getline(file, line))
    {
        records.push_back(new Record(line));
    }
    
    file.close();
    
    // Sort records by time
    std::sort(records.begin(), records.end(), comparePtr);
    
    // Keep track of existing guard IDs
    std::set<int> guardIDs;
    // Map containing guard ID as a key and sleep data as value
    std::map<int, Guard*> guards;
    
    Guard *currentGuard;
    int fallAsleepTime, wakeUpTime;
    
    // Loop through records
    // If new Guard ID is found, create Guard
    // If existing Guard ID, change to that Guard
    // Guards will begin shift between 23:00 - 00:59
    // Fall asleep will happen between 00:00 - 00:58
    // Wake up will happen between     00:01 - 00:59
    // Guards will always wake up before 01:00
    
    for (auto record : records)
    {
        if (record->action() == Begin_Shift)
        {
            // Is this the first record for this guard?
            bool newGuard = guardIDs.insert(record->guardID()).second;
            
            if (newGuard)
            {
                guards.insert({ record->guardID(), new Guard() });
            }
            currentGuard = guards[record->guardID()];
        }
        else if (record->action() == Fall_Asleep)
        {
            fallAsleepTime = record->minute();
        }
        else if (record->action() == Wake_Up)
        {
            wakeUpTime = record->minute();
            currentGuard->addSleepMinutes(fallAsleepTime, wakeUpTime);
        }
        else
        {
            std::cout << "[" << __LINE__ << "]: something went kaflooey";
        }
    }
    
    int idOfGuardThatWasMostFrequentlyAsleepOnTheSameMinute = -1;
    int mostMinutesAsleepAtSingleMinute = 0;
    
    for (auto id : guardIDs)
    {
        if (guards[id]->mostAsleepAt().second > mostMinutesAsleepAtSingleMinute)
        {
            mostMinutesAsleepAtSingleMinute = guards[id]->mostAsleepAt().second;
            idOfGuardThatWasMostFrequentlyAsleepOnTheSameMinute = id;
        }
    }
    
    int mostAsleepAtMinute = guards[idOfGuardThatWasMostFrequentlyAsleepOnTheSameMinute]->mostAsleepAt().first;
    int answer = idOfGuardThatWasMostFrequentlyAsleepOnTheSameMinute * mostAsleepAtMinute;
    
    std::cout << "Guard #" << idOfGuardThatWasMostFrequentlyAsleepOnTheSameMinute
              << " was most frequently asleep at minute " << mostAsleepAtMinute
              << ". The answer is " << answer << std::endl;
    
    for (auto r : records)
        delete r;
    
    for (auto i : guardIDs)
        delete guards[i];
    
    return 0;
}
