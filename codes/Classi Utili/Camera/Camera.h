#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "My Algebra/MyAlgebra.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};





class Camera
{
	private:
		//camera attributes
		glm::vec3 cameraPosition;
		glm::vec3 cameraDirection;
		glm::vec3 cameraRight;
		glm::vec3 cameraUp;
		//Euler angle
		float pitch; //camera rotation around x-axis
		float yaw;//camera rotation around y-axis
		//camera default settings and options
		float speed;
		float sensitivity;
		float deltaTime;
		float zoom;
		float fov;

	public:
		
		Camera(glm::vec3,glm::vec3);//constructor
		//set camera attribute
		glm::vec3 getCameraPos();
		glm::vec3 getCameraDir();
		glm::vec3 getCameraRight();
		glm::vec3 getCameraUp();
		void setCameraPos(glm::vec3);
		void setCameraDir(glm::vec3);
		void setCameraRight();
		void setCameraUp();
		//camera matrix
		glm::mat4 getMatrixView();
		//IO events
		void processKeyboard(Camera_Movement, float);
		void processMouseMovement(float , float , GLboolean);
		void processMouseScroll(float);

		//set camera option and default settings
		void setCamSpeed(float);
		void setCameSensitivity(float);
		void setCamDeltaT(float);
		void setCamPitch(float);
		void setCamYaw(float);
		void setCamZoom(float);
		void setCamFov(float);
		float getCamFov();
		float getCamSpeed();
		float getCamSensitivity();
		float getCamDeltaT();
		float getCamPitch();
		float getCamYaw();
		void updateCameraVector();
		~Camera();

};

#endif

