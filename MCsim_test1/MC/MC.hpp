#ifndef _MC_
#define _MC_

#include <Eigen/Dense>
using namespace Eigen;

#include <math.h>

template <typename T>
class Block{
public:
	T mass;
	Matrix<T, 3, 3> J; //慣性テンソル
	VectorBlock<T, 3> c_o_g; //構成時重心座標
	VectorBlock<T, 3> r; //重心からの距離
	virtual void calc_m_o_i(); //慣性テンソルの計算
};

template <typename T>
class Cylinder : public Block<T>{
public:
	T r;
	T h;
	void calc_m_o_i();
};

template <typename T>
class Cuboid : public Block<T>{
public:
	T w;
	T h;
	T d;
	void calc_m_o_i();
};

template <typename T>
class MotorPlop : public Block < T > {
public:
	T r;
	T h;
	T c_t;
	T c_q;
	void calc_m_o_i();
	T get_f_thrust();
	T get_tau_reaction();
};

template <typename T>
class MC{
public:
	VectorBlock<T, 12> x;
	VectorBlock<T, 12> u;
	T m;
	Matrix<T, 3, 3> J; 
	Matrix<T, 12, 12> Z;
	
	
	MotorPlop& motorplops;
	unsigned int m_o_m;

	void update_Z();
	void update();

private:
	Matrix<T, 3, 3> mk_ssm_cp(VectorBlock<T, 3> v); //外積マトリクス

};


#endif // !_MC_








