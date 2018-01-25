#include "std.h"
#include "Game.h"

void onDisplay();
void onUpdate();
void myMouse(int button, int state, int x, int y);
void 	MyInit();
Game *p = new Game();

int main(int argc, char*  argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("五子棋Ai");
	glutDisplayFunc(&onDisplay);
	glutIdleFunc(onUpdate);
	glutMouseFunc(myMouse);
	MyInit();
	glutMainLoop();
	return 0;
}

void onDisplay()
{
	p->onDisplay();
}

void onUpdate()
{
	p->onUpdate();
	p->onDisplay();
	glutSwapBuffers();
}

void myMouse(int button, int state, int x, int y)
{
	p->myMouse(button, state, x, y);
	onUpdate();
}

void 	MyInit()
{
	glClearColor(1, 1.0 * 153 / 256, 0, 1.0);//背景颜色
	gluOrtho2D(0.0, WINDOW_SIZE, 0.0, WINDOW_SIZE);//设置缩放比,建立坐标系
}