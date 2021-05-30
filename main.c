#include <GL/glut.h>
#include <fileReader.h>
#include <polygonsClipper.h>
#include <utility.h>

// global variables to hold the file name and polygons information
char *filename;
Polygon *allPolygons;

void draw()
{
    Polygon *clipRectangle = allPolygons;

    int x_min = WIDTH + 1, x_max = -1, y_min = HEIGHT + 1, y_max = -1;

    // Drawing GL_LINE_LOOP for the clip rectangle
    glColor3f(clipRectangle->R, clipRectangle->G, clipRectangle->B);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < clipRectangle->n; i++)
    {
        glVertex2i(clipRectangle->x[i], clipRectangle->y[i]);
        x_min = clipRectangle->x[i] < x_min ? clipRectangle->x[i] : x_min;
        x_max = clipRectangle->x[i] > x_max ? clipRectangle->x[i] : x_max;
        y_min = clipRectangle->y[i] < y_min ? clipRectangle->y[i] : y_min;
        y_max = clipRectangle->y[i] > y_max ? clipRectangle->y[i] : y_max;
    }
    glEnd();
    glFlush();

    // Processing the polygons
    Polygon *processedPolygons = processPolygons(clipRectangle->next, x_min, x_max, y_min, y_max);

    Polygon *currentPolygon = processedPolygons;
    while (currentPolygon != NULL)
    {
        // Draw GL_LINE_LOOP for all vertices of each polygon
        glColor3f(currentPolygon->R, currentPolygon->G, currentPolygon->B);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < currentPolygon->n; i++)
        {
            glVertex2i(currentPolygon->x[i], currentPolygon->y[i]);
        }
        glEnd();
        glFlush();

        currentPolygon = currentPolygon->next;
    }

    freePolygonMemory(processedPolygons);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Please pass in the filename as a command-line argument!");
    }

    filename = argv[1];

    glutInit(&argc, argv);

    glutCreateWindow("Polygon Clipping Assignment");
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);

    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT); // To configure the window to correspond directly to the 1st quadrant

    // Get all polygons data
    allPolygons = getPolygons(filename);

    glutDisplayFunc(draw);

    glutMainLoop();
    return 0;
}
