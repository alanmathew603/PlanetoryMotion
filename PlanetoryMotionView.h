
// PlanetoryMotionView.h : interface of the CPlanetoryMotionView class
//

#pragma once


class CPlanetoryMotionView : public CView
{
	CWinThread* m_pCurrentThread;
	CArray<CPoint, CPoint> m_PointArray;

protected: // create from serialization only
	CPlanetoryMotionView() noexcept;
	DECLARE_DYNCREATE(CPlanetoryMotionView)

// Attributes
public:
	CPlanetoryMotionDoc* GetDocument() const;
	int m_iCounter;
	int x1, y1, x2, y2;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPlanetoryMotionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMotionStart();
	afx_msg void OnMotionPause();
	afx_msg void OnMotionResume();
	static UINT StartThread(LPVOID param);
};

#ifndef _DEBUG  // debug version in PlanetoryMotionView.cpp
inline CPlanetoryMotionDoc* CPlanetoryMotionView::GetDocument() const
   { return reinterpret_cast<CPlanetoryMotionDoc*>(m_pDocument); }
#endif

