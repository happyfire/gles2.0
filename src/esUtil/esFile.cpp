#include <stdio.h>
#include <stdlib.h>
#include "esUtil.h"

size_t ESUTIL_API esLoadFile(const char* pFilename, char** pData)
{
	size_t size = 0;

	FILE* pFile = fopen(pFilename, "rb");

	if (pFile)
	{
		// Get the file size
		fseek(pFile, 0, SEEK_END);
		size = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		// read the data
		char* pTmp = new char[size+1];
		size_t BytesRead = fread(pTmp, 1, size, pFile);

		if (BytesRead != size)
		{
			delete [] pTmp;
			size = 0;
		}
		else
		{
			pTmp[size] = '\0';
			*pData = pTmp;
		}

		fclose(pFile);		
	}

	return size;
}