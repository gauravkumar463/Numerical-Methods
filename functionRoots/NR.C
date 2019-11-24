/* A program to find the root "x" of a function f(x) = 0  using Newton-Raphson method*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// function
double f(double x){
	return x*tan(x)-1; 
}
// derivative of the function
double f1(double x){
	return tan(x) + x*pow(cos(x),-2);
}

int main(){
cout << "Enter initial guess" <<endl;
double x, tolerance;
cout << "x1 = \t";
cin >> x;
cout << "tolerance for convergence = ";
cin >> tolerance;
cout << endl;
int step = 2;
while(1){
	x -= f(x)/f1(x);
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
