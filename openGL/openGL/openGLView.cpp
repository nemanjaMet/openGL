
// openGLView.cpp : implementation of the CopenGLView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "openGL.h"
#endif

#include "openGLDoc.h"
#include "openGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CopenGLView

IMPLEMENT_DYNCREATE(CopenGLView, CView)

BEGIN_MESSAGE_MAP(CopenGLView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CopenGLView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CopenGLView construction/destruction

CopenGLView::CopenGLView()
{
	// TODO: add construction code here

}

CopenGLView::~CopenGLView()
{
}

BOOL CopenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CopenGLView drawing

void CopenGLView::OnDraw(CDC* pDC)
{
	CopenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	/*if (!pDoc)
		return;*/

	// TODO: add draw code for native data here

	m_glRenderer.DrawScene(pDC);
}


// CopenGLView printing


void CopenGLView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CopenGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CopenGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CopenGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CopenGLView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CopenGLView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CopenGLView diagnostics

#ifdef _DEBUG
void CopenGLView::AssertValid() const
{
	CView::AssertValid();
}

void CopenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CopenGLDoc* CopenGLView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CopenGLDoc)));
	return (CopenGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CopenGLView message handlers


int CopenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


BOOL CopenGLView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;

	//return CView::OnEraseBkgnd(pDC);
}


void CopenGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void CopenGLView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


void CopenGLView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


void CopenGLView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP)
	{
		m_glRenderer.pogledY += 5;
	}
	else if (nChar == VK_DOWN)
	{
		m_glRenderer.pogledY -= 5;
	}
	else if (nChar == VK_LEFT)
	{
		m_glRenderer.pogledX -= 5;
	}
	else if (nChar == VK_RIGHT)
	{
		m_glRenderer.pogledX += 5;
	}
	else if (nChar == VK_ADD)
	{
		m_glRenderer.pogledZ += 5;
	}
	else if (nChar == VK_SUBTRACT)
	{
		m_glRenderer.pogledZ -= 5;
	}
	else if (nChar == VK_SPACE)
	{
		m_glRenderer.posX = 20;
		m_glRenderer.posY = 12;
		m_glRenderer.posZ = 20;
		m_glRenderer.pogledX = 0;
		m_glRenderer.pogledY = 5;
		m_glRenderer.pogledZ = 0;
		m_glRenderer.zoom = -20;
		m_glRenderer.rotationAngle = 0;

		m_glRenderer.cameraVectorX = 0;
		m_glRenderer.cameraVectorY = 1;
		m_glRenderer.cameraVectorZ = 0;
	}
	else if (nChar == 'R')
	{
		if (m_glRenderer.cameraVectorX == 1)
		{
			m_glRenderer.cameraVectorX = 0;
			m_glRenderer.cameraVectorY = 1;
			m_glRenderer.cameraVectorZ = 0;
		}
		else if (m_glRenderer.cameraVectorY == 1)
		{
			m_glRenderer.cameraVectorX = 0;
			m_glRenderer.cameraVectorY = 0;
			m_glRenderer.cameraVectorZ = 1;
		}
	}
	else if (nChar == 'W')
	{
		m_glRenderer.posY -= 1;
	}
	else if (nChar == 'S')
	{
		m_glRenderer.posY += 1;
	}
	else if (nChar == 'A')
	{
		m_glRenderer.posX -= 1;
	}
	else if (nChar == 'D')
	{
		m_glRenderer.posX += 1;
	}
	else if (nChar == 'Z')
	{
		m_glRenderer.posZ += 1;
	}
	else if (nChar == 'E')
	{
		m_glRenderer.posZ -= 1;
	}
	this->RedrawWindow();
}
