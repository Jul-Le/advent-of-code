/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            2.12.2019
 *  Modified:           2.12.2019
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int add(int, int, int);
int mul(int, int, int);
void printProgram();

int programInput[256] = { 0 };
int program[256] = { 0 };
int programLength = 0;
int ptr = 0;

int main()
{
    // https://adventofcode.com/2019/day/2/input
    FILE *fp = fopen("input.txt", "r");
    
    if (!fp)
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }
    
    // Buffer to store the input
    char buf[1024];
    // Read input from file
    fgets(buf, 1024, fp);
    fclose(fp);
    
    char *token;
    const char s[2] = ",";
    token = strtok(buf, s);
    
    int i = 0;
    
    while (token)
    {
        program[i] = atoi(token);
        token = strtok(NULL, s);
        i++;
    }
    
    programLength = i;
    memcpy(programInput, program, 256 * sizeof(int));
    
    bool programFinished, inputsFound;
    int noun, verb;
    
    programFinished = false;
    inputsFound = false;
    
    for (noun = 0; noun < 100; noun++)
    {
        for (verb = 0; verb < 100; verb++)
        {
            // Restore program
            memcpy(program, programInput, 256 * sizeof(int));
            programFinished = false;
            ptr = 0;
            // Replace code
            program[1] = noun;
            program[2] = verb;
            
            while (ptr < programLength && !programFinished)
            {
                switch (program[ptr])
                {
                    case 1: add(program[ptr+1], program[ptr+2], program[ptr+3]); break;
                    case 2: mul(program[ptr+1], program[ptr+2], program[ptr+3]); break;
                    case 99: programFinished = true; break;
                    // Invalid instruction:
                    default: programFinished = true; break;
                }
                
                ptr += 4;
            }
            if (program[0] == 19690720)
            {
                inputsFound = true;
                break;
            }
        }
        if (inputsFound)
            break;
    }
    
    printProgram();
    printf("noun: %d, verb: %d, answer: %d\n", noun, verb, 100 * noun + verb);
    
    return 0;
}

int add(int a, int b, int result)
{
    program[result] = program[a] + program[b];
}

int mul(int a, int b, int result)
{
    program[result] = program[a] * program[b];
}

void printProgram()
{
    int i;
    for (i = 0; i < programLength; i++)
    {
        if (i % 4 == 0 && i)
            printf("\n");
        printf("%d, ", program[i]);
    }
    printf("\n");
}
