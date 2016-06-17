#pragma once
#include "openGLMaterial.h"
class openGLRenderer
{
public:
	openGLRenderer();
	virtual ~openGLRenderer();

	bool CreateGLContext(CDC* pDC); // kreira openGL Rendering Context
	void PrepareScene(CDC *pDC); // inicijalizuje scenu
	void DestroyScene(CDC* pDC); // oslobadja resurse alocirane u drugim funkcijama ove klase
	void Reshape(CDC* pDC, int w, int h); // kod koji treba da se izvrsi svaki put kada se promeni velicina prozora ili pogleda
	void DrawScene(CDC* pDC); // isrtava scenu

	//Atributi
	double posX, posY, posZ, pogledX, pogledY, pogledZ;
	double cameraVectorX, cameraVectorY, cameraVectorZ;

	//double rotX, rotY, rotZ;
	double zoom;
	float rotationAngle;
	bool lightOn;
	float light_Position[4];
	openGLMaterial matTable, matWalls, matLamp;

	//Lab1
	void DrawWalls(double a, double b);
	void DrawTable(double x, double y, double z, double sirina, double duzina, double visina);
	void DrawBox(double a, double b, double c);
	void DrawLamp();
	void DrawHalfSphere(int scaley, int scalex, float r);

	// ISPIT VEZBA
	//---------------------------

	void DrawTestBox(double a, double b, double c);
	void Testing();
	void DrawPiramide(double a, double h);

	// 12.11.2011. ISPIT
	void DrawTrapezoid(float a, float b, float h, float H);
	void DrawRing(float a, float b, float h, float H);
	void SetMaterialRing(COLORREF clr);
	void ScenaTrapezoidi(float a, float b, float h, float H);
	//---------------------------

	// 05.10.2011.
	void DrawPatch(double R, int howMany);
	void DrawScenePatch();
	//---------------------------

	// 28.08.2015
	void DrawBoxIspit(double a, double b, double c);
	void DrawCylinderIspit(double r, double h, int steps);
	//---------------------------

	// Lab2
	void PrepareLighting();
	void PrepareMaterials(float ambinet[4], float diffuse[4], float specular[4], float emission[4], float shiness);

	// Free test
	void DrawPrimitives();

	

protected:
	HGLRC m_hrc; // OpenGL Rendering Context (openGL server koji vrsi iscrtavanje)
	float m_aspect;
};

