/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            8.12.2020
 *  Modified:           8.12.2020
 *
 *  
 *
 *  What is the value of the accumulator when an program
 *  terminates? To terminate the program, either exactly one
 *  nop needs to be changed to jmp or jmp changed to nop.
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

    Program(int start)
        : m_start(start)
    {
        m_acc = 0;
        hasLooped = false;
    }
    
    Program(int start, std::vector<Instruction> i)
        : m_start(start), m_instructions(i)
    {
        m_acc = 0;
        hasLooped = false;
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
        
        if (!hasLooped)
        {
            // Check if instruction at current index has been executed before
            if (alreadyExecuted(index))
            {
                hasLooped = true;
                if (m_start == 0) // First program loop
                {
                    m_acc = 0;
                    return execute(0);
                }
                else // Subprograms will halt if they enter a loop
                    return 1;
            }
        }
        
        // Add current instruction index to list of executed indexes
        m_history.push_back(index);
        
        // Instruction handlers
        
        // nop - just move to next instruction
        if (m_instructions.at(index).name() == "nop")
        {
            if (hasLooped) // Try swapping instructions
            {
                int temp;
                temp = jmp(index);
                
                // If program terminates
                if (temp >= m_instructions.size())
                {
                    return 0;
                }
                // If swap would lead to executing new instruction
                else if (!alreadyExecuted(temp))
                {
                    // Create new program, start executing from new instruction
                    Program subProgram = Program(temp, m_instructions);
                    // If subprogram terminates
                    if (subProgram.execute(temp) == 0)
                    {
                        m_acc += subProgram.acc();
                        return 0;
                    }
                }
            }
            // Execute instruction normally
            nextIndex = nop(index);
        }
        // acc - Add the value at current instruction to acc,
        //       then move to the next instruction
        else if (m_instructions.at(index).name() == "acc")
        {
            nextIndex = acc(index);
        }
        // jmp - move to specified instruction
        else if (m_instructions.at(index).name() == "jmp")
        {
            if (hasLooped) // Try swapping instructions
            {
                int temp;
                temp = nop(index);
                
                // If program terminates
                if (temp >= m_instructions.size())
                {
                    return 0;
                }
                // If swap would lead to executing new instruction
                else if (!alreadyExecuted(temp))
                {
                    // Create new program, start executing from new instruction
                    Program subProgram = Program(temp, m_instructions);
                    // If subprogram terminates
                    if (subProgram.execute(temp) == 0)
                    {
                        m_acc += subProgram.acc();
                        return 0;
                    }
                }
            }
            nextIndex = jmp(index);
        }
        else
        {
            // This should never happen
            this->print();
            return 1;
        }
        
        if (nextIndex >= m_instructions.size())
        {
            // Program has terminated
            printPid();
            std::cout << "Terminated" << std::endl;
            return 0;
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

    bool alreadyExecuted(int index)
    {
        // Check if program entered a loop
        auto it = std::find(m_history.begin(), m_history.end(), index);
        
        return (it != m_history.end());
    }
    
    int nop(int i)
    {
        int next = i + 1;
        printPid();
        std::cout << "nop - moving to index " << next << std::endl;
        return next;
    }
    
    int acc(int i)
    {
        int val = m_instructions.at(i).value();
            
        m_acc += val;
        int next = i + 1;
        printPid();
        std::cout << "acc - added " << val << " to acc, total is now " << m_acc
                  << ", moving to index " << next << std::endl;
        return next;
    }
    
    int jmp(int i)
    {
        int next = i + m_instructions.at(i).value();
        printPid();
        std::cout << "jmp - moving to index " << next << std::endl;
        return next;
    }
    
    void printPid()
    {
        std::cout << "[" << m_start << "] ";
    }
    
    // Index of instruction where program will start
    int m_start;
    std::vector<Instruction> m_instructions;
    int m_acc;
    std::list<int> m_history;
    bool hasLooped;
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
    
    Program program(0);
    
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
    
    /*
     *  After executing the program, go through the instructions
     *  and try to find one nop or jmp instruction, that when
     *  changed (jmp->nop or nop->jmp) would make the program
     *  to either execute an instruction that has not been
     *  executed before, or to try to execute instruction after
     *  the last one on the list.
    */
    
    return 0;
}
