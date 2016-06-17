#include "stdafx.h"
#include "opengGLTexture.h"

//#include "StdAfx.h" //
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"

opengGLTexture::opengGLTexture()
{
	m_ID = 0;
}


opengGLTexture::~opengGLTexture()
{
}

void opengGLTexture::PrepareTexturing(bool bEnableLighting)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	if (bEnableLighting)
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	else
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
}

void opengGLTexture::LoadFromFile(CString datoteka, int umanjenje)
{
	if (m_ID != 0) 
		Release();

	// Alokacija ID-a i kreirnjae teksture
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	// Definisanje parametra teksture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Ponavljanje po x-osi
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Ponavljanje po y-osi
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linearno priblizavanje
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linearno udaljavanje

	// Ucitavanje bitmape
	/*AUX_RGBImageRec * TextureImage;
	TextureImage = auxDIBImageLoad(datoteka);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);

	glTexImage2D(GL_TEXTURE_2D, umanjenje, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	
	if (TextureImage)
	{
		if (TextureImage->data)
			free(TextureImage->data);
		free(TextureImage);
	}*/
}

void opengGLTexture::Select()
{
	if (m_ID)
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}

void opengGLTexture::Release()
{
	if (m_ID)
	{
		glDeleteTextures(1, &m_ID);
		m_ID = 0;
	}
}

