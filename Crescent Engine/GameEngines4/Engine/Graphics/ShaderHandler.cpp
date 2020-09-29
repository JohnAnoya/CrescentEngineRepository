#include "ShaderHandler.h"

std::unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;
std::map<std::string, GLuint> ShaderHandler::programs = std::map<std::string, GLuint>();


ShaderHandler::ShaderHandler()
{

}

ShaderHandler::~ShaderHandler()
{
	OnDestroy();
}

ShaderHandler* ShaderHandler::GetInstance()
{
	if (shaderInstance.get() == nullptr)
	{
		shaderInstance.reset(new ShaderHandler());
	}
	return shaderInstance.get();	
}

void ShaderHandler::CreateProgram(const std::string& shaderName_, const std::string& vertexShaderFileName_, const std::string& fragmentShaderFileName_)
{
	std::string vertexShaderCode = ReadShader(vertexShaderFileName_);
	std::string fragementShaderCode = ReadShader(fragmentShaderFileName_);

	if (vertexShaderCode == "" || fragementShaderCode == "") 
	{
		return;
	}

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, shaderName_);
	GLuint fragementShader = CreateShader(GL_FRAGMENT_SHADER, fragementShaderCode, shaderName_);

	if (vertexShader == 0 || fragementShader == 0) 
	{
		return;
	}

	GLint linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragementShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	if (!linkResult)
	{
		GLint infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::string programString(programLog.begin(), programLog.end());
		
		Debugger::Error("Failed to link shader " + shaderName_ + " Error: " + programString, "ShaderHandler.cpp", __LINE__);
		
		glDeleteShader(vertexShader);
		glDeleteShader(fragementShader);
		glDeleteProgram(program);
	
		return;
	}

	programs[shaderName_] = program;
	glDeleteShader(vertexShader);
	glDeleteShader(fragementShader);
}

GLuint ShaderHandler::GetShader(const std::string& shaderName_)
{
	if (programs.find(shaderName_) != programs.end()) 
	{
		return programs[shaderName_];
	}
	return 0;
}

void ShaderHandler::OnDestroy()
{
	if (programs.size() > 0) {
		for (auto p : programs)
		{
			glDeleteProgram(p.second);
		}
		programs.clear();
	}
}

std::string ShaderHandler::ReadShader(const std::string& filePath_)
{
	std::string shaderCode = "";
	std::fstream file;
	file.exceptions(std::ifstream::badbit);
	try
	{
		file.open(filePath_);
		std::stringstream tmpString;
		tmpString << file.rdbuf();
		file.close();
		shaderCode = tmpString.str();
	}
	catch(std::ifstream::failure error_)
	{
		Debugger::Error("Could not read shader file " + filePath_, " ShaderHandler.cpp ", __LINE__);
		return "";
	}

	return shaderCode;
}

GLuint ShaderHandler::CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_)
{
	GLint compileResult = 0;
	GLuint shader = glCreateShader(shaderType_);
	const char* shaderCodePtr = source_.c_str();
	const int shaderCodeSize = source_.size();

	// load shader
	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (!compileResult) 
	{
		GLint infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::string shaderString(shaderLog.begin(), shaderLog.end());
		Debugger::Error("Could not compile shader: " + shaderName_ + ". Error: \n" + shaderString, "ShaderHandler.cpp", __LINE__);
		return 0;
	}

	return shader;
}
