#include "camera.h"
#include <stdio.h>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include "debug.h"
//TODO configuration file/class for all hard coded things

Camera::Camera(float ratio, float* position, float* direction, float moveSpeed, float rotationSpeed){
	this->acceleration=vec3();
	this->position=vec3(position[0],position[1],position[2]);
	this->direction=vec3(direction[0],direction[1],direction[2]);
	this->moveSpeed=moveSpeed;
	this->rotationSpeed=rotationSpeed;
	cachedViewMatrix=glm::mat4();//this is identity matrix
	projection=perspective(
			30.0f,//FOV (zoom en degrée)
			ratio,//depending size of windows 
			0.1f,// near limit
			10000.0f//far limit
			);
	debug();
}

mat4 Camera::orient(vec3 dir){
	direction=dir;
	debug();
	//return lookAt( position, position+direction , vec3(0,1,0));
}

void Camera::move(){
	position+=acceleration;
}


void Camera::accelerateForward(){
	acceleration += moveSpeed * direction;
	debug();

}

void Camera::accelerateBackward(){
	acceleration -= moveSpeed * direction;
	debug();
}
void Camera::accelerateRight(){// may be bugged if looking at up, also normed? TODO remplacer tous les constructeur int en float	
	vec3 crossProduct= cross( vec3(0,1,0), direction);	
	acceleration += moveSpeed * crossProduct;
	debug();	
	
}

void Camera::accelerateLeft(){//idem
	vec3 crossProduct= cross( vec3(0,1,0), direction);
	acceleration -= moveSpeed * crossProduct;

	debug();

}

float Camera::getRotationSpeed(){
	return rotationSpeed;
}

#ifdef DEBUG
void Camera::debug(){
	printf("\nposition : %f, %f, %f\n\
			acceleration : %f, %f, %f\n\
			direction : %f, %f, %f\n\
			norme direction : %f",\
			position[0],position[1],position[2],\
			acceleration[0], acceleration[1],acceleration[2],\
			direction[0],direction[1],direction[2],\
			length(direction));
}
#endif


