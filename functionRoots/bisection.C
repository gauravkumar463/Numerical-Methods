/* A program to find the root "x" of a function f(x) = 0  using bisction method */

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// function
double f(double x){
	return x*tan(x)-1; 
}

int main(){
cout << "Enter x1 and x2 as guess values such that f(x1)<0 and f(x2)>0" <<endl;
double x1, x2, x, tolerance;
cout << "x1 = \t";
cin >> x1;
cout << "\nx2 = \t";
cin >> x2;
cout << endl;
cout << "tolerance for convergence = ";
cin >> tolerance;
cout << endl;
//check of f(x1) <0 and f(x) >0
int step = 3;
if(f(x1) < 0 && f(x2) >0){
	while(1){
		x = (x1 + x2)/2;
		cout << "x" << step << " = " << setprecision(10) << x  << "\t" 
		<< "f(" << setprecision(10) << x << ") = " << f(x) << endl;
		if(abs(f(x)) > tolerance ){
			if (f(x) > 0) x2 = x;
			else if (f(x) < 0) x1 = x;
		}
		else{
		cout << "x = " << setprecision(10) << x << endl;
		break;
		}
		step++;
	}
}
else{
	cout << "wrong sign of f(x1) or f(x2) or both. " << "f(" << setprecision(10) << x1 << ") = " 
				<< setprecision(10) << f(x1) << "\t" 
				<< "f(" << setprecision(10) << x2 << ") = " 
				<< setprecision(10) << f(x2) << endl;
}
}
