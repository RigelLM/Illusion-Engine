#pragma once

/*****************************************************************//**
 * \file   ResourceManager.h
 * \brief  ResourceManager class, contains some static helper
 * functions
 *
 * \author Mian Li
 * \date   January 2023
 *********************************************************************/

#include "Engine/Render/Utils/Shader.h"

#include <unordered_map>


 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	class ResourceManager
	{

	public:

		// Statically store all the shaders used in the application 
		static std::unordered_map<std::string, Ref<Shader>> m_Shaders;


		// Add the shader into the map
		static void AddShader(const Ref<Shader>& shader);

		// Load and create the shader program from the file and assign them name
		static Ref<Shader> LoadShader(const std::string& filepath, const std::string& name = "");

		static Ref<Shader> GetShader(const std::string& name);

	};

	//--------------------namespace: Illusion ends--------------------
}


