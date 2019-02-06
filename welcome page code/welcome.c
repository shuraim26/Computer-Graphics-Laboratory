
//g++ welcome.c -o l -lGL -lGLU -lglut

#include <GL/glut.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
void init (void)
{
	glClearColor (0.0 ,0.1, 0.0,1.0); // White display window.
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 600.0, 0.0, 500.0);
}

char line1[100] = {"college name"};
char line2[100] = {"Computer science department"};
char line3[100] = {"Computer Graphics project"};
char line4[100] = {"project name"};
char line5[100] = {"student name	 : usn"};
char line6[100] = {"student name     : usn"};
char line7[100] = {"project page"};


void displayText( float x, float y, int r, int g, int b, const char *string ) {
	int j = strlen (string);
	glColor3f( r, g, b );
	glRasterPos2f( x, y );
	for( int i = 0; i < j; i++ )
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
glFlush ( );

}

void displayfirst(void){
  displayText(350, 450, 0, 0, 1,line1);
  displayText(350, 400, 1, 1, 1,line2);
  displayText(350, 350, 1, 1, 1,line3);
  displayText(80, 150, 1, 1, 1,line4);
  displayText(80, 100,1, 1, 1,line5);
  displayText(80, 50, 1, 1, 1,line6);

}

void keys(unsigned char key, int x, int y)
{

if(key == '1') {

  glClear (GL_COLOR_BUFFER_BIT);
  displayfirst();
	}

if(key == '2') {
glClear (GL_COLOR_BUFFER_BIT);
displayText(250, 400, 1, 1, 1,line7);

}


}
void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ( );
	gluOrtho2D (0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
	glClear (GL_COLOR_BUFFER_BIT);

}

main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (1000, 500);
	glutCreateWindow ("Line Chart Data Plot");
	init ( );
	glutDisplayFunc (displayfirst);
	glutKeyboardFunc(keys);
	glutReshapeFunc (winReshapeFcn);
	glutMainLoop ( );
}
