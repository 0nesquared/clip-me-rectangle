#include <utility.h>
#include <stdlib.h>

void addVertex(Vertex **list, int x, int y)
{
    Vertex *v = (Vertex *)malloc(sizeof(Vertex));

    v->x = x;
    v->y = y;
    v->next = NULL;

    if (*list == NULL)
    {
        *list = v;
        return;
    }

    Vertex *ptr = *list;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = v;
}

void freeMemory(Vertex *list)
{
    Vertex *temp;
    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp);
        temp = NULL;
    }
}

void freePolygonMemory(Polygon *list)
{
    Polygon *temp;
    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp);
        temp = NULL;
    }
}