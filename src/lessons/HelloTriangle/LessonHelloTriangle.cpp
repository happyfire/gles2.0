// hello_triangle.cpp : Defines the entry point for the console application.
//

#include "LessonHelloTriangle.h"
#include "eslib/Shader.h"
#include "eslib/ShaderProgram.h"

USING_NS_ESLIB

//attribute loc
static GLuint colorLoc, posLoc;
//uniform loc
static GLuint ublendColorLoc, uPosOffsetLoc;

static float colorScale; 
static GLuint arrayBuffer;

static ShaderProgramPtr g_program;

void InitVBO(ESContext* esContext);

int LessonHelloTriangle::onInit(ESContext *esContext)
{
	UserData *userData = (UserData*)esContext->userData;

	GLbyte vShaderStr[] =
		"uniform vec4 u_blendColor;		\n"
		"uniform vec3 u_posOffset;		\n"
		"attribute vec4 a_position;		\n"
		"attribute vec4 a_color;		\n"
		"varying vec4 v_color;			\n"
		"void main()					\n"
		"{								\n"
		"	v_color = a_color*u_blendColor;		\n"
		"	gl_Position = a_position+vec4(u_posOffset,0.0);	\n"
		"	gl_Position *= 0.5;\n"
		"	gl_Position.w = 1.0;\n"	//It's important to set w to 1.0 again, or else it will have no effect of *0.5
		"}								\n";

	GLbyte fShaderStr[] =
		"precision mediump float;					\n"
		"varying vec4 v_color;						\n"
		"void main()								\n"
		"{											\n"
		"	gl_FragColor = v_color;					\n"
		"}											\n";

	ShaderPtr vs = new Shader();
	vs->create(GL_VERTEX_SHADER, (const char*)vShaderStr);

	ShaderPtr fs = new Shader();
	fs->create(GL_FRAGMENT_SHADER, (const char*)fShaderStr);

	g_program = new ShaderProgram();
	g_program->create(vs,fs);

	if(!g_program->isValid())
		return 0;

	//GLuint vertexShader;
	//GLuint fragmentShader;
	//GLuint programObject;
	
	//Load the vertex/fragment shaders
	//vertexShader = esLoadShader(GL_VERTEX_SHADER, (const char*)vShaderStr);
	//fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, (const char*)fShaderStr);

	//Create the program object
	//programObject = esCreateProgram(vertexShader, fragmentShader);

	//if(programObject==0)
	//	return 0;

	//get uniform loc after link
	ublendColorLoc = glGetUniformLocation(g_program->getProgramObject(), "u_blendColor");
	uPosOffsetLoc = glGetUniformLocation(g_program->getProgramObject(), "u_posOffset");
	
	//get attributes loc after link
	colorLoc = glGetAttribLocation(g_program->getProgramObject(), "a_color");
	posLoc = glGetAttribLocation(g_program->getProgramObject(), "a_position");	

	//userData->programObject = g_program->getProgramObject();

	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

	colorScale = 1.0f;

	//init VBO
	InitVBO(esContext);	

	return TRUE;
}

void LessonHelloTriangle::update(ESContext *esContext, float dt)
{
	
	colorScale -= dt*0.5;
		
	if(colorScale<0.0f)
		colorScale=1.0f;
	
}

void InitVBO(ESContext* esContext)
{	
	GLfloat vertexDatas[]=
	{//pos, color
		0.0f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
	};

	arrayBuffer = esCreateBufferObject(GL_ARRAY_BUFFER, 7*sizeof(GL_FLOAT)*6, vertexDatas);	
}

void DrawArrayOfStructuresWithVBO(ESContext *esContext)
{
	UserData *userData = (UserData*)esContext->userData;

	
	glUseProgram(userData->programObject);

	glUniform4f(ublendColorLoc, colorScale, 1.0, 1.0, 1.0);
	glUniform3f(uPosOffsetLoc, 1.0, -0.1, 0);
	

	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);

	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(colorLoc);

	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (const void*)0);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (const void*)(3*sizeof(GLfloat)));

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void DrawArrayOfStructures(ESContext *esContext)
{
	UserData *userData = (UserData*)esContext->userData;

	//Use the program object
	//glUseProgram(userData->programObject);
	glUseProgram(g_program->getProgramObject());

	//set uniform
	glUniform4f(ublendColorLoc, 1.0, colorScale, 1.0, 1.0);
	glUniform3f(uPosOffsetLoc, 0, 0, 0);

	GLfloat vertexDatas[]=
	{//pos, color
		0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
	};

	//If used vbo before without VBO, should bind vbo to 0 to clear it, or else will crash ( no buffer data found)
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//color, 4f
	glEnableVertexAttribArray(colorLoc);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), vertexDatas+3);	

	//pos, 3f
	glEnableVertexAttribArray(posLoc);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), vertexDatas);	
		
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void DrawStructureOfArrays(ESContext *esContext)
{
	UserData *userData = (UserData*)esContext->userData;

	GLfloat vVertices[] = 
	{
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		
		0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	//Use the program object
	glUseProgram(userData->programObject);

	//set uniform
	glUniform4f(ublendColorLoc, 1.0, 1.0, colorScale, 1.0);
	glUniform3f(uPosOffsetLoc, -1.0, 0, 0);

	//Load the vertex data
	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f	
	};

	//If used vbo before without VBO, should bind vbo to 0 to clear it, or else will crash ( no buffer data found)
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(colorLoc);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), colors);	

	glEnableVertexAttribArray(posLoc);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), vVertices);	
	

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void LessonHelloTriangle::draw(ESContext *esContext)
{
	glViewport(0, 0, esContext->width, esContext->height);

	glClear(GL_COLOR_BUFFER_BIT);


	DrawArrayOfStructures(esContext);
	DrawArrayOfStructuresWithVBO(esContext);
	DrawStructureOfArrays(esContext);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

