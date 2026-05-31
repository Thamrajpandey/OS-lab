#include <stdio.h>

int main() {
    int buffer[5];
    int in = 0, out = 0;
    int item;

    for(item = 1; item <= 5; item++) {
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in++;
    }

    for(item = 0; item < 5; item++) {
        printf("Consumed: %d\n", buffer[out]);
        out++;
    }

    printf("USN:1BF24CS318");

    return 0;
}