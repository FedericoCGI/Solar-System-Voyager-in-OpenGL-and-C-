#include <iostream>
#include <iomanip>
#include <math.h>
#include "MyAlgebra.h"






//Functions


float myA::myALength(glm::vec3 v)//return vector v length
{
	float length = pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
	length = sqrt(length);
	return length;
}

void myA::printVec3(glm::vec3 v)//show on output vector v 
{
	std::cout << "--" << std::setw(8) << "--" << std::endl << "|";
	myA::printFloat(v.x);
	std::cout << std::setw(4) << "|";
	std::cout << std::endl << "|";
	myA::printFloat(v.y);
	std::cout << std::setw(4) << "|" << std::endl << "|";
	myA::printFloat(v.z);
	std::cout << std::setw(4) << "|" << std::endl;
	std::cout << "--" << std::setw(8) << "--" << std::endl;


}

void myA::printFloat(float f)//print float f on output
{

	std::cout << std::setiosflags(std::ios::fixed | std::ios::showpoint) << std::setprecision(1);
	if (f > 0.0)
	{
		std::cout << std::setw(5) << f;
	}
	if (f < 0.0)
	{
		std::cout << std::setw(5) << f;

	}
	if (f == 0.0)
	{
		std::cout << std::setw(3) << static_cast<unsigned>(f) << ".0";
	}
}

glm::vec3 myA::myANormalize(glm::vec3 v)//normalize vector v
{
	glm::vec3 n;

	if (myALength(v) > 0)
	{
		n.x = v.x / myALength(v);
		n.y = v.y / myALength(v);
		n.z = v.z / myALength(v);
	}
	else
	{
		std::cout << "Division per Zero not Possible!\n(Vector Lenght is NULL)";
		n = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	return n;

}

float myA::myADot(glm::vec3 v, glm::vec3 u)//compute dot product of v and u
{
	float dot = v.x * u.x + v.y * u.y + v.z * u.z;
	return dot;
}

glm::vec3 myA::myACross(glm::vec3 v, glm::vec3 u)//compute cross product of v and u
{
	glm::vec3 k;
	k.x = v.y * u.z - v.z * u.y;
	k.y = v.z * u.x - v.x * u.z;
	k.z = v.x * u.y - v.y * u.x;

	return k;
}

glm::vec3 myA::myADiff(glm::vec3 v, glm::vec3 u)//compute difference of v and u
{
	glm::vec3 d;

	d.x = v.x - u.x;
	d.y = v.y - u.y;
	d.z = v.z - u.z;

	return d;

}

glm::vec3 myA::myANegVec3(glm::vec3 v)//negation of vector v
{
	glm::vec3 k;

	k.x = -v.x;
	k.y = -v.y;
	k.z = -v.z;

	return k;
}

glm::vec3 myA::myAMultiplyVecWithScalar(glm::vec3 v, float s)//multiply vector v with scalar s
{
	glm::vec3 m;

	m.x = v.x * s;
	m.y = v.y * s;
	m.z = v.z * s;

	return m;
}

glm::vec3 myA::myASum(glm::vec3 v, glm::vec3 u)//compute sum of vector v and vector u
{
	glm::vec3 s;
	s.x = v.x + u.x;
	s.y = v.y + u.y;
	s.z = v.z + u.z;

	return s;
}
