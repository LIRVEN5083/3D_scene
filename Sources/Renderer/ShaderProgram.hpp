#ifndef _SHADER_PROGRAM_HPP
#define _SHADER_PROGRAM_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader);
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram& operator = (ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
		~ShaderProgram();

		bool isComipled() { return programShaderID_isCompiled; }
		void use() const;
		GLuint getProgramID() const;

	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool programShaderID_isCompiled = false;
		GLuint programShaderID = 0;
	};
}

#endif