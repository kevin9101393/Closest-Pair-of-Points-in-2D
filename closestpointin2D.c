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
double findMinDist(point2D *points, int len);
double findMinDistStrip(point2D *points, int len, double minDist);
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

    double minDistance = findMinDist(points, numRandomPoints);

    printf("Divide-and-Conquer result:\n");
    printf("The smallest distance is %.2f\n", minDistance);

    return 0;
}

int comparePointsX(const void *pointA, const void *pointB){
    return (((point2D *)pointA)->x - ((point2D *)pointB)->x) * 10;
}

int comparePointsY(const void *pointA, const void *pointB){
    return (((point2D *)pointA)->y - ((point2D *)pointB)->y) * 10;
}

double findMinDist(point2D *points, int len){

    // printf("\n\n");
    // for(int i = 0 ; i<len ; i++)
    //     printf("x = %.1f, y = %.1f\n", points[i].x, points[i].y);

    if(len == 2){
        return sqrt(pow(points[0].x-points[1].x, 2) + pow(points[0].y-points[1].y, 2));
    }
    else if(len == 1)
        return DBL_MAX;
    else{
        double minDistL = findMinDist(points, len/2);
        double minDistR = findMinDist(points+len/2, len-len/2);
        double d;
        if(minDistL < minDistR){
            d = minDistL;
        }
        else{
            d = minDistR;
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
            // printf("points[i].x = %.1f\n", points[i].x);
            // printf("median + (float)d = %.1f\n", median + (float)d); 
            if (points[i].x > median + (float)d){
                break;
            }
            end = i;
        }
        // printf("len out = %d\n", len);
        // printf("start = %d\n", start);
        // printf("end = %d\n", end);
        // printf("len = %d\n", end-start+1);
        // printf("median = %.2f\n", median);
        double minDistStrip = findMinDistStrip(points+start, end-start+1, d);
        if(minDistStrip < d){
            return minDistStrip;
        }
        else{
            return d;
        }
    }
    
    return 0;
}

double findMinDistStrip(point2D *points, int len, double minDist){

    double outputDist = minDist;
    
    // sort according to the y coordinate
    qsort(points, len, sizeof(point2D), comparePointsY);

    for(int i = 0 ; i<len ; i++){
        for(int j = i+1 ; j<len && (points[j].y-points[i].y)<minDist ; j++){
            double dist = sqrt(pow(points[i].x-points[j].x, 2) + pow(points[i].y-points[j].y, 2));
            if(dist < outputDist){
                outputDist = dist;
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
