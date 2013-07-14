#include "LessonCube.h"

static GLuint uMVPMatrixLoc;
static GLuint uTextureLoc;
static GLuint aPositionLoc;
static GLuint aTexCoordLoc;

//buffer objects name/ids
static GLuint vboStructure;
static GLuint vboIndices;

static GLuint cub_texture;

int LessonCube::onInit(ESContext* esContext)
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

	vboStructure = esCreateBufferObject(GL_ARRAY_BUFFER, 100*sizeof(GLfloat), cubeStructure);
	vboIndices = esCreateBufferObject(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(GLushort), cubeIndices);


	//create shaders

	char* vsSrc = 0;
	esLoadFile("media/texture.vs", &vsSrc);

	char* fsSrc = 0;
	esLoadFile("media/texture.fs", &fsSrc);

	GLuint vs, fs;
	vs = esLoadShader(GL_VERTEX_SHADER, vsSrc);
	fs = esLoadShader(GL_FRAGMENT_SHADER, fsSrc);

	GLuint program;
	program = esCreateProgram(vs, fs);

	UserData *userData = (UserData*)esContext->userData;
	userData->programObject = program;
		

	uMVPMatrixLoc = glGetUniformLocation(program, "u_mvpMatrix");
	uTextureLoc = glGetUniformLocation(program, "u_map");

	aPositionLoc = glGetAttribLocation(program, "a_position");
	aTexCoordLoc = glGetAttribLocation(program, "a_texCoord");

	glEnableVertexAttribArray(aPositionLoc);
	glEnableVertexAttribArray(aTexCoordLoc);

	cub_texture = esCreateTextureFromTGA("media/cube.tga");

	glEnable(GL_DEPTH_TEST);	

	return TRUE;
}

void LessonCube::draw(ESContext* esContext)
{
	glViewport(0, 0, esContext->width, esContext->height);

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

	esMatrixPerspective(matProjection, 45.0f, 0.1f, 100.0f, (float)esContext->width/esContext->height);

	esMatrixMultiply(matProjection, matModelView, matModelViewProjection);

	//-------------------------------------------------

	UserData *userData = (UserData*)esContext->userData;

	glUseProgram(userData->programObject);

	//set the uniform to MVP matrix
	glUniformMatrix4fv(uMVPMatrixLoc, 1, GL_FALSE, matModelViewProjection);

	//bind the texture to an texture unit
	glActiveTexture(GL_TEXTURE1);//just for illustration
	glBindTexture(GL_TEXTURE_2D, cub_texture);

	//set the uniform to the desired texture unit
	glUniform1i(uTextureLoc, 1);

	//bind buffer objects
	glBindBuffer(GL_ARRAY_BUFFER, vboStructure);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);

	int stride = 5*sizeof(GLfloat);
	glVertexAttribPointer(aPositionLoc, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glVertexAttribPointer(aTexCoordLoc, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(GLfloat)));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void LessonCube::update(ESContext* esContext, float dt)
{

}