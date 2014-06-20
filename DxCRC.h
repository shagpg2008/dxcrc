// DxCRC.h : main header file for the DXCRC application
//

#if !defined(AFX_DXCRC_H__57F0EF85_939B_45ED_BC32_5BC74A51ECB5__INCLUDED_)
#define AFX_DXCRC_H__57F0EF85_939B_45ED_BC32_5BC74A51ECB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDxCRCApp:
// See DxCRC.cpp for the implementation of this class
//

class CDxCRCApp : public CWinApp
{
public:
	CDxCRCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDxCRCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDxCRCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DXCRC_H__57F0EF85_939B_45ED_BC32_5BC74A51ECB5__INCLUDED_)
