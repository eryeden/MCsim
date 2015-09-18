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




// キューブの頂点情報。
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
// キューブの面。
static const int aCubeFace [][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 }
};
// キューブに対する法線ベクトル。
static const GLdouble aCubeNormal [][3] = {
	{ 0.0, 0.0, -1.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ -1.0, 0.0, 0.0 },
	{ 0.0, -1.0, 0.0 },
	{ 0.0, 1.0, 0.0 }
};
// キューブの材質。光源の色と合わせて陰影が少し青みがかって表示される。
static const GLfloat aCubeMaterial [] = { 0.8, 0.2, 0.2, 1.0 };
// 光源。
static const GLfloat aLightColor [] = { 0.2, 0.2, 0.8, 1.0 };// 光源の色。
static const GLfloat aLight0pos [] = { 0.0, 3.0, 5.0, 1.0 };// 光源0の位置。
static const GLfloat aLight1pos [] = { 5.0, 3.0, 0.0, 1.0 };// 光源1の位置。



void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

//初期化 これよりウィンドウコンテクストを得る
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

//後始末
void GLFW_deinitialize(GLFWwindow *window){
	glfwDestroyWindow(window);
	glfwTerminate();
	return;
}

//OpenGL初期化
void GL_initialize(GLFWwindow *window){
	float ratio;
	int width, height;
	
	glfwMakeContextCurrent(window); //これで描画するウィンドウを設定するのかもしれない

	/* OpenGLの初期化  */
	glEnable(GL_DEPTH_TEST);// デプスバッファの有効化。
	glEnable(GL_CULL_FACE);// カリングの有効化。
	glEnable(GL_LIGHTING);// ライティングの有効化。
	glEnable(GL_LIGHT0);// 光源0 を有効化。
	glEnable(GL_LIGHT1);// 光源1 を有効化。
	glCullFace(GL_FRONT);// カリング。
	glLightfv(GL_LIGHT1, GL_DIFFUSE, aLightColor);// 光源1の色を設定。
	glLightfv(GL_LIGHT1, GL_SPECULAR, aLightColor);// 光源1の色を設定。

	glClearColor(1, 1, 1, 1);// glClear() で使用する色（RGBA）

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;
	glViewport(0, 0, width, height);
}

static void drawCube()
{
	// キューブの材質パラメータを設定。
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, aCubeMaterial);
	// キューブの頂点を描画。
	glBegin(GL_QUADS);
	for (size_t i = 0; i < 6; ++i)
	{
		glNormal3dv(aCubeNormal[i]);// 法線ベクトルをキューブに当てる。
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
	glColor3d(0.8, 0.8, 0.8);  // 大地の色

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

		// 透視投影。
		gluPerspective(30.0, ratio, 0.1, 500.0);
		// 視点設定前の行列をすべて平行移動（視界に収める）。
		glTranslated(0.0, 0.0, 0.0);
		// 視点の設定。
		gluLookAt(3.0*4, 4.0*4, 5.0*4, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

		drawGround();

		// 光源の位置設定 （＊重要 視点の位置を設定した後に行う） 
		glLightfv(GL_LIGHT0, GL_POSITION, aLight0pos);
		glLightfv(GL_LIGHT1, GL_POSITION, aLight1pos);

		/* 描画 */
		
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

	glfwMakeContextCurrent(window); //これで描画するウィンドウを設定するのかもしれない
	glfwSwapInterval(1);

	/* OpenGLの初期化  */
	glEnable(GL_DEPTH_TEST);// デプスバッファの有効化。
	glEnable(GL_CULL_FACE);// カリングの有効化。
	glEnable(GL_LIGHTING);// ライティングの有効化。
	glEnable(GL_LIGHT0);// 光源0 を有効化。
	glEnable(GL_LIGHT1);// 光源1 を有効化。
	glCullFace(GL_FRONT);// カリング。
	glLightfv(GL_LIGHT1, GL_DIFFUSE, aLightColor);// 光源1の色を設定。
	glLightfv(GL_LIGHT1, GL_SPECULAR, aLightColor);// 光源1の色を設定。

	glClearColor(1, 1, 1, 1);// glClear() で使用する色（RGBA）

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

		// 透視投影。
		gluPerspective(30.0, ratio, 0.1, 500.0);
		// 視点設定前の行列をすべて平行移動（視界に収める）。
		glTranslated(0.0, 0.0, 0.0);
		// 視点の設定。
		gluLookAt(3.0 * 4, 4.0 * 4, 5.0 * 4, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

		drawGround();

		// 光源の位置設定 （＊重要 視点の位置を設定した後に行う） 
		glLightfv(GL_LIGHT0, GL_POSITION, aLight0pos);
		glLightfv(GL_LIGHT1, GL_POSITION, aLight1pos);

		/* 描画 */

		//drawCube();
		Drawer_test1::Cuboid(1, 2, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwMakeContextCurrent(NULL);

	//破壊すると、JOINがこまるのでHIDEして閉じたように見せる
	//Window自体は破壊されるがコンテクストは破壊されない
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



