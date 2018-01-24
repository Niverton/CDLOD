#include <GLFW/glfw3.h>
#include "interface.h"
#include "inputmanager.h"//lib-independent callbacks
#include <stdlib.h>//error control
#include <stdio.h>

/**
 * This class contain all thing related to glfw
 * */
extern InputManager* Interface::inputManager; //needed to compile
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action ==GLFW_REPEAT){
		return;
	}

#define SYMPOINT ->
#define SWITCHCASE(string) if (action==GLFW_PRESS){\
	Interface::inputManager->string##Press();\
	}\
	else{\
		Interface::inputManager->string##Release();\
	}
	switch(key){
		case GLFW_KEY_LEFT: 
			SWITCHCASE(left)
			break;

		case GLFW_KEY_UP:
			SWITCHCASE(up)
			break;

		case GLFW_KEY_RIGHT:
			SWITCHCASE(right)	
			break;

		case GLFW_KEY_DOWN:
			SWITCHCASE(down)
			break;

		case GLFW_KEY_ESCAPE:
		Interface::inputManager->escapePressed();		
		break;

	}

#undef SWITCHCASE
}


void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


Interface::Interface(int width, int height){
	ratio=(float) width/height;

	//setting up conf, we dont want to use deprecated stuff	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//printf("%s\n", glfwGetVersionString());

	//setting error callBack ( obviously before doing anything else)
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()){
		exit(EXIT_FAILURE);
	}
	//creation of the window

	window=glfwCreateWindow(width, height, "3DWorld", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//linking window whit key callbacks
	glfwSetKeyCallback(window, key_callback);


	//locking cursor (fps mode) 
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



	//focus on this window
	glfwMakeContextCurrent(window);
	//setting cursor to 0,0 (need to be after focusing window)
	glfwSetCursorPos(window,0.0, 0.0);


}



void Interface::getMousePosition(double* receiveX, double* receiveY){
	glfwGetCursorPos(window, receiveX, receiveY);	


}

bool Interface::windowShouldClose(){
	return glfwWindowShouldClose(window)==GLFW_TRUE; 
}

float Interface::getRatio(){
	return ratio;
}

void Interface::refreshBuffer(){
	glfwSwapBuffers(window);
}

void Interface::threatEvents(){
	glfwPollEvents();
}

void Interface::closeWindow(){
	glfwSetWindowShouldClose(window, GL_TRUE);
}
void Interface::quit(){
	glfwDestroyWindow(window);
	glfwTerminate();
}



