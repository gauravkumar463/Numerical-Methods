/* Vector space definitions*/
// row is an row vector object 
class row{

	double *r;
	int length;   // vector length

public:
	row(){}        // default constructor

	row(int n):        // constructor when vector length is known
        length(n),
        r(new double[n])
    {}

	row(double *b, int n):     // contructor when row vector is given as an array
        length(n),
        r(b)
    {}

    double* getValue(){         // return row vector as an array
    	return r;
    }

    void setValue(double *b, int n){    // replace vector values with given array
        this->length = n;
        this->r = b;
    }

    void replaceValue(double b, int i){    // replace vector values with given array
        this->r[i] = b;
    }

    int size(){                     // return vector length
        return length;
    }

	row& operator=(const row& b) {     // assignment operator
        length = b.length;
        r = b.r;
        return *this;
    }

    row operator+(const row& b) {       // define addition operator for a row vector
        row tmp;
        tmp.length = this->length;
        tmp.r = new double[this->length];
        for(int i=0;i<this->length;i++){
        	tmp.r[i] = this->r[i]+b.r[i]; 
        } 	
        return tmp;
    }

    row operator-(const row& b) {       // define subtration operator for a row vector
        row tmp;
        tmp.length = this->length;
        tmp.r = new double[this->length];
        for(int i=0;i<this->length;i++){
        	tmp.r[i] = this->r[i]-b.r[i]; 
        }
        // cout << tmp << endl;
        return tmp;
    }

    row operator*(const double c) {     // define multiplication with a scalar operator for a row vector
        row tmp;
        tmp.length = this->length;
        tmp.r = new double[this->length];
        for(int i=0;i<this->length;i++){
        	tmp.r[i] = c*this->r[i]; 
        } 	
        return tmp;
    }

    row operator/(const double c) {    // define division with a scalar operator for a row vector
        row tmp;
        tmp.length = this->length;
        tmp.r = new double[this->length];
        for(int i=0;i<this->length;i++){
        	tmp.r[i] = this->r[i]/c; 
        } 	
        return tmp;
    }

    double maxMag() {               // return maximum element value in a row vector
    	double max=abs(this->r[0]);
    	for(int i=1;i<this->length-1;i++){
    		if(max < abs(this->r[i])) max= abs(this->r[i]);
    	}
        return max;
    }

    // define print operation for row vector
  	friend std::ostream &operator<<(std::ostream &os, const row a){  
  		for(int i=0;i<a.length;i++){
  			os << a.r[i] << "\t"; 
  		}
  		os << endl;
		return os;  
	} 

};


// column is a column vector object 
class column{

    row *c;

public:

	column(){}     // default constructor

	column(int m):     // constructor when column vector size is give
        c(new row(m))
    {}

	column(double *b, int n)   // contructor when column vector is given as an array
    {
		c->setValue(b,n);
    }

    double* getValue(){         // return column vector as an array
    	return this->c->getValue();
    }

    void setValue(double *b, int n){        // replace column vector with a given array
        return this->c->setValue(b,n);
    }

    void replaceValue(double b, int i){        // replace column vector with a given array
        return this->c->replaceValue(b,i);
    }

    int size(){             // return column vector length
        return c->size();
    }

    //print operation for column vector
  	friend std::ostream &operator<<(std::ostream &os, column a){  
		for(int i=0;i<a.size();i++){
			os << a.c->getValue()[i] << "\n"; 
		}
		return os;  
	} 
};

// define matrix as an array of row vectors
class matrix{
	row *C;
	int nrows_, ncols_;
    string type_;

public:
	matrix(int m, int n):      // matrix constructor when size of matrix is given
        nrows_(m),
        ncols_(n),
        type_("f"),
        C(new row[m])
    {
		for(int i=0;i<m;i++){
			C[i].setValue(new double[n],n);
		}
	}

    matrix(int m, int n, string type):      // matrix constructor when size of matrix is given
        nrows_(m),
        ncols_(n),
        type_(type),
        C(new row[m])
    {
        if(type == "lower" || type == "l"){
            for(int i=0;i<m;i++){
                C[i].setValue(new double[i+1],i+1);
            }
        }
        else if(type == "upper" || type == "u"){
            for(int i=0;i<m;i++){
                C[i].setValue(new double[n-i],n-i);
            }
        }
        else {
            type_ = "f";
            for(int i=0;i<m;i++){
                C[i].setValue(new double[n],n);
            }
        }
    }

    int nrows(){            // return number of rows in a matrix
        return nrows_;
    }

    int ncols(){            // return number of column in a matrix
        return ncols_;
    }

    string type(){
        return type_;
    }
    row getRow(int i){      // return ith row vector of a matrix
    	return C[i];
    }

    column getColumn(int i){        // return ith column vector of a matrix
        column col(this->nrows_);
        double *tmp = new double[nrows_];
        for(int j=0;j<nrows_;j++){
            tmp[j] = this->getRow(j).getValue()[i];
        }
        col.setValue(tmp,nrows_);
        return col;
    }

	void setRow(double *a, int i){         // replace ith row vector of the matrix with given array
		C[i].setValue(a,ncols_);
	}

	void setRow(row a, int i){             // replace ith row vector of the matrix with given row vector
		C[i].setValue(a.getValue(),a.size());
	}

	void switchRow(int i, int j){         // switch between two rows of a matrix
		row tmp;
		tmp = this->getRow(i);
		this->setRow(this->getRow(j),i);
		this->setRow(tmp, j);
	}

    matrix LU(matrix lower, matrix upper){
        for(int j=0;j<ncols_;j++){
            lower.getRow(j).replaceValue(1,j);
            
            for(int i=0;i<=j;i++){
                upper.getRow(i).replaceValue(this->getRow(i).getValue()[j],j-i);
                
                for(int k=0;k<i;k++){
                    upper.getRow(i).replaceValue(
                        upper.getRow(i).getValue()[j-i]
                        -(lower.getRow(i).getValue()[k]
                            *upper.getRow(k).getValue()[j-k]),
                        j-i
                        );
                }
            }
            for(int i=j+1;i<nrows_;i++){
                lower.getRow(i).replaceValue(
                    this->getRow(i).getValue()[j]
                        /upper.getRow(j).getValue()[0],
                    j);

                for(int k=0;k<j;k++){
                    lower.getRow(i).replaceValue(
                        lower.getRow(i).getValue()[j]
                        -(lower.getRow(i).getValue()[k]
                            *upper.getRow(k).getValue()[j-k]
                                /upper.getRow(j).getValue()[0]),
                    j);
                }
            }
        }
    }

    // define print operation for a matrix
  	friend std::ostream &operator<<(std::ostream &os, matrix A){  
        if(A.type() == "upper" || A.type() == "u"){
    		for(int i=0;i<A.nrows_;i++){
                for(int j=0;j<i;j++){
                    os << "\t";
                }
    			os << A.getRow(i) << "\n"; 
    		}
        }
        else{
            for(int i=0;i<A.nrows_;i++){
                os << A.getRow(i) << "\n"; 
            }
        }
		return os;  
	} 
};