#ifndef structs_H
#define structs_H

#define HEIGHT 750
#define WIDTH 750

// Structure to store the polygon information
typedef struct polygon
{
    /* 
    - This structure is created in accordance with the format of the data specified in the .dat files.
    */

    int n;   // the number of vertices
    float R; // value corresponding to the Red color component
    float G; // value corresponding to the Green color component
    float B; // value corresponding to the Blue color component
    int *x;  // array to store the x-coordinates of the vertices
    int *y;  // array to store the y-coordinates of the vertices

    struct polygon *next; // pointer to the next polygon

} Polygon;

// Structure to store a vertex information
typedef struct vertex
{
    int x;
    int y;

    struct vertex *next;
} Vertex;

#endif