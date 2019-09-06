#include "../include/KMeans.h"
#include <stdlib.h>
#include "../include/Exception.h"



typedef struct KMeansStructure
{
    int centroids;
    float tolerance;
    int max_iteractions;
    float* data;
    float* initial_centroids;
    int data_num;
    int dimension;
}*KMeansStructure;


KMeans InitKMeans(int centroids, float tolerance, int max_iteractions)
{
    KMeansStructure km = NULL;

    try
    {
        km = (KMeansStructure)malloc(sizeof(struct KMeansStructure));
        if(NULLReference(km))
        {
            throw (__MemoryAllocationException__);
        }
    }
    catch(MemoryAllocationException)
    {

    }
    km->centroids = centroids;
    km->tolerance = tolerance;
    km->max_iteractions = max_iteractions;


    return (KMeans)km;
}