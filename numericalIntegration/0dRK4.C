/* A time integration for 0-dimensional system. 
Template function d/dt[x(t)] = x + 2t -t^2 */

#include<iostream>
#include<cmath>
#include <fstream>
#include<iomanip>
using namespace std;


// function to be integrated
double f(double t, double x){
	return x + (2*t) -pow(t,2);
}

// exact solution
double fInt(double t){
	return pow(t,2) + exp(t);
}

int main(){
double t0 = 0;
double x0 = 1;
double dt = 0.5;
double N = 10;
ofstream myfile;
myfile.open ("0dRK4solution.dat");
double K1, K2, K3, K4;
	myfile << "i \t X \t K1 \t K2 \t K3 \t K4 \t Ynum \t Yexact \t Error(%)" << endl;  
for(int i=1;i<=N;i++){
	K1 = dt*f(t0,x0);
	K2 = dt*f(t0+dt/2.0, x0+K1/2.0);
	K3 = dt*f(t0+dt/2.0, x0+K2/2.0);
	K4 = dt*f(t0+dt, x0+K3);
	x0 += (K1+2*(K2+K3)+K4)/6.0;
	t0 += dt;
	myfile << i << "\t" 
		<< setprecision(6) << t0 << "\t" 
		<< setprecision(6) << K1 << "\t" 
		<< setprecision(6) << K2 << "\t" 
		<< setprecision(6) << K3 << "\t" 
		<< setprecision(6) << K4 << "\t" 
		<< setprecision(6) << x0 << "\t" 
		<< setprecision(6) << fInt(t0) << "\t" 
		<< setprecision(6) << (fInt(t0)-x0)*100/fInt(t0) << endl;

}
myfile.close();

FILE *gnuplotPipe = popen("gnuplot -persist", "w");  // Open a pipe to gnuplot

if (gnuplotPipe) {   // If gnuplot is found

  fprintf(gnuplotPipe, "reset\n"); //gnuplot commands
  fprintf(gnuplotPipe, "set term png #output terminal and file\n");
  fprintf(gnuplotPipe, "set output '0dPlot.png'\n");
  fprintf(gnuplotPipe, "set xlabel 't'\n");
  fprintf(gnuplotPipe, "set ylabel 'x'\n");
  fprintf(gnuplotPipe, "set title 'Integrated Values'\n");

  fprintf(gnuplotPipe, "plot '0dRK4solution.dat' using 2:7 with lines\n");

  fflush(gnuplotPipe); //flush pipe

  fprintf(gnuplotPipe,"exit \n");   // exit gnuplot
  pclose(gnuplotPipe);    //close pipe
}
return 0;
}
