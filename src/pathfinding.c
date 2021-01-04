#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
/* and not not_eq */
#include <iso646.h>
/* add -lm to command line to compile with this header */
#include <math.h>
#include "includes/map.h"
#include "includes/env.h"
#include "includes/pathfinding.h"

void pathfinding(int path_index[20][2], int x, int y, GameMap * map, Vector2 target) {

	int ind[PATHFINDING_SIZE][PATHFINDING_SIZE] = {{-1}};

	int carte[PATHFINDING_SIZE][PATHFINDING_SIZE] = {0};

	for (int i = 0; i < PATHFINDING_SIZE; i++) {
		for (int j = 0; j < PATHFINDING_SIZE; j++) {
			// En dehors de la map ?
			if (y + i <= 0 || y + i >= MAP_HEIGHT || x + j <= 0 || x + j >= MAP_WIDTH) carte[i][j] = 1;

			// Est-ce qu'on rencontre un mur ? si oui 1
			else if (map->sprite[y + i][x + j]->blocking || !map->sprite[y + i][x + j]->hasTexture) carte[i][j] = 1;

			// Sinon on met un 0, déplacement libre nécessaire pour votre algo A*
			else carte[i][j] = 0;
		}
	}


	int i, j, k, l, b, found = 0;
	int p_len = 0;
	int * path = NULL;
	int c_len = 0;
	int * closed = NULL;
	int o_len = 1;
	int * open = (int*)calloc(o_len, sizeof(int));
	double min, tempg;
	int s;
	int e;
	int current;
	int s_len = 0; //position de l'entité divisé par 5
	struct stop * stops = NULL;
	int r_len = 0;
	struct route * routes = NULL;




	//+------------------------------------------------------------------------------------------------------------+
	for (i = 0; i < PATHFINDING_SIZE; i++) {
		for (j = 0; j < PATHFINDING_SIZE; j++) {
			if (!carte[i][j]) {
				++s_len;
				stops = (struct stop *)realloc(stops, s_len * sizeof(struct stop));
				int t = s_len - 1;
				stops[t].col = j;
				stops[t].row = i;
				stops[t].from = -1;
				stops[t].g = DBL_MAX;
				stops[t].n_len = 0;
				stops[t].n = NULL;
				ind[i][j] = t;
			}
		}
	}
	/* si la position du joueur est compris dans le tableau ind QUI défini l'aura de l'entité alors on calcule le chemin pour
	 * atteindre le joueur et on le retourne*/



	/* index of start stop */
	s = ind[(PATHFINDING_SIZE/2)][(PATHFINDING_SIZE/2)]; //position entité ATTENTION à retenir
	/* index of finish stop */
	int playerY = (int) (target.y / MAP_TEXTURE_SCALE)-y;
	int playerX = (int) (target.x / MAP_TEXTURE_SCALE)-x;
	e = ind[playerY >= PATHFINDING_SIZE ? PATHFINDING_SIZE-1 : playerY][playerX >= PATHFINDING_SIZE ? PATHFINDING_SIZE-1 : playerX]; //position joueur qui est = à s_len

	for (i = 0; i < s_len; i++)
		stops[i].h = sqrt(pow(stops[e].row - stops[i].row, 2) + pow(stops[e].col - stops[i].col, 2));
	
	//stop


	for (i = 1; i < PATHFINDING_SIZE-1; i++) {
		for (j = 1; j < PATHFINDING_SIZE-1; j++) {
			if (ind[i][j] >= 0) {
				for (k = i - 1; k <= i + 1; k++) {
					for (l = j - 1; l <= j + 1; l++) {
						if ((k == i) and (l == j)) {
							continue;
						}
						if (ind[k][l] >= 0) {
							++r_len;
							routes = (struct route *)realloc(routes, r_len * sizeof(struct route));
							int t = r_len - 1;
							routes[t].x = ind[i][j];
							routes[t].y = ind[k][l];
							routes[t].d = sqrt(pow(stops[routes[t].y].row - stops[routes[t].x].row, 2) + pow(stops[routes[t].y].col - stops[routes[t].x].col, 2));
							++stops[routes[t].x].n_len;
							stops[routes[t].x].n = (int*)realloc(stops[routes[t].x].n, stops[routes[t].x].n_len * sizeof(int));
							stops[routes[t].x].n[stops[routes[t].x].n_len - 1] = t;
						}
					}
				}
			}
		}
	}

	open[0] = s;
	stops[s].g = 0;
	stops[s].f = stops[s].g + stops[s].h;
	found = 0;

	while (o_len and not found) {
		min = DBL_MAX;

		for (i = 0; i < o_len; i++) {
			if (stops[open[i]].f < min) {
				current = open[i];
				min = stops[open[i]].f;
			}
		}

		if (current == e) {
			found = 1;

			++p_len;
			path = (int*)realloc(path, p_len * sizeof(int));
			path[p_len - 1] = current;
			while (stops[current].from >= 0) {
				current = stops[current].from;
				++p_len;
				path = (int*)realloc(path, p_len * sizeof(int));
				path[p_len - 1] = current;
			}
		}

		for (i = 0; i < o_len; i++) {
			if (open[i] == current) {
				if (i not_eq (o_len - 1)) {
					for (j = i; j < (o_len - 1); j++) {
						open[j] = open[j + 1];
					}
				}
				--o_len;
				open = (int*)realloc(open, o_len * sizeof(int));
				break;
			}
		}

		++c_len;
		closed = (int*)realloc(closed, c_len * sizeof(int));
		closed[c_len - 1] = current;

		for (i = 0; i < stops[current].n_len; i++) {
			b = 0;

			for (j = 0; j < c_len; j++) {
				if (routes[stops[current].n[i]].y == closed[j]) {
					b = 1;
				}
			}

			if (b) {
				continue;
			}

			tempg = stops[current].g + routes[stops[current].n[i]].d;

			b = 1;

			if (o_len > 0) {
				for (j = 0; j < o_len; j++) {
					if (routes[stops[current].n[i]].y == open[j]) {
						b = 0;
					}
				}
			}

			if (b or (tempg < stops[routes[stops[current].n[i]].y].g)) {
				stops[routes[stops[current].n[i]].y].from = current;
				stops[routes[stops[current].n[i]].y].g = tempg;
				stops[routes[stops[current].n[i]].y].f = stops[routes[stops[current].n[i]].y].g + stops[routes[stops[current].n[i]].y].h;

				if (b) {
					++o_len;
					open = (int*)realloc(open, o_len * sizeof(int));
					open[o_len - 1] = routes[stops[current].n[i]].y;
				}
			}
		}
	}

	if (DEBUG) {
		for (i = 0; i < PATHFINDING_SIZE; i++) {
			for (j = 0; j < PATHFINDING_SIZE; j++) {
				if (carte[i][j]) {
		            putchar(0xdb);
		        } else {
					b = 0;
					for (k = 0; k < p_len; k++) {
						if (ind[i][j] == path[k]) {
							++b;
						}
					}
					if (b) {
						putchar('x');
					} else {
						putchar('.');
					}
				}
			}
			putchar('\n');
		}
	}

	//carl
	
	int var1=0;
	int var2=0;
	int cpt1=0;

	if (!found) {
		if (DEBUG)
			puts("IMPOSSIBLE");
	} else {
		if (DEBUG)
		printf("path cost is %d:\n", p_len-1);

		for (i = p_len - 2; i >= 0; i--) {
			if (DEBUG)
				printf("(%1.0f, %1.0f)\n", stops[path[i]].row, stops[path[i]].col);
			//pour moi
			// @dylan : add X and Y coordinates
			var1=stops[path[i]].row+y;
			var2=stops[path[i]].col+x;
			//tableau que retournera la fonction pour indiquer le chemin à prendre 		    pour l'entité
			path_index[cpt1][0]=var1;
			path_index[cpt1][1]=var2;


			cpt1++;
		}
	}

	for (i = 0; i < s_len; ++i) {
		free(stops[i].n);
	}

	free(stops);
	free(routes);
	free(path);
	free(open);
	free(closed);
	//free(ind);
	//free(carte);
}