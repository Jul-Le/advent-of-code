/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-22
 *  Modified:           2021-11-23
 *
 *
 *
 *  Instructions have execution times, and up to 5 instructions
 *  may be worked on at once. How long does it take to complete
 *  all steps?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <queue>

enum Status
{
    Idle,
    On_Queue,
    Working,
    Completed
};

class Task
{
public:
    Task(char ch) : m_letter(ch)
    {
        m_workLeft = 60 + m_letter - 'A' + 1;
        m_status = Idle;
    }
    
    void addDependency(Task *task)
    {
        m_depends.push_back(task);
    }
            
    void setStatus(Status s)
    {
        m_status = s;
    }
    
    void doWork()
    {
        m_workLeft--;
    }
    
    bool isComplete() const
    {
        return m_workLeft == 0;
    }
    
    bool hasDependencies() const
    {
        bool depends = false;
        
        for (auto task : m_depends)
        {
            if (task->status() != Completed)
            {
                depends = true;
                break;
            }
        }
        return depends;
    }
    
    Status status() const { return m_status; }
    char letter() const { return m_letter; }
    int priority() const
    {
        // A == 26 ... Z == 0
        return -(m_letter - 'Z');
    }
    
    
private:
    char m_letter;
    std::vector<Task*> m_depends;
    int m_workLeft;
    Status m_status;
};

class TaskCompare
{
public:
    bool operator()(Task *a, Task *b)
    {
        return a->priority() < b->priority();
    }
};

class TaskManager
{
public:
    TaskManager(int w = 5)
        : m_workersAvailable(w)
    {
        
    }
    
    ~TaskManager()
    {
        for (auto task : m_tasks)
            delete task;
    }
    
    void addTask(Task *task)
    {
        m_tasks.push_back(task);
        std::cout << "TaskManager: New task " << task->letter() << std::endl;
    }
    
    int exec()
    {
        int timeSpent = 0;
        bool done = false;
        
        while (!done)
        {
            done = true;
            
            // Look for idle tasks with no dependencies, add them to queue
            for (auto task : m_tasks)
            {
                if (task->status() == Idle && !task->hasDependencies())
                {
                    m_queue.push(task);
                    task->setStatus(On_Queue);
                    std::cout << "Task " << task->letter() << " added to queue" << std::endl;
                }
            }
            
            // If there are free workers, start executing queued tasks
            while (m_workersAvailable && !m_queue.empty())
            {
                std::cout << "Task " << m_queue.top()->letter() << " started, available workers: " << m_workersAvailable-1 << std::endl;
                m_queue.top()->setStatus(Working);
                m_queue.pop();
                m_workersAvailable--;
            }
            
            // Work on started tasks
            for (auto task : m_tasks)
            {
                if (task->status() == Idle || task->status() == On_Queue)
                    done = false;
                
                if (task->status() == Working)
                {
                    task->doWork();
                    
                    if (task->isComplete())
                    {
                        task->setStatus(Completed);
                        m_workersAvailable++;
                        std::cout << "Task " << task->letter() << " completed, available workers: " << m_workersAvailable << std::endl;
                    }
                    else
                        done = false;
                }
            }
            timeSpent++;
        }
        return timeSpent;
    }
    
private:
    
    int m_workersAvailable;
    
    std::vector<Task*> m_tasks;
    std::priority_queue<Task*, std::vector<Task*>, TaskCompare> m_queue;
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
    std::map<char, Task*> instructions;
    
    while (getline(file, line))
    {
        char letter, depends;
        sscanf(line.c_str(), "Step %c must be finished before step %c can begin.", &depends, &letter);
        
        bool isNewLetter = letters.insert(letter).second;
        bool isNewDependency = letters.insert(depends).second;
        
        if (isNewLetter)
        {
            Task *second = new Task(letter);
            instructions.insert({ letter, second });
            
            if (isNewDependency)
            {
                Task *first = new Task(depends);
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
                Task *first = new Task(depends);
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
    
    TaskManager taskMgr;
    int timeSpent;
    
    for (auto ch : letters)
    {
        Task *t = instructions[ch];
        taskMgr.addTask(t);
    }
    
    timeSpent = taskMgr.exec();
    
    std::cout << "Total time spent: " << timeSpent << " seconds." << std::endl;
    
    return 0;
}
