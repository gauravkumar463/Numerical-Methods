/* A program to find the root "x" of a function f(x) = 0  using Secant method*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// function
double f(double x){
	return x*tan(x)-1; 
}
double f1(double x, double dx){
	return (f(x+dx)-f(x))/dx;
}

int main(){
cout << "Enter initial guess" <<endl;
double x, dx, tolerance;
cout << "x1 = \t";
cin >> x;
cout << "\ndx = \t";
cin >> dx;
cout << endl;
cout << "tolerance for convergence = ";
cin >> tolerance;
cout << endl;
int step = 3;
while(1){
	dx = f(x)/f1(x,dx);
	x -= dx;
	cout << "x" << step << " = " << setprecision(10)  << x << "\tf(" << setprecision(10)  << x << ") = " 
				<< setprecision(10)  << f(x) << endl;
	if(abs(f(x)) < tolerance ) 
	{
		cout << "x = " << setprecision(10)  << x << endl;
		break;
	}
	step++;
}
}
