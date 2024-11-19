#include "Camera.h"
#include <iostream>


using namespace std;
using namespace glm;
using namespace myA;//namespace of MyAlgebra

Camera::Camera(vec3 pos, vec3 front)//constructor
{
	
	//set camera position
	setCameraPos(pos);

	//set camera direction
	setCameraDir(front);

	//set camera right axis
	setCameraRight();

	//set camera up axis
	setCameraUp();

	//set camera default option 
	this->speed = 2.5f;//set speed for camera movement
	this->sensitivity = 0.25f;//set sesnitivity of the camera
	this->deltaTime = 0.0f;
	this->zoom = 100;//set cemra zoom
	this->fov = 45.0;//set camera fov

	//set euler angle
	this->yaw = -90.0f;//yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	this->pitch = 0.0f;//the horizon

	updateCameraVector();
	
}

//	CAMERA ATTRIBUTES SETTINGS

void Camera::setCameraPos(vec3 pos)//set camera position
{
	this->cameraPosition = pos;
	//std::cout << "\nPL\n";
	//printFloat(myALength(cameraPosition));
}

void Camera::setCameraDir(vec3 front)//set camera direction at where it's pointing at (z-axis)
{
	//camera direction vector is obtaining subtracting the camera position from scene 's origin vector (target-pos)
	this->cameraDirection = myANormalize(front);//scene's origin
	//this->cameraDirection = myANormalize(myADiff(this->cameraPosition, cameraTarget));//we switch the subraction order to get a vector pointing towards camera's postive z-axis
	//std::cout << "\nDL\n";
	//printFloat(myALength(cameraDirection));
}

void Camera::setCameraRight()//set camera right (x)-axis 
{
	vec3 up = vec3(0.0f, 1.0f, 0.0f);//we define a vector that points upwards
	this->cameraRight = myANormalize(myACross(this->cameraDirection,up));//cross product make us obtain a orthogal vector to up and direction
	//std::cout << "\nRL\n";
	//printFloat(myALength(cameraRight));
}

void Camera::setCameraUp()//set camera up (y)-axis
{
	this->cameraUp = myANormalize(myACross(this->cameraRight,this->cameraDirection ));//compute camera up as cross product of camera direction and camera right
	//std::cout << "\nUL\n";
	//printFloat(myALength(cameraUp));
}



vec3 Camera::getCameraDir()//return camera direction
{
	return this->cameraDirection;
}

vec3 Camera::getCameraPos()//return camera position
{
	return this->cameraPosition;
}

vec3 Camera::getCameraRight()//return camera right axis
{
	return this->cameraRight;
}

vec3 Camera::getCameraUp()//return camera up axis
{
	return this->cameraUp;
}

mat4 Camera::getMatrixView()//return the view matrix using look at matrix --> pag 98 of the book
{
	mat4 view;
	view = lookAt(this->cameraPosition, myASum(this->cameraPosition, this->cameraDirection), this->cameraUp);
	return view;
}



// CAMERA IO EVENTS

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)//update camera position when one of the WASD key is pressed to create a WALK AROUND EFFECT
{
	
	float cameraSpeed = this->speed * deltaTime;

	if (direction == FORWARD)//go forward--> go up
	{
		//we want to move along camera up axis
		vec3 p = myADiff(this->cameraPosition,myAMultiplyVecWithScalar(myANormalize(myACross(this->cameraDirection, this->cameraRight)), cameraSpeed));//update position
		setCameraPos(p);//
		//editPos(p);//edit position with the updated one
	}

	if (direction == BACKWARD)//go backward --> go down
	{
		vec3 p = myASum(this->cameraPosition, myAMultiplyVecWithScalar(myANormalize(myACross(this->cameraDirection, this->cameraRight)), cameraSpeed));//update position
		setCameraPos(p);
		//editPos(p);//edit position with the updated one
	}

	if (direction == LEFT)//go left
	{
		//this->cameraPosition = this->cameraPosition - this->cameraRight * cameraSpeed;
		vec3 p = myADiff(this->cameraPosition, myAMultiplyVecWithScalar( myANormalize( myACross(this->cameraDirection, this->cameraUp) ), cameraSpeed ) );//update position
		setCameraPos(p);
		//editPos(p);//edit position with the updated one
		
	}

	if (direction == RIGHT)//go right
	{
		vec3 p = myASum(this->cameraPosition, myAMultiplyVecWithScalar(myANormalize(myACross(this->cameraDirection, this->cameraUp)), cameraSpeed));//update position
		setCameraPos(p);
		//editPos(p);//edit position with the updated one
	}
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)//update camera direction when mouse is moved
{
	
	
	//make smooth mouse and camera movement 
	xoffset = xoffset * this->sensitivity;
	yoffset = yoffset * this->sensitivity;

	//update yaw and pitch when mouse is moved
	setCamYaw(this->yaw + xoffset);
	setCamPitch(this->pitch + yoffset);

	//PITCH CONSTRAINT --> make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (this->pitch > 89.0)
		{
			setCamPitch(89.9);
		}

		if (this->pitch < -89.0)
		{
			setCamPitch(-89.0);
		}
	}

	updateCameraVector();
}

void Camera::updateCameraVector()//update camera data
{
	//compute the new direction vector, using pitch and yaw
	vec3 front;
	front.x= cos(radians(this->yaw)) * cos(radians(this->pitch)); //from trigonometry --> page 101 of the book
	front.y = sin(radians(this->pitch)); //from trigonometry --> see page 101 of the book
	front.z = sin(radians(this->yaw)) * cos(radians(this->pitch)); //from trigonometry --> page 101 of the book
	front = myANormalize(front);
	setCameraDir(front);

	//update right and up vectors
	setCameraRight();
	setCameraUp();
}


void Camera::processMouseScroll(float yoffset)//handle mouse scrolling and zooming on scene
{	
	
	float cameraSpeed = this->speed * this->deltaTime*this->zoom;
	
	if (yoffset > 0)
	{
		//std::cout << "\ndelta time : " << deltaTime << endl;
		//cout << "offset:m " << yoffset << endl;

		//we want to move along camera direction (z) axis -->forward
		vec3 p = myASum(this->cameraPosition, myAMultiplyVecWithScalar(this->cameraDirection, cameraSpeed));//update position
		setCameraPos(p);//
	}

	if (yoffset < 0)
	{
		//we want to move along camera direction (z) axis -->backward
		vec3 p = myADiff(this->cameraPosition, myAMultiplyVecWithScalar(this->cameraDirection, cameraSpeed));//update position
		setCameraPos(p);//
	}
}


//	CAMERA OPTION SETTINGS
void Camera::setCamSpeed(float s)//set camera speed
{
	this->speed = s;
}


void Camera::setCameSensitivity(float ss)//set camera sensitivity
{
	this->sensitivity = ss;
}

void Camera::setCamDeltaT(float dt)//set camera zoom
{
	this->deltaTime = dt;
}

void Camera::setCamPitch(float p)//set camera pitch
{
	this->pitch = p;
}

void Camera::setCamYaw(float y)//set camera yaw
{
	this->yaw = y;
}

void Camera::setCamZoom(float z)//set camera zoom
{
	this->zoom = z;
}

void Camera::setCamFov(float f)//set camera field of view (FOV)
{
	if (f >= 1.0f && f <= 45.0f)
	{
		this->fov = f;
	}

	if (f <= 1.0f)
	{
		this->fov = 1.0f;
	}
	
	if (f >= 45.0f)
	{
		this->fov = 45.0f;
	}
}

float Camera::getCamFov()//return camera FOV
{
	return this->fov;
}

float Camera::getCamSpeed()//return camera speed
{
	return this->speed;
}

float Camera::getCamSensitivity()//return camera sensitivity
{
	return this->sensitivity;
}

float Camera::getCamDeltaT()//return camera zoom
{
	return this->deltaTime;
}

float Camera::getCamPitch()//return camera pitch
{
	return this->pitch;
}
float Camera::getCamYaw()//return camera yaw
{
	return this->yaw;
}



Camera::~Camera()//destructor
{
	std::cout << "\nCamera destroyed!" << std::endl;
}


