/**
 * @file pathfinding.h
 *
 * @author Carl | Alexandre
 *
 * @brief Pathfinding
 *
 * This file contains all declarations and function regarding Pathfinding
 *
 */

#ifndef PATHFINDING_H
#define PATHFINDING_H
#include "map.h"
#include "raylib.h"

#define PATHFINDING_SIZE 10

/* description of graph node */
struct stop {
	double col, row;
	/* array of indexes of routes from this stop to neighbours in array of all routes */
	int * n;
	int n_len;
	double f, g, h;
	int from;
};


/* description of route between two nodes */
struct route {
	/* route has only one direction! */
	int x; /* index of stop in array of all stops of src of this route */
	int y; /* intex of stop in array of all stops od dst of this route */
	double d;
};

void pathfinding(int path_index[20][2], int x, int y, GameMap * map, Vector2 target);

#endif