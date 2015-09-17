#ifndef __MC_DRAWER__
#define __MC_DRAWER__

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

//初期化 これよりウィンドウコンテクストを得る
void GLFW_initialize(GLFWwindow **window, GLFWerrorfun ec, GLFWkeyfun kc);
//後始末
void GLFW_deinitialize(GLFWwindow *window);
//OpenGL初期化
void GL_initialize(GLFWwindow *window);

void GL_run(GLFWwindow *window);

#endif // !__MC_DRAWER__
