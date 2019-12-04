/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            3.12.2019
 *  Modified:           4.12.2019
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct Line
{
    int32_t     x;              // Coordinates of line start
    int32_t     y;              // Coordinates of line start
    bool        isHorizontal;   // Direction of line
    uint32_t    len;            // Length of line
    uint32_t    crossPoint;     // 0 == no cross, nonzero == distance from start to cross
    struct Line *next;          // Pointer to next line
};

typedef struct Line Line;

typedef struct
{
    Line *first;
    Line *last;
} Wire;

// Set wire first and last to null
void wire_init(Wire*);
// Add line to the end
void wire_addLine(Wire*, char, uint32_t);
// Delete lines and wire
void wire_free(Wire*);

bool linesIntersect(Line*, Line*);
// Get distance from wire start to the start of current line
uint32_t getLineDist(Wire*, Line*);
// Get distance from start of current line to the intersection point
// First parameter is the line of which distance we are getting,
// second is the intersecting one
uint32_t getIntersectDist(Line*, Line*);

int main()
{
    Wire *wire1 = (Wire*)malloc(sizeof(Wire));
    Wire *wire2 = (Wire*)malloc(sizeof(Wire));
    
    wire_init(wire1);
    wire_init(wire2);
    
    // https://adventofcode.com/2019/day/3/input
    FILE *fp = fopen("input.txt", "r");
    
    if (!fp)
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    // Buffer to store the input
    char buf1[4096];
    char buf2[4096];
    
    // Read input from file
    fgets(buf1, 4096, fp);
    fgets(buf2, 4096, fp);
    
    fclose(fp);
    
    char *token;
    const char s[2] = ",";
    token = strtok(buf1, s);
    
    while (token)
    {
        char dir;
        uint32_t len;
        
        sscanf(token, "%c%d", &dir, &len);
        wire_addLine(wire1, dir, len);
        token = strtok(NULL, s);
    }
    
    token = strtok(buf2, s);
    
    while (token)
    {
        char dir;
        uint32_t len;
        
        sscanf(token, "%c%d", &dir, &len);
        wire_addLine(wire2, dir, len);
        token = strtok(NULL, s);
    }
    
    Line *l1 = wire1->first;
    Line *l2 = wire2->first;
    
    uint32_t smallestTotal = UINT32_MAX;
    
    while (l1)
    {
        while (l2)
        {
            if (linesIntersect(l1, l2))
            {
                uint32_t total = getLineDist(wire1, l1)
                               + getIntersectDist(l1, l2)
                               + getLineDist(wire2, l2)
                               + getIntersectDist(l2, l1);
                if (total < smallestTotal)
                    smallestTotal = total;
            }
            
            l2 = l2->next;
        }
        l1 = l1->next;
    }
    
    wire_free(wire1);
    wire_free(wire2);
    
    printf("%u\n", smallestTotal);
    
    return 0;
}

void wire_init(Wire *w)
{
    w->first = NULL;
    w->last = NULL;
}

void wire_addLine(Wire *w, char dir, uint32_t l)
{
    // If wire is empty, create first line
    if (!(w->first))
    {
        w->first = (Line*)malloc(sizeof(Line));
        w->first->x = 0;
        w->first->y = 0;
        w->first->isHorizontal = (dir == 'L' || dir == 'R');
        w->first->len = dir == 'U' || dir == 'R' ? l : -l;
        w->first->next = NULL;
        w->last = w->first;
    }
    // Else add to the end
    else
    {
        if (!(w->first->next))
        {
            w->first->next = (Line*)malloc(sizeof(Line));
            w->last->next = w->first->next;
        }
        else
        {
            w->last->next = (Line*)malloc(sizeof(Line));
        }
        
        w->last->next->x = w->last->isHorizontal ? w->last->x + w->last->len : w->last->x;
        w->last->next->y = !(w->last->isHorizontal) ? w->last->y + w->last->len : w->last->y;
        w->last->next->isHorizontal = (dir == 'L' || dir == 'R');
        w->last->next->len = dir == 'U' || dir == 'R' ? l : -l;
        w->last->next->next = NULL;
        
        w->last = w->last->next;
    }
}

void wire_free(Wire *w)
{
    Line *temp  = NULL;
    Line *temp2 = NULL;
    
    temp = w->first;
    
    while (temp->next)
    {
        temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    free(temp);
    free(w);
}

bool linesIntersect(Line *l1, Line *l2)
{
    // If lines are not prependicular
    if (l1->isHorizontal == l2->isHorizontal)
        return false;
    
    // If lines cross
    if (l1->isHorizontal)
    {
        if (l1->x < l2->x && abs(l1->len) > abs(l2->x - l1->x)
        ||  l1->x > l2->x && abs(l1->len) > abs(l2->x - l1->x)
        && ((l1->y > l2->y) != (l1->y > l2->y + l2->len)))
            return true;
    }
    else
    {
        if (l1->y < l2->y && abs(l1->len) > abs(l2->y - l1->y)
        ||  l1->y > l2->y && abs(l1->len) > abs(l2->y - l1->y)
        && ((l1->x > l2->x) != (l1->x > l2->x + l2->len)))
            return true;
    }
    return false;
}

uint32_t getLineDist(Wire *w, Line *line)
{
    uint32_t total = 0;
    
    if (w->first == line)
        return 0;
    
    Line *l = w->first;
    
    total += l->len;
    
    while (l->next != line)
    {
        l = l->next;
        total += l->len;
    }
    
    return total;
}

uint32_t getIntersectDist(Line *l1, Line *l2)
{
    uint32_t dist = 0;
    
    if (l1->isHorizontal)
    {
        dist = abs(l2->x - l1->x);
    }
    else
    {
        dist = abs(l2->y - l1->y);
    }
    
    return dist;
}
