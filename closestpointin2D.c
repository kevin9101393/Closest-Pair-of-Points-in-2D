#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

typedef struct{
    float x;
    float y;
}point2D;

int comparePoints(const void *pointA, const void *pointB);
double min(double a, double b);
double findMinDist(point2D *points, int len, point2D *closestP1, point2D *closestP2);

int main(void){

    int numRandomPoints = 1;    // 1 is default value
    printf("Enter the number of random points: ");
    scanf("%d", &numRandomPoints);
    printf("The number you enter is: %d\n", numRandomPoints);

    point2D points[numRandomPoints];

    srand(time(NULL));
    for(int i = 0 ; i<numRandomPoints ; i++){
        points[i].x = rand() % 100 / 10.0;
        points[i].y = rand() % 100 / 10.0;
        printf("x = %.1f, y = %.1f\n", points[i].x, points[i].y);
    }

    // sort the array according to the x axis
    qsort(points, sizeof(points)/sizeof(point2D), sizeof(point2D), comparePoints);

    point2D closestP1;
    point2D closestP2;
    double minDistance = findMinDist(points, numRandomPoints, &closestP1, &closestP2);

    return 0;
}

int comparePoints(const void *pointA, const void *pointB)
{
    const point2D *a = pointA;
    const point2D *b = pointB;
    
    if(a->x > b->x)
        return 1;
    else if(a->x == b->x)
        return 0;
    else
        return -1;
}

double min(double a, double b){
    if(a < b)
        return a;
    else
        return b;
}

double findMinDist(point2D *points, int len, point2D *closestP1, point2D *closestP2){

    if(len == 2)
        return sqrt(pow(points[0].x-points[1].x, 2) + pow(points[0].y-points[1].y, 2));
    else if(len == 1)
        return 0;
    else{
        double minDistL = findMinDist(points, len/2, closestP1, closestP2);
        double minDistR = findMinDist(points+len/2, len-len/2, closestP1, closestP2);
        double d = min(minDistL, minDistR);
    }
    
    return 0;
}
