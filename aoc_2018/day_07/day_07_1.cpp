/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-21
 *  Modified:           2021-11-22
 *
 *
 *
 *  In what order should the instructions be executed?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

class Step
{
public:
    Step(char ch) : m_letter(ch)
    {
        
    }
    
    void addDependency(Step *step)
    {
        m_depends.push_back(step);
    }
    
    void removeDependency(Step *step)
    {
        for (int i = 0; i < m_depends.size(); i++)
        {
            if (m_depends.at(i) == step)
            {
                m_depends.erase(m_depends.begin() + i);
                break;
            }
        }
    }
    
    bool hasDependencies() const
    {
        return !m_depends.empty();
    }
    
    char letter() const { return m_letter; }
    
private:
    char m_letter;
    std::vector<Step*> m_depends;
};

int main()
{
    std::ifstream file;
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    std::string line;
    std::set<char> letters;
    std::map<char, Step*> instructions;
    
    while (getline(file, line))
    {
        char letter, depends;
        sscanf(line.c_str(), "Step %c must be finished before step %c can begin.", &depends, &letter);
        
        bool isNewLetter = letters.insert(letter).second;
        bool isNewDependency = letters.insert(depends).second;
        
        if (isNewLetter)
        {
            Step *second = new Step(letter);
            instructions.insert({ letter, second });
            
            if (isNewDependency)
            {
                Step *first = new Step(depends);
                instructions.insert({ depends, first });
                second->addDependency(first);
            }
            else
            {
                second->addDependency(instructions[depends]);
            }
        }
        else
        {
            if (isNewDependency)
            {
                Step *first = new Step(depends);
                instructions.insert({ depends, first });
                instructions[letter]->addDependency(first);
            }
            else
            {
                instructions[letter]->addDependency(instructions[depends]);
            }
        }
    }
    
    file.close();
    
    // Find steps that have no dependencies
    // Execute one with smallest letter
    // Update all dependencies
    // Repeat...
    
    std::string correctOrder = "";
    Step *next;
    
    while (letters.size() > 0)
    {
        next = nullptr;
        
        for (auto ch : letters)
        {
            Step *temp = instructions[ch];
            
            // If step has dependencies, it can't be executed
            if (temp->hasDependencies())
                continue;
            
            std::cout << "Step " << ch << " has no dependencies" << std::endl;
            
            // On first loop iteration next will be null
            if (!next)
            {
                next = temp;
                continue;
            }
            
            // If there is already a step without dependencies,
            // find out which one has smaller letter
            if (temp->letter() < next->letter())
                next = temp;
        }
        
        // Add step to final result
        correctOrder += next->letter();
        
        // Update dependencies
        for (auto ch : letters)
            instructions[ch]->removeDependency(next);
        
        char ch = next->letter();
        
        std::cout << "Step " << ch << " will be executed." << std::endl << std::endl;
        
        // Cleanup
        delete next;
        
        auto it = letters.find(ch);
        letters.erase(it);
        
        auto itr = instructions.find(ch);
        instructions.erase(itr);
    }
    
    std::cout << "The correct order is: " << correctOrder << std::endl;
    
    return 0;
}
