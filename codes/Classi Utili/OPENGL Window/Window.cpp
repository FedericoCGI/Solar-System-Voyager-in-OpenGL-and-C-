//create an OPENGL WINDOW

#include "Window.h"
#include <iostream>





using namespace std;

Window::Window(int w, int h, const char*n)//constructor of the window
{
	setWindow(w, h, n);

	//glfw settings
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window
	 this->window= glfwCreateWindow(width,height , this->name , NULL, NULL);
	if (window == NULL)
	{
		cout << "WINDOW CREATION FAILED!\n" << endl;
		glfwTerminate();
		
	}
	else
	{
		cout << "WINDOW CREATION SUCCESS!\n" << endl;
	}

	glfwMakeContextCurrent(window);//make the context of the window the MAIN CURRENT CONTEXT OF THE THREAD
	


	//Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "FAILED TO INITIALIZE GLAD\n" << endl;
		glfwTerminate();
	}
	else
	{
		cout << "GLAD INITIALIZATION SUCESSFULL!\n" << endl;
	}



}

void Window::setWindow(int w, int h, std::string n)//set window
{
	this->height = h;
	this->width = w;
	
	//set window name
	string_ToChar(n, this->name);
}


void Window::string_ToChar(std::string s, char* p)//converts std::string to a char* array considered as a string
{

	int count = 0;
	for (int j = 0; s[j] != '\0'; j++)
	{
		p[j] = s[j];
		count++;



	}
	p[count] = '\0';


}

int Window::getWidth()//return window width
{
	return width;
}

int Window::getHeight()//return window height
{
	return height;
}

GLFWwindow* Window::getWindow()//return the OPENGL window created
{
	return window;
}

void Window::attachCamToWind(Camera* cam)//attach camera cam to window
{
	this->camera = cam;
}

Camera* Window::getCam()//return camera attached to the window
{
	return this->camera;
}


void Window::processInput(GLFWwindow* window, float dt)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//if a key is pressed, otherwhise return GLFW_RELASE
	{
		glfwSetWindowShouldClose(window, true);
	}

	//CAMERA MOVEMENT MANAGEMENT
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)//go left
	{
		camera->processKeyboard(LEFT, dt);
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)//go right
	{
		camera->processKeyboard(RIGHT, dt);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)//go forward
	{
		camera->processKeyboard(FORWARD, dt);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)//go backward
	{
		camera->processKeyboard(BACKWARD, dt);
	}

	this->camera->setCamDeltaT(dt);

}
		



Window::~Window()//destructor
{
	cout << "Window " << this->name << " destroyed!\n" << endl;
}


