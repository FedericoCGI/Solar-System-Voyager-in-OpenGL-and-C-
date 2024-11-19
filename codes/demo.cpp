#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <irrKlang.h>


#include <Camera/Camera.h>
#include <OPENGL Window/Window.h>
#include <Shader/Shader.h>
#include <Shader/ShaderLinker.h>
#include <Texture/Texture.h>
#include <Model/Model.h>
#include <Skybox/Skybox.h>

#include "Planet.h"

#include <iostream>
#include <iomanip>






void framebuffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);
void printMat(glm::mat4);
void printFloatComp(float);

//settings
//creating a global OpenGl - GLFW window
Window* window = new Window(1900, 1060, "SOLAR SISTEM VOYAGER");
float deltaTime = 0.0;//time needed to render the last frame (time between current and last frame)
float lastFrame = 0.0; //last frame mouse position or key pressed
bool firstMouse = true;//first time that mouse enter in the window
float lastX = (float)window->getWidth() / 2.0;
float lastY = (float)window->getHeight() / 2.0;


int main()
{
	using namespace std;
	using namespace glm;
	using namespace myA; //namespace of MyAlgebra
	using namespace irrklang;

	//window IO event settings
	glfwSetFramebufferSizeCallback(window->getWindow(), framebuffer_size_callback);//risize window
	glfwSetCursorPosCallback(window->getWindow(), mouse_callback);//handle mouse events and inputs 
	glfwSetScrollCallback(window->getWindow(), scroll_callback);//handle mouse scrolling and zooming
	
	

	//SCENE SHADER

	//Build and compile a Scene Vertex Shader Program
	Shader* sceneVertexShader = new Shader("C:/Users/F£D XX)/Desktop/Solar System Voyager/Shader file/vertexShaderSourceCode.glsl", GL_VERTEX_SHADER);

	//Build and compile a Scene Fragment Shader program
	Shader* sceneFragmentShader = new Shader("C:/Users/F£D XX)/Desktop/Solar System Voyager/Shader file/fragmentShaderSourceCode.glsl", GL_FRAGMENT_SHADER);

	//Create a Scene Shader Linking program
	ShaderLinker* sceneShaderProgram = new ShaderLinker(sceneVertexShader->getShader(), sceneFragmentShader->getShader());
	
	//we don't need vertex and fragment shader anymore, so we can delete them
	glDeleteShader(sceneVertexShader->getShader());
	glDeleteShader(sceneFragmentShader->getShader());

	
	//SKYBOX SHADER

	//Build and Compile a Skybox Vertex Shader program
	Shader* skyboxVertex = new Shader("C:/Users/F£D XX)/Desktop/Solar System Voyager/Skybox file/Skybox Shader/skyboxVertexSourceCode.glsl", GL_VERTEX_SHADER);

	//Build and Compile a Skybox Fragment Shader program
	Shader* skyboxFragment = new Shader("C:/Users/F£D XX)/Desktop/Solar System Voyager/Skybox file/Skybox Shader/skyboxFragmentSourceCode.glsl", GL_FRAGMENT_SHADER);

	//Create a Skybox Shader Linking program
	ShaderLinker* skyboxProgram = new ShaderLinker(skyboxVertex->getShader(), skyboxFragment->getShader());

	//we don't need vertex and fragment shader anymore, so we can delete them
	glDeleteShader(skyboxVertex->getShader());
	glDeleteShader(skyboxFragment->getShader());



	//LOAD 3D MODEL 
	//Model* solarSystemModel = new Model("Model-file/Solar-System/Solar-System.obj");
	Model* s_un = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Sun.obj");
	Model* m_ercury = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Mercury.obj");
	Model* v_enus = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Venus.obj");
	Model* earth_moon = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Earth-Moon.obj");
	Model* m_ars = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Mars.obj");
	Model* a_steroid = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Asteroids.obj");
	Model* a_steroid2 = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Asteroids2.obj");
	Model* a_steroid3 = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Asteroids3.obj");
	Model* j_upiter = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Jupiter.obj");
	Model* s_aturn = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Saturn.obj");
	Model* u_ranus = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Uranus.obj");
	Model* n_eptune = new Model("C:/Users/F£D XX)/Desktop/Solar System Voyager/Model-file/Solar-System/Neptune.obj");
	
	
	
	//create Planet
	Planet Sun("Sun", s_un, 0.2f, 0.0f);
	Planet Mercury("Mercury", m_ercury,0.008f , 5.0f*2.0f);
	Planet Venus("Venus", v_enus, 0.007f, 10.0f+4.0f);
	Planet Earth_Moon("Heart and Moon",earth_moon, 0.006f, 14.0f+4.0f);
	Planet Mars("Mars", m_ars,0.005f, 22.0f);
	Planet Asteroids("Asteroids",a_steroid ,0.00009, 0.0f);
	Planet Asteroids2("Asteroids2",a_steroid2 ,0.00009, 0.0f);
	Planet Asteroids3("Asteroids3", a_steroid3, 0.00009, 0.0f);
	Planet Jupiter("Jupiter", j_upiter, 0.0045f, 77.0f-15.0f);
	Planet Saturn("Saturn", s_aturn, 0.004f, 100.0f-15.0f);
	Planet Uranus("Uranus", u_ranus, 0.0035f, 120.0f-15.0f);
	Planet Neptune("Neptune", n_eptune, 0.003f, 140.0f-30.0f);
	

	vector<Planet> solarSystem;
	solarSystem.push_back(Sun);
	solarSystem.push_back(Mercury);
	solarSystem.push_back(Venus);
	solarSystem.push_back(Earth_Moon);
	solarSystem.push_back(Mars);
	solarSystem.push_back(Asteroids);
	solarSystem.push_back(Asteroids2);
	solarSystem.push_back(Asteroids3);
	solarSystem.push_back(Jupiter);
	solarSystem.push_back(Saturn);
	solarSystem.push_back(Uranus);
	solarSystem.push_back(Neptune);


	//Create and Generate a Skybox CubeMap Texture 
	Texture* cubeMapTexture = new Texture(GL_TEXTURE_CUBE_MAP);

	//Skybox  configuration

	vector<string> faces
	{
		"C:/Users/F£D XX)/Desktop/Solar System Voyager/Skybox file/Milky Way/right.jpg",
		"C:/Users/F£D XX)/Desktop/Solar System Voyager/Skybox file/Milky Way/left.jpg",
		"C:/Users/F£D XX)/Desktop/Solar System Voyager/Skybox file/Milky Way/top.jpg",
		"C:/Users/F£D XX)/Desktop/Solar System Voyager/Skybox file/Milky Way/bottom.jpg",
		"C:/Users/F£D XX)/Desktop/Solar System Voyager/Skybox file/Milky Way/front.jpg",
		"C:/Users/F£D XX)/Desktop/Solar System Voyager/Skybox file/Milky Way/back.jpg"
	};//contains skybox texture faces


	//create SKYBOX ans settings
	Skybox* skybox = new Skybox(cubeMapTexture, faces);


	//create camera
	Camera* camera = new Camera(vec3(5.5f, 0.0f, 8.0f), vec3(0.0f, 0.0f, -1.0f));
	//camera->setCameSensitivity(0.1f);--> with default sensitivy value i can rotate 360 for yaw, with lower value for camera sensitivity i cannot make a 360 degree rotation
	camera->setCamSpeed(2.0f);//set camera speed for camera vomement
	camera->setCamZoom(150.f);//set camera zoom
	camera->setCamFov(45.0f);//set camera FOV
	//Edit Camera Pitch
	 //camera->setCamPitch(-5.0f);
	//camera->updateCameraVector();
	window->attachCamToWind(camera); //attach camera to window to allow camera movements as walking around the scene 

	//Import Audio
	ISoundEngine* SoundEngine = createIrrKlangDevice();
	SoundEngine->play2D("audio-file/Space Music.mp3", GL_TRUE);//play audio

	//enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);

	

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	
	//RENDER LOOP
	while (!glfwWindowShouldClose(window->getWindow()))//till the user close the window
	{

		//deltaTime prepraring for camera movement
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//process input
		window->processInput(window->getWindow(), deltaTime);



		//rendering commands
		
		//clear screen and color it
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);






		//activate Scene  Shader program before any calls to glUniform
		glUseProgram(sceneShaderProgram->getShaderProgram());

		//create transformation --> matrix transformation must be inserted in render loop if they are edited by parameter that exists only in render loop, other whise they go out of the rendering loop

		//projection matrix
		mat4 projection = mat4(1.0f);
		projection = perspective(radians(camera->getCamFov()), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 100.0f);
		sceneShaderProgram->uniformGetLocAndSendMatToShader("projection", projection);//compact istruction for get uniform location and send matrix data to the shaders		

		//view matrix
		mat4 view = camera->getMatrixView();
		sceneShaderProgram->uniformGetLocAndSendMatToShader("view", view);

		
		//model matrix

		mat4 model = mat4(1.0f); 
		model = scale(model, vec3(0.4f, 0.4f, 0.4f));	// it's a bit too big for our scene, so scale it down
		model = translate(model, vec3(0.0f, -1.55f, 3.0f)); // translate it down so it's at the center of the scene
		sceneShaderProgram->uniformGetLocAndSendMatToShader("model", model);
		

		
		
		for (int i = 0; i < solarSystem.size(); i++)
		{
			mat4 planetModel = mat4(1.0f);//matrix for planet motion
			
			

			float angle = solarSystem[i].getRotAngle(i);
			vec3 orbitPos = solarSystem[i].orbitPosition(i);
			
			
				
				
				
			planetModel = translate(planetModel, orbitPos) * rotate(planetModel, angle, vec3(0.0f, 1.0f, 0.0f));//move the planet

			if (i == 5 || i == 6 || i == 7)//scale asteroids
			{
				planetModel = scale(planetModel, vec3(0.7f, 0.7f, 0.7f));
			}



			sceneShaderProgram->uniformGetLocAndSendMatToShader("planetModel", planetModel);



			//render models
			solarSystem[i].getPlanetModel()->Draw(sceneShaderProgram);
				
				
	
		}

		


		
		

		//Activate texture Units 3
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture->getTexture());
		//get uniform skybox variable location and send texture to scene shader program
		glUniform1i(glGetUniformLocation(sceneShaderProgram->getShaderProgram(), "skybox"), 3);
		//get uniform cameraPos variable location and send to scene shader program 
		vec3 unvar = camera->getCameraPos();
		glUniform3f(glGetUniformLocation(sceneShaderProgram->getShaderProgram(), "cameraPos"), unvar.x, unvar.y, unvar.z);
		
		


		//render Skybox 
		//activate Skybox Shader Program
		glUseProgram(skyboxProgram->getShaderProgram());//activate skybox shader program

		//set view matrix
		view = mat4(mat3(camera->getMatrixView())); //do not consider translation column in camera matrix view! (skybox won't translate if camera translate)
		skyboxProgram->uniformGetLocAndSendMatToShader("view", view);
		//set projection matrix
		skyboxProgram->uniformGetLocAndSendMatToShader("projection", projection);



		//Draw SKYBOX CUBE
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture->getTexture());
		skyboxProgram->uniformGetLocAndSetText("skybox", 0);


		skybox->drawSB(skyboxProgram);







		glBindVertexArray(0); //unbind vertex array
		glUseProgram(0);











		// glfw: swap buffers and poll IO events
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();


	}

	//clear allocated memory


	delete camera;
	//delete solarSystemModel;
	delete s_un;
	delete m_ercury;
	delete v_enus;
	delete earth_moon;
	delete m_ars;
	delete a_steroid;
	delete a_steroid2;
	delete a_steroid3;
	delete j_upiter;
	delete s_aturn;
	delete u_ranus;
	delete n_eptune;
	delete sceneVertexShader;
	delete sceneFragmentShader;
	delete sceneShaderProgram;
	delete skyboxVertex;
	delete skyboxFragment;
	delete skyboxProgram;
	delete cubeMapTexture;
	delete skybox;
	delete window;
	glfwTerminate();

	return 0;
}







//Functions

void framebuffer_size_callback(GLFWwindow* window, int width, int height)//window resize
{
	glViewport(0, 0, width, height);
}



void mouse_callback(GLFWwindow* glfw_wind, double mouseX, double mouseY)//handle free cam (pitch and yaw) when mouse is clicked on window scene
{

	if (glfwGetMouseButton(glfw_wind, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//if user press left button of the mouse
	{

		glfwGetCursorPos(glfw_wind, &mouseX, &mouseY);//get cursor position

		if (firstMouse)//if mouse has been clicked for the first time 
		{
			lastX = mouseX;
			lastY = mouseY;
			firstMouse = false;//next time that mouse has been clicked, it won't be the first anymore
		}

		//std::cout << "\nMouse x: " << mouseX << std::endl;
		//std::cout << "Mouse y: " << mouseY << std::endl;

		float xoffset = mouseX - lastX;//difference between current mouse position and last mouse position
		float yoffset = lastY - mouseY; // reversed since y-coordinates go from bottom to top

		lastX = mouseX;
		lastY = mouseY;

		window->getCam()->processMouseMovement(xoffset, yoffset, true);//camera handle and configure pitch and yaw


	}

}

void scroll_callback(GLFWwindow* glfw_wind, double xoffset, double yoffset)//handle mouse scrolling and zoom in the scene
{
	window->getCam()->processMouseScroll(yoffset);
}


void printMat(glm::mat4 m)
{
	//std::cout << glm::to_string(m) << std::endl;
	for (int i = 0; i < 4; i++)//print first row 
	{
		//M is column-wise
		//each COLUMN of m is a vec4! m[0] is the 0 column-vector! So we have to write in the following way:
		printFloatComp(m[i].x);
	}

	std::cout << std::endl;

	for (int i = 0; i < 4; i++)//print second row
	{
		printFloatComp(m[i].y);
	}

	std::cout << std::endl;

	for (int i = 0; i < 4; i++)//print third row
	{
		printFloatComp(m[i].z);
	}

	std::cout << std::endl;

	for (int i = 0; i < 4; i++)//print fourth row
	{
		printFloatComp(m[i].w);
	}

	std::cout << std::endl << std::endl;

}

void printFloatComp(float f)//print float component on output
{
	std::cout << std::setw(2) << f;
}






