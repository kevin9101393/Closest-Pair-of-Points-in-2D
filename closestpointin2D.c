#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<float.h>

typedef struct{
    float x;
    float y;
}point2D;

int comparePointsX(const void *pointA, const void *pointB);
int comparePointsY(const void *pointA, const void *pointB);
double min(double a, double b);
double findMinDist(point2D *points, int len, point2D *closestP1, point2D *closestP2);
double findMinDistStrip(point2D *points, int len, double minDist, point2D *closestP1, point2D *closestP2);

int main(void){

    int numRandomPoints = 1;    // 1 is default value
    printf("Enter the number of random points: ");
    scanf("%d", &numRandomPoints);
    printf("The number you enter is: %d\n", numRandomPoints);

    point2D points[numRandomPoints];

    // generate random 2D points
    srand(time(NULL));
    for(int i = 0 ; i<numRandomPoints ; i++){
        points[i].x = rand() % 100 / 10.0;
        points[i].y = rand() % 100 / 10.0;
        printf("x = %.1f, y = %.1f\n", points[i].x, points[i].y);
    }

    // sort the array according to the x axis
    qsort(points, sizeof(points)/sizeof(point2D), sizeof(point2D), comparePointsX);

    point2D closestP1;
    point2D closestP2;
    double minDistance = findMinDist(points, numRandomPoints, &closestP1, &closestP2);

    return 0;
}

int comparePointsX(const void *pointA, const void *pointB){
    return (((point2D *)pointA)->x - ((point2D *)pointB)->x) * 10;
}

int comparePointsY(const void *pointA, const void *pointB){
    return (((point2D *)pointA)->y - ((point2D *)pointB)->y) * 10;
}

double min(double a, double b){
    if(a < b)
        return a;
    else
        return b;
}

double findMinDist(point2D *points, int len, point2D *closestP1, point2D *closestP2){

    printf("\n\n");
    for(int i = 0 ; i<len ; i++)
        printf("x = %.1f, y = %.1f\n", points[i].x, points[i].y);

    if(len == 2){
        closestP1->x = points[0].x;
        closestP1->y = points[0].y;
        closestP2->x = points[1].x;
        closestP2->y = points[1].y;
        return sqrt(pow(points[0].x-points[1].x, 2) + pow(points[0].y-points[1].y, 2));
    }
    else if(len == 1)
        return DBL_MAX;
    else{
        // double minDistL = findMinDist(points, len/2, closestP1, closestP2);
        // double minDistR = findMinDist(points+len/2, len-len/2, closestP1, closestP2);
        // double d = min(minDistL, minDistR);

        // calculate median of x-coordinates
        float median = 0;
        for(int i = 0 ; i<len ; i++)
            median += points[i].x;
        median /= len;
        
        double d = 2;
        int start, end;
        for(int i = 0 ; i<len ; i++){
            if(points[i].x >= median - (float)d){
                start = i;
                break;
            }
        }
        for (int i = start+1; i < len; i++){
            if (points[i].x > median + (float)d){
                end = i-1;
                break;
            }
        }
        // printf("len = %d\n", end-start+1);
        // printf("median = %.2f\n", median);
        double minDistStrip = findMinDistStrip(points+start, end-start+1, d, closestP1, closestP2);
    }
    
    return 0;
}

double findMinDistStrip(point2D *points, int len, double minDist, point2D *closestP1, point2D *closestP2){

    double outputDist = minDist;

    // printf("\n\n");
    // for (int i = 0; i < len; i++)
    //     printf("x = %.1f, y = %.1f\n", points[i].x, points[i].y);

    // sort according to the y coordinate
    qsort(points, len, sizeof(point2D), comparePointsY);

    // printf("\n\n");
    // for (int i = 0; i < len; i++)
    //     printf("x = %.1f, y = %.1f\n", points[i].x, points[i].y);

    for(int i = 0 ; i<len ; i++){
        for(int j = i+1 ; j<len && (points[j].y-points[i].y)<minDist ; j++){
            double dist = sqrt(pow(points[i].x-points[j].x, 2) + pow(points[i].y-points[j].y, 2));
            if(dist < outputDist){
                outputDist = dist;
                closestP1->x = points[i].x;
                closestP1->y = points[i].y;
                closestP2->x = points[j].x;
                closestP2->y = points[j].y;
            }
        }
    }

    return outputDist;
}
