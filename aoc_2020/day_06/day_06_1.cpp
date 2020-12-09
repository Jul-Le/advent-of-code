/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            9.12.2020
 *  Modified:           9.12.2020
 *
 *  
 *
 *  Input is list of answers to guestions.
 *  Every group is separated by a blank line.
 *  Every person in a group is separated by a newline.
 *  Every line contains list of questions to which a person
 *  answered "yes".
 *
 *  For each group, count the number of questions to which
 *  anyone answered "yes". What is the sum of those counts?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Person
{
public:
    Person(std::string answer)
    {
        for (auto ch : answer)
            m_yes.push_back(ch);
    }
    
    int getDistinctYes(std::vector<char> &questions)
    {
        int sum = 0;
        
        for (auto i : m_yes)
        {
            // Check if question is already answered by someone else in the group
            auto it = std::find(questions.begin(), questions.end(), i);
            
            // If not, add to distinct answers
            if (it == questions.end())
            {
                questions.push_back(i);
                sum++;
            }
        }
        return sum;
    }
    
private:
    // String containing list of answers to which person
    // answered "yes"
    std::vector<char> m_yes;
};


class Group
{
public:
    Group()
    {
        
    }
    
    void addPerson(Person p)
    {
        m_people.push_back(p);
    }
    
    // Get number of distinct "yes" answers from group
    int getDistinctYes()
    {
        int sum = 0;
        std::vector<char> questions;
        
        // For each person in group
        for (auto p : m_people)
        {
            sum += p.getDistinctYes(questions);
        }
        return sum;
    }
    
private:
    std::vector<Person> m_people;
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
    
    // All groups
    std::vector<Group> groups;
    
    // Group object, will be reinitilized after every group
    Group group = Group();
    
    // Read data from file
    while (getline(file, line))
    {
        if (line.length() > 0)
        {
            // Create Person object and add to group
            Person p(line);
            group.addPerson(p);
        }
        else
        {
            // End of group
            groups.push_back(group);
            // Reinitilize
            group = Group();
        }
    }
    
    file.close();
    
    // After EOF there is no blank line, so do last addition outside loop
    groups.push_back(group);
    
    
    int sum = 0;
    
    for (auto g : groups)
    {
        sum += g.getDistinctYes();
    }
    
    std::cout << sum << std::endl;
    
    return 0;
}
