//! This class stores the data of an individual bird 
class boid{
public:
	//! gives the coordinates of bird 
	float x, y ,z ;
	//! gives the velocities of the bird 
	float v1,v2,v3,flap;
	//! constructor
	boid();

};
//! this class stores data of a fixed points
class vector_3{
public:
	//! coordinates of the fixed point
	float x, y, z ;
	//! constructor
	vector_3();
} ;



//! This class stores the data of the entire flock and their velocities
class flock
{
public:
	//! Number of birds
	int n ;
    //! radius in which rules apply
	float distance[3];
	//! coefficient of cohesion, reflection, alignment
	float coef[3];
	//! all birds
	boid set_of_boids[15000];
	//! constructor
 	flock(int n1,float dis[3],float co[3],boid set[15000]);
  	//! calculates distance between two birds
	float  radius(int a , int b);
	  //! limits velocity boundary
  	void velocity_boundary(int a);
    //!limits position_boundary
    void position_boundary(int a,vector_3* ans);
	//! individual cohesion calculation
	void cohesive(int a,vector_3* ans);
	//! individual reflection calculation
	void moving_away(int a,vector_3* ans);
	//! individual alignment calculation
	void allignment(int a,vector_3* ans);
	//! summs up all the coefficients and updates it to next instant
	//void nextInstant();
};


