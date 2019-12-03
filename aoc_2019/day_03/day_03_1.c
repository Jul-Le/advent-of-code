/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            3.12.2019
 *  Modified:           3.12.2019
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#define GRID_SIZE   40000
#define PRINT_GRID  0

typedef struct
{
    uint32_t x;
    uint32_t y;
} Point;

typedef struct 
{
    char        direc;
    uint32_t    steps;
} Line;

char grid[GRID_SIZE][GRID_SIZE];

// Initialize every point to '.'
void initGrid();
// Print to console
void printGrid();
// Set point to any character
void setPoint(Point, char, int);
// Move current coordinate
void movePoint(Point*, char);
// Draw from starting point to direction and distance determined by line
void draw(Point*, Line, int);
// Check if intersection at Point is nearest to start
void checkIfNearest(Point);

uint32_t closestDistance = UINT32_MAX;

int main()
{
    Line line1[400];
    Line line2[400];
    uint16_t line1Count, line2Count;
    
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
    
    int i = 0;
    
    while (token)
    {
        sscanf(token, "%c%d", &line1[i].direc, &line1[i].steps);
        token = strtok(NULL, s);
        i++;
    }
    line1Count = i;
    
    token = strtok(buf2, s);
    
    i = 0;
    
    while (token)
    {
        sscanf(token, "%c%d", &line2[i].direc, &line2[i].steps);
        token = strtok(NULL, s);
        i++;
    }
    line2Count = i;
    
    initGrid();
    
    // Current point on the grid
    Point point =
    {
        .x = GRID_SIZE / 2,
        .y = GRID_SIZE / 2
    };
    
    setPoint(point, 'o', 1);
    
    for (i = 0; i < line1Count; i++)
    {
        draw(&point, line1[i], 1);
    }
    
    point.x = GRID_SIZE / 2;
    point.y = GRID_SIZE / 2;
    
    for (i = 0; i < line2Count; i++)
    {
        draw(&point, line2[i], 2);
    }
    
    printGrid();
    
    printf("Distance from central port to closest intersection: %lu\n", closestDistance);
    
    return 0;
}

void initGrid()
{
    int y, x;
    
    for (y = 0; y < GRID_SIZE; y++)
    {
        for (x = 0; x < GRID_SIZE; x++)
        {
            grid[y][x] = '.';
        }
    }
}

void printGrid()
{
#if PRINT_GRID
    int y, x;
    
    for (y = 0; y < GRID_SIZE; y++)
    {
        for (x = 0; x < GRID_SIZE; x++)
        {
            if (grid[y][x] != '.')
                printf("%c", grid[y][x]);
            else
                printf("%c", ' ');
        }
        printf("\n");
    }
#else
    return;
#endif
}

void setPoint(Point p, char ch, int lineNum)
{
    if (p.x >= GRID_SIZE || p.y >= GRID_SIZE)
    {
        fprintf(stderr, "Index out of range, exiting...\n");
        exit(EXIT_FAILURE);
    }
    
    char curChar = grid[(GRID_SIZE - 1) - p.y][p.x];
    
    if (curChar != '.' && ch != '+'
    && (curChar == '-' && ch == '/'
    || curChar == '/' && ch == '-'
    || curChar == '_' && ch == '|'
    || curChar == '|' && ch == '_'))
    {
        grid[(GRID_SIZE - 1) - p.y][p.x] = 'X';
        // Check if current intersection is closest to start
        checkIfNearest(p);
    }
    else
    {
        grid[(GRID_SIZE - 1) - p.y][p.x] = ch;
    }
}

void movePoint(Point *p, char d)
{
    switch (d)
    {
        case 'R': (*p).x++; break;
        case 'L': (*p).x--; break;
        case 'U': (*p).y++; break;
        case 'D': (*p).y--; break;
        default:
            fprintf(stderr, "Invalid direction\n");
            exit(EXIT_FAILURE);
    }
}

void draw(Point *point, Line line, int lineNum)
{    
    char ch;
    
    if (line.direc == 'R' || line.direc == 'L')
    {
        if (lineNum == 1)
            ch = '-';
        else
            ch = '_';
    }
    else
    {
        if (lineNum == 1)
            ch = '|';
        else
            ch = '/';
    }
    
    int i;
    // Draw line
    for (i = 0; i < line.steps; i++)
    {
        movePoint(point, line.direc);
        setPoint(*point, ch, lineNum);
    }
    setPoint(*point, '+', lineNum);
}

void checkIfNearest(Point p)
{
    const Point start = 
    {
        .x = GRID_SIZE / 2,
        .y = GRID_SIZE / 2
    };
    
    uint32_t distance = abs(p.x - start.x) + abs(p.y - start.y);
    
    closestDistance = distance < closestDistance ? distance : closestDistance;
}
