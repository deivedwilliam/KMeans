#include "../include/KMeans.h"
#include <stdlib.h>
#include "../include/Exception.h"
#include <math.h>
#include <string.h>
#include <time.h>

#define CKMeans(Obj) ((KMeansStructure)Obj)

typedef float (*DistanceMethod)(Pointer q, Pointer r);

typedef struct KMeansStructure
{
    int centroids;
    float tolerance;
    int max_iteractions;
    int iteractions;
    Pointer dataPointer;
    DistanceMethod calcDistanceFunction;
    Pointer initial_centroids;
    int data_num;
    int* clusters;
    int dimension;
}*KMeansStructure;




float CalcDistance(Pointer q, Pointer r)
{
    Point a = ((Point)q);
    Point b = ((Point)r);
    float res;

    res = (a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y);

    return sqrt(res);
}


KMeans InitKMeans(int centroids, float tolerance, int max_iteractions)
{
    KMeansStructure km = NULL;

    try
    {
        km = (KMeansStructure)malloc(sizeof(struct KMeansStructure));
        if(NULLReference(km))
        {
            throw(__MemoryAllocationException__);
        }
        km->centroids = centroids;
        km->tolerance = tolerance;
        km->max_iteractions = max_iteractions;
        km->calcDistanceFunction = CalcDistance;
        km->clusters = NULL;
        km->dataPointer = NULL;
        km->data_num = 0;
        km->iteractions = 0;
#ifdef RAND_CENTROID_POINTS
        srand(time(NULL));
        km->initial_centroids = (Pointer)calloc(km->centroids, sizeof(struct Point));
        for(int i = 0; i < km->centroids; i++)
        {
            ((Point)km->initial_centroids)[i].x = -rand()%20 + rand()%20;
            ((Point)km->initial_centroids)[i].y = -rand()%20 + rand()%20;

        }
#endif
#ifdef DEBUG_ON

        puts("Initial Centroids");
        for(int i = 0; i < km->centroids; i++)
        {
            printf("Cenroid [%i] -> x = %f", i, ((Point)km->initial_centroids)[i].x);
            printf("\tCenroid [%i] -> y = %f", i, ((Point)km->initial_centroids)[i].y);
            puts(" ");
        }
#endif
    }
    catch(MemoryAllocationException)
    {
        PrintExceptionStdOut(MemoryAllocationException);
    }
    

    return (KMeans)km;
}

void InitCentroids(KMeans km)
{
    
}

void fit(KMeans* km, Pointer data, int data_num)
{
    int i;
    struct Point* p;
    struct Point sum = {
        .x = 0.0f,
        .y = 0.0f
        };
    float distance;
    float currenteDist;
    int cluster = 0;
    int clusterFound;
    int centroid;
    int sum_counter = 0;
    int* clusters_prev = NULL;
    CKMeans(km)->dataPointer = data;
    CKMeans(km)->data_num = data_num;

    p = ((Point)CKMeans(km)->dataPointer);

#ifdef PRINT_DATASET
    for(i = 0; i < data_num; i++)
    {
        printf("%f, %f\n", p[i].x, p[i].y);
    }
#endif
    
    try
    {
        if(NULLReference(km))
        {
            throw(__NullPointerException__);
        }
        CKMeans(km)->clusters = (int*)calloc(data_num, sizeof(int));
        clusters_prev = (int*)calloc(data_num, sizeof(int));
        if(NULLReference(CKMeans(km)->clusters) | NULLReference(clusters_prev))
        {
            throw(__MemoryAllocationException__);
        }
    }
    catch(MemoryAllocationException)
    {
        PrintExceptionStdOut(MemoryAllocationException);
    }
    catch(NullPointerException)
    {
        PrintExceptionStdOut(NullPointerException);
    }
    p = ((Point)CKMeans(km)->dataPointer);
    while(1)
    {
        memcpy(clusters_prev, CKMeans(km)->clusters, CKMeans(km)->data_num*sizeof(int));

        for(i = 0; i < CKMeans(km)->data_num; i++)
        {
            currenteDist = CKMeans(km)->calcDistanceFunction(&p[i], &(((Point)CKMeans(km)->initial_centroids)[0]));
          
            for(cluster = 1; cluster < CKMeans(km)->centroids; cluster++)
            {
                distance = CKMeans(km)->calcDistanceFunction(&p[i], &(((Point)CKMeans(km)->initial_centroids)[cluster]));

                if(distance < currenteDist)
                {
                    currenteDist = distance;
                    clusterFound = cluster;
                } 
            }

            CKMeans(km)->clusters[i] = clusterFound;
        }
        
        for(centroid = 0; centroid < CKMeans(km)->centroids; centroid++)
        {

            for(i = 0; i < CKMeans(km)->data_num; i++)
            {
                if(CKMeans(km)->clusters[i] == centroid)
                {
                    sum.x += p[i].x;
                    sum.y += p[i].y;
                    sum_counter += 1;
                }

            }

            if(sum_counter > 0)
            {
                sum.x /= sum_counter;
                sum.y /= sum_counter;
                ((Point)CKMeans(km)->initial_centroids)[centroid].x = sum.x;
                ((Point)CKMeans(km)->initial_centroids)[centroid].y = sum.y;
                sum_counter = 0;
            }
        }

        if(memcmp(clusters_prev, CKMeans(km)->clusters, CKMeans(km)->data_num*sizeof(int)) == 0)
        {
            break;
        }
    }
#ifdef DEBUG_ON
    for(i = 0; i < CKMeans(km)->data_num; i++)
    {
        printf("[%i]\n", CKMeans(km)->clusters[i]);
    }

    puts("Final Centroids");
    for(i = 0; i < CKMeans(km)->centroids; i++)
    {
        printf("Cenroid [%i] -> x = %f", i, ((Point)CKMeans(km)->initial_centroids)[i].x);
        printf("\tCenroid [%i] -> y = %f\n", i, ((Point)CKMeans(km)->initial_centroids)[i].y);
    }
#endif    

}