#ifndef K_MEANS_H
#define K_MEANS_H


typedef void* KMeans;

KMeans InitKMeans(int centroids, float tolerance, int max_iteractions);

void fit(KMeans* km, float* data, int data_num);
extern void DrawData(void) __attribute__((weak));



#endif