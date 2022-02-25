
// PlanetoryMotionView.cpp : implementation of the CPlanetoryMotionView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PlanetoryMotion.h"
#endif

#include "PlanetoryMotionDoc.h"
#include "PlanetoryMotionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanetoryMotionView

IMPLEMENT_DYNCREATE(CPlanetoryMotionView, CView)

BEGIN_MESSAGE_MAP(CPlanetoryMotionView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlanetoryMotionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_MOTION_START, &CPlanetoryMotionView::OnMotionStart)
	ON_COMMAND(ID_MOTION_PAUSE, &CPlanetoryMotionView::OnMotionPause)
	ON_COMMAND(ID_MOTION_RESUME, &CPlanetoryMotionView::OnMotionResume)
END_MESSAGE_MAP()

// CPlanetoryMotionView construction/destruction

CPlanetoryMotionView::CPlanetoryMotionView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	m_iCounter = 0;
	x1 = 590;
	y1 = 240;

	x2 = 440 + 190 * cos(5);
	y2 = 240 + 190 * sin(5);

}

CPlanetoryMotionView::~CPlanetoryMotionView()
{
}

BOOL CPlanetoryMotionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlanetoryMotionView drawing

void CPlanetoryMotionView::OnDraw(CDC* pDC)
{
	CPlanetoryMotionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPen blackPen, yellowpen, graypen, redpen;
	CBrush YellowBrush(RGB(255, 255, 51));
	CBrush grayBrush(RGB(128, 128, 128));
	CBrush RedBrush(RGB(255, 0, 0));

	blackPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	yellowpen.CreatePen(PS_SOLID, 2, RGB(255, 255, 51));
	graypen.CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
	redpen.CreatePen(PS_SOLID, 2, RGB(255,0, 0));

	CPen* pOldPen = pDC->SelectObject(&blackPen);


	/*CString strCounter;
	strCounter.Format(L"The Counter is %d", m_iCounter);*/
	pDC->Ellipse(250, 50, 635, 430);
	pDC->Ellipse(300, 100, 585, 380);
	CPen* pOldPen0 = pDC->SelectObject(&yellowpen);
	CBrush* pOldBrush = pDC->SelectObject(&YellowBrush);
	pDC->Ellipse(400, 200, 480, 280);
	pDC->SelectObject(pOldBrush);

	CPen* pOldPen1 = pDC->SelectObject(&graypen);
	pOldBrush = pDC->SelectObject(&grayBrush);
	pDC->Ellipse(x1 + 20, y1 + 20, x1 - 20, y1 - 20);
	CPen* pOldPen2 = pDC->SelectObject(&redpen);
	pDC->SelectObject(&RedBrush);
	pDC->Ellipse(x2 + 15, y2 + 15, x2 - 15, y2 - 15);
	pDC->SelectObject(pOldBrush);

	// TODO: add draw code for native data here
}


// CPlanetoryMotionView printing


void CPlanetoryMotionView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlanetoryMotionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlanetoryMotionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlanetoryMotionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPlanetoryMotionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlanetoryMotionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlanetoryMotionView diagnostics

#ifdef _DEBUG
void CPlanetoryMotionView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanetoryMotionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanetoryMotionDoc* CPlanetoryMotionView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanetoryMotionDoc)));
	return (CPlanetoryMotionDoc*)m_pDocument;
}
#endif //_DEBUG	


// CPlanetoryMotionView message handlers


void CPlanetoryMotionView::OnMotionStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread = AfxBeginThread(CPlanetoryMotionView::StartThread, this);
}


void CPlanetoryMotionView::OnMotionPause()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();
}


void CPlanetoryMotionView::OnMotionResume()
{
	m_pCurrentThread->ResumeThread();
	// TODO: Add your command handler code here
}

UINT CPlanetoryMotionView::StartThread(LPVOID param)
{
	CPlanetoryMotionView* pView = (CPlanetoryMotionView*)param;
	double j = 0;
	while (true) {

		//MyPoint.y = 200 + 50 * sin(pView->m_iCounter);
		//MyPoint.x = 100 + pView->m_iCounter;

		j = j + 6;
		int i = j + 5;

		pView->x1 = 440 + 140 * cos(j);
		pView->y1 = 240 + 140 * sin(j);

		pView->x2 = 440 + 190 * cos(i);
		pView->y2 = 240 + 190 * sin(i);

		pView->Invalidate();
		Sleep(300);
	}

	return 0;
}
