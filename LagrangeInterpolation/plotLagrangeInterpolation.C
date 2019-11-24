/* This program calculates interpolation of a data set using Lagrange interpolator
 and plots the function in the give data range.
A sample input file is plotSin. 
A plot LP.png will be generated as output.
Also, a LP.dat file will be generated as output.*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
double Lagrange(vector <double> X, double X0, long n){
double Ln=1;
for(int i=0;i<X.size();i++){
    if(i==n) continue;
    else {
    	Ln *= (X0-X[i])/(X[n]-X[i]);
    }
}
return Ln;
}

int main(){
long n;
cout << "Number of data points (n) = ";
cin >> n;
vector <double> X(n), Y(n);
cout << "Enter n ordered pairs of X and Y" << endl;
for(int i=0;i<n;i++){
    cin >> X[i] >> Y[i];
}

double Xl,Xu,X0,Y0;
long m;
cout << "Enter Domain of interpolation, (X0, X1, n) = ";
cin >> Xl >> Xu >> m;
ofstream myfile;
myfile.open("LP.dat");
myfile << "X Y" << endl;
for(long j=0;j<m;j++){
X0=Xl+j*(Xu-Xl)/(m-1);
Y0=0;
for(long i=0;i<n;i++){
Y0 += Y[i]*Lagrange(X,X0,i);
}
myfile << X0 << " " << Y0 << endl;
}
myfile.close();

FILE *gnuplotPipe = popen("gnuplot -persist", "w");  // Open a pipe to gnuplot

if (gnuplotPipe) {   // If gnuplot is found

  fprintf(gnuplotPipe, "reset\n"); //gnuplot commands
  fprintf(gnuplotPipe, "set term png #output terminal and file\n");
  fprintf(gnuplotPipe, "set output 'LP.png'\n");
  fprintf(gnuplotPipe, "set xlabel 'X'\n");
  fprintf(gnuplotPipe, "set ylabel 'Y'\n");
  fprintf(gnuplotPipe, "set title 'Langrange Interpolated Values'\n");

  fprintf(gnuplotPipe, "plot 'LP.dat' using 1:2 with line\n");

  fflush(gnuplotPipe); //flush pipe

  fprintf(gnuplotPipe,"exit \n");   // exit gnuplot
  pclose(gnuplotPipe);    //close pipe
}

return 0;
}
