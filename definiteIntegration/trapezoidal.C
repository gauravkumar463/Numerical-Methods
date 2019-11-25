/* Integration of a function using traperzoidal rule */

#include <iostream>
#include <cmath>

using namespace std;

//function to be integrated
double f(double x){
 return 1.0/(1.0+pow(x,2));
}

double trapz(double Xmin,double Xmax, long n)
{	
	double Integral = 0;
	double dx = (Xmax-Xmin)/n;
	for(long i=0;i<n;i=i+1){
		Integral += (dx/2)*(f(Xmin+i*dx)+f(Xmin+(i+1)*dx));
	}
}
int main(){
double Xmin, Xmax;
long n;	

cout << "Input integration Range for the function: [Xmin Xmax] = ";
cin >> Xmin >> Xmax;

cout << "Input number of number of steps for integration: ";
cin >> n;

cout << "Integration of f(x) = 1/(1+x^2) in range [" << Xmin << ", " << Xmax << "] = "  <<trapz(Xmin,Xmax,n) << endl;
}
