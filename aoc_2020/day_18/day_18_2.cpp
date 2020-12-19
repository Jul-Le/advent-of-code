/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            18.12.2020
 *  Modified:           19.12.2020
 *
 *  
 *
 *  In part 2, addition is evaluated before multiplication.
 *
 *  What is the sum of the values, after all lines of input
 *  are evaluated?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Expression
{
public:
    Expression(const std::string &str)
        : m_str(str)
    {
        //std::cout << "Expression(" << str << ")" << std::endl;
    }
    
    void addValue(const long long &value)
    {
        m_values.push_back(value);
    }
    
    void addValue(const char &chValue)
    {
        long long value = chValue - '0';
        addValue(value);
    }

    void addOperator(const char &op)
    {
        m_ops.push_back(op);
    }
    
    long long evaluate()
    {
        for (int i = 0; i < m_str.length(); i++)
        {
            char c = m_str.at(i);
            switch (c)
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    this->addValue(c);
                    break;
                case '+':
                case '*':
                    this->addOperator(c);
                    break;
                case '(':
                {
                    // Search until number of opening and closing parenthesis match
                    int j = i+1;
                    
                    int countOpen = 1;
                    int countClose = 0;
                    
                    while (countOpen > countClose)
                    {
                        if (m_str.at(j) == '(')
                            countOpen++;
                        else if (m_str.at(j) == ')')
                            countClose++;
                        j++;
                    }
                    int end = j-1;
                    
                    std::string s = m_str.substr(i+1, end-1-i);
                    
                    Expression parenthesis(s);
                    this->addValue(parenthesis.evaluate());
                    
                    i = end;
                    break;
                }
                case ')':
                    // This is never reached
                    break;
                default:
                    break;
            }
        }
        
        return this->calculate();
    }
    
    long long calculate()
    {
        // Evaluate addition
        while (!additionsDone())
        {
            for (int i = 1; i < m_values.size(); i++)
            {
                char op = m_ops[i-1];
                
                if (op == '+')
                {
                    //std::cout << m_values[i-1] << " + " << m_values[i] << std::endl;
                    
                    m_values[i] = m_values[i-1] + m_values[i];
                    m_values.erase(m_values.begin() + i-1);
                    m_ops.erase(m_ops.begin() + i-1);
                }
            }
        }
        
        // Evaluate multiplication
        for (int i = 1; i < m_values.size(); i++)
        {
            char op = m_ops[i-1];
            
            if (op == '*' )
            {
                //std::cout << m_values[i-1] << " * " << m_values[i] << std::endl;
                m_values[i] = m_values[i-1] * m_values[i];
            }
            else
                std::cout << "Something went kaflooey: op = " << op << std::endl;
        }
        return m_values.at(m_values.size() - 1);
    }
    
    bool additionsDone() const
    {
        return (std::find(m_ops.begin(), m_ops.end(), '+') == m_ops.end());
    }
    
private:
    std::string m_str; // The expression as string
    std::vector<long long> m_values; // Values in expression
    std::vector<char> m_ops; // Operators in expression
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
    
    long long total = 0;
    
    while(getline(file, line))
    {
        Expression expression(line);
        
        total += expression.evaluate();
    }
    
    file.close();
    
    std::cout << total << std::endl;
    
    return 0;
}
