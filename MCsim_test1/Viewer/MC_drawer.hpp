#ifndef __MC_DRAWER__
#define __MC_DRAWER__

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <pthread.h>

//������ ������E�B���h�E�R���e�N�X�g�𓾂�
void GLFW_initialize(GLFWwindow **window, GLFWerrorfun ec, GLFWkeyfun kc);
//��n��
void GLFW_deinitialize(GLFWwindow *window);
//OpenGL������
void GL_initialize(GLFWwindow *window);

void GL_run(GLFWwindow *window);


class GLFW_test2{
public:
	void initialize();
	void run();
	void join();

private:
	GLFWwindow *window;
	pthread_t ctxt_thread;
	
	static void* executeLauncher(void* p);

	static void _error_callback(int error, const char* description);
	static void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void run_thread();

};


class Drawer_test1{
public:
	static void Cylinder(double r, double h);
	static void Cuboid(double w, double h, double d);
};




#endif // !__MC_DRAWER__


//�o�^