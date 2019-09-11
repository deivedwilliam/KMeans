#ifndef K_MEANS_H
#define K_MEANS_H

#define RAND_DATA 100U
#define INPUT_DATA 0U

#ifndef DIMENSION
    typedef struct Point 
    {
        float x;
        float y;
    }*Point;
#endif

typedef void* KMeans;
typedef void* Pointer;

KMeans InitKMeans(int centroids, float tolerance, int max_iteractions);
extern float CalcDistance(Pointer q, Pointer r) __attribute__((weak));
extern void InitCentroids(KMeans km) __attribute__((weak));
void fit(KMeans* km, Pointer data, int data_num);
extern void DrawData(void) __attribute__((weak));



#endif