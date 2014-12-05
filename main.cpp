#include "mtdata.h" 

#define WINDOW_TITLE "MultiTouch Demo"

int        g_width = 600;
int        g_height = 400;
MultiTouch g_touch;

static void handleDisplay()
{

}

static void handleIdle()
{

}

static void handleKeypress(unsigned char key, int x, int y)
{
	switch(key) {
	case 27:
		g_touch.FreeSystem();
		exit(0);
		break;
	}
}

static void handleResize(int w, int h)
{
	if (h == 0) h = 1;
	if (w == 0) w = 1;

	width = w;
	height = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w/h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static int id = 0;
static int down = 0;

static void handleMouse(int button, int state, int x, int y
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			down = 1;
			g_touch.RecordStar(id, x, y);
			id++;
		} else if (state == GLUT_DOWN) {
			down = 0;
			g_touch.RecordFree(id);
			id--;
		}
	}
}

static void handleMotion(int x, int y)
{
	if (down) {
		g_touch.RecordData(id, x, y);
	}
}

void GL_Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void GL_Setup()
{
	glutDisplayFunc(handleDisplay);
	glutIdleFunc(handleIdle);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMouseFunc(handleMouse);
	glutMotionFunc(handleMotion);
}

int main(int argc, char *argv[])
{
	//initialize Touch System
	g_touch.InitSystem();

	//initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(g_width, g_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(WINDOW_TITLE);

	//initialize OpenGL
	GL_Init();

	//setup callback functions
	GL_Setup();

	//running man...
	glutMainLoop();

	return 0;
}