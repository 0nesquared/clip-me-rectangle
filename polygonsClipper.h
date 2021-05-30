#ifndef polygonsclipper_h
#define polygonsclipper_h

#include <structs.h>

// Function to return the linked list of the polygons whose vertices have been clipped
Polygon *processPolygons(Polygon *allPolygons, int x_min, int x_max, int y_min, int y_max);

#endif