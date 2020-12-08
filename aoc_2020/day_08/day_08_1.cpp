/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            8.12.2020
 *  Modified:           8.12.2020
 *
 *  
 *
 *  Input is some assembly instructions.
 *
 *  What is the value of the accumulator when an instruction
 *  is repeated for the first time? (Before repeating the
 *  instruction)
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

class Instruction
{
public:
    Instruction(std::string name, int value)
        : m_name(name), m_value(value) { }

    std::string name() { return m_name; }
    int value() { return m_value; };

private:
    std::string m_name;
    int m_value;
};

class Program
{
public:

    Program()
    {
        m_acc = 0;
    }
    
    /**
     *  @brief Execute program recursively until it enters a loop
     *  @param index The index of executed instruction in the instruction vector
     *  @return 0 when success, nonzero means either a bug or invalid instruction
     */
    int execute(int index)
    {
        // Next instruction to be executed
        int nextIndex;
        
        // Check if program entered a loop
        auto it = std::find(m_history.begin(), m_history.end(), index);
        
        if (it != m_history.end())
            return 0;
        
        // Add current instruction index to list of executed indexes
        m_history.push_back(index);
        
        // Instruction handlers
        
        // nop - just move to next instruction
        if (m_instructions.at(index).name() == "nop")
        {
            nextIndex = index + 1;
            std::cout << "nop - moving to index " << nextIndex << std::endl;
        }
        // acc - Add the value at current instruction to acc,
        //       then move to the next instruction
        else if (m_instructions.at(index).name() == "acc")
        {
            int val = m_instructions.at(index).value();
            
            m_acc += val;
            nextIndex = index + 1;
            std::cout << "acc - added " << val << " to acc, total is now " << m_acc
                      << ", moving to index " << nextIndex << std::endl;
        }
        // jmp - move to specified instruction
        else if (m_instructions.at(index).name() == "jmp")
        {
            nextIndex = index + m_instructions.at(index).value();
            std::cout << "jmp - moving to index " << nextIndex << std::endl;
        }
        else
        {
            // This should never happen
            this->print();
            return 1;
        }
        
        return execute(nextIndex);
    }
    
    void addInstruction(Instruction i)
    {
        m_instructions.push_back(i);
    }
    
    void print()
    {
        for (auto i : m_instructions)
            std::cout << i.name() << " " << i.value() << std::endl;
    }
    
    int acc() { return m_acc; }
    
private:

    std::vector<Instruction> m_instructions;
    int m_acc;
    std::list<int> m_history;
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
    
    Program program;
    
    // Read data from file
    while (getline(file, line))
    {        
        char inst[32];
        char sign;
        int val;
        
        // Parse line
        sscanf(line.c_str(), "%s %c%d", inst, &sign, &val);
        
        val = sign == '-' ? -val : val;
        Instruction op(inst, val);
        
        // Append instruction to program instruction list
        program.addInstruction(op);
    }
    
    file.close();
    
    if (program.execute(0) != 0)
    {
        std::cout << "execute() returned nonzero" << std::endl;
        return 0;
    }
    else
    {
        std::cout << program.acc() << std::endl;
    }
    
    return 0;
}
