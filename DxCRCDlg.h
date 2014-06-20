// DxCRCDlg.h : header file
//

#if !defined(AFX_DXCRCDLG_H__77032BCD_1CDB_467B_B71C_D3F06195AFF9__INCLUDED_)
#define AFX_DXCRCDLG_H__77032BCD_1CDB_467B_B71C_D3F06195AFF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDxCRCDlg dialog

class CDxCRCDlg : public CDialog
{
// Construction
public:
	CDxCRCDlg(CWnd* pParent = NULL);	// standard constructor
	void GetFileChksum(unsigned long *oldChkSum, unsigned long *newChkSum);

// Dialog Data
	//{{AFX_DATA(CDxCRCDlg)
	enum { IDD = IDD_DXCRC_DIALOG };
	CString	m_strFileName;
	CString	m_strCrc;
	unsigned long m_newChkSum;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDxCRCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDxCRCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButtonCheck();
	afx_msg void OnButtonUpdate();
	afx_msg void OnDropFiles( HDROP hDropInfo );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DXCRCDLG_H__77032BCD_1CDB_467B_B71C_D3F06195AFF9__INCLUDED_)
