//http://www.glfw.org/docs/latest/input_guide.html
#include "inputmanager.h"
#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>//transforming mouse input into angle 

InputManager::InputManager(Interface* interface, Camera* camera){
	this->camera=camera;
	this->interface=interface;
}
void InputManager::upPress(){
	camera->accelerateForward();
}

void InputManager::upRelease(){
	camera->accelerateBackward();
}

void InputManager::downPress(){
	camera->accelerateBackward();
}

void InputManager::downRelease(){
	camera->accelerateForward();
}

void InputManager::leftPress(){
	camera->accelerateLeft();
}

void InputManager::leftRelease(){
	camera->accelerateRight();
}

void InputManager::rightPress(){
	camera->accelerateRight();
}

void InputManager::rightRelease(){
	camera->accelerateLeft();
}

mat4 InputManager::orientCamera(){	
	double xMouseD, yMouseD;
	interface->getMousePosition(&xMouseD, &yMouseD);	
	float xMouse= (float) xMouseD;
	float yMouse=(float) yMouseD;
	float speed = camera->getRotationSpeed(); 
	vec3 initialDir=vec3(0.0f,0.0f,1.0f);//TODO put up and right global, use more pointer 
	vec3 up= vec3(0.0f,1.0f,0.0f);
	vec3 right =vec3(1.0f,0.0f,0.0f);
	initialDir=rotate(initialDir, xMouse*speed, up); 
	initialDir=rotate(initialDir, yMouse*speed, right);
	return camera->orient(initialDir);

}

void InputManager::escapePressed(){
	interface->closeWindow();
}

