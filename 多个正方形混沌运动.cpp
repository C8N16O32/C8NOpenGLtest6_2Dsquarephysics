// 多个正方形混沌运动.cpp : 定义控制台应用程序的入口点。
//
#ifndef GLUT_DISABLE_ATEXIT_HACK  
#define GLUT_DISABLE_ATEXIT_HACK 
#endif
#include<windows.h>
#include"stdafx.h"
#include "math.h"
#include"gl/glut.h"
/*方块*/
struct __OBJECTS__ objects[On] = { 0 };
/*计算正方形四个顶点*/
void obj_cal(struct __OBJECTS__ *p,int n, GLfloat *x, GLfloat *y) {
	double cx = (p + n)->phy.x, cy = (p + n)->phy.y, a = (p + n)->phy.a, mod = sqrt(2) / 2.0 * Osize;
	int i = 0; for (i = 0; i < 4; i++) { 
		*(x + i) = cx + mod*cos(a + PI / 2 * i + PI / 4);
		*(y + i) = cy + mod*sin(a + PI / 2 * i + PI / 4);
	}
}
/*画图主程序*/
void obj_print(void) {
	int i = 0, n = 0;
	GLfloat x[4], y[4];
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (n = 0; n < On; n++) {
		if (n == lognum)glColor3f(0.5,0.25, 0.15);
		else glColor3f(0, 0, 0);
		obj_cal(objects, n, x, y);//计算顶点
		glBegin(GL_POLYGON); 
		for (i = 0; i < 4; i++)glVertex2f((x[i]-10)/11.0, (y[i]+5)/11.0);//指定多边形的顶点
		glEnd(); 
	}
	glFlush();
	glutSwapBuffers();
}
/*进行运算以更新数值*/
void physical(void) {
	physical_main(objects, 0.05);
	obj_print();
}
/*快速初始化*/
void fastset_flat(struct __OBJECTS__ *p) {
	(p + 2)->phy.vx = 37;
	(p + 2)->phy.vy = -37;
	int i; for (i = 0; i < On; i++) {
		(p + i)->phy.x = i % 15 * 1.3;
		(p + i)->phy.y = -i / 15 * 1.3 + i % 15 * 0.1;
		(p + i)->phy.a = -i*0.005;
	}
	(p + 2)->phy.x -= 60;
	(p + 2)->phy.y += 60;
}
int main(int argc, char *argv[]) {
	int f = 0;
	glutInit(&argc, argv);
	if (f == 0) { fastset_flat(objects); f = 1; }
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(400, 400);
	glutCreateWindow("test v1.5");
	glutDisplayFunc(&obj_print);
	glutIdleFunc(&physical);
	glutMainLoop();
	return 0;
}