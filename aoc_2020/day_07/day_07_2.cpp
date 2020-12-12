/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            12.12.2020
 *  Modified:           12.12.2020
 *
 *  
 *
 *  How many bags does a single shiny gold bag contain?
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

class Bag
{
public:
    Bag() {}
    Bag(std::string a, std::string c)
        : m_adjective(a), m_color(c)
    {
        //std::cout << "Bag(" << m_adjective << ", " << m_color << ")" << std::endl;
    }
    
    bool operator==(const Bag& b)
    {
        return (this->m_adjective == b.m_adjective) && (this->m_color == b.m_color);
    }
    
    void addContents(int count, Bag *b)
    {
        std::pair<int, Bag*> contents (count, b);
        
        m_contents.push_back(contents);
    }
    
    // For debugging
    void printContents()
    {
        std::cout << m_adjective << " " << m_color << " bags contain ";
        bool addComma = false;
        
        if (!m_contents.empty())
        {
            for (auto pair : m_contents)
            {
                if (addComma)
                    std::cout << ", ";
                else
                    addComma = true;
                
                int count = pair.first;
                std::string adj = pair.second->adjective();
                std::string col = pair.second->color();
                
                std::cout << count << " " << adj << " " << col << " bag";
                if (count > 1)
                    std::cout << "s";
            }
            std::cout << "." << std::endl;
        }
        else // No contents
        {
            std::cout << "no other bags." << std::endl;
        }
    }
    
    /**
     *  @brief Check whether a bag contains another bag
     *  @param adjective What kind of bag we're looking for
     *  @param color What colored bag we're looking for
     *  @return true if bag is found
     */
    bool containsBag(std::string adjective = "shiny", std::string color = "gold")
    {
        for (auto pair : m_contents)
        {
            std::string adj = pair.second->adjective();
            std::string col = pair.second->color();
            
            // Return true if this bag contains the wanted bag,
            // or any bag within this bag contains the wanted bag
            if ((adj == adjective && col == color) || pair.second->containsBag())
            {
                return true;
            }
        }
        
        return false;
    }
    
    int getNumOfContainedBags()
    {
        int count = 0;
        
        for (auto pair : m_contents)
        {
            count += pair.first;
            count += pair.first * pair.second->getNumOfContainedBags();
        }
        
        return count;
    }
    
    std::string description()
    {
        return m_adjective + " " + m_color;
    }
    
    // Getters
    std::string adjective() { return m_adjective; }
    std::string color() { return m_color; }
    std::vector<std::pair<int, Bag*>> contents() { return m_contents; }
    
private:
    std::string m_adjective;
    std::string m_color;
    
    // Contents of bag, number of contained bags and
    // pointer to bag
    std::vector<std::pair<int, Bag*>> m_contents;
};

namespace FirstBag
{
    enum FirstBag
    {
        Adjective = 0,
        Color
    };
};

namespace OtherBag
{
    enum OtherBag
    {
        Count = 0,
        Adjective,
        Color
    };
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
    
    // Container for bags
    std::vector<Bag> bags;
    // Vector of pairs of bags
    // First of pair is parent, second is child
    std::vector<std::pair<Bag, Bag>> relations;
    // How many child bags are within each parent bag
    std::vector<int> counts;
    
    Bag firstBag;
    
    // Index of word within input line
    int wordIndex = 0;
        
    // Read data from file
    while (getline(file, line))
    {        
        // Separate by space
        boost::char_separator<char> sep(" ");
        tokenizer tokens(line, sep);
        
        std::string adjective;
        std::string color;
        int count;
        
        // Loop handing each word within line
        BOOST_FOREACH(std::string const& token, tokens)
        {
            // First bag consists of 4 tokens
            // (adjective, color, "bags" word, "contain" word )
            if (wordIndex < 4)
            {
                switch (wordIndex)
                {
                    case FirstBag::Adjective:
                    {
                        adjective = token;
                        break;
                    }
                    case FirstBag::Color:
                    {
                        color = token;
                        // First bag adjective and token are parsed,
                        // create first bag object
                        firstBag = Bag(adjective, color);
                        break;
                    }
                    default: // "bags" and "contain" words that don't do anything
                    {
                        wordIndex++;
                        continue;
                    }
                }
            }
            // Subsequent bags, each bag consists of 4 tokens
            // (count, adjective, color, "bag(s)" word)
            else
            {
                switch (wordIndex % 4)
                {
                    case OtherBag::Count:
                    {
                        if (token == "no") // Bag has no contents
                        {
                            goto nextBag;
                        }
                        else
                        {
                            sscanf(token.c_str(), "%d", &count);
                        }
                        break;
                    }
                    case OtherBag::Adjective:
                    {
                        adjective = token;
                        break;
                    }
                    case OtherBag::Color:
                    {
                        color = token;
                        // Other bag count, adjective and color are parsed,
                        // create bag object
                        Bag otherBag = Bag(adjective, color);
                        // Store the information about relationships between bags
                        relations.push_back(std::pair<Bag, Bag>(firstBag, otherBag));
                        counts.push_back(count);
                        break;
                    }
                    default: // "bag(s)" word
                    {
                        wordIndex++;
                        continue;
                    }
                }
            }
            
            wordIndex++;
            continue;
            
            // If bag contains no other bags, jump here
            // to stop processing last two tokens
        nextBag:
            break;
        }
        // Process next line of input
        bags.push_back(firstBag);
        wordIndex = 0;
    }
    
    file.close();
    
    int countOfBagsWithinSingleShinyGoldBag = 0;
    
    for (int i = 0; i < relations.size(); i++)
    {
        // Add contents to each bag within bags vector.
        // In relations vector, the bag matching the description
        // of second in the pair should be found from the bag
        // matching the description of first in the pair.
        
        for (int parentIndex = 0; parentIndex < bags.size(); parentIndex++)
        {
            if (relations.at(i).first == bags.at(parentIndex))
            {
                for (int childIndex = 0; childIndex < bags.size(); childIndex++)
                {
                    if (relations.at(i).second == bags.at(childIndex))
                    {
                        bags.at(parentIndex).addContents(counts.at(i), &bags.at(childIndex));
                    }
                }
            }
        }
    }
    
    for (auto bag : bags)
    {
        if (bag.description() == "shiny gold")
        {
            countOfBagsWithinSingleShinyGoldBag = bag.getNumOfContainedBags();
            break;
        }
    }
    
    std::cout << "Single shiny gold bag contains " << countOfBagsWithinSingleShinyGoldBag
              << " bags." << std::endl;

    return 0;
}
