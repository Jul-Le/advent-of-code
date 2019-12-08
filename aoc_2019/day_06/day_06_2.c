/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            7.12.2019
 *  Modified:           7.12.2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG(format, ...)  //printf("%d:%s(): " format, __LINE__, __func__, ##__VA_ARGS__);

struct Body
{
    uint32_t    id;
    uint16_t    parentCount;    // Includes grandparents
    uint16_t    childCount;     // Does not include grandchildren
    struct Body *next;
    struct Body **children;     // List of pointers to child bodies
};

typedef struct Body Body;

typedef struct
{
    Body *first;
    Body *last;
} BodyList;

// Generate unique 32-bit id from 1-4 character string
uint32_t strToId(char*);
// Create BodyList instance and initialize it
BodyList *createBodyList();
// Check if body id exists, if does, return pointer to it
Body *bodyList_idExists(BodyList*, uint32_t);
// Add Body to BodyList
void bodyList_push_back(BodyList*, Body*);
// Clean up
void bodyList_free(BodyList*);
// Update parent count for all children and their children recursively
void updateParentCountForChildren(Body*, uint16_t);
// Get total number of direct and indirect orbits
uint32_t getTotalOrbits(BodyList*);
// Get number of orbital transfer required to go from body to another
uint16_t getTransfers(BodyList*, Body*, Body*);
// Check if body is a child of another body
bool isChildOf(Body*, Body*);

int main()
{
    // https://adventofcode.com/2019/day/6/input
    // !TRAILING NEWLINE MUST BE DELETED FROM INPUT FILE!
    FILE *fp = fopen("input.txt", "r");
    
    if (!fp)
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    
    BodyList *bodies = createBodyList();
    Body *yourParent, *santasParent;
    
    while (!feof(fp))
    {
        const char s[2] = ")";
        char *token;
        char buf[32];
        uint32_t id;
        Body *parent, *child;
        
        fgets(buf, 32, fp);
        
        // Parent body id
        token = strtok(buf, s);
        id = strToId(token);
        parent = bodyList_idExists(bodies, id);
        
        // If parent id doesn't exist, create new instance
        if (!parent)
        {
            parent = (Body*)malloc(sizeof(Body));
            if (!parent)
            {
                perror("malloc()");
                bodyList_free(bodies);
                exit(EXIT_FAILURE);
            }
            parent->id = id;
            parent->parentCount = 0;
            parent->childCount = 0;
            parent->next = NULL;
            parent->children = NULL;
            
            bodyList_push_back(bodies, parent);
        }
        
        // Child body id
        token = strtok(NULL, s);
        strtok(token, "\n");
        if (!token)
        {
            printf("strtok() returned NULL. Try removing newline from end of input file\n");
            bodyList_free(bodies);
            exit(EXIT_FAILURE);
        }
        id = strToId(token);
        
        child = bodyList_idExists(bodies, id);
        
        // If child id doesn't exist, create new instance
        if (!child)
        {
            child = (Body*)malloc(sizeof(Body));
            if (!child)
            {
                perror("malloc()");
                bodyList_free(bodies);
                exit(EXIT_FAILURE);
            }
            child->id = id;
            child->parentCount = 0;
            child->childCount = 0;
            child->next = NULL;
            child->children = NULL;
            
            bodyList_push_back(bodies, child);
        }
        
        parent->childCount++;
        parent->children = (Body**)realloc(parent->children, sizeof(Body*) * parent->childCount);
        if (!parent->children)
        {
            perror("realloc()");
            bodyList_free(bodies);
            exit(EXIT_FAILURE);
        }
        parent->children[parent->childCount - 1] = child;
        
        updateParentCountForChildren(child, parent->parentCount);
        
        if (child->id == strToId("YOU"))
            yourParent = parent;
        else if (child->id == strToId("SAN"))
            santasParent = parent;
        
        DEBUG("%u has %u parents and %u children\n", parent->id, parent->parentCount, parent->childCount);
        DEBUG("%u has %u parents and %u children\n\n", child->id, child->parentCount, child->childCount);
    }
    fclose(fp);
    
    printf("Transfers required: %u\n", getTransfers(bodies, yourParent, santasParent));
    
    bodyList_free(bodies);
    
    return 0;
}

uint32_t strToId(char *str)
{
    uint32_t id = 0;
    
    switch (strlen(str))
    {
        case 1:
            id |= str[0];
            break;
        case 2:
            id |= (str[0] << 8);
            id |= str[1];
            break;
        case 3:
            id |= (str[0] << 16);
            id |= (str[1] << 8);
            id |= str[2];
            break;
        case 4:
            id |= (str[0] << 24);
            id |= (str[1] << 16);
            id |= (str[2] << 8);
            id |= str[3];
            break;
    }
    return id;
}

BodyList *createBodyList()
{
    BodyList *list = (BodyList*)malloc(sizeof(BodyList));
    
    list->first = NULL;
    list->last = NULL;
    
    return list;
}

Body *bodyList_idExists(BodyList *list, uint32_t id)
{
    Body *body = list->first;
    
    while (body)
    {
        if (body->id == id)
        {
            DEBUG("%s %u %s\n", "id", id, "found");
            return body;
        }
        body = body->next;
    }
    DEBUG("%s %u %s\n", "id", id, "not found");
    return NULL;
}

void bodyList_push_back(BodyList *list, Body *body)
{
    // If list is empty
    if (!list->first)
    {
        list->first = body;
        list->last = list->first;
    }
    else
    {
        list->last->next = body;
        list->last = list->last->next;
    }
    DEBUG("%s %u %s\n", "id", body->id, "added");
}

void bodyList_free(BodyList *list)
{
    Body *temp = NULL;
    Body *temp2 = NULL;
    
    temp = list->first;
    
    while (temp->next)
    {
        temp2 = temp;
        temp = temp->next;
        free(temp2->children);
        free(temp2);
    }
    free(temp);
    free(list);
}

void updateParentCountForChildren(Body *body, uint16_t count)
{
    body->parentCount = count + 1;
    
    int i;
    for (i = 0; i < body->childCount; i++)
    {
        updateParentCountForChildren(body->children[i], body->parentCount);
    }
}

uint32_t getTotalOrbits(BodyList *list)
{
    uint32_t total = 0;
    
    Body *body;
    
    for (body = list->first; body; body = body->next)
    {
        total += body->parentCount;
    }
    
    return total;
}

uint16_t getTransfers(BodyList *list, Body *a, Body *b)
{
    Body *body;
    uint16_t leastTransfers = UINT16_MAX;
    
    for (body = list->first; body; body = body->next)
    {
        if (isChildOf(a, body) && isChildOf(b, body))
        {
            uint16_t transfers = (a->parentCount - body->parentCount) + (b->parentCount - body->parentCount);
            if (transfers < leastTransfers)
                leastTransfers = transfers;
        }
    }
    return leastTransfers;
}

bool isChildOf(Body *child, Body *parent)
{
    int i;
    
    for (i = 0; i < parent->childCount; i++)
    {
        if (parent->children[i] == child || isChildOf(child, parent->children[i]))
            return true;
    }
    return false;
}
