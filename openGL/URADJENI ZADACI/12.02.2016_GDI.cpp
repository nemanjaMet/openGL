void CCockpit2View::DrawPuzzle(CDC * pDC, CRect rcPuzzle, int nRow, int nCols, float ratio, CString sPicture, CString arQuestions[], int nValues, bool arOpen[], COLORREF arColors[])
{
	// Ucitavanje slike
	DImage x;
	x.Load(CString("D:Htc.jpg"));
	CRect pictureSize = new CRect(0, 0, x.Width(), x.Height());
	x.Draw(pDC, pictureSize, rcPuzzle);

	CPen nova(BS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&nova);
	CBrush newBrush(RGB(0, 0, 0));
	CBrush *oldBrush = pDC->SelectObject(&newBrush);

	// horizontalne linije
	double linijaRazmak = rcPuzzle.Height() / 6;
	double razmak = 0;
	for (int i = 0; i < nRow+1; i++)
	{	
		pDC->MoveTo(rcPuzzle.left, razmak);
		pDC->LineTo(rcPuzzle.right, razmak);
		razmak += linijaRazmak;
	}

	// Trapezi // Mozda nije najbolji nacin i valjda radi dobro
	razmak = 0;
	double sredinaOsnovice = rcPuzzle.Width() / (nCols+2);
	double polaDuzeOsnovice = (sredinaOsnovice *0.5);
	double kracaOsnovica = polaDuzeOsnovice * ratio;
	double sledeciTrapezX = 0;
	int checkTrapazoid = -2;
	for (int i = 0; i < nRow; i++)
	{
		double sledeciTrapezY = razmak;
		sledeciTrapezX = 0;
		for (int j = 0; j < nCols; j++)
		{
			checkTrapazoid += 2;
			if (i % 2 == 0)
			{
				// Poligon #trapezoid
				sledeciTrapezX += sredinaOsnovice;
				POINT poligon[4];
				poligon[0].x = sledeciTrapezX - kracaOsnovica; poligon[0].y = sledeciTrapezY;
				sledeciTrapezY += linijaRazmak;
				poligon[1].x = sledeciTrapezX - polaDuzeOsnovice; poligon[1].y = sledeciTrapezY;
				poligon[2].x = sledeciTrapezX + polaDuzeOsnovice; poligon[2].y = sledeciTrapezY;
				sledeciTrapezY -= linijaRazmak;
				poligon[3].x = sledeciTrapezX + kracaOsnovica; poligon[3].y = sledeciTrapezY;
				sledeciTrapezY = razmak;
				sledeciTrapezX += kracaOsnovica * 2;			

				if (arOpen[checkTrapazoid])
				{
					pDC->BeginPath();
					pDC->Polygon(poligon, 4);
					pDC->EndPath();
					pDC->StrokeAndFillPath();
				}
				else
				{
					pDC->BeginPath();
					pDC->Polygon(poligon, 4);
					pDC->EndPath();
					pDC->StrokePath();
				}
			}
			else
			{
				// Poligon #trapezoid
				sledeciTrapezX += sredinaOsnovice;
				POINT poligon[4];
				poligon[0].x = sledeciTrapezX - polaDuzeOsnovice; poligon[0].y = sledeciTrapezY;
				sledeciTrapezY += linijaRazmak;
				poligon[1].x = sledeciTrapezX - kracaOsnovica; poligon[1].y = sledeciTrapezY;
				poligon[2].x = sledeciTrapezX + kracaOsnovica; poligon[2].y = sledeciTrapezY;
				sledeciTrapezY -= linijaRazmak;
				poligon[3].x = sledeciTrapezX + polaDuzeOsnovice; poligon[3].y = sledeciTrapezY;
				sledeciTrapezY = razmak;
				sledeciTrapezX += kracaOsnovica * 2;

				if (arOpen[checkTrapazoid])
				{
					pDC->BeginPath();
					pDC->Polygon(poligon, 4);
					pDC->EndPath();
					pDC->StrokeAndFillPath();
				}
				else
				{
					pDC->BeginPath();
					pDC->Polygon(poligon, 4);
					pDC->EndPath();
					pDC->StrokePath();
				}
			}
		}
		razmak += linijaRazmak;
		checkTrapazoid -= 1;
	}

	double sredinaTrapezoidi = sredinaOsnovice + kracaOsnovica + polaDuzeOsnovice;
	checkTrapazoid = 1;
	razmak = 0;
	double saveCheckTrapezoid = 1;
	/*for (int i = 0; i < nRow; i++)
	{
		checkTrapazoid = saveCheckTrapezoid;
		for (int j = 0; j < nCols-1; j++)
		{
			if (arOpen[checkTrapazoid])
			{
				if (i % 2 == 0)
				{
					// Poligon #trapezoid
					sledeciTrapezX += sredinaTrapezoidi;
					POINT poligon[4];
					poligon[0].x = sledeciTrapezX - kracaOsnovica; poligon[0].y = sledeciTrapezY;
					sledeciTrapezY += linijaRazmak;
					poligon[1].x = sledeciTrapezX - polaDuzeOsnovice; poligon[1].y = sledeciTrapezY;
					poligon[2].x = sledeciTrapezX + polaDuzeOsnovice; poligon[2].y = sledeciTrapezY;
					sledeciTrapezY -= linijaRazmak;
					poligon[3].x = sledeciTrapezX + kracaOsnovica; poligon[3].y = sledeciTrapezY;
					sledeciTrapezY = razmak;
					sledeciTrapezX += kracaOsnovica * 2;

					if (arOpen[checkTrapazoid])
					{
						pDC->BeginPath();
						pDC->Polygon(poligon, 4);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
					else
					{
						pDC->BeginPath();
						pDC->Polygon(poligon, 4);
						pDC->EndPath();
						pDC->StrokePath();
					}
				}
				else
				{
					// Poligon #trapezoid
					sledeciTrapezX += sredinaTrapezoidi;
					POINT poligon[4];
					poligon[0].x = sledeciTrapezX - polaDuzeOsnovice; poligon[0].y = sledeciTrapezY;
					sledeciTrapezY += linijaRazmak;
					poligon[1].x = sledeciTrapezX - kracaOsnovica; poligon[1].y = sledeciTrapezY;
					poligon[2].x = sledeciTrapezX + kracaOsnovica; poligon[2].y = sledeciTrapezY;
					sledeciTrapezY -= linijaRazmak;
					poligon[3].x = sledeciTrapezX + polaDuzeOsnovice; poligon[3].y = sledeciTrapezY;
					sledeciTrapezY = razmak;
					sledeciTrapezX += kracaOsnovica * 2;

					if (arOpen[checkTrapazoid])
					{
						pDC->BeginPath();
						pDC->Polygon(poligon, 4);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
					else
					{
						pDC->BeginPath();
						pDC->Polygon(poligon, 4);
						pDC->EndPath();
						pDC->StrokePath();
					}
				}
			}
			checkTrapazoid += nCols - 1;
		}
		saveCheckTrapezoid += nRow - 1;
		razmak += linijaRazmak;
	}*/

	// Bojenje trapeza
	/*CBrush newBrush(RGB(0,0,0));
	CBrush *oldBrush = pDC->SelectObject(&newBrush);
	
	CPoint test(sredinaOsnovice, linijaRazmak / 2);
	pDC->SetBrushOrg(test);*/

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	newBrush.DeleteObject();
	nova.DeleteObject();
}

void CCockpit2View::DrawEnd(CDC * pDC, CRect rcPuzzle, int size, COLORREF clr, CString sText)
{ 
	CFont font;
	int charHeight = 20;
	int charWidth = 10;
	font.CreateFontW(charHeight, charWidth, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, 0, 0, 0, CString("Verdana"));
	CFont * oldFont = pDC->SelectObject(&font);
	pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SetTextColor(RGB(255, 255, 255));

	// Ne racuna se ovako charSpace 
	int charSpace = (180) / (charWidth);
	int pocetniUgao = 180;

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));

	//Translacija i rotacija teksta pozicije
	int translateTextX = rcPuzzle.Width() / 2;
	int translateTextY = rcPuzzle.bottom - rcPuzzle.Height() /4;

	// Graficki Mod
	int prevMod = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM xForm, xFormOld;
	GetWorldTransform(pDC->m_hDC, &xFormOld);

	int duzinaStringa = sText.GetLength();
	for (int i = 0; i < duzinaStringa; i++)
	{
		CString print(sText[duzinaStringa-i-1]);		

		int stringStartX = rcPuzzle.Height()* 0.8;
		int stringStartY = rcPuzzle.Height()* 0.8;


		//Transliranje do koordinatnog pocetka, simulirajuci da je koordinatni pocetak centar kruga, tj sata
		xForm.eM11 = (FLOAT) 0.5; //0.5
		xForm.eM12 = (FLOAT) 0.0;
		xForm.eM21 = (FLOAT) 0.0;
		xForm.eM22 = (FLOAT) 0.75; // 0.75
		xForm.eDx = (FLOAT)-translateTextX;
		xForm.eDy = (FLOAT)-translateTextY;

		//Odredjivanje ugla rotiranje
		double ugao = pocetniUgao - i * charSpace;
		double ugaoRad = stepen_u_radian(ugao);

		//Rotacija linije sa translacijom do odredisne pozicije
		SetWorldTransform(pDC->m_hDC, &xForm);

		xForm.eM11 = (FLOAT)cos(ugaoRad);
		xForm.eM12 = (FLOAT)sin(ugaoRad);
		xForm.eM21 = (FLOAT)-sin(ugaoRad);
		xForm.eM22 = (FLOAT)cos(ugaoRad);
		xForm.eDx = (FLOAT)translateTextX;
		xForm.eDy = (FLOAT)translateTextY;

		ModifyWorldTransform(pDC->m_hDC, &xForm, MWT_RIGHTMULTIPLY);

		pDC->TextOutW(stringStartX, stringStartY, print);
	}

	//Vracanje grafickog moda
	SetWorldTransform(pDC->m_hDC, &xFormOld);
	SetGraphicsMode(pDC->m_hDC, prevMod);

	pDC->SelectObject(oldFont);
	font.DeleteObject();
}


/* POZIV F-JA
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