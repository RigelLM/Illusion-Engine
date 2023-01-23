/*
 * ======================= Shader.h ===========================
 *                        -- ils --
 *                                         CREATE -- 2023.01.14
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The Shader Class
 * Use for shader program
 * ----------------------------
 */
#pragma once

#include <string>
#include <glm/glm.hpp>

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// Shader class
	class Shader
	{
	public:

		// Generate the shader program from the source code
		Shader(const std::string& filepath, const std::string& name);

		~Shader();

		void Bind() const;

		void Unbind() const;

		const std::string& GetName() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& value);
		void UploadUniformMat3(const std::string& name, const glm::mat3& value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		void UploadUniformInt(const std::string& name, const int value);
		void UploadUniformBool(const std::string& name, const bool value);
		void UploadUniformFloat(const std::string& name, const float value);

	private:

		std::string m_Name;

		uint32_t m_Program;

	};

	//--------------------namespace: Illusion ends--------------------
}