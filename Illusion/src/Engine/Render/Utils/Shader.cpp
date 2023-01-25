/*
 * ===================== Shader.cpp ===========================
 *                       -- ils --
 *                                         CREATE -- 2023.01.14
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The Shader Class
 * Use for shader program
 * ----------------------------
 */
#include "pch.h"

#include "Shader.h"

#include "Engine/Core/Resource/FileReader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment")
			return GL_FRAGMENT_SHADER;
		else
			return 0;
	}

	// Generate the shader program from the source code
	Shader::Shader(const std::string& filepath, const std::string& name)
		: m_Name(name)
	{

		// Read the source code from the source file
		std::string rawSource = FileReader::ReadFileBin(filepath);

		std::unordered_map<GLenum, std::string> sourceCodes;

		// Preprocessing the source code
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = rawSource.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = rawSource.find_first_of("\r\n", pos);
			ILLUSION_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = rawSource.substr(begin, eol - begin);
			ILLUSION_CORE_ASSERT(type == "vertex" || type == "fragment", "Invalid shader type specified!");
			
			size_t nextLinePos = rawSource.find_first_of("\r\n", eol);
			pos = rawSource.find(typeToken, nextLinePos);
			sourceCodes[ShaderTypeFromString(type)] = rawSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? rawSource.size() - 1 : nextLinePos));
		}

		// Get a program object.
		m_Program = glCreateProgram();

		// Only two shaders for now
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;

		for (auto& kv : sourceCodes)
		{
			GLenum type = kv.first;
			std::string& code = kv.second;

			// Create an empty vertex shader handle
			GLuint shader = glCreateShader(type);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* source = code.c_str();
			glShaderSource(shader, 1, &source, 0);

			// Compile the vertex shader
			glCompileShader(shader);
		
			// Check if the shader compiled
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				ENGINE_CORE_ERROR("Shader Compilation Failure!:\n {0}", infoLog.data());
				break;
			}

			// Attach our shaders to our program
			glAttachShader(m_Program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		// Link our program
		glLinkProgram(m_Program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_Program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_Program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_Program);
			// Don't leak shaders either.
			for (auto id : glShaderIDs)
				glDeleteShader(id);


			ENGINE_CORE_ERROR("Shaders Link Failure!:\n {0}", infoLog.data());
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIDs)
			glDetachShader(m_Program, id);

	}

	Shader::~Shader()
	{
		glDeleteProgram(m_Program);
	}


	void Shader::Bind() const
	{
		glUseProgram(m_Program);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	const std::string& Shader::GetName() const
	{
		return m_Name;
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	void Shader::UploadUniformMat3(const std::string& name, const glm::mat3& value)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_Program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(glGetUniformLocation(m_Program, name.c_str()), value.x, value.y);
	}
	void Shader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(glGetUniformLocation(m_Program, name.c_str()), value.x, value.y, value.z);
	}
	void Shader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(glGetUniformLocation(m_Program, name.c_str()), value.x, value.y, value.z, value.w);
	}

	void Shader::UploadUniformInt(const std::string& name, const int value)
	{
		glUniform1i(glGetUniformLocation(m_Program, name.c_str()), value);
	}
	void Shader::UploadUniformBool(const std::string& name, const bool value)
	{
		glUniform1i(glGetUniformLocation(m_Program, name.c_str()), value);
	}
	void Shader::UploadUniformFloat(const std::string& name, const float value)
	{
		glUniform1f(glGetUniformLocation(m_Program, name.c_str()), value);
	}


	//--------------------namespace: Illusion ends--------------------
}