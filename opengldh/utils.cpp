#include "utils.h"
GLuint CompileShader(GLenum shaderType, const char*shaderCode) 
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);
	GLint compileResult = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) 
	{
		char szLog[1024] = { 0 };
		GLsizei logLen = 0;
		glGetShaderInfoLog(shader, 1024, &logLen, szLog);
		printf("Compile Shader fail error log : %s \nshader code :\n%s\n", szLog, shaderCode);
		glDeleteShader(shader);
		shader = 0;
	}
	return shader;
}

GLuint CreateProgram(GLuint vsShader, GLuint fsShader) 
{
	GLuint program = glCreateProgram();
	glAttachShader(program, vsShader);
	glAttachShader(program, fsShader);
	glLinkProgram(program);
	glDetachShader(program, vsShader);
	glDetachShader(program, fsShader);
	GLint nResult;
	glGetProgramiv(program, GL_LINK_STATUS, &nResult);
	if (nResult == GL_FALSE) {
		char log[1024] = { 0 };
		GLsizei writed = 0;
		glGetProgramInfoLog(program, 1024, &writed, log);
		printf("create gpu program fail,link error : %s\n", log);
		glDeleteProgram(program);
		program = 0;
	}
	return program;
}

unsigned char * LoadFileContent(const char *path, int &filesize)
{
	unsigned char*fileContent = nullptr;
	filesize = 0;
	FILE*pFile = fopen(path, "rb");
	if (pFile) {
		fseek(pFile, 0, SEEK_END);
		int nLen = ftell(pFile);
		if (nLen > 0) 
		{
			rewind(pFile);
			fileContent = new unsigned char[nLen + 1];
			fread(fileContent, sizeof(unsigned char), nLen, pFile);
			fileContent[nLen] = '\0';
			filesize = nLen;
		}
		fclose(pFile);
	}
	return fileContent;
}



GLuint CreateGPUProgram(const char* vs, const char* fs)
{
	int fileSize = 0;
	unsigned char * shaderCode = LoadFileContent(vs, fileSize);
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)shaderCode);
	delete shaderCode;
	shaderCode = LoadFileContent(fs, fileSize);
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)shaderCode);
	delete shaderCode;
	GLuint program = CreateProgram(vsShader, fsShader);

	glDeleteShader(vsShader);
	glDeleteShader(fsShader);
	return program;
}
