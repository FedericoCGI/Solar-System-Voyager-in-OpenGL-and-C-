#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Camera/Camera.h"



class Window
{
	private:
		int width;
		int height;
		char name[25];
		GLFWwindow* window;
		Camera* camera;


	public:
		Window(int, int, const char*);
		void setWindow(int, int, std::string);
		void string_ToChar(std::string, char*);
		int getWidth();
		int getHeight();
		void attachCamToWind(Camera*);
		Camera* getCam();

		GLFWwindow* getWindow();
		
		void processInput(GLFWwindow*, float);
		

		~Window();

};




#endif
