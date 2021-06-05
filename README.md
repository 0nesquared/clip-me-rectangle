# clip-me-rectangle
Implementation of the Sutherland Polygon Clipping for any convex polygon, and a clip rectangle.

To compile the code and create the runnable files, one needs to type the command **make** in the terminal with the file directory open.
And to run, one just needs to type the command **make run** 
The data file needs to have the clip rectangle as the last entry in order to work.
Besides, the freeglut packages should already be installed in the system beforehand.

To run the program for a different data file, one can just change the __FILENAME__ parameter value in the Makefile.

To delete the output files generated, one can run the command **make clean**

Attached below is the screenshot for the given data file - 

![Screenshot from 2021-06-06 02-25-17](https://user-images.githubusercontent.com/73273781/120905407-7f0a8f00-c66f-11eb-90a0-a1c7f403cab2.png)

The clip rectangle is marked in green, and all the other polygons have been clipped according to the boundary of this rectangle.
