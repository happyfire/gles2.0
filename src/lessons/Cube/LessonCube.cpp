#include "eslib/Application.h"
#include "eslib/Shader.h"
#include "eslib/ShaderProgram.h"
#include "eslib/Geometry.h"
#include "esUtil/esUtil.h"

#include "LessonCube.h"

USING_NS_ESLIB


static GLuint cub_texture;

static ShaderProgramPtr g_program;
static GeometryPtr g_mesh;

int LessonCube::onInit()
{
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

	//create buffer objects
	GLfloat cubeStructure[]=
	{
		0.50, -0.50, -0.50, -0.00, 0.00,
		0.50, -0.50, 0.50, 0.33, 0.00,
		-0.50, -0.50, 0.50, 0.33, 0.33,
		-0.50, -0.50, -0.50, -0.00, 0.33,
		0.50, 0.50, -0.50, 0.67, 0.33,
		0.50, -0.50, -0.50, 0.33, 0.33,
		-0.50, -0.50, -0.50, 0.33, 0.00,
		-0.50, 0.50, -0.50, 0.67, 0.00,
		0.50, 0.50, 0.50, 0.67, 0.67,
		0.50, -0.50, 0.50, 0.33, 0.67,
		-0.50, 0.50, 0.50, 0.67, 1.00,
		-0.50, -0.50, 0.50, 0.33, 1.00,
		-0.50, 0.50, -0.50, 0.33, 1.00,
		-0.50, -0.50, -0.50, -0.00, 1.00,
		-0.50, -0.50, 0.50, -0.00, 0.67,
		-0.50, 0.50, 0.50, 0.33, 0.67,
		-0.50, 0.50, 0.50, -0.00, 0.67,
		0.50, 0.50, 0.50, -0.00, 0.33,
		0.50, 0.50, -0.50, 0.33, 0.33,
		-0.50, 0.50, -0.50, 0.33, 0.67,
	};

	GLushort cubeIndices[]=
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 5,
		5, 4, 8,
		10, 11, 9,
		9, 8, 10,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
	};

	g_mesh = new Geometry();

	std::vector<const VertexAttribute*> meshAttributes;
	VertexAttribute attributePos;
	attributePos.ElementCount = 3;
	attributePos.Name = "a_position";
	meshAttributes.push_back(&attributePos);

	VertexAttribute attributeTexcoord;
	attributeTexcoord.ElementCount = 2;
	attributeTexcoord.Name = "a_texCoord";
	meshAttributes.push_back(&attributeTexcoord);

	g_mesh->create(meshAttributes, 20, 36, true);
	g_mesh->appendVertexData(cubeStructure, sizeof(cubeStructure));
	g_mesh->appendIndexData(cubeIndices, sizeof(cubeIndices));


	//create shaders

	char* vsSrc = 0;
	esLoadFile("media/texture.vs", &vsSrc);

	char* fsSrc = 0;
	esLoadFile("media/texture.fs", &fsSrc);


	ShaderPtr vs = new Shader();
	vs->create(GL_VERTEX_SHADER, (const char*)vsSrc);

	ShaderPtr fs = new Shader();
	fs->create(GL_FRAGMENT_SHADER, (const char*)fsSrc);

	g_program = new ShaderProgram();
	g_program->create(vs,fs);

	if(!g_program->isValid())
		return 0;

	cub_texture = esCreateTextureFromTGA("media/cube.tga");

	glEnable(GL_DEPTH_TEST);	

	return TRUE;
}

void LessonCube::draw()
{
	int screenWidth = Application::GetScreenWidth();
	int screenHeight = Application::GetScreenHeight();

	glViewport(0, 0, screenWidth, screenHeight);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//----------- compute mvpMatrix ---------------------
	static float rotation = 0.0f;
	rotation += 0.1f;

	ESMatrix matRotY, matRotX, matModelView, matProjection;
	ESMatrix matModelViewProjection;

	esMatrixRotateX(matRotX, -rotation * 0.25f);
	esMatrixRotateY(matRotY, rotation);

	esMatrixMultiply(matRotY, matRotX, matModelView);

	esMatrixSetTranslate(matModelView, 0, 0, -3);

	esMatrixPerspective(matProjection, 45.0f, 0.1f, 100.0f, (float)screenWidth/screenHeight);

	esMatrixMultiply(matProjection, matModelView, matModelViewProjection);

	//-------------------------------------------------

	glUseProgram(g_program->getProgramObject());

	g_program->setUniformMatrix4fv("u_mvpMatrix", matModelViewProjection);
	g_program->setUniform("u_map", 1);//set the uniform to the desired texture unit

	
	
	//bind the texture to an texture unit
	glActiveTexture(GL_TEXTURE1);//just for illustration
	glBindTexture(GL_TEXTURE_2D, cub_texture);

	g_mesh->render(g_program);

	
}

void LessonCube::update(float dt)
{

}