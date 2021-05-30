#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <polygonsClipper.h>
#include <utility.h>

Polygon *processPolygons(Polygon *allPolygons, int x_min, int x_max, int y_min, int y_max)
{
    Polygon *processedPolygons = (Polygon *)malloc(sizeof(Polygon));
    processedPolygons->n = 0; // to signal that this is the head at the moment

    Polygon *currentPolygon = allPolygons;
    while (currentPolygon != NULL)
    {
        Vertex *leftClipped = NULL;

        // FOR THE LEFT EDGE OF THE CLIP RECTANGLE

        // Traversing edge-wise from (x1, y1) to (x2, y2)
        for (int i = 0; i < currentPolygon->n; i++)
        {
            int x1, y1, x2, y2;
            x1 = currentPolygon->x[i];
            y1 = currentPolygon->y[i];
            if (i == currentPolygon->n - 1)
            {
                // Deal with the edge between the last and the 1st vertex here
                x2 = currentPolygon->x[0];
                y2 = currentPolygon->y[0];
            }
            else
            {
                // Deal with the edge between the i'th and the (i + 1)'th vertex here
                x2 = currentPolygon->x[i + 1];
                y2 = currentPolygon->y[i + 1];
            }

            //            printf("Edge from (%d, %d) to (%d, %d)\n", x1, y1, x2, y2);

            // If the first point is inside, add it
            if (x1 >= x_min)
            {
                addVertex(&leftClipped, x1, y1);
                // if the second point is outside, add the intersection
                if (x2 < x_min)
                {
                    float t = -(float)(x1 - x_min) / (x2 - x1);
                    addVertex(&leftClipped, x_min, y1 + (int)(t * (y2 - y1)));
                }
            }
            else // first point is outside
            {
                // if the second point is inside, add the intersection
                if (x2 >= x_min)
                {
                    float t = -(float)(x1 - x_min) / (x2 - x1);
                    addVertex(&leftClipped, x_min, y1 + (int)(t * (y2 - y1)));
                }
            }
        }

        // FOR THE RIGHT EDGE OF THE CLIP RECTANGLE

        Vertex *rightClipped = NULL;

        // Now for traversing the edges, we need to actually traverse the linked list
        // Storing the 1st vertex
        Vertex *first = leftClipped;

        Vertex *v1 = leftClipped;
        Vertex *v2 = leftClipped->next;

        while (v2 != NULL)
        {
            // If the first point is inside, add it
            if (v1->x <= x_max)
            {
                addVertex(&rightClipped, v1->x, v1->y);
                // if the second point is outside, add the intersection
                if (v2->x > x_max)
                {
                    float t = -(float)(v1->x - x_max) / (v2->x - v1->x);
                    addVertex(&rightClipped, x_max, v1->y + (int)(t * (v2->y - v1->y)));
                }
            }
            else // first point is outside
            {
                // if the second point is inside, add the intersection
                if (v2->x <= x_max)
                {
                    float t = -(float)(v1->x - x_max) / (v2->x - v1->x);
                    addVertex(&rightClipped, x_max, v1->y + (int)(t * (v2->y - v1->y)));
                }
            }

            v1 = v1->next;
            v2 = v2->next;
        }

        // Handling the edge between the last and the first point separately
        v2 = first;
        // If the first point is inside, add it
        if (v1->x <= x_max)
        {
            addVertex(&rightClipped, v1->x, v1->y);
            // if the second point is outside, add the intersection
            if (v2->x > x_max)
            {
                float t = -(float)(v1->x - x_max) / (v2->x - v1->x);
                addVertex(&rightClipped, x_max, v1->y + (int)(t * (v2->y - v1->y)));
            }
        }
        else // first point is outside
        {
            // if the second point is inside, add the intersection
            if (v2->x <= x_max)
            {
                float t = -(float)(v1->x - x_max) / (v2->x - v1->x);
                addVertex(&rightClipped, x_max, v1->y + (int)(t * (v2->y - v1->y)));
            }
        }

        // WRT BOTTOM EDGE
        Vertex *bottomClipped = NULL;

        // Now for traversing the edges, we need to actually traverse the linked list
        // Storing the 1st vertex
        first = rightClipped;

        v1 = rightClipped;
        v2 = rightClipped->next;

        while (v2 != NULL)
        {
            // If the first point is inside, add it
            if (v1->y >= y_min)
            {
                addVertex(&bottomClipped, v1->x, v1->y);
                // if the second point is outside, add the intersection
                if (v2->y < y_min)
                {
                    float t = -(float)(v1->y - y_min) / (v2->y - v1->y);
                    addVertex(&bottomClipped, v1->x + (int)(t * (v2->x - v1->x)), y_min);
                }
            }
            else // first point is outside
            {
                // if the second point is inside, add the intersection
                if (v2->y >= y_min)
                {
                    float t = -(float)(v1->y - y_min) / (v2->y - v1->y);
                    addVertex(&bottomClipped, v1->x + (int)(t * (v2->x - v1->x)), y_min);
                }
            }

            v1 = v1->next;
            v2 = v2->next;
        }

        // Handling the edge between the last and the first point separately
        v2 = first;

        // If the first point is inside, add it
        if (v1->y >= y_min)
        {
            addVertex(&bottomClipped, v1->x, v1->y);
            // if the second point is outside, add the intersection
            if (v2->y < y_min)
            {
                float t = -(float)(v1->y - y_min) / (v2->y - v1->y);
                addVertex(&bottomClipped, v1->x + (int)(t * (v2->x - v1->x)), y_min);
            }
        }
        else // first point is outside
        {
            // if the second point is inside, add the intersection
            if (v2->y >= y_min)
            {
                float t = -(float)(v1->y - y_min) / (v2->y - v1->y);
                addVertex(&bottomClipped, v1->x + (int)(t * (v2->x - v1->x)), y_min);
            }
        }

        // WRT TOP EDGE
        Vertex *topClipped = NULL;

        // Now for traversing the edges, we need to actually traverse the linked list
        // Storing the 1st vertex
        first = bottomClipped;

        v1 = bottomClipped;
        // Add the case of bottomClipped->next == NULL here
        v2 = bottomClipped->next;

        while (v2 != NULL)
        {
            // If the first point is inside, add it
            if (v1->y <= y_max)
            {
                addVertex(&topClipped, v1->x, v1->y);
                // if the second point is outside, add the intersection
                if (v2->y > y_max)
                {
                    float t = -(float)(v1->y - y_max) / (v2->y - v1->y);
                    addVertex(&topClipped, v1->x + (int)(t * (v2->x - v1->x)), y_max);
                }
            }
            else // first point is outside
            {
                // if the second point is inside, add the intersection
                if (v2->y <= y_max)
                {
                    float t = -(float)(v1->y - y_max) / (v2->y - v1->y);
                    addVertex(&topClipped, v1->x + (int)(t * (v2->x - v1->x)), y_max);
                }
            }

            v1 = v1->next;
            v2 = v2->next;
        }

        // Handling the edge between the last and the first point separately
        v2 = first;

        // If the first point is inside, add it
        if (v1->y <= y_max)
        {
            addVertex(&topClipped, v1->x, v1->y);
            // if the second point is outside, add the intersection
            if (v2->y > y_max)
            {
                float t = -(float)(v1->y - y_max) / (v2->y - v1->y);
                addVertex(&topClipped, v1->x + (int)(t * (v2->x - v1->x)), y_max);
            }
        }
        else // first point is outside
        {
            // if the second point is inside, add the intersection
            if (v2->y <= y_max)
            {
                float t = -(float)(v1->y - y_max) / (v2->y - v1->y);
                addVertex(&topClipped, v1->x + (int)(t * (v2->x - v1->x)), y_max);
            }
        }

        // Inserting the finally clipped polygon in the processedPolygons linked list

        Polygon *toInsert = (Polygon *)malloc(sizeof(Polygon));
        int n = 0;
        Vertex *counter = topClipped;
        while (counter != NULL)
        {
            n++;
            counter = counter->next;
        }

        toInsert->n = n;
        toInsert->R = currentPolygon->R;
        toInsert->G = currentPolygon->G;
        toInsert->B = currentPolygon->B;

        // Dynamically allocating memory to store the vertices
        toInsert->x = (int *)malloc(sizeof(int) * toInsert->n);
        toInsert->y = (int *)malloc(sizeof(int) * toInsert->n);

        counter = topClipped;
        for (int i = 0; i < toInsert->n; i++)
        {
            toInsert->x[i] = counter->x;
            toInsert->y[i] = counter->y;
            counter = counter->next;
        }

        // Adding the polygon at the beginning and setting the pointers correctly
        if (processedPolygons->n == 0)
        {
            toInsert->next = NULL;
            processedPolygons = toInsert;
        }
        else
        {
            toInsert->next = processedPolygons;
            processedPolygons = toInsert;
        }

        freeMemory(leftClipped);
        freeMemory(rightClipped);
        freeMemory(bottomClipped);
        freeMemory(topClipped);

        currentPolygon = currentPolygon->next;
    }

    return processedPolygons;
}