//Includes
#include "Application.h"

//Main Function
int main()
{
	//Creates New Application
	Application* app = new Application();

	//Runs New Application
	app->Run(1280, 720, "OpenGL Program", false);

	//Deletes App
	delete app;

	//Ends
	return 0;
}