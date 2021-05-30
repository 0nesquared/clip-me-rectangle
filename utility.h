#ifndef utility_H
#define utility_H

#include <structs.h>

void addVertex(Vertex **list, int x, int y);

void freeMemory(Vertex *list);

void freePolygonMemory(Polygon *list);

#endif