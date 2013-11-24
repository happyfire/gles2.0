// hello_triangle.cpp : Defines the entry point for the console application.
//
#include "eslib/Application.h"
#include "eslib/Shader.h"
#include "eslib/ShaderProgram.h"
#include "eslib/Geometry.h"

#include "LessonHelloTriangle.h"

USING_NS_ESLIB

//attribute loc
static GLuint colorLoc, posLoc;
//uniform loc
static GLuint ublendColorLoc, uPosOffsetLoc;

static float colorScale; 
static GLuint arrayBuffer;

static ShaderProgramPtr g_program;

static GeometryPtr g_mesh;


int LessonHelloTriangle::onInit()
{

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

	
	//get attributes loc after link
	colorLoc = glGetAttribLocation(g_program->getProgramObject(), "a_color");
	posLoc = glGetAttribLocation(g_program->getProgramObject(), "a_position");	


	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

	colorScale = 1.0f;

	//init mesh
	g_mesh = new Geometry();
	std::vector<const VertexAttribute*> meshAttributes;
	VertexAttribute attributePos;
	attributePos.ElementCount = 3;
	attributePos.Name = "a_position";
	meshAttributes.push_back(&attributePos);
	
	VertexAttribute attributeColor;
	attributeColor.ElementCount = 4;
	attributeColor.Name = "a_color";
	meshAttributes.push_back(&attributeColor);

	g_mesh->create(meshAttributes, 6, 0, true);
	
	//GLfloat vertexDatas[]=
	//{//pos, color
	//	0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
	//	-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,

	//	0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	//	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	//	0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
	//};
	//g_mesh->appendVertexData(vertexDatas, sizeof(vertexDatas));

	GLfloat vertex1Datas[]=
	{//pos, color
		0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	};

	GLfloat vertex2Datas[]=
	{
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
	};
	g_mesh->appendVertexData(vertex1Datas, sizeof(vertex1Datas));
	g_mesh->appendVertexData(vertex2Datas, sizeof(vertex2Datas));
	

	return 1;
}

void LessonHelloTriangle::update(float dt)
{
	
	colorScale -= dt*0.5;
		
	if(colorScale<0.0f)
		colorScale=1.0f;
	
}


void DrawArrayOfStructures()
{
	glUseProgram(g_program->getProgramObject());

	//set uniform
	g_program->setUniform("u_blendColor", 1.0, colorScale, 1.0, 1.0);
	g_program->setUniform("u_posOffset", 0, 0, 0);

	g_mesh->render(g_program);
}

void DrawStructureOfArrays()
{
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
	//glUseProgram(userData->programObject);
	glUseProgram(g_program->getProgramObject());

	//set uniform
	g_program->setUniform("u_blendColor", 1.0, 1.0, colorScale, 1.0);
	g_program->setUniform("u_posOffset", -1.0, 0, 0);
	//glUniform4f(ublendColorLoc, 1.0, 1.0, colorScale, 1.0);
	//glUniform3f(uPosOffsetLoc, -1.0, 0, 0);

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

void LessonHelloTriangle::draw()
{
	int screenWidth = Application::GetScreenWidth();
	int screenHeight = Application::GetScreenHeight();

	glViewport(0, 0, screenWidth, screenHeight);

	glClear(GL_COLOR_BUFFER_BIT);


	DrawArrayOfStructures();

	DrawStructureOfArrays();
}

