#include <iostream>
#include <Eigen/Dense>
#include <cmath>


using namespace Eigen;
using namespace std;

int main(){
	Matrix<double, 5, 5> m;
	m = MatrixXd::Zero(5, 5);
	m << 00, 01, 02, 03, 04,
		10, 11, 12, 13, 14,
		20, 21, 22, 23, 24,
		30, 31, 32, 33, 34,
		40, 41, 42, 43, 44;
	cout << "m:" << endl;
	cout << m << endl;

	cout << "m<3, 3>(0, 0)" << endl;
	cout << m.block<3, 3>(0, 0) << endl;

	cout << "m<3, 3>(1, 0)" << endl;
	cout << m.block<3, 3>(1, 0) << endl;

	cout << "m<3, 3>(0, 1)" << endl;
	cout << m.block<3, 3>(0, 1) << endl;

	cout << "m<3, 3>(2, 1)" << endl;
	cout << m.block<3, 3>(2, 1) << endl;

	cout << "m<2, 1>(2, 1)" << endl;
	cout << m.block<2, 1>(2, 1) << endl;

	m.block<3, 3>(0, 0) = Matrix3d::Zero();
	cout << "mZero" << endl;
	cout << m << endl;

	Matrix3d mm; 
	mm << 
		1, 2, 3,
		4, 5, 6,
		7, 8, 9;

	cout << mm << endl;

	Vector3d iz(0, 0, 1);
	AngleAxisd aa(M_PI / 3.0, iz);
	cout << "F1(- pi / 3)" << endl;
	cout << aa.matrix() << endl;

	Vector3d iy(0, 1, 0);
	AngleAxisd ab(M_PI / 3.0, iy);
	cout << "F2(- pi / 3)" << endl;
	cout << ab.matrix() << endl;

	Vector3d ix(1, 0, 0);
	AngleAxisd ac(M_PI / 3.0, ix);
	cout << "F3(- pi / 3)" << endl;
	cout << ac.matrix() << endl;

	cout << "F1 * F2 * F3" << endl;
	cout << (aa.matrix()) * (ab.matrix()) * (ac.matrix()) << endl;

	while (1);

}

