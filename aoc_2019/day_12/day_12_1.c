/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            12.12.2019
 *  Modified:           12.12.2019
 */

#include <stdio.h>
#include <stdlib.h>
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

// Apply gravity
void calcVel(List*);
// Apply velocity
void calcPos(List*);

unsigned long getTotalEnergy(List*);
unsigned long getKinEnergy(Moon*);
unsigned long getPotEnergy(Moon*);

int main()
{
    FILE *fp = parse();
    char buf[256];
    int i;
    
    List *moons = createList();
    
    while (!feof(fp))
    {
        fgets(buf, 256, fp);
        Moon *moon = createMoon();
        
        if (strlen(buf) < strlen("<x=0, y=0, z=0>"))
            break;
        
        sscanf(buf, "<x=%d, y=%d, z=%d>", &(moon->pos.x), &(moon->pos.y), &(moon->pos.z));
        
        DEBUG("%s", buf);
        DEBUG("<x=%d, y=%d, z=%d>\n", moon->pos.x, moon->pos.y, moon->pos.z);
        
        List_push_back(moons, moon);
        memset(buf, '\0', strlen(buf));
    }
    fclose(fp);
    
    for (i = 0; i < 1000; i++)
    {
        calcVel(moons);
        calcPos(moons);
    }
    
    printf("Total energy: %lu\n", getTotalEnergy(moons));
    
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

void calcVel(List *list)
{
    Moon *moon1 = NULL;
    Moon *moon2 = NULL;
    static int i = 0;
    i++;
    
    for (moon1 = list->first; moon1 != list->last; moon1 = moon1->next)
    {
        for (moon2 = moon1->next; moon2; moon2 = moon2->next)
        {
            // Update x
            if (moon1->pos.x > moon2->pos.x)
            {
                moon1->vel.x--;
                moon2->vel.x++;
            }
            else if (moon1->pos.x < moon2->pos.x)
            {
                moon1->vel.x++;
                moon2->vel.x--;
            }
            // Update y
            if (moon1->pos.y > moon2->pos.y)
            {
                moon1->vel.y--;
                moon2->vel.y++;
            }
            else if (moon1->pos.y < moon2->pos.y)
            {
                moon1->vel.y++;
                moon2->vel.y--;
            }
            // Update z
            if (moon1->pos.z > moon2->pos.z)
            {
                moon1->vel.z--;
                moon2->vel.z++;
            }
            else if (moon1->pos.z < moon2->pos.z)
            {
                moon1->vel.z++;
                moon2->vel.z--;
            }
        }
    }
    for (moon1 = list->first; moon1; moon1 = moon1->next)
    {
        DEBUG("%d> %d, %d, %d\n", i, moon1->vel.x, moon1->vel.y, moon1->vel.z);
    }
    DEBUG("\n");
}

void calcPos(List *list)
{
    Moon *moon = NULL;
    static int i = 0;
    i++;
    
    for (moon = list->first; moon; moon = moon->next)
    {
        moon->pos.x += moon->vel.x;
        moon->pos.y += moon->vel.y;
        moon->pos.z += moon->vel.z;
        
        DEBUG("%d> %d, %d, %d\n", i, moon->pos.x, moon->pos.y, moon->pos.z);
    }
    DEBUG("\n");
}

unsigned long getTotalEnergy(List *list)
{
    unsigned long ek, ep, totalEnergy = 0;
    Moon *moon = NULL;
    
    for (moon = list->first; moon; moon = moon->next)
    {
        ek = getKinEnergy(moon);
        ep = getPotEnergy(moon);
        
        totalEnergy += ek * ep;
    }
    
    return totalEnergy;
}

unsigned long getKinEnergy(Moon *moon)
{
    unsigned long energy = 0;
    
    energy += abs(moon->vel.x);
    energy += abs(moon->vel.y);
    energy += abs(moon->vel.z);
    
    return energy;
}

unsigned long getPotEnergy(Moon *moon)
{
    unsigned long energy = 0;
    
    energy += abs(moon->pos.x);
    energy += abs(moon->pos.y);
    energy += abs(moon->pos.z);
    
    return energy;
}
