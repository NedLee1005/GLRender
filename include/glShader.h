#ifndef GL_SHADER_H
#define GL_SHADER_H

#include <iostream>
#include <string>
#include <memory>
#include <stdlib.h>
#include <stdio.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

class glProgramObjectFromFile
{
public:
	/**
	 * Function :
	 *  Load vert shaders and frag shaders then link program. 
	 *
	 * Parameter :
	 *  Input :
	 *      string vShaderFName : vert shaders name.
	 * 		string pShaderFName : frag shaders name.
	*/
    glProgramObjectFromFile(){};
    ~glProgramObjectFromFile(){
        this->DestroyShaders();
    };
	void loadShaders(std::string vShaderFName, std::string pShaderFName)
	{
		GLint linked = 0;
        // GLint compiler;
		int ret = 0;
		char * infoLog;

        // build Shader and Programe ID
		vertShader = glCreateShader(GL_VERTEX_SHADER);
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		program = glCreateProgram();

        // Compile Shader Code 
		if (CompileShader(vShaderFName.data(), vertShader) == GL_FALSE) exit(-1);
		if (CompileShader(pShaderFName.data(), fragShader) == GL_FALSE) exit(-1);

        // Link vertex and gragment with Shader Code 
		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);

        // Link Shader Info
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLint errorBufSize, errorLength;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &errorBufSize);
	    	infoLog = new char[errorBufSize+1];
			if (!infoLog)
			{
			// Retrieve error.
				glGetProgramInfoLog(program, errorBufSize, &errorLength, infoLog);
				infoLog[errorBufSize + 1] = '\0';
				fprintf(stderr, "%s", infoLog);
				delete [] infoLog;
			}
			fprintf(stderr, "Error linking program\n");
			return;
		}

        // Activate(Bind) the Shader Code 
		// glUseProgram(program);
	}

    // return the Shader Code ID
	GLuint getProgram()
	{
		return GLuint(program);
	}
    
    // Detroy and UnBind  
	void DestroyShaders()
	{
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		glDeleteProgram(program);
		// glUseProgram(0);
	}
private:

	/**
	 * Function :
	 *  Compile shaders. 
	 * 	return 0 : fail.
	 *  return 1 : successful.
	 *
	 * Parameter :
	 *  Input :
	 *      const char * FName : shaders name.
	 * 		GLuint ShaderNum : number of shader.
	 * 
	*/
	int CompileShader(const char * FName, GLuint ShaderNum)
	{
		FILE * fptr = NULL;
	    GLint compiled = 0;
	    int ret = 0;
	    int length;
	    char * shaderSource;
	    char * infoLog;

	    fptr = fopen(FName, "rb");
	    if (fptr == NULL)
	    {
			fprintf(stderr, "Cannot open file '%s'\n", FName);
			return 0;
	    }
	    fseek(fptr, 0, SEEK_END);
	    length = ftell(fptr);
	    fseek(fptr, 0 ,SEEK_SET);

	    shaderSource = new char[length];
	    if (shaderSource == NULL)
	    {
	        fprintf(stderr, "Out of memory.\n");
	        return 0;
	    }

	    ret = fread(shaderSource, length, 1, fptr);

	    glShaderSource(ShaderNum, 1, (const char**)&shaderSource, &length);
	    glCompileShader(ShaderNum);
	    
	    delete [] shaderSource;
	    fclose(fptr);

	    glGetShaderiv(ShaderNum, GL_COMPILE_STATUS, &compiled);
	    if (!compiled)
	    {
	        // Retrieve error buffer size.
	        GLint errorBufSize, errorLength;
	        glGetShaderiv(ShaderNum, GL_INFO_LOG_LENGTH, &errorBufSize);
	    	// infoLog = new char[errorBufSize+1];
            // std::unique_ptr<GLchar[]> infoLog = std::make_unique<GLchar[]>(512);
            GLchar *infoLog = (GLchar*)calloc(256, sizeof(GLchar));
	            glGetShaderInfoLog(ShaderNum, errorBufSize, &errorLength, infoLog);
	            infoLog[errorBufSize + 1] = '\0';
	            fprintf(stderr, "%s\n", infoLog);
	        fprintf(stderr, "Error compiling shader '%s'\n", FName);
            free(infoLog);
            system("PAUSE");
	        return 0;
	    }

	    return 1;
	}
	GLuint vertShader; // Verter shader
	GLuint fragShader; // Fragment shader
	GLuint program; // OpenGL program.
};

class glProgramObjectFromC{
private:
	GLuint vertShader; // Verter shader
	GLuint fragShader; // Fragment shader
	GLuint program; // OpenGL program.

	GLuint createShader(GLenum shaderType, const char shader[]) {
		GLint isShaderCompiled;
		GLuint shaderValue = glCreateShader(shaderType);

		// 檢查 shader是否創建成功。失敗為0
		if (!shaderValue) {
			fprintf(stderr, "glCreateShader failure type =  %d, value = %d", shaderType, shaderValue);
			return 0;
		}
		glShaderSource(shaderValue, 1, &shader, NULL);
		glCompileShader(shaderValue);
		glGetShaderiv(shaderValue, GL_COMPILE_STATUS, &isShaderCompiled);
		
		if(isShaderCompiled != GL_TRUE)
		{
			fprintf(stderr, "---------- CompileShader: failed ----------\n");
			// 檢查GL日誌中是否有log，沒有則為0(log長度為0)；有值則代表有錯誤訊息(log長度不為0)
			GLint infoLenght;
			glGetShaderiv(shaderValue, GL_INFO_LOG_LENGTH, &infoLenght);

			if (infoLenght) {
				char *infoLog = (char *) malloc(infoLenght + 1);
				glGetShaderInfoLog(shaderValue, infoLenght, NULL, infoLog);
				fprintf(stderr, "shaderinfo log shader = %d\n%s\n", shaderValue, infoLog);
				free(infoLog);
				// system("PAUSE");
				exit(-1);
			}
		}
		return shaderValue;
	}
	void destroyProgram(void){
		glDeleteProgram(this->program);
		glDeleteShader(this->vertShader);
		glDeleteShader(this->fragShader);
		glUseProgram(0);
	}
public:
	glProgramObjectFromC(){}
	~glProgramObjectFromC(){
		destroyProgram();
	}
	void createPrograme(const char v[], const char f[])
	{
		this->vertShader = this->createShader(GL_VERTEX_SHADER, v);
		if(!this->vertShader){
			fprintf(stderr, "Create vertShader fail !!!\n");
			exit(-1);
		}
		this->fragShader = this->createShader(GL_FRAGMENT_SHADER, f);
		if(!this->fragShader){
			fprintf(stderr, "Create fragShader fail !!!\n");
			exit(-1);
		}
		this->program = glCreateProgram();
		glAttachShader(this->program, this->vertShader);
		glAttachShader(this->program, this->fragShader);
		glLinkProgram(this->program);
		printf("Create Shader Program Done\n");
	}
	GLuint getProgram(void){
		return this->program;
	}
};

#endif