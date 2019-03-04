#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void){

    int numRandomPoints = 1;    // 1 is default value
    printf("Enter the number of random points: ");
    scanf("%d", &numRandomPoints);
    printf("The number you enter is: %d\n", numRandomPoints);

    float x[numRandomPoints];
    float y[numRandomPoints];

    srand(time(NULL));
    for(int i = 0 ; i<numRandomPoints ; i++){
        x[i] = rand() % 100 / 10.0;
        y[i] = rand() % 100 / 10.0;
        printf("x = %.1f, y = %.1f\n", x[i], y[i]);
    }

    return 0;
}