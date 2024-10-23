#include "glRender.h"

int screenWidth = 1920;
int screenHeight = 1080;

glRender::glRender(/* args */){}
glRender::~glRender(){
    glDeleteBuffers(2, &VBO[0]);
    glDeleteVertexArrays(1, &VAO);
    glDeleteTextures(1, &textUnit_YUY2);
    glDeleteTextures(1, &textUnit_RGB);
}
void glRender::glAttribInit(void){
	float v_coord[] = {
		+1.0000, +1.0000, +0.0000,
		-1.0000, +1.0000, +0.0000,
		-1.0000, -1.0000, +0.0000,
		+1.0000, +1.0000, +0.0000,
		-1.0000, -1.0000, +0.0000,
		+1.0000, -1.0000, +0.0000
		
	};

	float t_coord[] = {
		1.0000, 0.0000,
		0.0000, 0.0000,
		0.0000, 1.0000,
		1.0000, 0.0000,
		0.0000, 1.0000,
		1.0000, 1.0000
	};

	glGenBuffers(2, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(v_coord), v_coord, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(t_coord), t_coord, GL_STATIC_DRAW);

	attrIndex[0] = glGetAttribLocation(programe.getProgram(), "vPosition");
	attrIndex[1] = glGetAttribLocation(programe.getProgram(), "a_texCoord");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// GL_ELEMENT_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
			glVertexAttribPointer(attrIndex[0], 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
			glVertexAttribPointer(attrIndex[1], 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(attrIndex[0]);
		glEnableVertexAttribArray(attrIndex[1]);
	glBindVertexArray(0);

	/* 產生紋理物件. */
	glGenTextures(1, &textUnit_RGB);
	glActiveTexture(GL_TEXTURE0 + GLenum(glTextUnit::RGB));
	glBindTexture(GL_TEXTURE_2D, textUnit_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// glGenTextures(1, &textUnit);

	glGenTextures(1, &textUnit_YUY2);
	glActiveTexture(GL_TEXTURE0 + GLenum(glTextUnit::YUY2));
	glBindTexture(GL_TEXTURE_2D, textUnit_YUY2);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1280 / 2, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void glRender::glInit(void){
    programe.createPrograme(IMG_NV12_VERTEX_SHADER, IMG_YUY2_FRAG_SHADER);
    glAttribInit();
}

void glRender::imageRender(int width, int height, const unsigned char * const buf){
	int frame_size = width * height;

	/* 設定打畫面的大小. */
	glViewport(0, 0, screenWidth, screenHeight);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(programe.getProgram());
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0 + GLenum(glTextUnit::YUY2));
		glBindTexture(GL_TEXTURE_2D, textUnit_YUY2);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width / 2, height, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)buf);
		glUniform2i(glGetUniformLocation(programe.getProgram(), "text_YUYV_size"), GLint(width), GLint(height));
		glUniform1i(glGetUniformLocation(programe.getProgram(), "text_YUYV"), GLenum(glTextUnit::YUY2));
	glDrawArrays(GL_TRIANGLES, 0, 6);	
}
