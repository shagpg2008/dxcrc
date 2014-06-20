// DxCRCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DxCRC.h"
#include "DxCRCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef unsigned long dword;
static unsigned int util_long_check_sum_r(byte *data, size_t length)
{
#define BOC32(x) x
  unsigned int temp = 0;
  unsigned int checksum = -1;
  unsigned char *p = data + length;
  int i;
  
  i = length & 3;
  if(i) {
    /* process unaligned bytes */
    length -= i;
    while(i--) {
      p--;
      temp <<= 8;
      temp |= *p;
    }
    checksum ^= temp;
  }
  else if(length) {
    /* process first dword */
    p -= 4;
    checksum ^= BOC32(*(dword*)p);
    length -= 4;
  }
  
  length >>= 2;
  
  while(length) {
#define ror(x) ((x >> 1) | ((x & 1) << 31))
    checksum = ror(checksum);
    if(!(length & 0x1F)) {
      checksum = ror(checksum);
      if(!(length & 0x3FF)) {
        checksum = ror(checksum);
        if(!(length & 0x7FFF)) {
          checksum = ror(checksum);
          if(!(length & 0xFFFFF)) {
            checksum = ror(checksum);
          }
        }
      }
    }
    
    p -= 4;
    checksum ^= BOC32(*(dword*)p);
    length--;
  }
  
  return checksum;
}

void GetBakeFileName(const char *filename, char *backup, int len)
{
	FILE *fp = NULL;
	char file[260] = {0};
	char *tmp = NULL;
	const char *ext = NULL;
	int index = 0;
	strncpy(file, filename, sizeof(file)-1);
	if((tmp = strrchr(file, '.')) == NULL) {
		ext = "";
		tmp = file + strlen(file);
	} else {
		ext = filename+(int)(tmp-file);
	}

	do {
		sprintf(tmp, "_%d%s", index++, ext);
		if(fp != NULL) {
			fclose(fp);
		}
	}while((fp=fopen(file, "rb")) != NULL);
	strncpy(backup, file, len);
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDxCRCDlg dialog

CDxCRCDlg::CDxCRCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDxCRCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDxCRCDlg)
	m_strFileName = _T("");
	m_strCrc = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDxCRCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDxCRCDlg)
	DDX_Text(pDX, IDC_EDIT2, m_strFileName);
	DDX_Text(pDX, IDC_EDIT3, m_strCrc);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDxCRCDlg, CDialog)
	//{{AFX_MSG_MAP(CDxCRCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DROPFILES()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHECK, OnButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDxCRCDlg message handlers

BOOL CDxCRCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDxCRCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDxCRCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDxCRCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDxCRCDlg::OnOK() 
{
	CFileDialog dlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
		_T("IMAGE Files (*.IMG)|*.IMG||"));
	if(dlg.DoModal() != IDOK) {
		return ;
	}

	m_strFileName = dlg.GetPathName();
	unsigned long oldChkSum = 0;
	GetFileChksum(&oldChkSum, &m_newChkSum);
	char buff[128] = {0};
	sprintf(buff, "Checksum 0x%08X is%s correct!", oldChkSum, m_newChkSum==oldChkSum?"":"n't");
	m_strCrc = buff;
	GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(m_newChkSum!=oldChkSum);
	UpdateData(FALSE);
//	CDialog::OnOK();
}

void CDxCRCDlg::GetFileChksum(unsigned long *oldChkSum, unsigned long *newChkSum)
{
	FILE *fp = NULL;
	char *data = NULL;
	size_t size = 0;
	unsigned long chcksum = 0;

//	UpdateData();
	if(m_strFileName == _T("")) {
		AfxMessageBox(_T("Please select the image file first!"));
		return ;
	}

	if((fp = fopen(m_strFileName, "rb")) == NULL) {
		AfxMessageBox(_T("The image file doestn't exist!"));
		return ;
	}

	if(newChkSum != NULL) {
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		rewind(fp);
	} else {
		char buff[8] = {0};
		fread(data, 1, sizeof(buff), fp);
		*oldChkSum = *(unsigned long *)(buff+4);
		fclose(fp);
		return ;
	}

	if((data = (char*)malloc(size)) == NULL) {
		fclose(fp);
		AfxMessageBox(_T("Allocate memory failed!"));
		return ;
	}

	fread(data, 1, size, fp);
	*oldChkSum = *(unsigned long *)(data+8);
	*newChkSum = util_long_check_sum_r((unsigned char *)(data+12), size-12);
	fclose(fp);
}

void CDxCRCDlg::OnButtonCheck() 
{
	unsigned long oldChkSum = 0, newChkSum = 0;
	GetFileChksum(&oldChkSum, &newChkSum);
}

void CDxCRCDlg::OnButtonUpdate() 
{
	FILE *fp = NULL;
	size_t size = 0;
	char *data = NULL;
	char szDstFileName[MAX_PATH] = {0};
	unsigned long oldChkSum = 0, newChkSum = 0;

	if((fp = fopen(m_strFileName, "rb")) == NULL) {
		AfxMessageBox(_T("The image file doestn't exist!"));
		return ;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	if((data = (char*)malloc(size)) == NULL) {
		fclose(fp);
		AfxMessageBox(_T("Allocate memory failed!"));
		return ;
	}

	fread(data, 1, size, fp);
	fclose(fp);

	oldChkSum = *(unsigned long *)(data+8);
	newChkSum = util_long_check_sum_r((unsigned char *)(data+12), size-12);
	if(newChkSum == oldChkSum) {
		AfxMessageBox(_T("File check sum is right!"));
		char buff[128] = {0};
		sprintf(buff, "Checksum 0x%08X is%s correct!", oldChkSum, newChkSum==oldChkSum?"":"n't");
		m_strCrc = buff;
		GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}

	memcpy(data+8, &newChkSum, sizeof(newChkSum));
	GetBakeFileName(m_strFileName, szDstFileName, sizeof(szDstFileName));
	if((fp=fopen(szDstFileName, "wb")) == NULL) {
		AfxMessageBox(_T("Open temperory file failed!"));
		return ;
	}

	fwrite(data, 1, size, fp);
	fclose(fp);

	char buff[1024] = {0};
	sprintf(buff, "The right image file \"%s\" updated successfully!", szDstFileName);
	AfxMessageBox(buff);
}


void CDxCRCDlg::OnDropFiles( HDROP hDropInfo )
{
	CString strFileName;
	char szFile[MAX_PATH] = {0};
	DragQueryFile(hDropInfo, 0, szFile, sizeof(szFile));
	DragFinish(hDropInfo);
	
	int len = strlen(szFile) - sizeof(".IMG") + 1;
	char *lpFileSuffix = szFile + len;
	if(len < 0 || stricmp(lpFileSuffix, ".img") != 0) {
		AfxMessageBox(_T("You must select DMX image file!"));
		return;
	}

	m_strFileName = szFile;
	unsigned long oldChkSum = 0;
	GetFileChksum(&oldChkSum, &m_newChkSum);
	m_strCrc.Format(_T("Checksum 0x%08X is%s correct!"), oldChkSum, m_newChkSum==oldChkSum?"":"n't");
	GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(m_newChkSum!=oldChkSum);
	UpdateData(FALSE);
}
