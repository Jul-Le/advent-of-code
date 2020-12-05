/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            5.12.2020
 *  Modified:           5.12.2020
 *
 *  
 *
 *  Input is passport data. There are 9 different fields, and
 *  fields for one passport are separated by spaces or newlines.
 *  Different passports are separated by blank lines.
 *
 *  The fields are:
 *
 *  byr (Birth Year)
 *  iyr (Issue Year)
 *  eyr (Expiration Year)
 *  hgt (Height)
 *  hcl (Hair Color)
 *  ecl (Eye Color)
 *  pid (Passport ID)
 *  cid (Country ID)
 *
 *  Example entry:
 *
 *  ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
 *  byr:1937 iyr:2017 cid:147 hgt:183cm
 *
 *  Some of the passport fields are required, some not.
 *  In this case, "cid" is not required.
 *
 *  Question is, how many passports are valid?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

struct Field
{
    std::string name;
    bool isRequired;
};

class Passport
{
public:
    Passport()
    {
        m_birthYear = 0;
        m_issueYear = 0;
        m_expYear = 0;
        m_height = "";
        m_hairColor = "";
        m_eyeColor = "";
        m_passID = "";
        m_countryID = "";
    }
    
    Passport(const Passport& p)
    {
        m_birthYear = p.m_birthYear;
        m_issueYear = p.m_issueYear;
        m_expYear = p.m_expYear;
        m_height = p.m_height;
        m_hairColor = p.m_hairColor;
        m_eyeColor = p.m_eyeColor;
        m_passID = p.m_passID;
        m_countryID = p.m_countryID;
    }
    
    // Setter functions
    void setBirthYear(int year)        { m_birthYear = year; }
    void setIssueYear(int year)        { m_issueYear = year; }
    void setExpYear  (int year)        { m_expYear   = year; }
    void setHeight   (std::string str) { m_height    = str; }
    void setHairColor(std::string str) { m_hairColor = str; }
    void setEyeColor (std::string str) { m_eyeColor  = str; }
    void setPassID   (std::string str) { m_passID    = str; }
    void setCountryID(std::string str) { m_countryID = str; }

    // Debugging
    void print()
    {
        std::cout << "Birth Year: " << m_birthYear << std::endl
                  << "Issue Year: " << m_issueYear << std::endl
                  << "Expiration Year: " << m_expYear << std::endl
                  << "Height: " << m_height << std::endl
                  << "Hair Color: " << m_hairColor << std::endl
                  << "Eye Color: " << m_eyeColor << std::endl
                  << "Passport ID: " << m_passID << std::endl
                  << "Country ID: " << m_countryID << std::endl;
        
        if (isValid())
            std::cout << "Passport is valid." << std::endl;
        else
            std::cout << "Passport is invalid." << std::endl;
    }

    bool isValid()
    {
        if (m_birthYear == 0)
            return false;
        if (m_issueYear == 0)
            return false;
        if (m_expYear == 0)
            return false;
        if (m_height == "")
            return false;
        if (m_hairColor == "")
            return false;
        if (m_eyeColor == "")
            return false;
        if (m_passID == "")
            return false;
        if (m_countryID == "")
            ;
        
        return true;
    }

private:
    int m_birthYear;
    int m_issueYear;
    int m_expYear;
    std::string m_height;
    std::string m_hairColor;
    std::string m_eyeColor;
    std::string m_passID;
    std::string m_countryID;
};

int main()
{
    std::string line;
    std::ifstream file;
    std::list<Passport> passportList;
    
    file.open("input.txt");
    
    if (!file.is_open())
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    Passport *pass = new Passport;
    
    // Read data from file
    while (getline(file, line))
    {
        if (line.length() > 0)
        {            
            // Separate by space
            boost::char_separator<char> sep(" ");
            tokenizer tokens(line, sep);
            
            BOOST_FOREACH(std::string const& token, tokens)
            {
                // Get field key
                std::string key = token.substr(0, 3);
                
                if (key == "byr" || key == "iyr" || key == "eyr")
                {
                    int year;
                    
                    // Parse year
                    sscanf(token.c_str(), "%*c%*c%*c%*c%d", &year);
                    
                    if (key == "byr")
                        pass->setBirthYear(year);
                    else if (key == "iyr")
                        pass->setIssueYear(year);
                    else if (key == "eyr")
                        pass->setExpYear(year);
                }
                else
                {
                    // Parse value
                    std::string value = token.substr(4, token.length());
                    
                    if (key == "hgt")
                        pass->setHeight(value);
                    else if (key == "hcl")
                        pass->setHairColor(value);
                    else if (key == "ecl")
                        pass->setEyeColor(value);
                    else if (key == "pid")
                        pass->setPassID(value);
                    else if (key == "cid")
                        pass->setCountryID(value);
                }
            }
        }
        else
        {
            Passport p = *pass; // Create copy
            passportList.push_back(p); // Add to list
            delete pass; // Delete old
            pass = new Passport; // Create empty pass
        }
    }
    
    Passport last = *pass; // Create copy
    passportList.push_back(last); // Add to list
    delete pass; // Delete old
    
    file.close();
        
    int validCount = 0;
    
    for (auto p : passportList)
    {
        if (p.isValid())
            validCount++;
    }
    
    std::cout << validCount << std::endl;
    
    return 0;
}
