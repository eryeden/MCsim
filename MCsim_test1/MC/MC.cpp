#include <iostream>
#include "MC.hpp"

template <typename T>
void MC <T>::update_Z(){
	VectorBlock<T, 3> wb, faie;	
	Z.block<3, 3>(0, 0) = mk_ssm_cp()

}

template <typename T>
Matrix<T, 3, 3> MC <T>::mk_ssm_cp(VectorBlock<T, 3> &v){
	Matrix<T, 3, 3> cp;
	cp << 0,    v[2], -v[1],
		 -v[2], 0,    v[0],
		 v[1],  -v[0], 0;
	return cp;
}





























