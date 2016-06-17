void openGLRenderer::Testing()
{
	SetMaterialPrism(0.0, 0.5, 0.5);
	DrawFigure(1, 3, 0, -30, 0);
}

void openGLRenderer::DrawPrism(float dx, float dy, float dz)
{
	glBegin(GL_QUADS);

	glNormal3f(0, 0, 1);
	// prednja stranica
	glVertex3f(-dx / 2, dy / 2, dz / 2);
	glVertex3f(-dx / 2, -dy / 2, dz / 2);
	glVertex3f(dx / 2, -dy / 2, dz / 2);
	glVertex3f(dx / 2, dy / 2, dz / 2);

	glNormal3f(-1, 0, 0);
	// desna stranica
	glVertex3f(dx / 2, -dy / 2, dz / 2);
	glVertex3f(dx / 2, dy / 2, dz / 2);
	glVertex3f(dx / 2, dy / 2, -dz / 2);
	glVertex3f(dx / 2, -dy / 2, -dz / 2);

	glNormal3f(0, 0, -1);
	// zadnja stranica
	glVertex3f(dx / 2, dy / 2, -dz / 2);
	glVertex3f(dx / 2, -dy / 2, -dz / 2);
	glVertex3f(-dx / 2, -dy / 2, -dz / 2);
	glVertex3f(-dx / 2, dy / 2, -dz / 2);

	glNormal3f(-1, 0, 0);
	// leva stranica
	glVertex3f(-dx / 2, -dy / 2, -dz / 2);
	glVertex3f(-dx / 2, dy / 2, -dz / 2);
	glVertex3f(-dx / 2, dy / 2, dz / 2);
	glVertex3f(-dx / 2, -dy / 2, dz / 2);

	glNormal3f(0, 1, 0);
	// gornja stranica
	glVertex3f(-dx / 2, dy / 2, dz / 2);
	glVertex3f(dx / 2, dy / 2, dz / 2);
	glVertex3f(dx / 2, dy / 2, -dz / 2);
	glVertex3f(-dx / 2, dy / 2, -dz / 2);
	

	glNormal3f(0, -1, 0);
	// donja stranica
	glVertex3f(-dx / 2, -dy / 2, dz / 2);
	glVertex3f(dx / 2, -dy / 2, dz / 2);
	glVertex3f(dx / 2, -dy / 2, -dz / 2);
	glVertex3f(-dx / 2, -dy / 2, -dz / 2);
	

	glEnd();
}

void openGLRenderer::DrawFigure(float w, float dx, float alpha, float beta, float gama)
{
	// Sipka A
	DrawPrism(w*w, 15 * w, w*w);

	// B
	glPushMatrix();
	// B
	glTranslatef(0,15*w/2 - dx,0);
	glRotatef(alpha, 0, 1, 0);
	DrawPrism(1.5*w, 1.5*w, 1.5*w);
	// Produzetak
	glTranslatef(1.5*w/2 + 3*w/2,0,0);
	DrawPrism(3 * w, w*w, w*w);
	// Bomper 2
	glTranslatef(1.5 * w / 2 + 3*w/2, 0, 0);
	DrawPrism(1.5*w, 1.5*w, 1.5*w);
	// C
	glRotated(beta, 0, 0, 1);
	glTranslatef(1.5 * w /2 + 3*w/2, 0, 0);
	// zbog rotiranja jos jedan translate 
	glTranslatef(-fabs(w*w/2  *sin(beta)), w*w /2 * sin(beta), 0); 
	DrawPrism(3 * w, w*w, w*w);
	glTranslatef(1.5 * w / 2 + 3 * w / 2, 0, 0);	
	// D
	glRotatef(gama,1,0,0);
	DrawPrism(1.5*w, 1.5*w, 1.5*w); // ovo je iz C, ali treba i on da se rotira??
	DrawPrism(w * w, 4*w, w*w);
	glTranslatef(0, 4 * w / 2 + 1.5*w/2, 0);
	DrawPrism(1.5*w, 1.5*w, 1.5*w);
	glTranslatef(1.5*w/2+ 2*w/2, 0,0);
	DrawPrism(2 * w, 2 * w, 2 * w);

	glPopMatrix();
}

void openGLRenderer::SetMaterialPrism(float r, float g, float b)
{
	// Materijal 
	GLfloat wall_amb[] = { r/2, g/2, b/2, 0.0 };
	GLfloat wall_dif[] = { r, g, b, 0.0 };
	GLfloat wall_emission[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat wall_specular[] = { 1.0, 1.0, 1.0, 0.0 };
	float shiness = 20;
	PrepareMaterials(wall_amb, wall_dif, wall_specular, wall_emission, shiness);
}
