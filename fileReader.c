#include <fileReader.h>
#include <stdlib.h>

Polygon *getPolygons(char *filename)
{
    Polygon *allPolygons = (Polygon *)malloc(sizeof(Polygon));

    allPolygons->n = 0; // to signal that the list is empty at the moment

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error reading the data file!");
        return NULL;
    }

    char info[128];
    while (fgets(info, 128, file) != NULL)
    {
        if (info[0] == '#' || info[0] == ' ' || info[0] == '\n')
        {
            continue;
        }

        Polygon *nextPolygon = (Polygon *)malloc(sizeof(Polygon));

        if (sscanf(info, "%d  %f %f %f", &nextPolygon->n, &nextPolygon->R, &nextPolygon->G, &nextPolygon->B) != 4)
        {
            printf("Error reading the polygon information!");
            return NULL;
        }

        char vertices[64];

        // Dynamically allocating memory to store the vertices
        nextPolygon->x = (int *)malloc(sizeof(int) * nextPolygon->n);
        nextPolygon->y = (int *)malloc(sizeof(int) * nextPolygon->n);

        for (int i = 0; i < nextPolygon->n; i++)
        {
            if (fgets(vertices, 64, file) != NULL)
            {
                if (sscanf(vertices, "%d %d", &nextPolygon->x[i], &nextPolygon->y[i]) != 2)
                {
                    printf("Error reading some vertices from the file!");
                    return NULL;
                }
            }
        }

        // Adding the polygon at the beginning and setting the pointers correctly
        if (allPolygons->n == 0)
        {
            nextPolygon->next = NULL;
            allPolygons = nextPolygon;
        }
        else
        {
            nextPolygon->next = allPolygons;
            allPolygons = nextPolygon;
        }
    }

    fclose(file);

    return allPolygons;
}