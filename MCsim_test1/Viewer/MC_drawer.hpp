#ifndef __MC_DRAWER__
#define __MC_DRAWER__

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

//������ ������E�B���h�E�R���e�N�X�g�𓾂�
void GLFW_initialize(GLFWwindow **window, GLFWerrorfun ec, GLFWkeyfun kc);
//��n��
void GLFW_deinitialize(GLFWwindow *window);
//OpenGL������
void GL_initialize(GLFWwindow *window);

void GL_run(GLFWwindow *window);

#endif // !__MC_DRAWER__
