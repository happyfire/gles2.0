#ifndef ESUTIL_WIN_H
#define ESUTIL_WIN_H

#ifdef __cplusplus
extern "C" {
#endif

/// create win32 instance and window
GLboolean WinCreate( ESContext *esContext, const char *title);

void WinLoop( ESContext *esContext);

//int WinTGALoad (const char *fileName, char **buffer, int *width, int *height);


#ifdef __cplusplus
}
#endif

#endif //ESUTIL_WIN_H