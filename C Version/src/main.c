#include "../include/KMeans.h"
#include <stdio.h>





int main(int argc, char const *argv[])
{
    KMeans km;

    km = InitKMeans(3, 0.0001f, 500);

    return 0;
}
