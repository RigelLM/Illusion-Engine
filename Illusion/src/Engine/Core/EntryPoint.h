#pragma once

/*****************************************************************//**
 * \file   EntryPoint.h
 * \brief  Entry point for the application, including main functio
 * 
 * \author Mian Li
 * \date   January 2023
 *********************************************************************/

//The Creation function of the application should be implement by the user themselves
//Since we don't know what they will call their apps and what they will do with their apps
//There cannot be a uniform implementation of the creation function
//It is implemented in the application cpp file
extern Illusion::Application* Illusion::CreateApplication();

//The main function for the whole application
//Create the application
//Run the application
//Delete the application
int main(int argc, char** argv)
{
	//Initialization of the Logging system
	Illusion::Log::Init();
	ENGINE_CORE_INFO("--------------------Logging System Initialized--------------------");

	//Creation of the app
	auto app = Illusion::CreateApplication();

	//Start the app
	app->Run();

	//Delete the app
	delete app;

	return 0;
}
