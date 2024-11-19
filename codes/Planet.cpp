#include "Planet.h"
#include <iostream>
#include <math.h>

using namespace std;
using namespace glm;

Planet::Planet(string name,Model* planet, float planetSpeed, float orbitRadius)//constructor
{
	this->planet = planet;
	this->speed = planetSpeed;
	this->radius = orbitRadius;
	this->planetName = name;
}

float Planet::getRotAngle(int i)//set rotation angle and return it
{
	float angle;
	if (i != 0)
	{
		angle = (float)glfwGetTime() * this->speed * 55*i/4;//0.006f
	}
	else
	{
		angle = (float)glfwGetTime() * this->speed;
	}
	this->angleRot = angle;
	return this->angleRot;
}

float Planet::getRivAngle(int i)//set rotation angle and return it
{
	float angle= (float)glfwGetTime() * this->speed * 170;//0.006f
	
	if (i == 1)
	{
		angle = angle + 10.0f;
	}
	else
	{
		angle = angle + 10.0f - pow(i,2.739);
	}
	this->angleRiv = angle;
	return this->angleRiv;
}

vec3 Planet::orbitPosition(int i)//get orbit position of the planet
{
	float x, z;
	x = this->radius * sin(PI * 2 * getRivAngle(i) / 360);
	z =	this->radius * cos(PI * 2 * getRivAngle(i) / 360);
	
	vec3 orbitPos = vec3(x, 0.0f, z);

	return orbitPos;
}

void Planet::DrawRotPlanet(ShaderLinker* sp, int i)//draw rotation planet
{
	getRotAngle(i);
	mat4 model = mat4(1.0f);
	model = rotate(model, this->angleRot, vec3(0.0f, 1.0f, 0.0f));
	
}

Model* Planet::getPlanetModel()//return planet model object
{
	return this->planet;
}

Planet::~Planet()//destructor
{
	cout << "\n" << this->planetName << " destroyed!" << endl;
}