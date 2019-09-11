#include "../include/KMeans.h"
#include "../include/Exception.h"
#include <stdio.h>
#include <stdlib.h>




int main(int argc, char const *argv[])
{
    KMeans km;
    Point data;
    int i;
    FILE* dataFile = NULL;
    float x,y;

    FileOpen(dataFile, "xclara.csv", "r");

    data = (Point)calloc(3000, sizeof(struct Point));
    km = InitKMeans(3, 0.0001f, 500);

    for(i = 0; i < 3000; i += 1)
    {
        fscanf(dataFile, "%f,%f", &x, &y);
        
        data[i].x = x;
        data[i].y = y;
    }
    
    fit(km, data, 3000);

   

   

    return 0;
}
