#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char **argv){
    srand(time(NULL));
    int count = 0;
    int len = 1000000;
    int *sequence = malloc(len*sizeof(int));
    for (int i = 0; i < len; i++){
        sequence[i] = rand() % 100;
    }
    for (int i = 0; i < len; i++){
        if (sequence[i] == sequence[i+1]){
            count += 1;
        }
    }
    double prob = count/len;
    printf("The probability of seeing an identical number twice is %f", prob);
    printf("The count is %d", count);
}
