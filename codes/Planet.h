#ifndef PLANET_H
#define PLANET_H

#include <Model/Model.h>
#include <Shader/ShaderLinker.h>
#include <glm/glm.hpp>

const float PI = 3.14159f;

class Planet
{
	private:
		Model* planet;
		float speed;
		float radius;
		float angleRot;
		float angleRiv;
		std::string planetName;

	public:
		Planet(std::string name,Model* planet, float planetSpeed, float orbitRadius);
		float getRotAngle(int);
		float getRivAngle(int);
		glm::vec3 orbitPosition(int);
		void DrawRotPlanet(ShaderLinker* sp, int i);
		Model* getPlanetModel();
		~Planet();


};

#endif

