/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// MFCDemoView.cpp : implementation of the CMFCDemoView class
//

#include "stdafx.h"
#include "MFCDemo.h"

#include "MFCDemoDoc.h"
#include "MFCDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDemoView

IMPLEMENT_DYNCREATE(CMFCDemoView, CView)

BEGIN_MESSAGE_MAP(CMFCDemoView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCDemoView construction/destruction

CMFCDemoView::CMFCDemoView()
{
	// TODO: add construction code here

}

CMFCDemoView::~CMFCDemoView()
{
}

BOOL CMFCDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCDemoView drawing

void CMFCDemoView::OnDraw(CDC* /*pDC*/)
{
	CMFCDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCDemoView printing

BOOL CMFCDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCDemoView diagnostics

#ifdef _DEBUG
void CMFCDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDemoDoc* CMFCDemoView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDemoDoc)));
	return (CMFCDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDemoView message handlers
