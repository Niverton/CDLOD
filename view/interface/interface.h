#ifndef INTERFACE
#define INTERFACE
#include <GLFW/glfw3.h>
#include "inputmanager.h"
class InputManager; //forward declaration

class Interface{
	public:	
		static InputManager* inputManager;//lib-unrelated callback wrapper 
		/*
		 * size of the window
		 * */
		Interface(int width, int height);
		/*retrieve total deplacement of the mous since the creation of 
		 * the window
		 * */
		void getMousePosition(double* receiveX, double* receiveY);
		
		float getRatio();
		/*
		 * Close the window
		 * */
		void closeWindow();

		/*
		 * return true if closeWindow had been called
		 * */
		bool windowShouldClose();

		/**
		 * update the window
		 * */
		void refreshBuffer();
		
		/**
		 * Threat receved event 
		 * */	
		void threatEvents();
	//TODO should be in destructor??	
		void quit();
	private:
		GLFWwindow* window;	
		float ratio;
};
#endif
