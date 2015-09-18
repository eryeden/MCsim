#include <iostream>
#include <Eigen/Dense>
#include <cmath>

//#include "Viewer/OpenGL_test.hpp"
#include "Viewer/MC_drawer.hpp"
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

static void _error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(){
	////GLFW_run();
	//GLFWwindow *glwdw = NULL;
	//GLFW_initialize(&(glwdw), _error_callback, _key_callback);
	//GL_initialize(glwdw);
	//GL_run(glwdw);
	//GLFW_deinitialize(glwdw);

	GLFW_test2 gt2;
	gt2.initialize();

	gt2.run();

	gt2.join();

}

