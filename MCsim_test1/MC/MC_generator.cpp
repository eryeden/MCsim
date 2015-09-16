#include <iostream>
#include "MC.hpp"
#include <cmath>

using namespace Eigen;
using namespace MC;

MC::Generator::Generator()
	:
	mob(0), mom(0),
	blocks(NULL), motorplops(NULL)
{
	;
}

void MC::Generator::add(MC::Block *blk){
	blks.push_back(blk);
}

void MC::Generator::add(MC::MotorPlop *mp){
	mtrplps.push_back(mp);
	blks.push_back(mp);
}

MC::Core MC::Generator::generate_core(){
	if (mtrplps.empty() && blks.empty()){ //�����Ȃ���Ή����Ȃ�Core��Ԃ�
		return Core();
	}
	//�S�̂̊����e���\���A�d�S�������߂�
	//�d�S�Čv�Z
	double m_sum = 0; //�S����
	for (auto itr = blks.begin(); itr != blks.end(); ++itr){
		m_sum += (*itr)->mass;
	}

	Vector3d cog; //�S�̏d�S
	for (auto itr = blks.begin(); itr != blks.end(); ++itr){
		cog += (*itr)->c_o_g * (*itr)->mass;
	}
	cog /= m_sum;

	//r��� �\�����ʒu�X�V
	for (auto itr = blks.begin(); itr != blks.end(); ++itr){
		(*itr)->r = (*itr)->c_o_g - cog;
	}

	//�S�̂̊����e���\�������߂�
	Matrix3d J_sum = Matrix3d::Zero();
	Matrix3d T = Matrix3d::Zero();
	T << 
		0, 1, 1,
		1, 0, 1,
		1, 1, 0;

	for (auto itr = blks.begin(); itr != blks.end(); ++itr){
		J_sum = (*itr)->J + T * (*itr)->r.dot(((*itr)->r));
	}

	return Core(J_sum, m_sum, dt, mtrplps);


}




