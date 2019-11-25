/* Integration of a function using Simpson rule */

#include <iostream>
#include <cmath>

using namespace std;

// function to be integrated
double f(double x){
	return 1.0/(1.0+pow(x,2));	// return value of function at x
}

double simpson(double Xmin,double Xmax, long n)
{	
	double Integral = 0;		// value of integral
	double dx = (Xmax-Xmin)/n;	// x step size
	for(long i=0;i<n-1;i=i+2){
		// Simpson's rule using three points
		Integral += (dx/3)*
			(
			 f(Xmin+i*dx)
			 +4*(f(Xmin+(i+1)*dx))
			 +f(Xmin+(i+2)*dx)
			);
	}

}
int main(){
double Xmin, Xmax;		// variables to store range
long n;				// variable to store step number

cout << "Input integration Range for the function: [Xmin Xmax] = ";
cin >> Xmin >> Xmax;

cout << "Input number of steps for integration: ";
cin >> n;

// If number of steps is even call simpson function to find integral
if(n%2==0) cout << "Integration of f(x) = 1/(1+x^2) in range [" 
	<< Xmin << ", " << Xmax << "] = "  <<simpson(Xmin,Xmax,n) << endl;
// If number of steps is odd, output error message
else cout << "\n\n\nnumber of steps for integration should be a even number because " 
	"simpson's 1/3 rule\nrequire odd number of points for integration. "
		"Please try again with even number of steps.\n\n" << endl;
return 0;
}
