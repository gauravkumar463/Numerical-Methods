/* A time integration for 0-dimensional system. 
Template function simultaneously solves 3 second order ODES in time given by
d2(x1)/dt2 = g+k1(2x2-3x1)
d2(x2)/dt2 = g+k2(x1+x3-2x2)
d2(x3)/dt2 = g+k3(x2-x3) */

#include <iostream>
#include <fstream>
#include "vectorSpace.H"	// class declaration for veector calculations

using namespace std;

// Function to put initial condition
void SolutionInit(vector X, int nNodes, double dx){
	X.setValue(0,0.0);		// set t=0
	X.setValue(1,0.0);		// set x1=0
	X.setValue(2,0.0);		// set y1=0
	X.setValue(3,0.0);		// set x2=0
	X.setValue(4,0.0);		// set y2=0
	X.setValue(5,0.0);		// set x3=0
	X.setValue(6,0.0);		// set y3=0
}

// Function to return [x' y' y1'] = f(x, y, y1)
vector f(vector X, double dx){
	double g=9.81;
	double k1 = 10.0/2.0;
	double k2 = 10.0/3.0;
	double k3 = 10.0/2.5;
	vector Y(X.size());
	Y.setValue(0,1);		// set t=1

	Y.setValue(1,X.getValue(2));	// set x1' = y1
	Y.setValue(2,g+k1*((2*X.getValue(3))-(3*X.getValue(1))));	// set y1' = g + k1(2x2-3x1)

	Y.setValue(3,X.getValue(4));	// set x2' = y2
	Y.setValue(4,g+k2*((2*X.getValue(1))+X.getValue(5)-(3*X.getValue(3))));	// set y2' = g + k2(x1+x3-2x2)

	Y.setValue(5,X.getValue(6));	// set x3' = y3
	Y.setValue(6,g+k3*(X.getValue(3)-X.getValue(5)));	// set y3' = g + k3(x2-x3)
	return Y;
}

int main(){
int nEqn = 6;		// no. of equation. In this case we have two equation
double dx = 0.001;		// differential length scale
double L = 100;			// domain length
int nNodes = L/dx+1;		// number of nodes for calculation.
							// first node is used to store intial condition

// solution is stored as 2D array. rows corresponds to solution
// at different x and columns correspond to [x y y1]
vector *solution = new vector[nNodes];	
for(int i=0;i<nNodes;i++){
	solution[i] = vector(nEqn+1);
}

SolutionInit(solution[0],nNodes,dx);	// ensure intial condition

vector K1, K2, K3, K4;	// K1, K2 K3 and K4 in vector form.

// Here comes the RK4 algorithm
for(int i=0;i<nNodes-1;i++){
	K1 = f(solution[i],dx)*dx;
	K2 = f(solution[i]+K1/2,dx)*dx;
	K3 = f(solution[i]+K2/2,dx)*dx;
	K4 = f(solution[i]+K3,dx)*dx;
	solution[i+1] = solution[i] + (K1 + K2*2 + K3*2 + K4)/6;
}

ofstream myfile;
myfile.open ("1dRK4solution.dat");
// Print the solution
for(int i=0;i<nNodes;i=i+10){
		myfile <<solution[i];
	}

myfile.close();

FILE *gnuplotPipe = popen("gnuplot -persist", "w");  // Open a pipe to gnuplot

if (gnuplotPipe) {   // If gnuplot is found

  fprintf(gnuplotPipe, "reset\n"); //gnuplot commands
  fprintf(gnuplotPipe, "set term png #output terminal and file\n");
  fprintf(gnuplotPipe, "set output '1dRK4Plot.png'\n");
  fprintf(gnuplotPipe, "set xlabel 't'\n");
  fprintf(gnuplotPipe, "set ylabel 'x'\n");
  fprintf(gnuplotPipe, "set title 'Integrated Values'\n");

  fprintf(gnuplotPipe, "plot '1dRK4solution.dat' using 1:2 with lines title 'x1',\
  '1dRK4solution.dat' using 1:4 with lines title 'x2',\
  '1dRK4solution.dat' using 1:6 with lines title 'x3' \n");

  fflush(gnuplotPipe); //flush pipe

  fprintf(gnuplotPipe,"exit \n");   // exit gnuplot
  pclose(gnuplotPipe);    //close pipe
}
return 0;
}
