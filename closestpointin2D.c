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
double findMinDist(point2D *points, int len, point2D *closestP1, point2D *closestP2);
double findMinDistStrip(point2D *points, int len, double minDist, point2D *closestP1, point2D *closestP2);
void findMinDistOSqr(point2D *points, int len);

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

    //use O^2 method as answer
    findMinDistOSqr(points, numRandomPoints);


    // sort the array according to the x axis
    qsort(points, sizeof(points)/sizeof(point2D), sizeof(point2D), comparePointsX);

    point2D *closestP1 = malloc(sizeof(point2D));
    point2D *closestP2 = malloc(sizeof(point2D));
    double minDistance = findMinDist(points, numRandomPoints, closestP1, closestP2);

    printf("Divide-and-Conquer result:\n");
    printf("The smallest distance is %.2f\n", minDistance);
    printf("x = %.1f, y = %.1f\n", closestP1->x, closestP1->y);
    printf("x = %.1f, y = %.1f\n", closestP2->x, closestP2->y);

    return 0;
}

int comparePointsX(const void *pointA, const void *pointB){
    return (((point2D *)pointA)->x - ((point2D *)pointB)->x) * 10;
}

int comparePointsY(const void *pointA, const void *pointB){
    return (((point2D *)pointA)->y - ((point2D *)pointB)->y) * 10;
}

double findMinDist(point2D *points, int len, point2D *closestP1, point2D *closestP2){

    printf("\n\n");
    for(int i = 0 ; i<len ; i++)
        printf("x = %.1f, y = %.1f\n", points[i].x, points[i].y);

    if(len == 2){
        printf("ahhh\n");
        closestP1->x = points[0].x;
        closestP1->y = points[0].y;
        closestP2->x = points[1].x;
        closestP2->y = points[1].y;
        printf("ahhh2\n");
        return sqrt(pow(points[0].x-points[1].x, 2) + pow(points[0].y-points[1].y, 2));
    }
    else if(len == 1)
        return DBL_MAX;
    else{
        point2D *closestP1L, *closestP2L, *closestP1R, *closestP2R;
        double minDistL = findMinDist(points, len/2, closestP1L, closestP2L);
        double minDistR = findMinDist(points+len/2, len-len/2, closestP1R, closestP2R);
        double d;
        printf("minDistL = %.2f\n", minDistL);
        printf("minDistR = %.2f\n", minDistR);
        if(minDistL < minDistR){
            d = minDistL;
            closestP1->x = closestP1L->x;
            closestP1->y = closestP1L->y;
            closestP2->x = closestP2L->x;
            closestP2->y = closestP2L->y;
        }
        else{
            d = minDistR;
            printf("d = %.2f\n\n", d);
            printf("x = %.1f, y = %.1f\n", closestP1R->x, closestP1R->y);
            printf("x = %.1f, y = %.1f\n", closestP2R->x, closestP2R->y);
            closestP1->x = closestP1R->x;
            closestP1->y = closestP1R->y;
            closestP2->x = closestP2R->x;
            closestP2->y = closestP2R->y;
        }

        // calculate median of x-coordinates
        float median = 0;
        for(int i = 0 ; i<len ; i++)
            median += points[i].x;
        median /= len;
        
        // double d = 2;
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
        point2D *closestP1Strip, *closestP2Strip;
        double minDistStrip = findMinDistStrip(points+start, end-start+1, d, closestP1Strip, closestP2Strip);
        if(minDistStrip < d){
            closestP1->x = closestP1Strip->x;
            closestP1->y = closestP1Strip->y;
            closestP2->x = closestP2Strip->x;
            closestP2->y = closestP2Strip->y;
            return minDistStrip;
        }
        else{
            return d;
        }
    }
    
    return 0;
}

double findMinDistStrip(point2D *points, int len, double minDist, point2D *closestP1, point2D *closestP2){

    double outputDist = minDist;
    
    // sort according to the y coordinate
    qsort(points, len, sizeof(point2D), comparePointsY);

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

void findMinDistOSqr(point2D *points, int len){
    double minDist = DBL_MAX;
    point2D pointA, pointB;
    for(int i = 0 ; i<len ; i++){
        for(int j = 0 ; j<len ; j++){
            if(j == i)
                continue;
            else{
                double dist = sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2));
                if(dist < minDist){
                    minDist = dist;
                    pointA.x = points[i].x;
                    pointA.y = points[i].y;
                    pointB.x = points[j].x;
                    pointB.y = points[j].y;
                }
            }
        }
    }
    printf("The smallest distance is %.2f\n", minDist);
    printf("x = %.1f, y = %.1f\n", pointA.x, pointA.y);
    printf("x = %.1f, y = %.1f\n", pointB.x, pointB.y);
}
