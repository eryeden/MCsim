#define _USE_MATH_DEFINES

#include "MC_drawer.hpp"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GlU32.Lib")
#pragma comment(lib, "pthreadVC1.lib")
#pragma comment(lib, "pthreadVSE1.lib")




// �L���[�u�̒��_���B
static const GLdouble aCubeVertex [][3] = {
	{ 0.0, 0.0, 0.0 },
	{ 1.0, 0.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ 1.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 0.0, 1.0, 1.0 }
};
// �L���[�u�̖ʁB
static const int aCubeFace [][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 }
};
// �L���[�u�ɑ΂���@���x�N�g���B
static const GLdouble aCubeNormal [][3] = {
	{ 0.0, 0.0, -1.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ -1.0, 0.0, 0.0 },
	{ 0.0, -1.0, 0.0 },
	{ 0.0, 1.0, 0.0 }
};
// �L���[�u�̍ގ��B�����̐F�ƍ��킹�ĉA�e�������݂������ĕ\�������B
static const GLfloat aCubeMaterial [] = { 0.8, 0.2, 0.2, 1.0 };
// �����B
static const GLfloat aLightColor [] = { 0.2, 0.2, 0.8, 1.0 };// �����̐F�B
static const GLfloat aLight0pos [] = { 0.0, 3.0, 5.0, 1.0 };// ����0�̈ʒu�B
static const GLfloat aLight1pos [] = { 5.0, 3.0, 0.0, 1.0 };// ����1�̈ʒu�B



void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

//������ ������E�B���h�E�R���e�N�X�g�𓾂�
void GLFW_initialize(GLFWwindow **window, GLFWerrorfun ec, GLFWkeyfun kc){
	glfwSetErrorCallback(ec);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	*window = glfwCreateWindow(640, 480, "Hello GLFW", NULL, NULL);
	if (!(*window))
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(*window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(*window, kc);
	
	return;
}

//��n��
void GLFW_deinitialize(GLFWwindow *window){
	glfwDestroyWindow(window);
	glfwTerminate();
	return;
}

//OpenGL������
void GL_initialize(GLFWwindow *window){
	float ratio;
	int width, height;
	
	glfwMakeContextCurrent(window); //����ŕ`�悷��E�B���h�E��ݒ肷��̂�������Ȃ�

	/* OpenGL�̏�����  */
	glEnable(GL_DEPTH_TEST);// �f�v�X�o�b�t�@�̗L�����B
	glEnable(GL_CULL_FACE);// �J�����O�̗L�����B
	glEnable(GL_LIGHTING);// ���C�e�B���O�̗L�����B
	glEnable(GL_LIGHT0);// ����0 ��L�����B
	glEnable(GL_LIGHT1);// ����1 ��L�����B
	glCullFace(GL_FRONT);// �J�����O�B
	glLightfv(GL_LIGHT1, GL_DIFFUSE, aLightColor);// ����1�̐F��ݒ�B
	glLightfv(GL_LIGHT1, GL_SPECULAR, aLightColor);// ����1�̐F��ݒ�B

	glClearColor(1, 1, 1, 1);// glClear() �Ŏg�p����F�iRGBA�j

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;
	glViewport(0, 0, width, height);
}

static void drawCube()
{
	// �L���[�u�̍ގ��p�����[�^��ݒ�B
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, aCubeMaterial);
	// �L���[�u�̒��_��`��B
	glBegin(GL_QUADS);
	for (size_t i = 0; i < 6; ++i)
	{
		glNormal3dv(aCubeNormal[i]);// �@���x�N�g�����L���[�u�ɓ��Ă�B
		for (size_t j = 0; j < 4; ++j)
		{
			glVertex3dv(aCubeVertex[aCubeFace[i][j]]);
		}
	}
	glEnd();
}

void drawGround(){

	double ground_max_x = 300.0;
	double ground_max_y = 300.0;
	glColor3d(0.8, 0.8, 0.8);  // ��n�̐F

	glPushMatrix();

	glBegin(GL_LINES);
	for (double ly = -ground_max_y; ly <= ground_max_y; ly += 1.0){
		glVertex3d(-ground_max_x, ly, 0);
		glVertex3d(ground_max_x, ly, 0);
	}
	for (double lx = -ground_max_x; lx <= ground_max_x; lx += 1.0){
		glVertex3d(lx, ground_max_y, 0);
		glVertex3d(lx, -ground_max_y, 0);
	}
	glEnd();

	glLoadIdentity();

	glPopMatrix();
}

void GL_run(GLFWwindow *window){
	float ratio;
	int width, height;

	GL_initialize(window);

	while (!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();



		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float) height;
		glViewport(0, 0, width, height);

		// �������e�B
		gluPerspective(30.0, ratio, 0.1, 500.0);
		// ���_�ݒ�O�̍s������ׂĕ��s�ړ��i���E�Ɏ��߂�j�B
		glTranslated(0.0, 0.0, 0.0);
		// ���_�̐ݒ�B
		gluLookAt(3.0*4, 4.0*4, 5.0*4, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

		drawGround();

		// �����̈ʒu�ݒ� �i���d�v ���_�̈ʒu��ݒ肵����ɍs���j 
		glLightfv(GL_LIGHT0, GL_POSITION, aLight0pos);
		glLightfv(GL_LIGHT1, GL_POSITION, aLight1pos);

		/* �`�� */
		
		drawCube();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void *GL_mt_run(void *p){
	GLFWwindow *window = (GLFWwindow *)p;
	GL_run(window);
	return NULL;
}




void GLFW_test2::initialize(){
	glfwSetErrorCallback(GLFW_test2::_error_callback);
	if (!glfwInit()){}
		//exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "Hello GLFW", NULL, NULL);
	if (!(window))
	{
		glfwTerminate();
		//exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, GLFW_test2::_key_callback);
}

void * GLFW_test2::executeLauncher(void *p){
	std::cout << "Execute" << std::endl;
	reinterpret_cast<GLFW_test2*>(p)->run_thread();
	return NULL;
}


void GLFW_test2::run(){
	pthread_create(
		&ctxt_thread,
		NULL,
		GLFW_test2::executeLauncher,
		this
		);

}

void GLFW_test2::run_thread(){
	float ratio;
	int width, height;

	glfwMakeContextCurrent(window); //����ŕ`�悷��E�B���h�E��ݒ肷��̂�������Ȃ�
	glfwSwapInterval(1);

	/* OpenGL�̏�����  */
	glEnable(GL_DEPTH_TEST);// �f�v�X�o�b�t�@�̗L�����B
	glEnable(GL_CULL_FACE);// �J�����O�̗L�����B
	glEnable(GL_LIGHTING);// ���C�e�B���O�̗L�����B
	glEnable(GL_LIGHT0);// ����0 ��L�����B
	glEnable(GL_LIGHT1);// ����1 ��L�����B
	glCullFace(GL_FRONT);// �J�����O�B
	glLightfv(GL_LIGHT1, GL_DIFFUSE, aLightColor);// ����1�̐F��ݒ�B
	glLightfv(GL_LIGHT1, GL_SPECULAR, aLightColor);// ����1�̐F��ݒ�B

	glClearColor(1, 1, 1, 1);// glClear() �Ŏg�p����F�iRGBA�j

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;
	glViewport(0, 0, width, height);

	while (!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float) height;
		glViewport(0, 0, width, height);

		// �������e�B
		gluPerspective(30.0, ratio, 0.1, 500.0);
		// ���_�ݒ�O�̍s������ׂĕ��s�ړ��i���E�Ɏ��߂�j�B
		glTranslated(0.0, 0.0, 0.0);
		// ���_�̐ݒ�B
		gluLookAt(3.0 * 4, 4.0 * 4, 5.0 * 4, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

		drawGround();

		// �����̈ʒu�ݒ� �i���d�v ���_�̈ʒu��ݒ肵����ɍs���j 
		glLightfv(GL_LIGHT0, GL_POSITION, aLight0pos);
		glLightfv(GL_LIGHT1, GL_POSITION, aLight1pos);

		/* �`�� */

		//drawCube();
		Drawer_test1::Cuboid(1, 2, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwMakeContextCurrent(NULL);

	//�j�󂷂�ƁAJOIN�����܂�̂�HIDE���ĕ����悤�Ɍ�����
	//Window���͔̂j�󂳂�邪�R���e�N�X�g�͔j�󂳂�Ȃ�
	glfwHideWindow(window);
}

void GLFW_test2::join(){
	while (1){
		if (window == NULL){
			break;
		}

		glfwWaitEvents();

		if (glfwWindowShouldClose(window)){
			std::cout << "CLOSE" << std::endl;
			break;
		}
	}
		
	glfwDestroyWindow(window);
	pthread_join(ctxt_thread, NULL);
}

void GLFW_test2::_error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
void GLFW_test2::_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void Drawer_test1::Cylinder(double r, double h){
	int n = 10;
	float x, y, z, dq;
	int i;

	glEnable(GL_NORMALIZE);
	dq = M_2_PI / (float) n;
	y = 0.5*h;
	glPushMatrix();
	glRotatef(-dq*180.0 / M_2_PI, 0.0, 0.1, 0.0);
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= n; i += 1){
		x = r*cos(dq*(float) i);
		z = r*sin(dq*(float) i);
		glNormal3f(x, 0, z);
		glVertex3f(x, y, z);
		glVertex3f(x, -y, z);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	for (i = 0; i<n; i += 1){
		x = r*cos(dq*(float) i);
		z = r*sin(dq*(float) i);
		glVertex3f(x, -y, z);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 1.0, 0.0);
	for (i = 0; i<n; i += 1){
		x = r*cos(dq*(float) i);
		z = r*sin(dq*(float) i);
		glVertex3f(x, y, z);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_NORMALIZE);
}


void Drawer_test1::Cuboid(double _w, double _h, double _d){
	double w, h, d;
	w = _w * 0.5;
	h = _h * 0.5;
	d = _d * 0.5;
	double points[] = {
		w, -h, d,
		w, h, d,
		w, h, -d,
		w, -h, -d,
		-w, -h, -d,
		-w, -h, d,
		-w, h, d,
		-w, h, d,
		-w, h, d,
		-w, h, -d
	};
	GLuint idx[] = {
		2, 1, 4,  4, 3, 2,
		6, 5, 1,  1, 5, 4,
		6, 7, 8,  8, 5, 6,
		7, 2, 3,  3, 8, 7,
		5, 8, 4,  4, 8, 3
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, points);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, idx);
	glDisableClientState(GL_VERTEX_ARRAY);



}



