// Cohen-Suderland Line Clipping Algorithm with Window to viewport Mapping */
#include <stdio.h>
#include <GL/glut.h>
#include <stdbool.h> //imp

double xmin=50,ymin=50, xmax=100,ymax=100;
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;

const int RIGHT = 8;
const int LEFT = 2;
const int TOP = 4;
const int BOTTOM = 1;

int x0, x1, y0, y1;

int ComputeOutCode (double x, double y);

void CohenSutherlandLineClipAndDraw (double x0, double y0,double x1, double y1)
{
int outcode0, outcode1, outcodeOut;
bool accept = false, done = false;
outcode0 = ComputeOutCode (x0, y0);
outcode1 = ComputeOutCode (x1, y1);

do
{
	if (!(outcode0 | outcode1)) //completely inside
	{
		accept = true;
		done = true;
	}
	else if (outcode0 & outcode1) //logical and is not 0. Trivially reject and exit
		done = true;
	else
	{
			double x, y;
			outcodeOut = outcode0 ? outcode0: outcode1; // choose the outside end point  != 0

			// we know that one endpoint is outside but we don't know in which side
			if (outcodeOut & TOP)
			{
				x = x0 + (x1 - x0) * (ymax - y0)/(y1 - y0);
				y = ymax;
			}
			else if (outcodeOut & BOTTOM) //point is below the clip rectangle
			{
				x = x0 + (x1 - x0) * (ymin - y0)/(y1 - y0);
				y = ymin;
			}
			else if (outcodeOut & RIGHT) //point is to the right of clip rectangle
			{
				y = y0 + (y1 - y0) * (xmax - x0)/(x1 - x0);
				x = xmax;
			}
			else
			{
				y = y0 + (y1 - y0) * (xmin - x0)/(x1 - x0);
				x = xmin;
			}


			if(outcodeOut == outcode0)
			{
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode(x0, y0);
			}
			else
			{
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode(x1, y1);
			}
		}

} while (!done);


if (accept)
{
	//calculate the scale factor ( the size difference between both squares )
	double sx=(xvmax-xvmin)/(xmax-xmin);
	double sy=(yvmax-yvmin)/(ymax-ymin);


/*find the new coordinates that  match the new square considering the older scale
of the previous square example
x0-xmin will give how far was x0 from the left side of the older square so we set the same in
the new square. multiplying by sx is the scale factor because the new square might be bigger or smaller than the orginal square
*/
	double vx0=xvmin+(x0-xmin)*sx;
	double vy0=yvmin+(y0-ymin)*sy;
	double vx1=xvmin+(x1-xmin)*sx;
	double vy1=yvmin+(y1-ymin)*sy;

	glColor3f(1.0, 0.0, 0.0);
	//to draw the new square
	glBegin(GL_LINE_LOOP);
	glVertex2f(xvmin, yvmin);
	glVertex2f(xvmax, yvmin);
	glVertex2f(xvmax, yvmax);
	glVertex2f(xvmin, yvmax);
	glEnd();
	glColor3f(0.0,0.0,1.0); // draw blue colored clipped line

	// to draw the clipped line inside the new square 
	glBegin(GL_LINES);
	glVertex2d (vx0, vy0);
	glVertex2d (vx1, vy1);
	glEnd();
}
}


int ComputeOutCode (double x, double y)
{
	int code = 0;
	if (y > ymax)
	code |= TOP;
	else if (y < ymin)
	code |= BOTTOM;
	if (x > xmax)
	code |= RIGHT;
	else if (x < xmin)
	code |= LEFT;

	return code;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d (x0, y0);
	glVertex2d (x1, y1);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();
	CohenSutherlandLineClipAndDraw(x0,y0,x1,y1);
	glFlush();
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}

void main(int argc, char** argv)
{

	printf("Enter End points:");
	scanf("%d%d%d%d", &x0,&y0,&x1,&y1);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cohen Suderland Line Clipping Algorithm");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}


/*

Step 1 : Assign a region code for two endpoints of given line.
Step 2 : If both endpoints have a region code 0000
         then given line is completely inside.
Step 3 : Else, perform the logical AND operation for both region codes.
    Step 3.1 : If the result is not 0000, then given line is completely
               outside.
    Step 3.2 : Else line is partially inside.
        Step 3.2.1 : Choose an endpoint of the line
                     that is outside the given rectangle.
        Step 3.2.2 : Find the intersection point of the
                     rectangular boundary (based on region code).
        Step 3.2.3 : Replace endpoint with the intersection point
                     and update the region code.
        Step 3.2.4 : Repeat step 2 until we find a clipped line either
                     trivially accepted or trivially rejected.
Step 4 : Repeat step 1 for other lines
*/
