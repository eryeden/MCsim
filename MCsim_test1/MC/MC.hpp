#ifndef _MC_
#define _MC_

#include <Eigen/Dense>
using namespace Eigen;

#define MC_G 9.80665

class MCBlock{
public:
	double mass;
	Matrix3d J; //�����e���\��
	Vector3d c_o_g; //�\�����d�S���W
	Vector3d r; //�d�S����̋���
	virtual void calc_m_o_i(); //�����e���\���̌v�Z
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
	
	MCMotorPlop* motorplops; //���[�^�[���z��擪�A�h���X
	unsigned int n_o_m;      //���[�^�[��
	double sump;

	void update();

private:
	void update_Z();
	Matrix<double, 12, 12> mk_Z(const Vector3d &x);  //��ԃx�N�g���ɂ��Z�𐶐�
	Vector3d mk_u11(const Vector3d &x); //��ԃx�N�g���ɂ��U11�𐶐�
	Vector3d mk_u12(const Vector3d &x); //U12����
	Vector3d mk_u2(const Vector3d &x); //U2����
	Matrix3d mk_sk(const Vector3d &v); //�O�σ}�g���N�X
	Matrix3d mk_B_mat(const Vector3d &x, const Matrix3d &Jb, const double &sum_p); //B�}�g���b�N�X�̐���
	Matrix3d mk_E_mat(const Vector3d &x); //��]�s��̐���
	Matrix3d mk_D_mat(const Vector3d &x); //�p���x�p��]�s��p����

};


#endif // !_MC_








