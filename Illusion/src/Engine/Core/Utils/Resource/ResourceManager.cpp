/*
 * ==================== ResourceManager.cpp ====================
 *                          -- ils --
 *                                         CREATE -- 2023.01.20
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The ResourceManager class
 * Containing static helper methods
 * ----------------------------
 */
#include "pch.h"
#include "ResourceManager.h"

#include "FileReader.h"

#include <filesystem>


 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// Declare the map and assign storage to it
	std::unordered_map<std::string, Ref<Shader>> ResourceManager::m_Shaders;

	// Add shaders to the map 
	void ResourceManager::AddShader(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		ILLUSION_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	// Load and create shaders from the source file and assign them a name
	Ref<Shader> ResourceManager::LoadShader(const std::string& filepath, const std::string& name)
	{
		std::string shaderName;
		
		// If user did't assign the shader a name, its default name would be its filepath
		if (name == "")
		{
			// Extract name from filepath if user didn't specify a name for the shader
			std::filesystem::path path = filepath;
			shaderName = path.stem().string();
		}
		else
			shaderName = name;

		Ref<Shader> shader = std::make_shared<Shader>(filepath, name);

		// Add the shader to the map
		AddShader(shader);

		return shader;
	}


	Ref<Shader> ResourceManager::GetShader(const std::string& name)
	{
		ILLUSION_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found!");
		return m_Shaders[name];
	}


	//--------------------namespace: Illusion ends--------------------
}