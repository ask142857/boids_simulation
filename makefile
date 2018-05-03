all: main.o boid.o
	g++ -o Binary Myboid.o boid.o -framework GLUT -framework OpenGL

Myboid.o: Myboid.cpp
	g++ -c Myboid.cpp -I ./
 
boid.o: boid.cpp
	 ++ -std=c++11 -pthread -c boid.cpp -I ./
 
clean:
	 rm -rf *.o
	 rm -rf ask
              


              