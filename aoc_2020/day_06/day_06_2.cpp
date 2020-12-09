/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            9.12.2020
 *  Modified:           9.12.2020
 *
 *  
 *
 *  For each group, count the number of questions to which
 *  everyone answered "yes". What is the sum of those counts?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

class Person
{
public:
    Person(std::string answer)
    {
        for (auto ch : answer)
            m_yes.push_back(ch);
    }
    
    std::list<char> getYesAnswers()
    {
        return m_yes;
    }
    
private:
    std::list<char> m_yes;
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
    
    int getNumberOfQuestionsToWhichEveryoneAnsweredYes()
    {
        int sum = 0;
        // List of questions to which everyone answered yes
        std::list<char> questions;
        questions = m_people.at(0).getYesAnswers();
        
        // If group has only one person
        if (m_people.size() == 1)
            return questions.size();
        
        std::list<char> answersToBeRemoved;
        
        // For each person in group
        for (int i = 1; i < m_people.size(); i++)
        {
            /*
             *  Loop through the questions list. If a value in
             *  that list is not found in the list for the
             *  next person, remove that value from the
             *  questions list
             */
             
             for (auto q : questions)
             {
                 std::list<char> personAnswers = m_people.at(i).getYesAnswers();
                 
                 auto it = std::find(personAnswers.begin(), personAnswers.end(), q);
                 
                 // If not found
                 if (it == personAnswers.end())
                 {
                     answersToBeRemoved.push_back(q);
                 }
             }
         }
         
         for (auto i : answersToBeRemoved)
         {
             questions.remove(i);
         }
         
         return questions.size();
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
        sum += g.getNumberOfQuestionsToWhichEveryoneAnsweredYes();
    }
    
    std::cout << sum << std::endl;
    
    return 0;
}
