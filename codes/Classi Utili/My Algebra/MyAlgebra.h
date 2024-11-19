#pragma once
#include <glm/glm.hpp>

namespace myA
{
	float myALength(glm::vec3);
	void printVec3(glm::vec3);
	void printFloat(float);
	glm::vec3 myANormalize(glm::vec3);
	float myADot(glm::vec3, glm::vec3);
	glm::vec3 myACross(glm::vec3, glm::vec3);
	glm::vec3 myADiff(glm::vec3, glm::vec3);
	glm::vec3 myANegVec3(glm::vec3);
	glm::vec3 myAMultiplyVecWithScalar(glm::vec3, float);
	glm::vec3 myASum(glm::vec3, glm::vec3);

}