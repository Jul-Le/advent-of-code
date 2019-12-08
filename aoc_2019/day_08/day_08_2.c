/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            8.12.2019
 *  Modified:           8.12.2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define DEBUG(format, ...)  //printf("%d:%s(): " format, __LINE__, __func__, ##__VA_ARGS__);

#define WIDTH 25
#define HEIGHT 6

typedef enum
{
    BLACK       = '0',
    WHITE       = '1',
    TRANSPARENT = '2'
} pixelType_t;

struct Layer
{
    char pixels[WIDTH * HEIGHT];
    struct Layer *next;
};

typedef struct Layer Layer;

typedef struct
{
    Layer *first;
    Layer *last;
} List;

FILE *parse();

void printLayer(Layer*);
Layer *createLayer(char*);

List *createList();
void List_push_back(List*, Layer*);
void deleteList(List*);

Layer *getFinalLayer(List*);

int main()
{
    FILE *fp = parse();
    char buf[16384];
    
    fgets(buf, 16384, fp);
    fclose(fp);
    
    if (buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
    
    if (strlen(buf) % (WIDTH * HEIGHT) != 0)
    {
        printf("Parser error: Buffer length %d, expected to be multiple of %d\n",
               (int)strlen(buf), WIDTH * HEIGHT);
        exit(EXIT_FAILURE);
    }
    
    List *list = createList();
    
    int i;
    
    for (i = 0; i < strlen(buf); i+=WIDTH * HEIGHT)
    {
        Layer *layer = createLayer(&buf[i]);
        List_push_back(list, layer);
        //printLayer(layer);
    }
    
    Layer *result = getFinalLayer(list);
    
    printLayer(result);
    
    free(result);
    deleteList(list);
    
    return 0;
}

FILE *parse()
{
    // https://adventofcode.com/2019/day/8/input
    FILE *fp = fopen("input.txt", "r");
    
    if (!fp)
    {
        perror("Failed to open file \"input.txt\"");
        exit(EXIT_FAILURE);
    }
    return fp;
}

void printLayer(Layer *layer)
{
    int i;
    for (i = 0; i < WIDTH * HEIGHT; i++)
    {
        if (i % WIDTH == 0)
            printf("\n");
        
        char pixel = layer->pixels[i];
        
        if (pixel == '0')
            printf("%c", ' ');    
        else
            printf("%c", pixel);
    }
    printf("\n");
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

Layer *createLayer(char *buf)
{
    Layer *layer = (Layer*)malloc(sizeof(Layer));
    
    layer->next = NULL;
    memcpy(layer->pixels, buf, HEIGHT * WIDTH);
    
    return layer;
}

void List_push_back(List *list, Layer *layer)
{
    // If list is empty
    if (!list->first)
    {
        list->first = layer;
        list->last = list->first;
    }
    else
    {
        list->last->next = layer;
        list->last = list->last->next;
    }
}

void deleteList(List *list)
{
    Layer *temp = NULL;
    Layer *temp2 = NULL;
    
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

Layer *getFinalLayer(List *list)
{
    Layer *result = NULL;
    Layer *layer  = NULL;
    int i;
    
    result = (Layer*)malloc(sizeof(Layer));
    
    result->next = NULL;
    
    for (i = 0; i < WIDTH * HEIGHT; i++)
    {
        result->pixels[i] = TRANSPARENT;
    }
    
    for (layer = list->first; layer; layer = layer->next)
    {
        for (i = 0; i < WIDTH * HEIGHT; i++)
        {
            pixelType_t pixel = layer->pixels[i];
            
            if (pixel != TRANSPARENT && result->pixels[i] == TRANSPARENT)
                result->pixels[i] = pixel;
        }
    }
    return result;
}
