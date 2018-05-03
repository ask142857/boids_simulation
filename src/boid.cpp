#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <thread>
#include "boid.h"
using namespace std;

boid::boid(){
	x = 0;
	y = 0 ;
	z = 0 ;
	v1 = 0;
	v2 = 0;
	v3 = 0;
	flap = 0 ;
}


vector_3::vector_3(){
	x = 0;
	y = 0 ;
	z = 0 ;

}

flock::flock(int n1,float dis[3],float co[3],boid set[15000])
{
      n = n1;
      int i = 0;
      for(i=0;i<3;i++)
      {
      	distance[i] = dis[i];
      	coef[i] = co[i];
      }
      for ( i = 0; i < 15000; ++i)
      {
      	set_of_boids[i] = set[i];
      }
}


float flock::radius(int a,int b)
{
 		float r;
 		r = ((set_of_boids[a].x - set_of_boids[b].x )*(set_of_boids[a].x - set_of_boids[b].x )) + ((set_of_boids[a].y - set_of_boids[b].y )*(set_of_boids[a].y - set_of_boids[b].y )) + ((set_of_boids[a].z - set_of_boids[b].z )*(set_of_boids[a].z - set_of_boids[b].z)) ;
 	    r = pow(r,0.5);

 	    return r;	
}

	void flock::cohesive(int a,vector_3* ans)
	{
		
		//vector_3 ans;
		ans->x =0;
		ans->y =0;
		ans->z =0;
		int count = 0;
		for(int i =0 ;i<n ; i++){
			if(i !=a && radius(a , i) <= distance[0]){
				ans->x = ans->x + set_of_boids[i].x ; 
				ans->y = ans->y + set_of_boids[i].y ; 
				ans->z = ans->z + set_of_boids[i].z ; 
				count ++ ;
			}
		}
		if(count != 0){
		ans->x = (ans->x )/count;
		ans->x = ans->x - set_of_boids[a].x ;
		ans->x = ans->x *  coef[0]  ;
		ans->y = (ans->y )/count;
		ans->y = ans->y - set_of_boids[a].y ;
		ans->y = ans->y *  coef[0]  ;	
		ans->z = (ans->z )/count;
		ans->z = ans->z - set_of_boids[a].z ;
		ans->z = ans->z *  coef[0];			
		}
		return  ;
	}
	void flock::moving_away(int a,vector_3* ans)
	{
		//vector_3 ans;
		ans->x =0;
		ans->y =0;
		ans->z =0;
		int count = 0;
		for(int i =0 ;i<n ; i++){
			if(i !=a && radius(a , i) <= distance[1]){
				ans->x = ans->x + set_of_boids[i].x ; 
				ans->y = ans->y + set_of_boids[i].y ; 
				ans->z = ans->z + set_of_boids[i].z ; 
				count ++ ;
			}
		}
		if(count != 0)
		{
		ans->x = (ans->x )/count;
		ans->x = ans->x - set_of_boids[a].x ;
		ans->x = -ans->x *  coef[1]  ;
		ans->y = (ans->y )/count;
		ans->y = ans->y - set_of_boids[a].y ;
		ans->y = -ans->y *  coef[1]  ;	
		ans->z = (ans->z )/count;
		ans->z = ans->z - set_of_boids[a].z ;
		ans->z = -ans->z *  coef[1];			
		}
		return ;
	}
    void flock::position_boundary(int a,vector_3* ans)
    {	
    	float limit = 1.32 ;
    	//vector_3 ans;
    	if(set_of_boids[a].x > limit)
    	{
           ans->x = limit - set_of_boids[a].x;
    	}
    	else if(set_of_boids[a].x < -limit)
    	{
    	  ans->x = -limit - set_of_boids[a].x;
    	}

    	if(set_of_boids[a].y > limit)
    	{
           ans->y = limit - set_of_boids[a].y;
    	}
    	else if(set_of_boids[a].y < -limit)
    	{
    	  ans->y = -limit - set_of_boids[a].y;
    	}    	
    	if(set_of_boids[a].z > limit)
    	{
           ans->z = limit - set_of_boids[a].z;
    	}
    	else if(set_of_boids[a].z < -limit)
    	{
    	  ans->z = -limit - set_of_boids[a].z;
    	} 
    	ans->x = ans->x * 0.1;
    	ans->y = ans->y * 0.1;
    	ans->z = ans->z * 0.1;
    	return ;

    }
    void flock::velocity_boundary(int a)
    {
    	vector_3 ans;
    	float speed = ((set_of_boids[a].v1)*(set_of_boids[a].v1))+((set_of_boids[a].v2)*(set_of_boids[a].v2))+((set_of_boids[a].v3)*(set_of_boids[a].v3));
    	speed = pow(speed,0.5);
    	if (speed<0.03)
    	{
    		set_of_boids[a].v1 = (set_of_boids[a].v1) * 2;
    		set_of_boids[a].v2 = (set_of_boids[a].v2) * 2;
    		set_of_boids[a].v3 = (set_of_boids[a].v3) * 2;
    	}
    	if (speed>0.1)
    	{
    		set_of_boids[a].v1 = (set_of_boids[a].v1) * 0.5;
    		set_of_boids[a].v2 = (set_of_boids[a].v2) * 0.5;
    		set_of_boids[a].v3 = (set_of_boids[a].v3) * 0.5;
    	}
    	return;

    }     
	void flock::allignment(int a,vector_3* ans)
	{
		
		//vector_3 ans;
		ans->x =0;
		ans->y =0;
		ans->z =0;
		int count = 0;
		for(int i =0 ;i<n ; i++){
			if(i !=a && radius(a , i) <= distance[2]){
				ans->x = ans->x + set_of_boids[i].v1 ; 
				ans->y = ans->y + set_of_boids[i].v2 ; 
				ans->z = ans->z + set_of_boids[i].v3 ; 
				count ++ ;
			}
		}
		if(count != 0){
		ans->x = (ans->x )/count;
		ans->x = ans->x - set_of_boids[a].v1 ;
		ans->x = ans->x *  coef[2]  ;
		ans->y = (ans->y )/count;
		ans->y = ans->y - set_of_boids[a].v2 ;
		ans->y = ans->y *  coef[2]  ;	
		ans->z = (ans->z )/count;
		ans->z = ans->z - set_of_boids[a].v3 ;
		ans->z = ans->z *  coef[2];			
		}
		return ;
	}


