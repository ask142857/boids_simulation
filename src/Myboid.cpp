#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include<OpenGl/glu.h>
#include<OpenGl/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <thread>

#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "boid.h"
using namespace std;


#define PI 3.14159265


void display();

void specialKeys();
//!rotates in y
float rotate_y=0; 
//!rotates in x

float rotate_x=0;
//!translates in x

float trans_x =0;
//!translates in y

float trans_y = 0;
//double flap = 0;
//!zooms in the screen

float zoom =1;

//! birds object
flock* birds;



  

  void nextInstant()
  {
    




    vector_3 values[15000][5];
    int n = birds->n;
    for(int i =0 ;i<n;i++)
    {
      
      thread th1(&flock::cohesive,birds,i,&values[i][0]);
      thread th2 (&flock::moving_away,birds,i,&values[i][1]);
      thread th3(&flock::allignment,birds,i,&values[i][2]);
      thread th4(&flock::position_boundary,birds,i,&values[i][3]);
      //values[i][4] = velocity_boundary(i);
      th1.join();
      th2.join();
      th3.join();
      th4.join();
      //birds->cohesive(i,&values[i][0]);
      //birds->moving_away(i,&values[i][0]);
      //birds->allignment(i,&values[i][0]);
      //birds->position_boundary(i,&values[i][0]);

    }

    for(int i =0 ; i<n ; i++)
    {

     birds->set_of_boids[i].v1 = birds->set_of_boids[i].v1 + values[i][0].x + values[i][1].x + values[i][2].x + values[i][3].x;  //+ values[i][4].x;
     birds->set_of_boids[i].v2 = birds->set_of_boids[i].v2 + values[i][0].y + values[i][1].y + values[i][2].y + values[i][3].y;  //+ values[i][4].y;
     birds->set_of_boids[i].v3 = birds->set_of_boids[i].v3 + values[i][0].z + values[i][1].z + values[i][2].z + values[i][3].z;  //+ values[i][4].z;
      
    }

    for(int i=0;i<n;i++)
    {
      birds->velocity_boundary(i);
    }
    for(int i =0 ;i<n;i++)
    {
      birds->set_of_boids[i].x = birds->set_of_boids[i].x + birds->set_of_boids[i].v1 ;
      birds->set_of_boids[i].y = birds->set_of_boids[i].y + birds->set_of_boids[i].v2 ;
      birds->set_of_boids[i].z = birds->set_of_boids[i].z + birds->set_of_boids[i].v3 ;
    }
  }




vector_3 direction(boid a)
{
	vector_3 ans;

	if(pow(a.v1,2) + pow(a.v2,2) + pow(a.v3,2) != 0)
	{
	ans.z = pow( pow(a.v1,2) + pow(a.v2,2) + pow(a.v3,2)  ,0.5  );
	
	ans.x = a.v1 /ans.z;
	ans.y = a.v2/ans.z;
	ans.z = a.v3/ans.z;}
	else
	{
		ans.x =1 ;
		ans.y =0 ;
		ans.z =0 ;
	}
	return ans;

}
//! display function

void display()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef( trans_x, trans_y, 0.0 ); 
  glRotatef(rotate_x,1,0,0);
  glRotatef(rotate_y,0,1,0);


  for(int i = 0 ; i< birds-> n ;i++)
  {

  	float x = (birds->set_of_boids[i]).x ;
  	float y = (birds->set_of_boids[i]).y ;
  	float z = (birds->set_of_boids[i]).z ;
  	  	//glColor3f(0.504,0.768,0.952);
  	glColor3f(0.5+x*x,0.5+y*y,0.5+z*z);


  	vector_3 ask = direction(birds->set_of_boids[i]);
/*
  	glTranslatef((x)*zoom , (y)*zoom , (z)*zoom    );

  	glRotatef( acos(ask.z)*180/PI,-ask.y,+ask.x,0 );


 	glutSolidCone((0.01)*zoom,0.05*zoom,10,10);


  	glRotatef( acos(ask.z)*180/PI,+ask.y,-ask.x,0 );


  	glTranslatef(-(x)*zoom , -(y)*zoom , -(z)*zoom  );*/
    float sc =  0.01 ;
    glTranslatef((x)*zoom , (y)*zoom , (z)*zoom    );
    glRotatef( acos(ask.z)*180/PI,-ask.y,+ask.x,0 );
   // stroke(h);
    //noFill();
    //noStroke();
    //fill(h);
    //draw bird
    float flap = (birds -> set_of_boids[i]).flap;
   // beginShape(TRIANGLES);
    glBegin(GL_POLYGON);
    glVertex3f(3*sc,0,0);
    glVertex3f(-3*sc,2*sc,0);
    glVertex3f(-3*sc,-2*sc,0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(3*sc,0,0);
    glVertex3f(-3*sc,2*sc,0);
    glVertex3f(-3*sc,0,2*sc);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(3*sc,0,0);
    glVertex3f(-3*sc,0,2*sc);
    glVertex3f(-3*sc,-2*sc,0);
    glEnd();
    // wings

    //double f =(double) rand();
    //double flap = 7;
    glBegin(GL_POLYGON);
    glVertex3f(2*sc, 0, 0);
    glVertex3f(-1*sc, 0, 0);

    glVertex3f(-1*sc, -8*sc, flap*sc);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2*sc, 0, 0);
    glVertex3f(-1*sc, 0, 0);
    glVertex3f(-1*sc, 8*sc,flap*sc);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex3f(-3*sc, 0, 2*sc);
    glVertex3f(-3*sc, 2*sc, 0);
    glVertex3f(-3*sc, -2*sc, 0);
    glEnd();
    //
    glRotatef( acos(ask.z)*180/PI,+ask.y,-ask.x,0 );


    glTranslatef(-(x)*zoom , -(y)*zoom , -(z)*zoom  );

    //box(10);

    if(flap > 7) birds -> set_of_boids[i].flap = 0;
    else birds -> set_of_boids[i].flap = birds -> set_of_boids[i].flap + 1;
  //  std::cout << "hot chick "<< flap << std::endl;
	

  }

  
  nextInstant();
  glFlush();
  glutSwapBuffers();
 	
}

//! processKeys

void processKeys(unsigned char key , int x , int y){

  if(key == 'y') trans_y += 0.5;
  else if(key == 'b') trans_y -=0.5;		
  else if(key == 'x') trans_x +=0.5;		
  else if(key == 'a') trans_x -=0.5;

  else if(key == 'i') zoom = zoom *1.6;
  else if(key == 'o') zoom = zoom *0.625;

  else if(key == 'j'){ 
  	if(birds->coef[0] ==0.001) birds->coef[0] =0;

  	else birds->coef[0] =0.001;}
 else if(key == 'k'){ 
  	if(birds->coef[1] ==0.2) birds->coef[1] =0;
  	else birds->coef[1] =0.2;}
 else if(key == 'l'){ 
  	if(birds->coef[2] ==0.1) birds->coef[2] =0;
  	else birds->coef[2] =0.1; }	 	

  glutPostRedisplay();
    
}
//! specialKeys 

void specialKeys( int key, int x, int y ) 
{
 
  if (key == GLUT_KEY_RIGHT)
    rotate_x += 5;
 
  else if (key == GLUT_KEY_LEFT)
    rotate_x -= 5;
 
  else if (key == GLUT_KEY_UP)
    rotate_y += 5;
 
  else if (key == GLUT_KEY_DOWN)
    rotate_y -= 5;
 
  glutPostRedisplay();
 
}
//! Timer function
/*
 responsible for updating the frames
*/

void Timer(int value)
{
	glutTimerFunc(30, Timer, 0);
	glutPostRedisplay();
}

//! main 
int main(int argc, char* argv[])
{
  





  int n_root = 10;	
  float distance[3];
  float coef[3];
  boid set_of_boids[15000];
  int q =0 ;

  for(int i =0 ; i< n_root ; i++){
  	for(int j =0 ; j<n_root ; j++){
  		for(int k=0 ; k<n_root ; k++)
  		{	

  		float m = (float) i ;
  		float n = (float) j ;
  		float l = (float) k ;
  		set_of_boids[q].x = m/(2*n_root);
  		set_of_boids[q].y = n/(2*n_root);
  		set_of_boids[q].z = l/(2*n_root);
  		set_of_boids[q].v1 = 0.015;
  		set_of_boids[q].v2 = 0;
  		set_of_boids[q].v3 = 0.02;
      set_of_boids[q].flap = 0;

  		q++;
  	   }
  	}
  }
  for(int i =0 ; i< n_root ; i++){
  	for(int j =0 ; j<n_root ; j++){
  		for(int k=0 ; k<n_root ; k++)
  		{
  		float m = (float) i ;
  		float n = (float) j ;
  		float l = (float) k ;
  		
  		set_of_boids[q].x = -m/(2*n_root);
  		set_of_boids[q].y = -n/(2*n_root);
  		set_of_boids[q].z = -l/(2*n_root);
  		set_of_boids[q].v1 = 0.05;
  		set_of_boids[q].v2 = 0;
  		set_of_boids[q].v3 = 0;
      set_of_boids[q].flap = 0;
  		q++;
  	 }
  	}
  }
  for(int i =0 ; i< n_root ; i++){
  	for(int j =0 ; j<n_root ; j++){
  		for(int k=0 ; k<n_root ; k++)
  		{
  		float m = (float) i ;
  		float n = (float) j ;
  		float l = (float) k ;
  		
  		set_of_boids[q].x = 5+m/(2*n_root);
  		set_of_boids[q].y = 5+n/(2*n_root);
  		set_of_boids[q].z = 5+l/(2*n_root);
  		set_of_boids[q].v1 = 0.0;
  		set_of_boids[q].v2 = 0;
  		set_of_boids[q].v3 = 0.014;
      set_of_boids[q].flap = 0;
  		q++;
  	 }
  	}
  }



  for(int i =0 ; i< n_root ; i++){
  	for(int j =0 ; j<n_root ; j++){
  		for(int k=0 ; k<n_root ; k++)
  		{
  		float m = (float) i ;
  		float n = (float) j ;
  		float l = (float) k ;
  		
  		set_of_boids[q].x = -5+m/(2*n_root);
  		set_of_boids[q].y = -5+n/(2*n_root);
  		set_of_boids[q].z = -5+l/(2*n_root);
  		set_of_boids[q].v1 = -0.014;
  		set_of_boids[q].v2 = -0.003;
  		set_of_boids[q].v3 = -0.02;
      set_of_boids[q].flap = 0;
  		q++;
  	 }
  	}
  }



  distance[0] = 0.1;
  distance[1] = 0.1;
  distance[2] = 0.5;
  coef[0] = 0.01;
  coef[1] = 0.1;
  coef[2] = 0.2;
  birds = new flock(4*n_root*n_root,distance,coef,set_of_boids);

 
  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
 
  //  Request float buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  // Create window
  glutCreateWindow("thop");
 
  //  Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);
 
  // Callback functions
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
   glutKeyboardFunc(processKeys);
 
  //  Pass control to GLUT for events
  
  Timer(0);
  glutMainLoop();
  //int oldTimeSinceStart = 0;

	
 
  //  Return to OS
  return 0;
 
}




