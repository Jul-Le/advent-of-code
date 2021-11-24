/*
 *  Contributor(s):     JulLe
 *
 *  Created:            2021-11-24
 *  Modified:           2021-11-24
 *
 *
 *
 *  Input describes number of nodes, their child nodes and
 *  number of metadata entries for each node.
 *
 *  What is the total sum of metadata entries?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

/**
 *  @brief Get metadata sum from node and all its children
 *  @param numbers Vector containing data for all nodes
 *  @param index Reference to current index in vector
 *  @details This function will be called recursively and the
 *           index will be incremented with each call
 */
int getMetadataSum(const std::vector<int> &numbers, int &index)
{
    int sum = 0;
    
    int childCount = numbers.at(index++);
    int metadataEntries = numbers.at(index++);
    
    for (int i = 0; i < childCount; i++)
    {
        sum += getMetadataSum(numbers, index);
    }
    
    for (int i = 0; i < metadataEntries; i++)
    {
        sum += numbers.at(index++);
    }
    return sum;
}

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
    getline(file, line);
    file.close();
    
    std::vector<int> data;
    
    char *token = strtok((char*)line.c_str(), " ");
    
    // Split string to integers
    while (token)
    {
        data.push_back(atoi(token));
        token = strtok(NULL, " ");
    }
    
    int i = 0;
    int answer = getMetadataSum(data, i);
    
    std::cout << "Total sum of metadata entries is " << answer << std::endl;
    
    return 0;
}
