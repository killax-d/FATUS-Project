#include "includes/collider.h"
#include <stdlib.h>

Collider * Collider_new() {
	Collider * collider = malloc(sizeof(Collider));
	Collider_reset(collider);
	return collider;
}

void Collider_reset(Collider * collider) {
	collider->UP = false;
	collider->RIGHT = false;
	collider->DOWN = false;
	collider->LEFT = false;
}