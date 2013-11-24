#ifndef ESUTIL_H
#define ESUTIL_H

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Macros

#define ESUTIL_API __cdecl
#define ESCALLBACK __cdecl


///
// Public Functions
//

void ESUTIL_API esLogMessage( const char *formatStr, ...);

/// load a shader, check for compile errors, print error messages to output log
/// type Type of shader (GL_VERTEX_SHADER or GL_FRAGEMENT_SHADER)
/// shaderSrc Shader source string
/// \return A new shader object on success, 0 on failure
GLuint ESUTIL_API esLoadShader(GLenum type, const char *shaderSrc);


/// create a program object, link program, errors output to log.
/// return A new program object linked with the vertex/fragment shader pair, 0 on failure
GLuint ESUTIL_API esCreateProgram(GLuint vs, GLuint fs);

/// createa a buffer object
GLuint ESUTIL_API esCreateBufferObject(GLenum type, GLsizeiptr size, const GLvoid *data);

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

void ESUTIL_API esMatrixIdentity(ESMatrix mat);
void ESUTIL_API esMatrixTranslate(ESMatrix mat, float x, float y, float z);
void ESUTIL_API esMatrixSetTranslate(ESMatrix mat, float x, float y, float z);
void ESUTIL_API esMatrixScale(ESMatrix mat, float sx, float sy, float sz);
void ESUTIL_API esMatrixRotateX(ESMatrix mat, float degrees);
void ESUTIL_API esMatrixRotateY(ESMatrix mat, float degrees);
void ESUTIL_API esMatrixRotateZ(ESMatrix mat, float degrees);
void ESUTIL_API esMatrixMultiply(ESMatrix m1, ESMatrix m2, ESMatrix result);

void ESUTIL_API esMatrixPerspective(ESMatrix matrix, float fovAngle, float nearPlane, float farPlane, float aspect);

/// Texture
GLuint ESUTIL_API esCreateTextureFromTGA(const char* tgaFilePath);

/// File
size_t ESUTIL_API esLoadFile(const char* pFilename, char** pData);

#ifdef __cplusplus
}
#endif

#endif //ESUTIL_H
