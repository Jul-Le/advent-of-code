/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            12.12.2019
 *  Modified:           12.12.2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define DEBUG(format, ...)  //printf("%d:%s(): " format, __LINE__, __func__, ##__VA_ARGS__);

struct SpaceCoord
{
    int x;
    int y;
    int z;
};

typedef struct SpaceCoord Position;
typedef struct SpaceCoord Velocity;

struct Moon
{
    Position pos;
    Velocity vel;
    struct Moon *next;
};

typedef struct Moon Moon;

typedef struct
{
    Moon *first;
    Moon *last;
} List;

FILE *parse();

Moon *createMoon();

List *createList();
void List_push_back(List*, Moon*);
void deleteList(List*);

int main()
{
    FILE *fp = parse();
    char buf[256];
    
    List *moons = createList();
    
    while (!feof(fp))
    {
        fgets(buf, 256, fp);
        Moon *moon = createMoon();
        
        sscanf(buf, "<x=%d, y=%d, z=%d>", &(moon->pos.x), &(moon->pos.y), &(moon->pos.z));
        
        List_push_back(moons, moon);
    }
    
    // TODO
    
    fclose(fp);
    
    printf("%d\t%d\t%d\n", moons->first->pos.x, moons->first->pos.y, moons->first->pos.z);
    printf("%d\t%d\t%d\n", moons->first->next->pos.x, moons->first->next->pos.y, moons->first->next->pos.z);
    printf("%d\t%d\t%d\n", moons->first->next->next->pos.x, moons->first->next->next->pos.y, moons->first->next->next->pos.z);
    printf("%d\t%d\t%d\n", moons->last->pos.x, moons->last->pos.y, moons->last->pos.z);
    
    deleteList(moons);
    
    return 0;
}

FILE *parse()
{
    // https://adventofcode.com/2019/day/12/input
    FILE *fp = fopen("input.txt", "r");
    
    if (!fp)
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    return fp;
}

List *createList()
{
    List *list = (List*)malloc(sizeof(List));
    if (!list)
    {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }
    list->first = NULL;
    list->last = NULL;
    
    return list;
}

Moon *createMoon()
{
    Moon *moon = (Moon*)malloc(sizeof(Moon));
    
    moon->pos.x = 0;
    moon->pos.y = 0;
    moon->pos.z = 0;
    
    moon->vel.x = 0;
    moon->vel.y = 0;
    moon->vel.z = 0;
    
    moon->next = NULL;
    
    return moon;
}

void List_push_back(List *list, Moon *moon)
{
    // If list is empty
    if (!list->first)
    {
        list->first = moon;
        list->last = list->first;
    }
    else
    {
        list->last->next = moon;
        list->last = list->last->next;
    }
}

void deleteList(List *list)
{
    Moon *temp = NULL;
    Moon *temp2 = NULL;
    
    temp = list->first;
    
    while (temp->next)
    {
        temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    free(temp);
    free(list);
}
