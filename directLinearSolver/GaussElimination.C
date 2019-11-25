/* This program solves a set of linear equations Ax = b using Gauss-elimination method .
See test files for input examples */

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

#include "vectorSpace.H"

// Gauss elimination method to solve Ax=b system
int GaussElimination(matrix A, column X){

int m = A.nrows();
int n = A.ncols()-1;

// Ensure digonal dominance
/*double max;
for(int k=0;k<m;k++){
		row rowk = A.getRow(k);
		max = rowk.maxMag();
		if (max!=1){
			A.setRow(rowk/max,k);
			cout << "R" << k << " --> R" << k << "/" << max << endl;
		}
}
*/
// forward Elimination with partial pivoting
double factor;
double pivotValue;
int switchRowi;
for(int k=0;k<m-1;k++){

	// partial pivoting
	// Find row index with largest absolute value of the pivot
	switchRowi = k;
	pivotValue = abs(A.getRow(switchRowi).getValue()[k]);
	for(int i=k+1;i<m;i++){
		if(pivotValue < abs(A.getRow(i).getValue()[k])){
			switchRowi = i;
			pivotValue = abs(A.getRow(switchRowi).getValue()[k]);
		}
	}
	//If current pivot doesn't has largest value, switch it with 
	//row with largest pivot value
	if(k!=switchRowi && A.getRow(switchRowi).getValue()[k]!=0){
		A.switchRow(k,switchRowi);
		cout << "R" << k << " <--> R" << switchRowi << endl;
	}

	// forward elimination
	for(int i=k+1;i<m;i++){
		row rowk = A.getRow(k);
		row rowi = A.getRow(i);
		if(rowk.getValue()[k]==0) break;
		factor = rowi.getValue()[k]/rowk.getValue()[k];
		if(factor !=0){
			A.setRow(rowi - rowk*factor,i);
			cout << "R" << i << " --> R" << i << " - " << factor << "*R" << k << endl;
		}	
	}

}
//cout << "\nmatrix A after forward elimination = \n\n" << A << endl;

// Back substitution
// Procedure same as forward elemenation, only in opposite direction, bottom to top
if(A.getRow(n-1).getValue()[n-1]!=0){
	for(int k=n-1;k>0;k--){
		for(int i=k-1;i>=0;i--){
			row rowk = A.getRow(k);
			row rowi = A.getRow(i);
			factor = rowi.getValue()[k]/rowk.getValue()[k];
			if(factor !=0){
				A.setRow(rowi - rowk*factor,i);
				cout << "R" << i << " --> R" << i << " - " << factor << "*R" << k << endl;
			}
		}
	}

	// Now we have only diagonal elements left in the matrix.
	// Hence, finding the final solution
	for(int k=0;k<n;k++){
			row rowk = A.getRow(k);
			if(rowk.getValue()[k]!=0) X.getValue()[k] = rowk.getValue()[n]/rowk.getValue()[k];
	}
	return 1;
}
else{
	cout << "No solution exists because system of linear equations is singular";
	return 0;
} 
}

int main()
{
clock_t begin = clock();	// define clock to measure execution time
int m,n;
cout << "number of equations: ";
cin >> m;
cout << m << endl;
cout << "number of unknowns: ";
cin >> n;
cout << n << endl;
cout << "Enter Augmented Matrix in the for A | b" << endl;

matrix A(m,n+1);	// define augmented matrix of size n x n+1

column X(n);		// define column vector X of size n to store solution

// input Augmented matrix A
for(int i=0;i<m;i++){
	double *tmpA = new double[n+1];
	for(int j=0;j<n+1;j++){
		cin >> tmpA[j];
	}
	A.setRow(tmpA,i);
}

// Solve Ax=b system with gauss elimination
int Notsingular = GaussElimination(A,X);

if(Notsingular){
	cout << "\nSolution after back substitution \nX = \n" << X << endl;
}
clock_t end = clock();
double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
cout << "Elapsed Time = " << elapsed_secs << endl;

return 0;
}

