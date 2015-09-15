#include <iostream>
#include "MC.hpp"
#include <cmath>


void MC::update_Z(){
	Z.block<3, 3>(0, 0) = mk_sk(x.block<3, 1>(3, 0));
	Z.block<3, 3>(3, 3) = mk_B_mat(x, J, sump);
	Z.block<3, 3>(6, 0) = mk_E_mat(x);
	Z.block<3, 3>(9, 3) = mk_D_mat(x);
}

Matrix<double, 12, 12> MC::mk_Z(const Vector3d &tx){
	Matrix<double, 12, 12> tZ = MatrixXd::Zero(12, 12);
	tZ.block<3, 3>(0, 0) = mk_sk(tx.block<3, 1>(3, 0));
	tZ.block<3, 3>(3, 3) = mk_B_mat(tx, J, sump);
	tZ.block<3, 3>(6, 0) = mk_E_mat(tx);
	tZ.block<3, 3>(9, 3) = mk_D_mat(tx);
	return tZ;
}

Vector3d MC::mk_u11(const Vector3d &tx){
	double phi, theta, psi; //φ、θ、ψ
	phi = x(9);
	theta = x(10);
	psi = x(11);
	Vector3d u11;
	u11 <<
		MC_G * sin(theta),
		-MC_G * sin(phi) * cos(theta),
		-MC_G * cos(phi) * cos(theta);

	return u11;
}

Vector3d MC::mk_u12(const Vector3d &tx){
	Vector3d u12;
	double sumf = 0;
	for (int i = 0; i < n_o_m; i++){
		sumf += motorplops[i].get_f_thrust();
	}
	u12 <<
		0,
		0,
		sumf;
	u12 /= m;
	return u12;
}

Vector3d MC::mk_u2(const Vector3d &tx){
	double phi, theta, psi; //φ、θ、ψ
	phi = x(9);
	theta = x(10);
	psi = x(11);

	Matrix3d Jb_inv;
	Jb_inv <<
		1.0 / J(0, 0), 0, 0,
		0, 1.0 / J(1, 1), 0,
		0, 0, 1.0 / J(2, 2);

	Vector3d u2, tu2;
	double th;
	for (int i = 0; i < n_o_m; i++){
		th = motorplops[i].get_f_thrust();
		tu2 <<
			th * motorplops[i].r(1),
			-th * motorplops[i].r(0),
			motorplops[i].get_tau_reaction();
		u2 += tu2;
	}

	return Jb_inv * u2;
}

Matrix3d MC::mk_sk(const Vector3d &v){
	Matrix3d cp;
	cp <<    0,  v(2), -v(1),
		 -v(2),     0,  v(0),
		  v(1), -v(0),     0;
		 
	return cp;
}

Matrix3d MC::mk_B_mat(const Vector3d &x, const Matrix3d &Jb, const double &sum_p){
	Matrix3d Jb_inv;
	Jb_inv << 1.0/Jb(0, 0), 0, 0,
			  0, 1.0/Jb(1, 1), 0,
			  0, 0, 1.0/Jb(2, 2);
	Matrix3d T1;
	T1 << 0, -1, 0,
		  1,  0, 0,
		  0,  0, 0;

	return Jb_inv * (mk_sk(x.block<3, 1>(3, 0)) * Jb + (sum_p * T1));
}

Matrix3d MC::mk_E_mat(const Vector3d &x){
	double phi, theta, psi; //φ、θ、ψ
	phi = x(9);
	theta = x(10);
	psi = x(11);
//	Matrix3d E;
//	E << 
//		cos(theta) * cos(phi), sin(phi) * sin(theta) * cos(phi) - cos(phi) * sin(psi)
	//F1(-psi) * F2(-theta) * F3(-phi)
	return 
		  (AngleAxisd(-psi,   Vector3d(0, 0, 1)).matrix())
		* (AngleAxisd(-theta, Vector3d(0, 1, 0)).matrix())
		* (AngleAxisd(-phi,   Vector3d(1, 0, 0)).matrix());
}

Matrix3d MC::mk_D_mat(const Vector3d &x){
	double phi, theta, psi; //φ、θ、ψ
	phi = x(9);
	theta = x(10);
	psi = x(11);
	Matrix3d D;
	D << 
		1, sin(phi) * tan(theta), cos(phi) * tan(theta),
		0, cos(phi), -sin(phi),
		0, sin(phi) / cos(theta), cos(phi) / cos(theta);
		
	return D;
}
























