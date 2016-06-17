void openGLRenderer::DrawBoxIspit(double a, double b, double c)
{
	glBegin(GL_QUADS);

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


void openGLRenderer::DrawCylinder(double r, double h, int aprox)
{
	double ugaoStep = 2.0f * 3.1415926f / (double)aprox;
	double x, y, z;
	double alfa = 0;

	glBegin(GL_QUADS);
	
	// cilindar
	for (int i = 0; i < aprox; i = i + 1)
	{
		alfa = ugaoStep * i;
		x = r * cos(alfa);
		z = r * sin(alfa);
		double xNext = r * cos(alfa + ugaoStep);
		double zNext = r * sin(alfa + ugaoStep);

		// Normale
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

	// gornji poklopac
	glBegin(GL_TRIANGLE_FAN);
	
	for (int i = 0; i < aprox; i++)
	{
		alfa = i * ugaoStep;
		x = r * cos(alfa);
		z = r * sin(alfa);

		glVertex3d(x, h, z);
	}
	glEnd();

	//donji poklopac
	glBegin(GL_TRIANGLE_FAN);

	for (int i = 0; i < aprox; i++)
	{
		alfa = i * ugaoStep;
		x = r * cos(alfa);
		z = r * sin(alfa);

		glVertex3d(z, 0, x);
	}
	glEnd();
}


void openGLRenderer::DrawColumn(double r, double h, int steps)
{
	DrawCylinder(r, h, steps);

	// gornji kvadrat
	glPushMatrix();
	glTranslated(0, h, 0);
	DrawBoxIspit(2.5*r, 0.5*r, 2.5*r);
	glPopMatrix();

	// 2 donja kvadrata
	glPushMatrix();
	DrawBoxIspit(3 * r, 0.3 * r, 3*r);
	glPushMatrix();
	glTranslated(0, -0.3*r, 0);
	DrawBoxIspit(4 * r, 0.3 * r, 4*r);
	glPopMatrix();
	glPopMatrix();
}

// DrawScene
void openGLRenderer::Testing()
{
	glPushMatrix();
	// Prvo donje postolje
	DrawBoxIspit(26, 0.75, 14);

	// Drugo donje postolje
	glTranslated(0, 0.75, 0);
	DrawBoxIspit(24, 0.5, 12);

	// Stubovi
	glTranslated(0, 0.5, 0);
	
	
	for (int i = 0; i < 8; i++)
	{
		// jedna strana
		glPushMatrix();
		glTranslated(-12 + 2.5*0.5 + 0.25 + i * 3, 0, -6 + 2.5*0.5);
		DrawColumn(0.5, 8, 20);
		//stubovi u sredini
		if (i == 0 || i == 7)
		{
			glTranslated(0, 0, 3);
			DrawColumn(0.5, 8, 20);
			glTranslated(0, 0, 3);
			DrawColumn(0.5, 8, 20);
		}
		glPopMatrix();

		// druga strana
		glPushMatrix();
		glTranslated(-12 + 2.5*0.5 + 0.25 + i * 3, 0, 6 - 2.5*0.5);
		DrawColumn(0.5, 8, 20);
		glPopMatrix();
	}
	
	// Gornja podloga // nesto ne valja racunica za translate 'y'
	glTranslated(0,8+2*0.3/2*0.5+0.5*0.5/2, 0);
	DrawBoxIspit(24, 0.3, 12);
	glTranslated(0, 0.3, 0);
	
	// Krov
	glPushMatrix();
	// visina (r)4*sin(60) = 3.46 // 4 zato sto je (0,0) u centru (DrawBoxIspit)
	// i posto je to sama ivica spusta se jos malo
	// 3.46 - 0.2(debljina) = 3.26
	// ne znam da li ima neke veze cos(60)
	glTranslated(0, 3.26, 2);
	glRotated(60, 1, 0, 0);
	//glTranslated(0, -5, 0);
	DrawBoxIspit(24, 0.2, 8);	
	glPopMatrix(); 

	glPushMatrix();
	glTranslated(0, 3.26, -2);
	glRotated(-60, 1, 0, 0);
	//glTranslated(0, -5, 0);
	DrawBoxIspit(24, 0.2, 8);
	glPopMatrix();
	
	glPopMatrix();


}
