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
#define EXPL_AMNNT 1000

bool start_explosion= false;
//Particle class
class Particle{
public:
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	Particle(){
	}
	void update(float timestep){
		position = position + velocity * timestep;
		velocity = velocity + acceleration * timestep;
		acceleration = acceleration/3;
	}
};

class Explosion{
public:
	Vec3 color;
	Vec3 extremeColor;
	vector<Particle> particles;
	float time;
	Explosion(){
		time = 0;
		extremeColor = Vec3(251,23,23);
		color = Vec3(255,0,0);
	}
	Explosion(int n){
		for (int i = 0; i < n; ++i)
		{
			Particle p;
			p.position = Vec3(0,0,0);
			double r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			double y = 2 * 3.14 * static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			double z = 1 - r*r;
			// cout<<r*cos(y)<<" "<<r*sin(y)<<" "<<z<<endl;
			// p.velocity = 0.5*Vec3(r*cos(y),r*sin(y),z);
			p.acceleration = 0.5*Vec3(r*cos(y),r*sin(y),z);
			particles.push_back(p);
		}
		time = 0.0;
		// extremeColor = Vec3(251,23,23);
		color = Vec3(240.0/255,162.0/255,14.0/255);
	}
	void update(float t){
		if (!start_explosion)
		{
			return;
		}
		for(int i = 0; i < particles.size(); i++){
			particles[i].update(t);
		}
		time += t;
		// cout << time << endl;
		if(time > TIMELIMIT){
			color = Vec3(0, 0, 0);
		}
		// else if(time < (TIMELIMIT/2)){
		// 	color = 2 * time * extremeColor / TIMELIMIT;
		// }
		// else{
		// 	color = extremeColor - 2*(time - TIMELIMIT/2)*extremeColor/TIMELIMIT;
		// }
		else{
			 if(time <= TIMELIMIT/6.0){
				color = Vec3(240.0/255,162.0/255,14.0/255);
			}
			else{
				if( (TIMELIMIT/6.0) < time <= (TIMELIMIT/3.0)){
					color = Vec3(251.0/255,23.0/255,23.0/255);
				}
				else{
					if((TIMELIMIT/3.0) < time <= (TIMELIMIT / 2.0)){
						color = Vec3(216.0/255,190.0/255,31.0/255);
						cout << "poop" << endl;
					}
					else {
						if((TIMELIMIT/2) < time <= (2 * TIMELIMIT/3)){
							color = Vec3(234.0/255,27.0/255,27.0/255);
						}
						else{
							if((2*TIMELIMIT/3) < time <= (5 * TIMELIMIT / 6)){
								color = Vec3(216.0/255,209.0/255,45.0/255);
							}
							else{
								color = Vec3(240.0/255,162.0/255,14.0/255);
							}
						}
					}
				}
			}
		}
		// cout << time << endl;
		// cout << color << endl;
		// cout << TIMELIMIT << endl;
	}
	void render(){
		// cout<<"render"<<endl;
		glPushMatrix();
		glDisable (GL_LIGHTING);
		glDisable (GL_DEPTH_TEST);
		glBegin(GL_POINTS);
		for (int i = 0; i < particles.size(); ++i)
		{
			glColor3f(color[0],color[1],color[2]);
			// cout<<particles[i].position[0]<<" "<<particles[i].position[1]<<" "<<particles[i].position[2]<<endl;
			glVertex3f (particles[i].position[0],particles[i].position[1],particles[i].position[2]);
		}
		glEnd();
		glPopMatrix();
		glEnable (GL_LIGHTING);
		glEnable (GL_LIGHT0);
		glEnable (GL_DEPTH_TEST);

		glNormal3f (0.0, 0.0, 1.0);
	}
};

Explosion e(EXPL_AMNNT);

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
	srand(time(NULL));
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