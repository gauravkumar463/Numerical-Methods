using namespace std;
class vector{

	double *r;
	int length;   // vector length

public:
	vector(){}        // default constructor

	vector(int n):        // constructor when vector length is known
        length(n),
        r(new double[n])
    {}

	vector(double *b, int n):     // contructor when vector vector is given as an array
        length(n),
        r(b)
    {}

    double* getValue(){         // return vector vector as an array
    	return r;
    }

    double getValue(int n){         // return vector vector as an array
        return r[n];
    }

    void setValue(int n, double *b){    // replace vector values with given array
        this->length = n;
        this->r = b;
    }

    void setValue(int n, double b){    // replace vector values with given array
        this->r[n] = b;
    }

    int size(){                     // return vector length
        return length;
    }

	vector& operator=(const vector& b) {     // assignment operator
        length = b.length;
        r = b.r;
        return *this;
    }

    vector operator+(const vector& b) {       // define addition operator for a vector vector
        vector tmp;
        tmp.length = this->length;
        tmp.r = new double[this->length];
        for(int i=0;i<this->length;i++){
        	tmp.r[i] = this->r[i]+b.r[i]; 
        } 	
        return tmp;
    }

    vector operator-(const vector& b) {       // define subtration operator for a vector vector
        vector tmp;
        tmp.length = this->length;
        tmp.r = new double[this->length];
        for(int i=0;i<this->length;i++){
        	tmp.r[i] = this->r[i]-b.r[i]; 
        }
        // cout << tmp << endl;
        return tmp;
    }

    vector operator*(const double c) {     // define multiplication with a scalar operator for a vector vector
        vector tmp;
        tmp.length = this->length;
        tmp.r = new double[this->length];
        for(int i=0;i<this->length;i++){
        	tmp.r[i] = c*this->r[i]; 
        } 	
        return tmp;
    }

    vector operator/(const double c) {    // define division with a scalar operator for a vector vector
        vector tmp;
        tmp.length = this->length;
        tmp.r = new double[this->length];
        for(int i=0;i<this->length;i++){
        	tmp.r[i] = this->r[i]/c; 
        } 	
        return tmp;
    }

    // define print operation for vector vector
  	friend std::ostream &operator<<(std::ostream &os, const vector a){  
  		for(int i=0;i<a.length;i++){
  			os << a.r[i] << " "; 
  		}
  		os << endl;
		return os;  
	} 
};