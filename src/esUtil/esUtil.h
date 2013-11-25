#ifndef ESUTIL_H
#define ESUTIL_H

#include "glcommon.h"



///
// Public Functions
//

/// load a shader, check for compile errors, print error messages to output log
/// type Type of shader (GL_VERTEX_SHADER or GL_FRAGEMENT_SHADER)
/// shaderSrc Shader source string
/// \return A new shader object on success, 0 on failure
GLuint esLoadShader(GLenum type, const char *shaderSrc);


/// create a program object, link program, errors output to log.
/// return A new program object linked with the vertex/fragment shader pair, 0 on failure
GLuint esCreateProgram(GLuint vs, GLuint fs);

/// createa a buffer object
GLuint esCreateBufferObject(GLenum type, GLsizeiptr size, const GLvoid *data);

///
// Math Functions, implemented in esMath.c
///

typedef float ESMatrix[16];

// PI/180
#define kPI180 0.017453
// 180/PI
#define k180PI 57.295780
// converts degrees to radians
#define DegreeToRadian(x) ((x)*kPI180)
// converts radians to degree
#define RadianToDegree(x) ((x)*k180PI)

void esMatrixIdentity(ESMatrix mat);
void esMatrixTranslate(ESMatrix mat, float x, float y, float z);
void esMatrixSetTranslate(ESMatrix mat, float x, float y, float z);
void esMatrixScale(ESMatrix mat, float sx, float sy, float sz);
void esMatrixRotateX(ESMatrix mat, float degrees);
void esMatrixRotateY(ESMatrix mat, float degrees);
void esMatrixRotateZ(ESMatrix mat, float degrees);
void esMatrixMultiply(ESMatrix m1, ESMatrix m2, ESMatrix result);

void esMatrixPerspective(ESMatrix matrix, float fovAngle, float nearPlane, float farPlane, float aspect);

/// Texture
GLuint esCreateTextureFromTGA(const char* tgaFilePath);

/// File
size_t esLoadFile(const char* pFilename, char** pData);


#endif //ESUTIL_H
