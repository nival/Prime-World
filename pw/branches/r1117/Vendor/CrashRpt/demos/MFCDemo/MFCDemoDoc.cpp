/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// MFCDemoDoc.cpp : implementation of the CMFCDemoDoc class
//

#include "stdafx.h"
#include "MFCDemo.h"

#include "MFCDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDemoDoc

IMPLEMENT_DYNCREATE(CMFCDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCDemoDoc, CDocument)
END_MESSAGE_MAP()


// CMFCDemoDoc construction/destruction

CMFCDemoDoc::CMFCDemoDoc()
{
	// TODO: add one-time construction code here

}

CMFCDemoDoc::~CMFCDemoDoc()
{
}

BOOL CMFCDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCDemoDoc serialization

void CMFCDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here

		int* p = NULL;
		*p = 13;
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMFCDemoDoc diagnostics

#ifdef _DEBUG
void CMFCDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCDemoDoc commands
