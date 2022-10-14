

#include <fstream>
#include <iostream>
#include "shader.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);

static GLuint CreateShader(const std::string& text, GLenum shaderType);




Shader::Shader(const std::string& fileName)
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
		exit(1);
	//creating shader program
	m_program = glCreateProgram();
	
	//defined in shader.h Creates shader by loading in the file and we then know what type of shader is made
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);
	
	
	//Loop for adding all shaders to shader program
	for(unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);
		
	//Tells OPENGL what part of data to read in as what variable
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");
	
	//Links
	glLinkProgram(m_program);
	//Checks for error
	CheckShaderError(m_program, GL_LINK_STATUS,true,"Error: Program linking failed:" );
	
	
	//Validates that the shader program is valid
	glValidateProgram(m_program);
	//Checks for error
	CheckShaderError(m_program, GL_VALIDATE_STATUS,true,"Error: Program is invalid:" );
	
}


Shader::~Shader()
{
	//Loop for detaching and deleting shaders
	for(unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	
	
	
	//deletes the shader program
	glDeleteProgram(m_program);
	
	
}


//Binding Program
void Shader::Bind()
{
	glUseProgram(m_program);
}


GLuint Shader::CreateShader(const std::string& text, unsigned int shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	
	
	if(shader == 0)
		std::cerr << "Error: Shader creation failed" << std::endl;
		
	//converting string
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];
	
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();
	
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);
	
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader Compilation failed: ");
	
	return shader;
	
}



std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());
	
	std::string output;
	std::string line;
	
	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
				output.append(line + "\n");
		}
	}
	else
	{
	std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success =0;
	GLchar error[1024] = {0};
	
	if(isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader,flag, &success);
		
	if(success == GL_FALSE)
	{
		if(isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		
		std::cerr <<errorMessage << ": '" << error << "'" << std::endl;
	
	}
}
