#include "stdafx.h"
#include "openGLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\GLAUX.H"
#include "GL\glut.h"
#include "math.h"
#include "vec3.h"

#define M_PI 3.141592653589793

openGLRenderer::openGLRenderer()
{
	posX = 20;
	posY = 12;
	posZ = 20;
	pogledX = 0;
	pogledY = 5;
	pogledZ = 0;
	zoom = -20;
	rotationAngle = 0;

	cameraVectorX = 0;
	cameraVectorY = 1;
	cameraVectorZ = 0;

	// Osvetljenje

    light_Position[0] = 10;
	light_Position[1] = 20;
	light_Position[2] = 10;
	light_Position[3] = 1;
}


openGLRenderer::~openGLRenderer()
{
}

bool openGLRenderer::CreateGLContext(CDC * pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0)
		return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult)
		return false;

	m_hrc = wglCreateContext(pDC->m_hDC);

	if (!m_hrc)
		return false;

	return true;
}

void openGLRenderer::PrepareScene(CDC * pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//--------------------------------
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	PrepareLighting(); // Osvetljenje

	//--------------------------------
	wglMakeCurrent(NULL, NULL);
}

void openGLRenderer::DestroyScene(CDC * pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ...
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void openGLRenderer::Reshape(CDC * pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	m_aspect = (float)w / (float)h;
    gluPerspective(40, m_aspect, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void openGLRenderer::DrawScene(CDC * pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//--------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(posX, posY, posZ, pogledX, pogledY, pogledZ, cameraVectorX, cameraVectorY, cameraVectorZ);

	// --- Osvetljavanje ---
	glLightfv(GL_LIGHT1, GL_POSITION, light_Position);

	/*// --- Materijal zid ---
	GLfloat wall_amb[] = { 0.0, 0.0, 0.2, 0.0 };
	GLfloat wall_dif[] = { 0.6, 0.6, 0.4, 0.0 };
	GLfloat wall_emission[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat wall_specular[] = { 1.0, 1.0, 1.0, 0.0 };
	float shiness = 128;
	PrepareMaterials(wall_amb, wall_dif, wall_specular, wall_emission, shiness);

	// Crtanje zida
	DrawWalls(20, 40);
	
	// --- Materijal sto ---
	GLfloat table_amb[] = { 0.0, 0.0, 0.2, 0.0 };
	GLfloat table_dif[] = { 0.9, 0.4, 0.1, 0.0 };
	GLfloat table_emission[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat table_specular[] = { 1.0, 1.0, 1.0, 0.0 };
	shiness = 7;
	PrepareMaterials(table_amb, table_dif, table_specular, table_emission, shiness);

	// Crtanje stola
	DrawTable(2.0, 0.0, 0.0, 5.0, 8.0, 5.0);


	GLfloat lamp_amb[] = { 0.0, 0.0, 0.2, 0.0 };
	GLfloat lamp_dif[] = { 1.0, 0.0, 0.0, 0.0 };
	GLfloat lamp_emission[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat lamp_specular[] = { 1.0, 1.0, 1.0, 0.0 };
	shiness = 80;
	PrepareMaterials(lamp_amb, lamp_dif, lamp_specular, lamp_emission, shiness);

	// Crtanje lampe
	DrawLamp();*/

	// ISPIT VEZBA
	// --------------------------
	//DrawTestBox(2.0, 2.0, 2.0);
	Testing();
	// --------------------------


	glFlush();
	//-------------------------------
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void openGLRenderer::DrawWalls(double a, double b)
{
	glNormal3f(0.0, 0.0, -1.0);
	// zadnji zid
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.65, 0.65, 0.65);

	glVertex3f(0.0, a, 0.0);
	glVertex3f(b, a, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(b, 0.0, 0.0);

	glEnd();

	glNormal3f(0.0, -1.0, 0.0); // -1/1 ?
	// Pod
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.5, 0.5, 0.5);

	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(b, 0.0, 0.0);
	glVertex3f(0.0, 0.0, a);
	glVertex3f(b, 0.0, a);
	
	glEnd();

	glNormal3f(1.0, 0.0, 0.0);
	// levi zid
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.6, 0.6, 0.6);

	glVertex3f(0, 0, 0);
	glVertex3f(0, a, 0);
	glVertex3f(0, 0, a);
	glVertex3f(0, a, a);

	glEnd();

	// Za testiranje tacaka
	/*glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.0, 0.0);
	glEnd();*/
}

void openGLRenderer::DrawTable(double x, double y, double z, double sirina, double duzina, double visina)
{
	// Dimenzija table
	double tablaSirina, tablaDuzina, tablaVisina;
	tablaSirina = sirina;
	tablaDuzina = duzina;
	tablaVisina = 0.2;

	// Domenzije noge stola
	double nogaSirina, nogaDuzina, nogaVisina;
	nogaSirina = 0.25;
	nogaVisina = visina - tablaVisina;
	nogaDuzina = 0.25;

	// Pomeraj noge
	double offset = 0.5;

	// Boja noge
	glColor3f(0.0, 1.0, 0.0);

	// -- 1. Zadnja leva noga stola --
	glPushMatrix();
	glTranslatef(x + offset, y + nogaVisina / 2, z + nogaSirina / 2); // Pozicioniranje noge
	DrawBox(nogaSirina, nogaVisina, nogaDuzina); // Kreiranje noge
	glPopMatrix();
	// -- 2. Zadnja desna noga stola --
	glPushMatrix();
	glTranslatef(x + tablaDuzina - nogaDuzina - offset, y + nogaVisina / 2, z + nogaSirina / 2); // Pozicioniranje noge
	DrawBox(nogaSirina, nogaVisina, nogaDuzina); // Kreiranje noge
	glPopMatrix();
	// -- 3. Prednja leva noga stola --
	glPushMatrix();
	glTranslatef(x + offset, y + nogaVisina / 2, z + tablaSirina - nogaSirina / 2);
	DrawBox(nogaSirina, nogaVisina, nogaDuzina); // Kreiranje noge
	glPopMatrix();
	// -- 4. Prednja desna noga stola --
	glPushMatrix();
	glTranslatef(x + tablaDuzina - nogaDuzina / 2 - offset, y + nogaVisina / 2, z + tablaSirina - nogaSirina / 2);
	DrawBox(nogaSirina, nogaVisina, nogaDuzina); // Kreiranje noge
	glPopMatrix();


	//------TABLA STOLA-------//
	glColor3f(0.65, 0.50, 0.39);
	glPushMatrix();
	glTranslatef(x + tablaDuzina / 2, nogaVisina - 2.3 + nogaVisina / 2, z + tablaSirina / 2);
	DrawBox(tablaDuzina + 1, tablaVisina, tablaSirina);
	glPopMatrix();

	// -- Dodatak ispod stola --
	glColor3f(0.5, 0.25, 0.3);
	glPushMatrix();
	glTranslatef(x + tablaDuzina / 2, nogaVisina - 2.3 + nogaVisina / 2 - 3 *tablaVisina + 0.1, z + tablaSirina / 2);
	DrawBox(tablaDuzina, tablaVisina * 4, tablaSirina * 0.9);
	glPopMatrix();
}

void openGLRenderer::DrawBox(double a, double b, double c)
{
	glBegin(GL_QUADS);

	glNormal3d(0.0, 0.0, 1.0);
	//Prednja stranica
	glVertex3d(-a / 2, b / 2, c / 2);
	glVertex3d(-a / 2, -b / 2, c / 2);
	glVertex3d(a / 2, -b / 2, c / 2);
	glVertex3d(a / 2, b / 2, c / 2);

	glNormal3d(1.0, 0.0, 0.0);
	// Desna stranica
	glVertex3d(a / 2, b / 2, c / 2);
	glVertex3d(a / 2, -b / 2, c / 2);
	glVertex3d(a / 2, -b / 2, -c / 2);
	glVertex3d(a / 2, b / 2, -c / 2);

	glNormal3d(0.0, 0.0, -1.0);
	// Zadnja stranica
	glVertex3d(a / 2, b / 2, -c / 2);
	glVertex3d(a / 2, -b / 2, -c / 2);
	glVertex3d(-a / 2, b / 2, -c / 2);
	glVertex3d(-a / 2, -b / 2, -c / 2);

	glNormal3d(-1.0, 0.0, 0.0);
	// Leva stranica
	glVertex3d(-a / 2, b / 2, -c / 2);
	glVertex3d(-a / 2, -b / 2, -c / 2);
	glVertex3d(-a / 2, b / 2, c / 2);
	glVertex3d(-a / 2, -b / 2, c / 2);

	glNormal3d(0.0, 1.0, 0.0);
	// Gornja stranica
	glVertex3d(-a / 2, b / 2, c / 2);
	glVertex3d(a / 2, b / 2, c / 2);
	glVertex3d(a / 2, b / 2, -c / 2);
	glVertex3d(-a / 2, b / 2, -c / 2);

	glNormal3d(0.0, -1.0, 0.0);
	// Donja stranica
	glVertex3d(-a / 2, -b / 2, -c / 2);
	glVertex3d(a / 2, -b / 2, -c / 2);
	glVertex3d(a / 2, -b / 2, c / 2);
	glVertex3d(-a / 2, -b / 2, c / 2);

	glEnd();
	
}

void openGLRenderer::DrawLamp()
{
	GLdouble eqn[4] = { 0.0, 1.0, 0.0, 0.0 };

	glPushMatrix();
	// translate
	glTranslatef(5.5, 5, 2);
	// rotate
	//glRotatef(90,0,1,0);

	// -- Podloga --
	glColor3f(1.0, 0.0, 0.0);
	//DrawHalfSphere(24, 24, 0.5);
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);
	// Sfera
	glutSolidSphere(0.45, 100, 100);
	glDisable(GL_CLIP_PLANE0);

	// -- Donja drska --
	glPushMatrix();
	glTranslatef(0.0, 2.0, 1.0);
	glRotatef(30, 1.0, 0.0, 0.0);
	DrawBox(0.2, 4.0, 0.2);
	glPopMatrix();

	// -- Gornja drska --
	glPushMatrix();
	glTranslatef(0.0, 5.0, 1.0);
	glRotatef(-45, 1.0, 0.0, 0.0);
	DrawBox(0.2, 3.0, 0.2);
	glPopMatrix();

	// -- Zglob --
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	glTranslatef(0, 3.8, 2.0);
	gluSphere(quadratic, 0.2, 24, 24);
	gluDeleteQuadric(quadratic);
	glPopMatrix();

	// -- Vrat --
	glPushMatrix();
	glTranslatef(0.0, 6.0, 0.10);
	glRotatef(45, 1.0, 0.0, 0.0);
	DrawBox(0.3, 1.0, 0.3);
	/*quadratic = gluNewQuadric();
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	glTranslatef(0.0, 6.5, 0.45);
	//glRotatef(100, 0.0, 1.0, 0.0);
	glRotatef(135, 1.0, 0.0, 0.0);
	gluCylinder(quadratic, 0.25, 0.25, 1, 24, 24);
	gluDeleteQuadric(quadratic);*/
	glPopMatrix();

	// -- Glava --
	glPushMatrix();

	glPopMatrix();
	glTranslatef(0.0, 5.25, -0.7);
	glRotatef(45, 1.0, 0.0, 0.0);
	//glRotatef(30, 0.0, 0.0, 1.0);
	//DrawHalfSphere(24, 24, 0.8);
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);
	glutSolidSphere(0.8, 100, 100);
	glDisable(GL_CLIP_PLANE0);

	glutSolidSphere(0.25, 100, 100);
	glPopMatrix();
}

// scalex - scaling of sphere around x - axis
// scaley - scaling of sphere around y - axis
// r - radius of sphere
void openGLRenderer::DrawHalfSphere(int scaley, int scalex, float r)
{
	if (scaley > 30 || scalex > 30)
		return;

	GLfloat v[30 * 30][3];

	for (int i = 0; i<scalex; ++i) 
	{
		for (int j = 0; j<scaley; ++j) 
		{
			v[i*scaley + j][0] = r*cos(j * 2 * M_PI / scaley)*cos(i * M_PI / (2 * scalex));
			v[i*scaley + j][1] = r*sin(i * M_PI / (2 * scalex));
			v[i*scaley + j][2] = r*sin(j * 2 * M_PI / scaley)*cos(i * M_PI / (2 * scalex));
		}
	}

	glBegin(GL_QUADS);
	for (int i = 0; i<scalex - 1; ++i) 
	{
		for (int j = 0; j<scaley; ++j) 
		{
			glVertex3fv(v[i*scaley + j]);
			glVertex3fv(v[i*scaley + (j + 1) % scaley]);
			glVertex3fv(v[(i + 1)*scaley + (j + 1) % scaley]);
			glVertex3fv(v[(i + 1)*scaley + j]);
		}
	}
	glEnd();
}

void openGLRenderer::Testing()
{
	/*glPushMatrix();
	GLfloat table_amb[] = { 0.0, 0.0, 0.2, 0.0 };
	GLfloat table_dif[] = { 0.1, 0.3, 0.5, 0.0 };
	GLfloat table_emission[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat table_specular[] = { 1.0, 1.0, 1.0, 0.0 };
	float shiness = 7;
	PrepareMaterials(table_amb, table_dif, table_specular, table_emission, shiness);
	//glTranslatef(0.0, 2.0, 1.0);
	glTranslatef(10, 10, 10);
	DrawTestBox(8.0, 8.0, 8.0);
	glPopMatrix();*/

	/*
	// BLANKET 12.11.2011

	// TRAPEZOID 
	//glPushMatrix();
	//glTranslatef(10, 10, 10);
	//DrawTrapezoid(5.0, 2.0, 2.5, 1.0);
	//glPopMatrix();

	// RING
	//glPushMatrix();
	//glTranslatef(10, 10, 10);
	//DrawRing(4.0, 2.0, 2.0, 1.0);
	//glPopMatrix();

	// --- SCENA ----
	glPushMatrix();
	glTranslatef(10, 10, 10);
	glTranslatef(0, 0, -20);
	ScenaTrapezoidi(4.0, 2.0, 2.0, 1.0);
	glPopMatrix();*/
	// ---------------------

	// Blanket --- Patch
	//DrawScenePatch();
	//-----------------

	// Blnket 28.08.2015.
	//DrawBox(5, 1, 2);
	//glTranslatef(0, 0, -20);
	//DrawCylinderIspit(2, 6, 50);
	//----------------------

	DrawPiramide(8, 16);

}

void openGLRenderer::DrawPiramide(double a, double h)
{
	glBegin(GL_QUADS);
	// postolje
	glVertex3d(-a / 2, -h / 2, -a / 2);
	glVertex3d(a / 2, -h / 2, -a / 2);
	glVertex3d(a / 2, -h / 2, a / 2);
	glVertex3d(-a / 2, -h / 2, a / 2);
	glEnd();

	glBegin(GL_TRIANGLES);
	// prednja stranica
	glVertex3d(-a / 2, -h / 2, a / 2);
	glVertex3d(a / 2, -h / 2, a / 2);
	glVertex3d(0, h / 2, 0);

	// desna strancia
	glVertex3d(a / 2, -h / 2, a / 2);
	glVertex3d(a / 2, -h / 2, -a / 2);
	glVertex3d(0, h / 2, 0);

	// zadnja stranica
	glVertex3d(a / 2, -h / 2, -a / 2);
	glVertex3d(-a / 2, -h / 2, -a / 2);	
	glVertex3d(0, h / 2, 0);

	// Leva stranica
	glVertex3d(-a / 2, -h / 2, a / 2);
	glVertex3d(-a / 2, -h / 2, a / 2);
	glVertex3d(0, h / 2, 0);

	glEnd();
}


void openGLRenderer::DrawTrapezoid(float a, float b, float h, float H)
{
	glBegin(GL_QUADS);

	glNormal3f(-1.0, 0, 0);
	// --- Leva stranica ----
	glVertex3f(-a / 2, -h / 2, H / 2);
	glVertex3f(-a / 2, -h / 2, -H / 2);
	glVertex3f(-a / 2 + b / 2, h / 2, -H / 2);
	glVertex3f(-a / 2 + b / 2, h / 2, H / 2);

	glNormal3f(0.0, 1.0, 0);
	// --- Gornja stranica ----
	glVertex3f(-a / 2 + b / 2, h / 2, -H / 2);
	glVertex3f(-a / 2 + b / 2, h / 2, H / 2);
	glVertex3f(a / 2 - b / 2, h / 2, H / 2);
	glVertex3f(a / 2 - b / 2, h / 2, -H / 2);

	glNormal3f(1.0, 0, 0);
	// ---- Desna strana ----
	glVertex3f(a / 2 - b / 2, h / 2, H / 2);
	glVertex3f(a / 2 - b / 2, h / 2, -H / 2);
	glVertex3f(a / 2, -h / 2, -H / 2);
	glVertex3f(a / 2, -h / 2, H / 2);
	
	glNormal3f(0, -1.0, 0);
	// ---- Donja stranica ----
	glVertex3f(a / 2, -h / 2, -H / 2);
	glVertex3f(a / 2, -h / 2, H / 2);
	glVertex3f(-a / 2, -h / 2, H / 2);
	glVertex3f(-a / 2, -h / 2, -H / 2);

	glNormal3f(0, 0, -1.0);
	// ---- Zadnja stranica ----
	glVertex3f(-a / 2, -h / 2, -H / 2);
	glVertex3f(-a / 2 + b / 2, h / 2, -H / 2);
	glVertex3f(a / 2 - b / 2, h / 2, -H / 2);
	glVertex3f(a / 2, -h / 2, -H / 2);

	glNormal3f(0, 0, 1.0);
	// ---- Prednja stranica ----
	glVertex3f(a / 2, -h / 2, H / 2);
	glVertex3f(a / 2 - b / 2, h / 2, H / 2);
	glVertex3f(-a / 2 + b / 2, h / 2, H / 2);
	glVertex3f(-a / 2, -h / 2, H / 2);

	glEnd();
}



void openGLRenderer::DrawRing(float a, float b, float h, float H)
{
	glPushMatrix();

	float d = (a - b) / 2;
	float hipotenuza = (a - b);
	h = sqrt(hipotenuza*hipotenuza - d*d);
	float ugao = asin(h / hipotenuza) * 180 / 3.14159265;

	glPushMatrix();
	DrawTrapezoid(a, b, h, H);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(a/2 * 1.11, sqrt(pow(h/2,2) *0.85 + pow(b/2,2)),	0);
	glRotatef(60, 0, 0, 1);
	DrawTrapezoid(a, b, h, H);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(a / 2 * 1.11, a * 0.96, 0);
	glRotatef(120, 0, 0, 1);
	DrawTrapezoid(a, b, h, H);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, a + d * 1.11, 0);
	glRotatef(180, 0, 0, 1);
	DrawTrapezoid(a, b, h, H);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(-(a / 2 * 1.11), a * 0.96, 0);
	glRotatef(240, 0, 0, 1);
	DrawTrapezoid(a, b, h, H);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(a / 2 * 1.11), sqrt(pow(h / 2, 2) *0.85 + pow(b / 2, 2)), 0);
	glRotatef(300, 0, 0, 1);
	DrawTrapezoid(a, b, h, H);
	glPopMatrix();

	glPopMatrix();
}

void openGLRenderer::SetMaterialRing(COLORREF clr)
{
	// Izvlacimo bajtove sa bojama
	BYTE red = clr & 255;
	clr = clr >> 8;
	BYTE green = clr & 255;
	clr = clr >> 8;
	BYTE blue = clr & 255;

	float niz[4] = { red / 256.0f, green / 256.0f, blue / 256.0f, 1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, niz);

	// prepolovljujemo boje
	red = red >> 1;
	green = green >> 1;
	blue = blue >> 1;
	float niz2[4] = { red / 256.0f, green / 256.0f, blue / 256.0f, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, niz2);
}

void openGLRenderer::ScenaTrapezoidi(float a, float b, float h, float H)
{
	float precnikPrstena = a*sqrt(3.0f);
	float d = (a - b) / 2;

	SetMaterialRing(RGB(200, 200, 200));
	DrawRing(a, b, h, H);

	glPushMatrix();
	glTranslatef(0, precnikPrstena, 0);
	SetMaterialRing(RGB(255, 0, 0));
	DrawRing(a, b, h, H);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -precnikPrstena, 0);
	SetMaterialRing(RGB(0, 255, 255));
	DrawRing(a, b, h, H);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(precnikPrstena - d, precnikPrstena/2, 0);
	SetMaterialRing(RGB(255, 0, 255));
	DrawRing(a, b, h, H);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(precnikPrstena - d, -precnikPrstena / 2, 0);
	SetMaterialRing(RGB(0, 0, 255));
	DrawRing(a, b, h, H);
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(-(precnikPrstena - d), -precnikPrstena / 2, 0);
	SetMaterialRing(RGB(0, 255, 0));
	DrawRing(a, b, h, H);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(precnikPrstena - d), precnikPrstena / 2, 0);
	SetMaterialRing(RGB(255, 255, 0));
	DrawRing(a, b, h, H);
	glPopMatrix();

}

void openGLRenderer::DrawTestBox(double a, double b, double c)
{
	glBegin(GL_QUADS);

	//glPushMatrix();

	//glTranslatef(10, 5, -10);

	///glNormal3d(0, 0, -1.0);
	glNormal3d(0, 0, 1.0);
	// ---- Prednja stranica -----
	glVertex3d(-a / 2, b / 2, c / 2);
	glVertex3d(-a / 2, -b / 2, c / 2);
	glVertex3d(a / 2, -b / 2, c / 2);
	glVertex3d(a / 2, b / 2, c / 2);
	
	///glNormal3d(-1.0, 0, 0);
	glNormal3d(1.0, 0, 0);
	// ----- Desna stranica ------
	glVertex3d(a / 2, b / 2, c / 2);
	glVertex3d(a / 2, -b / 2, c / 2);
	glVertex3d(a / 2, -b / 2, -c / 2);
	glVertex3d(a / 2, b / 2, -c / 2);
	
	///glNormal3d(0, 0, 1.0);
	glNormal3d(0, 0, -1.0);
	// ---- Zadnja stranica -----
	glVertex3d(a / 2, -b / 2, -c / 2);
	glVertex3f(a / 2, b / 2, -c / 2);	
	glVertex3d(-a / 2, b / 2, -c / 2);
	glVertex3d(-a / 2, -b / 2, -c / 2);
	
	///glNormal3d(1.0, 0, 0);
	glNormal3d(-1.0, 0, 0);
	// ----- Leva stranica -----
	glVertex3d(-a / 2, -b / 2, -c / 2);
	glVertex3d(-a / 2, b / 2, -c / 2);	
	glVertex3d(-a / 2, b / 2, c / 2);
	glVertex3d(-a / 2, -b / 2, c / 2);

	///glNormal3d(0, 1.0, 0);
	glNormal3d(0, -1.0, 0);
	// Donja stranica
	glVertex3d(-a / 2, -b / 2, c / 2);
	glVertex3d(-a / 2, -b / 2, -c / 2);
	glVertex3d(a / 2, -b / 2, -c / 2);
	glVertex3d(a / 2, -b / 2, c / 2);	

	///glNormal3d(0, -1.0, 0);
	glNormal3d(0, 1.0, 0);
	// Gornja stranica 
	glVertex3d(a / 2, b / 2, c / 2);
	glVertex3d(a / 2, b / 2, -c / 2);
	glVertex3d(-a / 2, b / 2, -c / 2);
	glVertex3d(-a / 2, b / 2, c / 2);
		
	//glPopMatrix();

	glEnd();
}

void openGLRenderer::DrawPatch(double R, int howMany)
{
	float f2 = 2;
	float korak = f2 / howMany;
	double korak2 = 1.0 / howMany;

	bool negativeNorm = true;

	glLineWidth(2.0);
	glPointSize(10);
	float texCoordX = 0;
	float texCoordY = 0;
	glBegin(GL_TRIANGLE_STRIP);
	for (float x = -1; x <= 1; x = x + korak)
	{
		texCoordX = 0;
		for (float y = -1; y <= 1; y = y + korak)
		{
			//vrednosti tekuce tacke
			float fiCurrent = atanf(x);
			float tetaCurrent = atanf(y * cos(fiCurrent));
			//vrednosti 'sledece' tacke (:.) => (::)
			float fiNext = atanf(x + korak);
			float tetaNext = atanf(y * cos(fiNext));

			float x1 = R * cos(tetaCurrent)*sin(fiCurrent);
			float y1 = R * cos(tetaCurrent)* cos(fiCurrent);
			float z1 = R * sin(tetaCurrent);

			float x2 = R * cos(tetaNext)*sin(fiNext);
			float y2 = R * cos(tetaNext)* cos(fiNext);
			float z2 = R * sin(tetaNext);


			glTexCoord2d(texCoordX, texCoordY);
			glVertex3f(x1, y1, z1);
			glTexCoord2d(texCoordX + korak2, texCoordY + korak2);
			glVertex3f(x2, y2, z2);

			texCoordX += korak2;
		}
		texCoordY += korak2;
	}
	glEnd();
}

void openGLRenderer::DrawScenePatch()
{
	//glEnable(GL_TEXTURE_2D);
	//textureEarthTop.Select();
	glPushMatrix();
	DrawPatch(3, 150);
	glRotated(90, 1, 0, 0);
	//textureEarthFront.Select();
	DrawPatch(3, 150);
	glRotated(90, 1, 0, 0);
	//textureEarthBottom.Select();
	DrawPatch(3, 150);
	glRotated(90, 1, 0, 0);
	//textureEarthBack.Select();
	DrawPatch(3, 150);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	//textureEarthRight.Select();
	DrawPatch(3, 150);
	glRotated(180, 0, 0, 1);
	//textureEarthLeft.Select();
	DrawPatch(3, 150);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void openGLRenderer::DrawBoxIspit(double a, double b, double c)
{
	
	glEnable(GL_QUADS);

	glNormal3f(0, 0, 1);
	// Prednja stranica
	glVertex3f(-a / 2, b / 2, c / 2);
	glVertex3f(-a / 2, -b / 2, c / 2);
	glVertex3f(a / 2, -b / 2, c / 2);
	glVertex3f(a / 2, b / 2, c / 2);

	glNormal3f(1, 0, 0);
	// Desna stranica
	glVertex3f(a / 2, -b / 2, c / 2);
	glVertex3f(a / 2, b / 2, c / 2);
	glVertex3f(a / 2, b / 2, -c / 2);
	glVertex3f(a / 2, -b / 2, -c / 2);

	glNormal3f(0, 0, -1);
	// Zadnja stranica
	glVertex3f(a / 2, b / 2, -c / 2);
	glVertex3f(a / 2, -b / 2, -c / 2);
	glVertex3f(-a / 2, -b / 2, -c / 2);
	glVertex3f(-a / 2, b / 2, -c / 2);

	glNormal3f(-1, 0, 0);
	// Leva stranica
	glVertex3f(-a / 2, -b / 2, -c / 2);
	glVertex3f(-a / 2, b / 2, -c / 2);
	glVertex3f(-a / 2, b / 2, c / 2);
	glVertex3f(-a / 2, -b / 2, c / 2);

	glNormal3f(0, -1, 0);
	// Donja stranica
	glVertex3f(-a / 2, -b / 2, c / 2);
	glVertex3f(-a / 2, -b / 2, -c / 2);
	glVertex3f(a / 2, -b / 2, -c / 2);
	glVertex3f(a / 2, -b / 2, c / 2);

	glNormal3f(0, 1, 0);
	// Gornja stranica
	glVertex3f(a / 2, b / 2, c / 2);
	glVertex3f(a / 2, b / 2, -c / 2);
	glVertex3f(-a / 2, b / 2, -c / 2);
	glVertex3f(-a / 2, b / 2, c / 2);

	glEnd();
}

void openGLRenderer::DrawCylinderIspit(double r, double h, int aprox)
{
	double ugaoStep = 2.0f * 3.1415926f / (double)aprox;
	double x;
	double y;
	double z;
	glBegin(GL_QUADS);
	double alfa = 0;

	// Cilindar 
	for (int i = 0; i < aprox; i = i + 1)
	{
		alfa = i * ugaoStep;
		x = r * cos(alfa);
		z = r * sin(alfa);
		double xNext = r * cos(alfa + ugaoStep);
		double zNext = r * sin(alfa + ugaoStep);
		
		// NORMALE
		vec3 donji(xNext - x, 0, zNext - z);
		vec3 gornji(x - x, h, z - z);
		vec3 normala = donji.cross(donji, gornji);
		normala.normalize();
		glNormal3d(normala.x, normala.y, normala.z);

		glVertex3d(xNext, h, zNext);
		glVertex3d(xNext, 0, zNext);

		glVertex3d(x, 0, z);
		glVertex3d(x, h, z);
	}

	glEnd();

	// Gornji poklopac
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < aprox; i++)
	{
		alfa = i * ugaoStep;
		x = r * cos(alfa);
		z = r *sin(alfa);
		// Zamena x i z menja boje (umesto crne zbacuje boju materijala)
		glVertex3d(x, h, z);
	}
	//x = r * cos(alfa + ugaoStep);
	//z = r * sin(alfa + ugaoStep);
	//glVertex3f(x, h, z);
	glEnd();

	// Donji poklopac
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < aprox; i++)
	{
		alfa = i * ugaoStep;
		z = r * cos(alfa);
		x = r *sin(alfa);
		// Zamena x i z menja boje (umesto crne zbacuje boju materijala)
		glVertex3d(x, 0, z);
	}
	//x = r * cos(alfa + ugaoStep);
	//z = r * sin(alfa + ugaoStep);
	//glVertex3f(x, h, z);
	glEnd();
}

void openGLRenderer::PrepareLighting()
{
	// --- Ambijentalno svetlo ---
	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	float light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	float light1_deffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightf(GL_LIGHT1, GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	// Boja i intezitet svetlosti
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_deffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	// Slabljenje
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1);

	// Aktiviranje
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	lightOn = true;
}


void openGLRenderer::PrepareMaterials(float ambinet[4], float diffuse[4], float specular[4], float emission[4], float shiness)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambinet);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shiness);
}

void openGLRenderer::DrawPrimitives()
{
	///////////TACKE////////////
	/*glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(0.0, 1.0);
	glEnd();*/
	///////////////////////////
	
	//////////LINIJE//////////////
	/*glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2d(0.0, 1.5);
	glVertex2d(-1.5, 0.5);
	glVertex2d(-1.0, -1.5);
	glVertex2d(1.0, -0.5);
	glVertex2d(1.5, 1.0);
	glVertex2d(0.0, 0.0);
	glEnd();*/

	/*glLineWidth(1.0);
	glLineStipple(1, 0xF0F0);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-2.0, 0.0);
	glVertex2f(2.0, 0.0);
	glEnd();
	
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-2.0, -0.5);
	glVertex2f(2.0, -0.5);
	glEnd();

	glLineStipple(4, 0xF0F0);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-2.0, -1.0);
	glVertex2f(2.0, -1.0);
	glEnd();*/

	/*glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2d(0.0, 1.5);
	glVertex2d(-1.5, 0.5);
	glVertex2d(-1.0, -1.5);
	glVertex2d(1.0, -0.5);
	glVertex2d(1.5, 1.0);
	glVertex2d(0.0, 0.0);
	glEnd();*/
	////////////////////////////
	
	//////////TROUGLOVI///////////////
	/*glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2d(0.0, 1.5);
	glVertex2d(-1.5, 0.5);
	glVertex2d(-1.0, -1.5);
	glVertex2d(1.0, -0.5);
	glVertex2d(1.5, 1.0);
	glVertex2d(0.0, 0.0);
	glEnd();*/

	//Crtanje trake trouglova
	/*glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.5, 0.5, 1.0);
	glVertex2f(-2.0, 1.0); // V1
	glVertex2f(-2.0, 0.0); // V2
	glVertex2f(-1.0, 1.0); // V3
	glVertex2f(-1.0, 0.0); // V4
	glVertex2f(0.0, 1.0); // V5
	glVertex2f(0.0, 0.0); // V6
	glVertex2f(1.0, 1.0); // V7
	glVertex2f(1.0, 0.0); // V8
	glVertex2f(2.0, 1.0); // V9
	glEnd();*/

	//Crtanje lepeze trouglova
	/*glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5, 0.5, 1.0);
	glVertex2f(0.0, 1.5); //V1
	glVertex2f(-2.0, 0.0); //V2
	glVertex2f(-1.0, -1.0); //V3
	glVertex2f(1.0, -1.0); //V4
	glVertex2f(2.0, 0.0); // V5
	glEnd();*/
	////////////////////////////////
	
	////////////CETVOROUGLOVI//////////
	/*glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 1.0);
	glVertex2f(-2.0, 1.0); //V1
	glVertex2f(-2.0, 0.0); //V2
	glVertex2f(-1.0, -1.0); //V3
	glVertex2f(-1.0, 1.0); //V4

	glVertex2f(0.5, 0.0); //V5
	glVertex2f(0.5, -1.0); //V6
	glVertex2f(1.5, 0.0); // V7
	glVertex2f(1.5, 1.0); // V8
	glEnd();*/

	//Trake cotvorouglova
	/*glBegin(GL_QUAD_STRIP);
	glColor3f(0.0, 0.0, 1.0);

	glVertex2f(-2.0, 1.0); //V1
	glVertex2f(-2.0, 0.0); //V2

	glVertex2f(-1.0, 0.0); //V3
	glVertex2f(-1.0, -1.0); //V4

	glVertex2f(0.5, 0.0); //V5
	glVertex2f(0.5, -1.0); //V6

	glVertex2f(1.5, 1.0); // V7
	glVertex2f(1.5, 0.0); // V8
	glEnd();*/
	//////////////////////////////////

	/////////POLIGONI////////////////
	/*glBegin(GL_POLYGON);
	glColor3f(0.1, 0.1, 0.5);
	glVertex2f(-2.0, 0.5); //V1
	glVertex2f(-1.0, -1.0); //V2
	glVertex2f(1.0, -1.0); //V3
	glVertex2f(2.0, 0.5); //V4
	glVertex2f(0.0, 1.5); //V5
	glEnd();*/
   //////////////////////////////////
}

