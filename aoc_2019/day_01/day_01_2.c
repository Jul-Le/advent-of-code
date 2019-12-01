/*
 *  Contributor(s):     Julius Lesonen
 *
 *  Created:            1.12.2019
 *  Modified:           1.12.2019
 */

#include <stdio.h>

long getFuelReq(long);

int main()
{
    // https://adventofcode.com/2019/day/1/input
    FILE *fp = fopen("input.txt", "r");
    
    if (!fp)
    {
        perror("Failed to open file \"input.txt\"");
        return 1;
    }

    // Total amount of fuel, including fuel required to move fuel
    long total = 0;
    // Mass of each vessel
    long vessels[100] = { 0 };
    
    int i;
    
    for (i = 0; i < 100; i++)
    {
        fscanf(fp, "%ld", &vessels[i]);
    }

    fclose(fp);
    
    for (i = 0; i < 100; i++)
    {
        long fuel = getFuelReq(vessels[i]);
        total += fuel;
        
        while (fuel > 0)
        {
            fuel = getFuelReq(fuel);
            total = fuel > 0 ? total + fuel : total;
        }
    }
    
    printf("%ld\n", total);
    
    return 0;
}

long getFuelReq(long mass)
{
    return mass / 3 - 2;
}
