#ifndef _MC_
#define _MC_

#include <Eigen/Dense>
using namespace Eigen;

#define MC_G 9.80665

class MCBlock{
public:
	double mass;
	Matrix3d J; //慣性テンソル
	Vector3d c_o_g; //構成時重心座標
	Vector3d r; //重心からの距離
	virtual void calc_m_o_i(); //慣性テンソルの計算
};


class MCCylinder : public MCBlock{
public:
	double r;
	double h;
	void calc_m_o_i();
};


class MCCuboid : public MCBlock{
public:
	double w;
	double h;
	double d;
	void calc_m_o_i();
};


class MCMotorPlop : public MCBlock{
public:
	double R;
	double h;
	double c_t;
	double c_q;
	void calc_m_o_i();
	double get_f_thrust();
	double get_tau_reaction();
};


class MC{
public:
	Vector3d x;
	Vector3d u;
	double m;
	Matrix3d J; 
	Matrix<double, 12, 12> Z;
	
	MCMotorPlop* motorplops; //モーター部配列先頭アドレス
	unsigned int n_o_m;      //モーター個数
	double sump;

	void update();

private:
	void update_Z();
	Matrix<double, 12, 12> mk_Z(const Vector3d &x);  //状態ベクトルによりZを生成
	Vector3d mk_u11(const Vector3d &x); //状態ベクトルによりU11を生成
	Vector3d mk_u12(const Vector3d &x); //U12生成
	Vector3d mk_u2(const Vector3d &x); //U2生成
	Matrix3d mk_sk(const Vector3d &v); //外積マトリクス
	Matrix3d mk_B_mat(const Vector3d &x, const Matrix3d &Jb, const double &sum_p); //Bマトリックスの生成
	Matrix3d mk_E_mat(const Vector3d &x); //回転行列の生成
	Matrix3d mk_D_mat(const Vector3d &x); //角速度用回転行例角生成

};


#endif // !_MC_








