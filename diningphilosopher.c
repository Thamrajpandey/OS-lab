#include <stdio.h>

int main()
{
    int i;

    for(i=0;i<5;i++)
    {
        printf("Philosopher %d is thinking\n",i);

        printf("Philosopher %d picked up left fork %d\n",i,i);

        printf("Philosopher %d picked up right fork %d\n",
               i,(i+1)%5);

        printf("Philosopher %d is eating\n",i);

        printf("Philosopher %d put down forks\n",i);
    }

    printf("USN:1BF24CS318");

    return 0;
}