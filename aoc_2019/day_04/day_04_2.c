/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            5.12.2019
 *  Modified:           5.12.2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// First valid number calculated manually
#define RANGE_MIN   158899 // 158126
#define RANGE_MAX   624574

void initDigits(int*, int);
bool nextNum(int*);
int getInt(int*);
bool validDouble(int*);

int main()
{
    int *digits = malloc(sizeof(int) * 6);
    // First valid number already counted
    int count = 1;
    
    initDigits(digits, RANGE_MIN);
    
    while (getInt(digits) < RANGE_MAX)
    {
        while (!nextNum(digits));
        count++;
      //printf("%d: %d\n", count, getInt(digits));
    }
    // Loop counts until first number is out of range, remove it
    count--;
    
    printf("%d\n", count);
    
    free(digits);
    
    return 0;
}

void initDigits(int *digits, int num)
{
    digits[0] = num / 100000;
    digits[1] = num / 10000 % 10;
    digits[2] = num / 1000 % 10;
    digits[3] = num / 100 % 10;
    digits[4] = num / 10 % 10;
    digits[5] = num % 10;
}

bool nextNum(int *digits)
{
    int i;
    
    for (i = 5; i >= 0; i--)
    {
        if (digits[i] < 9)
        {
            digits[i]++;
            int temp = digits[i];
            
            while(++i < 6)
            {
                digits[i] = temp;
            }
            
            break;
        }
    }
    
    return validDouble(digits);
}

int getInt(int *d)
{
    int ret = 0;
    
    ret += d[0] * 100000;
    ret += d[1] * 10000;
    ret += d[2] * 1000;
    ret += d[3] * 100;
    ret += d[4] * 10;
    ret += d[5] * 1;
    
    return ret;
}

bool validDouble(int *digits)
{
    int i;
    
    for (i = 0; i < 5; i++)
    {
        if (digits[i] == digits[i+1])
        {
            if ((i == 0 || digits[i - 1] != digits[i])
            && (i+1 == 5 || digits [i + 1] != digits[i + 2]))
                return true;
        }
    }
    
    return false;
}
