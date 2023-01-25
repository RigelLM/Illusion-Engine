/*
 * ===================== ResourceManager.h ====================
 *                          -- ils --
 *                                         CREATE -- 2023.01.20
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The ResourceManager class
 * Containing static helper methods
 * ----------------------------
 */

#pragma once

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


		// Add the shader in to the map
		static void AddShader(const Ref<Shader>& shader);

		// Load and create the shader program from the file and assign them name
		static Ref<Shader> LoadShader(const std::string& filepath, const std::string& name = "");

		static Ref<Shader> GetShader(const std::string& name);

	};

	//--------------------namespace: Illusion ends--------------------
}


