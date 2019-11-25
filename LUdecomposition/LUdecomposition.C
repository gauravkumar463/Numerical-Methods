#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

#include "vectorSpace.H"

int main()
{
clock_t begin = clock();	// define clock to measure execution time
int m,n;
cout << "number of rows: ";
cin >> m;
cout << m << endl;
cout << "number of columns: ";
cin >> n;
cout << n << endl;
cout << "Enter the matrix in the for A" << endl;

matrix A(m,n);

// input the matrix A
for(int i=0;i<m;i++){
	double *tmpA = new double[n];
	for(int j=0;j<n;j++){
		cin >> tmpA[j];
	}
	A.setRow(tmpA,i);
}

matrix L(m,n,"l");
matrix U(m,n,"u");

cout << "\nA = \n" << A <<  endl;

A.LU(L,U);

cout << "\nL = \n" << L << endl;
cout << "\nU = \n" << U << endl;

clock_t end = clock();
double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
cout << "Elapsed Time = " << elapsed_secs << endl;

return 0;
}

