OBJS = src/Exception.c src/KMeans.c src/main.c
CC = gcc
OBJ_NAME = main

all: $(OBJS)
	$(CC) $(OBJS)  -o $(OBJ_NAME) -lm -DRAND_CENTROID_POINTS -DDEBUG_ON