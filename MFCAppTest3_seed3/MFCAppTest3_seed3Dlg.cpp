// MFCAppTest3_seed3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCAppTest3_seed3.h"
#include "MFCAppTest3_seed3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAppTest3_seed3Dlg dialog

CMFCAppTest3_seed3Dlg::CMFCAppTest3_seed3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPTEST3_SEED3_DIALOG, pParent)
	, m_strInputNumber(_T(""))
	, m_strRandomNumber(_T(""))
	, m_nSuccessCount(0)
	, m_nFailureCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCAppTest3_seed3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_INPUT_NUMBER, m_strInputNumber);
	DDX_Text(pDX, IDC_STC_RANDOM_NUMBER, m_strRandomNumber);
}

BEGIN_MESSAGE_MAP(CMFCAppTest3_seed3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CMFCAppTest3_seed3Dlg::OnBnClickedBtnLogin)
	ON_EN_CHANGE(IDC_EDT_INPUT_NUMBER, &CMFCAppTest3_seed3Dlg::OnEnChangeEdtInputNumber)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCAppTest3_seed3Dlg initialization

BOOL CMFCAppTest3_seed3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// Generate initial random number
	GenerateRandomNumber();

	// Start timer to update random number every 3 seconds
	SetTimer(TIMER_ID_RANDOM, 3000, NULL);

	return TRUE;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCAppTest3_seed3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCAppTest3_seed3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Generate random 6-digit number
void CMFCAppTest3_seed3Dlg::GenerateRandomNumber()
{
	// Seed random number generator
	static bool bSeeded = false;
	if (!bSeeded)
	{
		srand(static_cast<unsigned int>(time(NULL)));
		bSeeded = true;
	}

	// Generate random 6-digit number
	int nRandom = rand() % 900000 + 100000;
	m_strRandomNumber.Format(_T("%06d"), nRandom);

	// Update the display
	UpdateData(FALSE);
}

// Login button click event
void CMFCAppTest3_seed3Dlg::OnBnClickedBtnLogin()
{
	UpdateData(TRUE);

	// Check if input is 6 digits
	if (m_strInputNumber.GetLength() != 6)
	{
		AfxMessageBox(_T("请输入6位数字！"), MB_ICONINFORMATION);
		return;
	}

	// Validate input against random number
	if (m_strInputNumber == m_strRandomNumber)
	{
		// Correct
		m_nSuccessCount++;
		AfxMessageBox(_T("输入正确！"), MB_ICONINFORMATION);
	}
	else
	{
		// Incorrect
		m_nFailureCount++;
		AfxMessageBox(_T("输入错误！"), MB_ICONERROR);
	}

	// Update success/failure count display
	UpdateCountDisplay();
}

// Input number edit box change event
void CMFCAppTest3_seed3Dlg::OnEnChangeEdtInputNumber()
{
	UpdateData(TRUE);

	// Check if input is 6 digits
	if (m_strInputNumber.GetLength() == 6)
	{
		// Validate input against random number
		if (m_strInputNumber == m_strRandomNumber)
		{
			// Correct
			m_nSuccessCount++;
			AfxMessageBox(_T("输入正确！"), MB_ICONINFORMATION);
		}
		else
		{
			// Incorrect
			m_nFailureCount++;
			AfxMessageBox(_T("输入错误！"), MB_ICONERROR);
		}

		// Update success/failure count display
		UpdateCountDisplay();

		// Clear input box
		m_strInputNumber.Empty();
		UpdateData(FALSE);
	}
}

// Timer event handler
void CMFCAppTest3_seed3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_ID_RANDOM)
	{
		// Generate new random number
		GenerateRandomNumber();
	}

	CDialogEx::OnTimer(nIDEvent);
}

// Update success/failure count display
void CMFCAppTest3_seed3Dlg::UpdateCountDisplay()
{
	// Get the login button
	CButton* pBtnLogin = static_cast<CButton*>(GetDlgItem(IDC_BTN_LOGIN));
	if (pBtnLogin == NULL)
		return;

	// Update button text with success/failure count
	CString strBtnText;
	strBtnText.Format(_T("登录\n成功: %d\n失败: %d"), m_nSuccessCount, m_nFailureCount);
	pBtnLogin->SetWindowText(strBtnText);
}
