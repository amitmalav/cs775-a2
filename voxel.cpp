#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Algebra3.hpp"
#include <vector>
using namespace std;
#define TIMELIMIT 50.0
#define EXPL_AMNNT 1000000
#define VOXUNIT 0.2
#define SCREENSIZE 20
bool start_explosion= false;

class Voxel{
public:
	int count;
	Voxel(){count =0;}
};

class Explosion{
public:
	Vec3 color;
	Vec3 extremeColor;
	Voxel voxels[int(SCREENSIZE/VOXUNIT)][int(SCREENSIZE/VOXUNIT)][int(SCREENSIZE/VOXUNIT)];
	Explosion(){

		for (int i1 = 1; i1 < SCREENSIZE/VOXUNIT - 1; ++i1)
		{
			for (int i2 = 1; i2 < SCREENSIZE/VOXUNIT - 1; ++i2)
			{
				for (int i3 = 1; i3 < SCREENSIZE/VOXUNIT - 1; ++i3)
				{
					voxels[i1][i2][i3].count = 0;
				}
			}
		}
		voxels[int(SCREENSIZE/(2*VOXUNIT))][int(SCREENSIZE/(2*VOXUNIT))][int(SCREENSIZE/(2*VOXUNIT))].count = EXPL_AMNNT;
		extremeColor = Vec3(251,23,23);
		color = Vec3(255,0,0);
	}
	void update(float t){
		if (!start_explosion)
		{
			return;
		}
		int new_voxels[int(SCREENSIZE/VOXUNIT)][int(SCREENSIZE/VOXUNIT)][int(SCREENSIZE/VOXUNIT)];
		for (int i1 = 1; i1 < SCREENSIZE/VOXUNIT - 1; ++i1)
		{
			for (int i2 = 1; i2 < SCREENSIZE/VOXUNIT - 1; ++i2)
			{
				for (int i3 = 1; i3 < SCREENSIZE/VOXUNIT - 1; ++i3)
				{
					if (voxels[i1][i2][i3].count< 0)
					{
						cout<<"error"<<endl;
					}
					new_voxels[i1][i2][i3] = (voxels[i1-1][i2][i3].count+voxels[i1+1][i2][i3].count+voxels[i1][i2+1][i3].count+voxels[i1][i2-1][i3].count+voxels[i1][i2][i3+1].count+voxels[i1][i2][i3-1].count+voxels[i1][i2][i3].count) / 7;
				}
			}
		}
		for (int i1 = 1; i1 < SCREENSIZE/VOXUNIT - 1; ++i1)
		{
			for (int i2 = 1; i2 < SCREENSIZE/VOXUNIT - 1; ++i2)
			{
				for (int i3 = 1; i3 < SCREENSIZE/VOXUNIT - 1; ++i3)
				{
					voxels[i1][i2][i3].count = new_voxels[i1][i2][i3];
				}
			}
		}
	}
	void render(){
		glPushMatrix();
		glDisable (GL_LIGHTING);
		glDisable (GL_DEPTH_TEST);
		glBegin(GL_POINTS);
		for (int i1 = 0; i1 < SCREENSIZE/VOXUNIT; ++i1)
		{
			for (int i2 = 0; i2 < SCREENSIZE/VOXUNIT; ++i2)
			{
				for (int i3 = 0; i3 < SCREENSIZE/VOXUNIT; ++i3)
				{
					if (voxels[i1][i2][i3].count <= 0)
					{
						continue;
					}
					Vec3 color1 = color;
					glColor3f(color1[0],color1[1],color1[2]);
					glVertex3f (i1*VOXUNIT - SCREENSIZE/2,i2*VOXUNIT - SCREENSIZE/2,i3*VOXUNIT - SCREENSIZE/2);
				}
			}
		}

		glEnd();
		glPopMatrix();
		glEnable (GL_LIGHTING);
		glEnable (GL_LIGHT0);
		glEnable (GL_DEPTH_TEST);

		glNormal3f (0.0, 0.0, 1.0);
	}
};

Explosion e;

void keyboard(unsigned char c, int x,int y){
	switch(c){
		case ' ':
			start_explosion = !start_explosion;
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

void
display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
  glTranslatef (0.0, 0.0, -20.0);
  glRotatef (0, 0.0, 1.0, 0.0);
	// glutSolidSphere (2.0,15,9);
	e.render();
	glutSwapBuffers();
}

void idle(void){
	e.update(0.1);
	// display();
	glutPostRedisplay();
}

void reshape(int w,int h){
	if (h == 0)h = 1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(((GLfloat)w)/h),0.1,100);
	glMatrixMode(GL_MODELVIEW);
}

// void
// mousePress(int button, int state, int x, int y){
// 	return;
// }

int main(int argc,char** argv){
	GLfloat  light0Amb[4] =  { 1.0, 0.6, 0.2, 1.0 };
	GLfloat  light0Dif[4] =  { 1.0, 0.6, 0.2, 1.0 };
	GLfloat  light0Spec[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat  light0Pos[4] =  { 0.0, 0.0, 0.0, 1.0 };

	GLfloat  light1Amb[4] =  { 0.0, 0.0, 0.0, 1.0 };
	GLfloat  light1Dif[4] =  { 1.0, 1.0, 1.0, 1.0 };
	GLfloat  light1Spec[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat  light1Pos[4] =  { 0.0, 5.0, 5.0, 0.0 };

	GLfloat  materialAmb[4] = { 0.25, 0.22, 0.26, 1.0 };
	GLfloat  materialDif[4] = { 0.93, 0.57, 0.20, 1.0 };
	GLfloat  materialSpec[4] = { 0.99, 0.91, 0.81, 1.0 };
	GLfloat  materialShininess = 27.8;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Explosion");
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	// glutMouseFunc(mousePress);
	// glutMotionFunc(mouseMove);
	
	glEnable (GL_LIGHT0);
	glEnable (GL_LIGHT1);
	glLightfv (GL_LIGHT0, GL_AMBIENT, light0Amb);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light0Dif);
	glLightfv (GL_LIGHT0, GL_SPECULAR, light0Spec);
	glLightfv (GL_LIGHT0, GL_POSITION, light0Pos);
	glLightfv (GL_LIGHT1, GL_AMBIENT, light1Amb);
	glLightfv (GL_LIGHT1, GL_DIFFUSE, light1Dif);
	glLightfv (GL_LIGHT1, GL_SPECULAR, light1Spec);
	glLightfv (GL_LIGHT1, GL_POSITION, light1Pos);
	glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, materialAmb);
	glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, materialDif);
	glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
	glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
	glEnable (GL_NORMALIZE);
	

	glutMainLoop();
	return 0;
}