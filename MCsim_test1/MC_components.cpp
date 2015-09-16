#include <iostream>
#include "MC.hpp"
#include <cmath>

using namespace Eigen;
using namespace MC;

Vector3d MotorPlop::get_f(){
	return Vector3d::Zero();
}
Vector3d MotorPlop::get_tau(){
	return Vector3d::Zero();
}
Vector3d MotorPlop::get_l(){
	return Vector3d::Zero();
}

