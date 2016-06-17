
XFORM CCockpit2View::Translate(float x, float y)
{
	XFORM Xform;

	Xform.eM11 = (FLOAT)1.0;
	Xform.eM12 = (FLOAT)0.0;
	Xform.eM21 = (FLOAT)0.0;
	Xform.eM22 = (FLOAT)1.0;
	Xform.eDx = (FLOAT)x;
	Xform.eDy = (FLOAT)y;

	return Xform;
}

XFORM CCockpit2View::Rotate(float a)
{
	XFORM Xform;

	float radian = stepen_u_radian(a);

	Xform.eM11 = cos(radian);
	Xform.eM12 = sin(radian);
	Xform.eM21 = -sin(radian);
	Xform.eM22 = cos(radian);
	Xform.eDx = 0.0;
	Xform.eDy = 0.0;

	return Xform;
}

XFORM CCockpit2View::Reflect(float Sx, float Sy)
{
	return XFORM();
}

void CCockpit2View::DrawTriangle(CDC * pDC)
{
	CPen newPen(BS_SOLID, 1, RGB(0, 100, 0));
	CPen* oldPen = pDC->SelectObject(&newPen);

	CBrush newBrush(RGB(100, 100, 100));
	CBrush* oldBrush = pDC->SelectObject(&newBrush);

	CPoint triangle[3];

	pDC->MoveTo(0, 0);

	triangle[0].x = 0; triangle[0].y = 100;
	triangle[1].x = 100; triangle[1].y = 0;
	triangle[2].x = 0; triangle[2].y = 0;

	pDC->Polygon(triangle, 3);


	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	newPen.DeleteObject();
	newBrush.DeleteObject();
}

/*POZIV F-JA

// trapezi koji otvoreni/zatvoreni
	bool arOpen [6 * (3+2)];
	for (int i = 0; i < 6 * (3+2); i++)
		arOpen[i] = false;
	arOpen[11] = true;
	arOpen[12] = true;
	arOpen[18] = true;
	arOpen[22] = true;
	arOpen[26] = true;
	arOpen[27] = true;
	arOpen[28] = true;

	// Boje
	COLORREF arColors[7];
	arColors[0] = RGB(20, 0, 0);
	arColors[1] = RGB(40, 0, 0);
	arColors[2] = RGB(60, 0, 0);
	arColors[3] = RGB(80, 0, 0);
	arColors[4] = RGB(100, 0, 0);
	arColors[5] = RGB(120, 0, 0);
	arColors[6] = RGB(140, 0, 0);
	
	DrawPuzzle(pDC, zid, 6, 3, 0.5, NULL, NULL, NULL, arOpen, arColors);
	DrawEnd(pDC, zid, 0, 0, CString("Your score: 9pts"));

	/*XFORM XformOld;
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	bool b = GetWorldTransform(pDC->m_hDC, &XformOld);	
	XFORM trans = Translate(100, 50);	
	b = SetWorldTransform(pDC->m_hDC, &trans);

	//DrawTriangle(pDC);

	//b = SetWorldTransform(pDC->m_hDC, &XformOld);

	XFORM rot = Rotate(90);

	//trans = Translate(300, 0);
	b = SetWorldTransform(pDC->m_hDC, &trans);
	trans = Rotate(90);
	//LPXFORM comboTransRot;
	//CombineTransform(comboTransRot, &trans, &rot);
	//b = ModifyWorldTransform(pDC->m_hDC, &trans, MWT_RIGHTMULTIPLY);
	//b = SetWorldTransform(pDC->m_hDC, comboTransRot);
	DrawTriangle(pDC);

	b = SetWorldTransform(pDC->m_hDC, &XformOld);
	SetGraphicsMode(pDC->m_hDC, prevMode);*/