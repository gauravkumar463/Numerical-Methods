/* This program calculates interpolation of a data set using Lagrange interpolator
 and output the interpolated value Y at a given point X. */

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

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

double X0,Y0;
string option;
while(1){
cout << "Want to calculate new point (y/n): ";
cin >> option;
if(option =="y" || option =="Y"){ 
cout << "Enter X to interpolate, X = ";
cin >> X0;
Y0=0;
for(long i=0;i<n;i++){
Y0 += Y[i]*Lagrange(X,X0,i);
}
cout << "Y = " << Y0 << endl;
}
else break;
}
return 0;
}
