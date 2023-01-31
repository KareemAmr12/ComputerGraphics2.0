#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string>


#define BODY_WIDTH 2
#define BODY_HEIGHT 4
#define BODY_DEPTH 1

#define WIN_X 100
#define WIN_Y 100
#define WIN_W 320
#define WIN_H 320

static int shoulderAngle = 0, elbowAngle = 0;
static int UpperLegAngle = 0, LowerLegAngle = 0;

int ArmXangle = 0;
int ArmYangle = 0;
int ArmZangle = 1;

int LegXangle = 1;
int LegYangle = 0;
int LegZangle = 0;


float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 5.0f;

//Color variables for robot parts
float red = 0.0f, blue = 0.0f, green = 1.0f;

//Color Variables for floor
float FloorR = 0.8f, FloorB = 0.8f, FloorG = 0.8f;


bool viewAxis = true;
bool viewSolid = true;
bool viewWire = false;
bool ActivateEaster = false; //boolen to activate the bonus work
bool DoOnce = false; //boolen to reset scene after deactivating the easteregg

//variables to generate random X and Y points to spawn the robots
float randomX[12]; 
float randomZ[12];

float angle = 0;

//Font used in the text
void* m_glutFont = GLUT_BITMAP_TIMES_ROMAN_24;


//function to draw text on the screen
void drawText(const std::string& text, const unsigned int x, const unsigned int y, const float r, const float g, const float b)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, WIN_W, 0, WIN_H, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(r, g, b);
	glRasterPos2i(x, y);
	for (const char c : text)
		glutBitmapCharacter(m_glutFont, (int)c);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


//function to display extra work (making a robot party)
void EasterEgg()
{
	srand(time(NULL));
	if (ActivateEaster)
	{

		//generating random colors for the robots and the floor
		red = (float)rand() / (float)RAND_MAX;
		blue = (float)rand() / (float)RAND_MAX;
		green = (float)rand() / (float)RAND_MAX;
		FloorR = (float)rand() / (float)RAND_MAX;
		FloorB = (float)rand() / (float)RAND_MAX;
		FloorG = (float)rand() / (float)RAND_MAX;


		//changing the orientation of the joints rotation 
		ArmXangle = 0;
		ArmYangle = 1;
		ArmZangle = 0;

		LegXangle = 0;
		LegYangle = 0;
		LegZangle = 1;


		//Making the robots joints spin
		(elbowAngle += 1) %= 360;
		(shoulderAngle += 1) %= 360;
		(UpperLegAngle += 1) %= 360;
		(LowerLegAngle += 1) %= 360;

		std::string name;
		name = "PARTY!!!";
		drawText(name.data(), WIN_W / 2 - name.size() , WIN_H / 2 , (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);

		DoOnce = true;
	}
	else
	{

		//reseting after easteregg is done
		if (DoOnce)
		{
			elbowAngle = 0;
			shoulderAngle = 0;
			UpperLegAngle = 0;
			LowerLegAngle = 0;
			DoOnce = false;
		}
	red = 0.0;
	blue = 0.0;
	green = 1.0;
	FloorR = 0.8f;
	FloorB = 0.8f;
	FloorG = 0.8f;

	ArmXangle = 0;
	ArmYangle = 0;
	ArmZangle = 1;

	LegXangle = 1;
	LegYangle = 0;
	LegZangle = 0;
	}
}

void randomXY()
{
	//generating random locations for the robots
	srand(time(NULL));
	for (int i = 0; i < 12; i++)
	{
		randomX[i] = rand() % 15;
		randomZ[i] = rand() % 15;
	}
}
// Handles the keyboard event: left and right arrows bend the elbow, the
// up and down keys bend the shoulder.
void special(int key, int, int)
{
	float fraction = 0.1f;
	switch (key)
	{
		case GLUT_KEY_F4: (elbowAngle -= 5) %= 360; break;
		case GLUT_KEY_F5: (shoulderAngle -= 5) %= 360; break;
		case GLUT_KEY_F6: (UpperLegAngle -= 5) %= 360; break;
		case GLUT_KEY_F7: (LowerLegAngle -= 5) %= 360; break;
		case GLUT_KEY_LEFT:
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT:
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP:
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN:
			x -= lx * fraction;
			z -= lz * fraction;
			break;
		case GLUT_KEY_END: exit(0); break;
		defualt: return;
	}
	glutPostRedisplay();
}


void wireBox(GLdouble width, GLdouble height, GLdouble depth)
{
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(width, height, depth);
	glutWireCube(1.0);
	glPopMatrix();
}

void wire_head()
{
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.0, 2.75, 0.0);
	glScalef(1.5, 1.5, 1.5);
	glutWireSphere(0.5, 20, 20);
	glPopMatrix();
}

void solidBox(GLdouble width, GLdouble height, GLdouble depth)
{
	glPushMatrix();
	glColor3f(red, green, blue);
	glScalef(width, height, depth);
	glutSolidCube(1.0);
	glPopMatrix();
}

void solid_head()
{
	glPushMatrix();
	glColor3f(red, green, blue);
	glTranslatef(0.0, 2.75, 0.0);
	glScalef(1.5, 1.5, 1.5);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();
}

void drawAxes() 
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(5, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 5, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 5);
	glEnd();
}

void drawWire()
{
	wire_head();
	glPushMatrix();
	wireBox(BODY_WIDTH, BODY_HEIGHT, BODY_DEPTH);
	glPopMatrix();
	

	// Draw right arm
	glPushMatrix();
	glTranslatef(1.0, 1.5, 0.0); 
	glRotatef((GLfloat)shoulderAngle, 0.0, 0.0, 1.0); 
	glTranslatef(1.0, 0.0, 0.0);
	wireBox(2.0, 0.4, 1.0); 


	glTranslatef(1.0, 0.0, 0.0); 
	glRotatef((GLfloat)elbowAngle, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0); 
	wireBox(2.0, 0.4, 1.0); 
	glPopMatrix();
	
	//Draw left arm
	glPushMatrix();
	glTranslatef(-1.0, 1.5, 0.0); 
	glRotatef(-(GLfloat)shoulderAngle, 0.0, 0.0, 1.0); 
	glTranslatef(-1.0, 0.0, 0.0); 
	wireBox(2.0, 0.4, 1.0); 

	glTranslatef(-1.0, 0.0, 0.0); 
	glRotatef(-(GLfloat)elbowAngle, 0.0, 0.0, 1.0); 
	glTranslatef(-1.0, 0.0, 0.0); 
	wireBox(2.0, 0.4, 1.0);
	glPopMatrix();

	//Draw right leg
	glPushMatrix();
	glTranslatef(0.5, -2.25, 0.0);
	glRotatef((GLfloat)UpperLegAngle, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);
	wireBox(0.5, 2.5, 1.0);


	glTranslatef(0, -1.5, 0.0);
	glRotatef((GLfloat)LowerLegAngle, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);
	wireBox(0.5, 2.5, 1.0);
	glPopMatrix();

	//Draw left leg
	glPushMatrix();
	glTranslatef(-0.5, -2.25, 0.0);
	glRotatef((GLfloat)UpperLegAngle, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);
	wireBox(0.5, 2.5, 1.0);


	glTranslatef(0, -1.5, 0.0);
	glRotatef((GLfloat)LowerLegAngle, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);
	wireBox(0.5, 2.5, 1.0);
	glPopMatrix();

	
}


void drawSolid()
{

	solid_head();
	glPushMatrix();
	solidBox(BODY_WIDTH, BODY_HEIGHT, BODY_DEPTH);
	glPopMatrix();


	// Draw right arm
	glPushMatrix();
	glTranslatef(1.0, 1.5, 0.0);
	glRotatef((GLfloat)shoulderAngle, ArmXangle, ArmYangle, ArmZangle);
	glTranslatef(1.0, 0.0, 0.0);
	solidBox(2.0, 0.4, 1.0);


	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbowAngle, ArmXangle, ArmYangle, ArmZangle);
	glTranslatef(1.0, 0.0, 0.0);
	solidBox(2.0, 0.4, 1.0);
	glPopMatrix();

	//Draw left arm
	glPushMatrix();
	glTranslatef(-1.0, 1.5, 0.0);
	glRotatef(-(GLfloat)shoulderAngle, ArmXangle, ArmYangle, ArmZangle);
	glTranslatef(-1.0, 0.0, 0.0);
	solidBox(2.0, 0.4, 1.0);

	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef(-(GLfloat)elbowAngle, ArmXangle, ArmYangle, ArmZangle);
	glTranslatef(-1.0, 0.0, 0.0);
	solidBox(2.0, 0.4, 1.0);
	glPopMatrix();

	//Draw right leg
	glPushMatrix();
	glTranslatef(0.5, -2.25, 0.0);
	glRotatef((GLfloat)UpperLegAngle, LegXangle, LegYangle, LegZangle);
	glTranslatef(0.0, -1.0, 0.0);
	solidBox(0.5, 2.5, 1.0);


	glTranslatef(0, -1, 0.0);
	glRotatef((GLfloat)LowerLegAngle, LegXangle, LegYangle, LegZangle);
	glTranslatef(0.0, -1.0, 0.0);
	solidBox(0.5, 2.5, 1.0);
	glPopMatrix();

	//Draw left leg
	glPushMatrix();
	glTranslatef(-0.5, -2.25, 0.0);
	glRotatef((GLfloat)UpperLegAngle, LegXangle, LegYangle, LegZangle);
	glTranslatef(0.0, -1.0, 0.0);
	solidBox(0.5, 2.5, 1.0);


	glTranslatef(0, -1, 0.0);
	glRotatef((GLfloat)LowerLegAngle, LegXangle, LegYangle, LegZangle);
	glTranslatef(0.0, -1.0, 0.0);
	solidBox(0.5, 2.5, 1.0);
	glPopMatrix();

	
}


void display()
{
	EasterEgg();
	if (viewSolid)
	{
		drawSolid();
	}
	if (viewWire)
	{
		drawWire();
	}
	
	
	if (viewAxis)
	{
		drawAxes();
	}
	

}

void reshape(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can't make a window of zero width).
	if (h == 0) h = 1;
	float ratio = w * 1.0 / h;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the correct perspective
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// Get back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void procKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
		case '1':
			viewSolid = false;
			viewWire = true;
			break;
		case '2':
			viewSolid = true;
			viewWire = false;
			break;
		case '3':
			viewAxis = !viewAxis;
			break;
		case '4':
			(elbowAngle += 5) %= 360;
			break;
		case '5':
			(shoulderAngle += 5) %= 360;
			break;
		case '6':
			(UpperLegAngle += 5) %= 360;
			break;
		case '7':
			(LowerLegAngle += 5) %= 360;
			break;
		case 'e':
			ActivateEaster = !ActivateEaster;
			viewWire = false;
			viewSolid = true;
			viewAxis = false;
			
			break;
		case 27:
			exit(0);
			break;
	}
	glutPostRedisplay();
}

void renderScene(void)
{
	// Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);
	// Draw the ground (a plane)
	glColor3f(FloorR, FloorG, FloorB);
	
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, -7.0f, -100.f);
	glVertex3f(-100.0f, -7.0f, 100.f);
	glVertex3f(100.0f, -7.0f, 100.f);
	glVertex3f(100.0f, -7.0f, -100.f);
	glEnd();
	
	// Draw 11 random robots
	for (int i = 0; i < 12; i++)
		{
			
			glPushMatrix();
			glTranslatef(i*randomX[i] , 0, i * randomZ[i]);
			display();
			glPopMatrix();
		}
	
	glutSwapBuffers(); // For double buffer display
}




int main(int argc, char** argv)
{
	randomXY();
	printf("\n\
----------------------------------------------------------------------------\n\
Key Instructions:\n\
- '1': display a wireframe (mesh only) model  \n\
- '2': display a solid model   \n\
- '3': toggle on/off to draw axes \n\
- '4' : increase the elbow angle by 5 degrees for both arms (the left and right arms)  \n\
- 'F4' : decrease the elbow angle by 5 degrees for both arms (the left and right arms)  \n\
- '5' : increase the shoulder angle by 5 degrees for both arms (the left and right arms)  \n\
- 'F5' : decrease the shoulder angle by 5 degrees for both arms (left and right arms)  \n\
- '6': increase the angles of the upper leg joints by 5 degrees for both legs \n\
- 'F6': decrease the angles of the upper leg joints by 5 degrees for both legs \n\
- '7': increase the angles of the lower leg joints by 5 degrees for both legs  \n\
- 'F7': decrease the angles of the lower leg joints by 5 degrees for both legs \n\
- 'e': toggle on/off EasterEgg \n\
- ESC to quit \n\
----------------------------------------------------------------------------\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowPosition(WIN_X, WIN_Y);
	glutInitWindowSize(WIN_W, WIN_H);
	glutCreateWindow("(Karim Amr Mohamed Talaat Mohamed Hassan) (811238841)");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(procKeys);
	glutSpecialFunc(special);
	
	glEnable(GL_DEPTH_TEST); // Enable hidden surface removal

	glutMainLoop();
	return 0;
}