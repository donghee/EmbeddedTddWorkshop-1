//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include <stdio.h>

int makeSum(int max)
{
    int i, sum;
    sum = 0;
    i = 0;
    while (i < max)
    {
        sum = sum + i;
        i = i + 1;
    }
    return sum;
}
int main(void)
{
    int input, sum;
    scanf("%d",&input);
    sum = makeSum(input);
    printf("Sum from 1 to %d is %d\n", input, sum);
    return 0;
}
