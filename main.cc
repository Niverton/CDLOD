
#include <stdlib.h>
#include <stdio.h>


#include "camera.h"
#include "interface.h"
#include "inputmanager.h"




int main(void)
{	
	int height=480;
	int width=640;
	float moveSpeed=1.0f;
	float rotationSpeed=0.0005f;	
	float* initialPosition= (float*) malloc(3*sizeof(float));
	initialPosition[0]=0.0f;
	initialPosition[1]=0.0f;
	initialPosition[2]=1.0f;
	Interface* interface= new Interface(width, height);	
	Camera* camera=new Camera(interface->getRatio(), initialPosition, initialPosition, moveSpeed, rotationSpeed);

	Interface::inputManager=new InputManager(interface, camera);

	while (!interface->windowShouldClose())
	{
		//update block (to put in Mover class (move all object that havent 0 as acceleration and check collision) 
		camera->move();



		//render block(to put in renderer class
		Interface::inputManager->orientCamera();	

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-interface->getRatio(), interface->getRatio(), -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef((float) glfwGetTime() * 50.f, 0.f, 1.f, 1.f);
		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();
		//essential stuff, SwapBuffer replace the ancient drawing whit the new, PollEvent process all event received since last poll event and proced them
		//TODO we should try to turn this busy wait into a lazy one see http://www.glfw.org/docs/latest/input_guide.html glfwWaitEvent()
		interface->refreshBuffer();
		interface->threatEvents();

	}
	interface->quit();
	delete(interface);
	delete(camera);
	exit(EXIT_SUCCESS);
}


