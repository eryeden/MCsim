#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;


int main(){
	Matrix<double, 5, 5> m;
	m << 11, 12, 13, 14, 15,
		 21, 22, 23, 24, 25,
		 31, 32, 33, 34, 35,
		 41, 42, 43, 44; 45,
		 51, 52, 53, 54, 55;

	cout << "m:" << endl;
	//cout << m << endl;

	cout << "m<3, 3>(0, 0)" << endl;
	//cout << m.block<3, 3>(0, 0) << endl;

	cout << "m<3, 3>(1, 0)" << endl;
	//cout << m.block<3, 3>(1, 0) << endl;

	cout << "m<3, 3>(0, 1)" << endl;
	//cout << m.block<3, 3>(0, 1) << endl;

	cout << "m<3, 3>(2, 1)" << endl;
	//cout << m.block<3, 3>(2, 1) << endl;


	return 0;
}


