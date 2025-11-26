// MainDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCAppTest3.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainDlg 对话框

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
	, m_nSuccessCount(0)
	, m_nFailureCount(0)
	, m_nTimerID(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_WELCOME_IMAGE, m_wndWelcomeImage);
	DDX_Control(pDX, IDC_STATIC_RANDOM_NUMBER, m_wndRandomNumber);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_wndInputEdit);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_wndLoginButton);
	DDX_Control(pDX, IDC_STATIC_SUCCESS_COUNT, m_wndSuccessCount);
	DDX_Control(pDX, IDC_STATIC_FAILURE_COUNT, m_wndFailureCount);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_INPUT, &CMainDlg::OnEnChangeInputEdit)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CMainDlg::OnBnClickedLoginButton)
END_MESSAGE_MAP()

// CMainDlg 初始化

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将 "关于..." 菜单项添加到系统菜单中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	setIcon(m_hIcon, TRUE);
	setIcon(m_hIcon, FALSE);

	// TODO: 在此添加额外的初始化代码

	// 设置欢迎图片（使用默认图标作为示例）
	m_wndWelcomeImage.SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	// 生成初始随机数字
	GenerateRandomNumber();
	m_wndRandomNumber.SetWindowText(m_strRandomNumber);

	// 设置输入框只能输入数字
	m_wndInputEdit.SetLimitText(6); // 限制输入6位

	// 更新统计信息显示
	UpdateStatistics();

	// 启动定时器，每3秒更新一次随机数字
	m_nTimerID = SetTimer(1, 3000, nullptr);

	return TRUE;
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 当用户拖动最小化窗口时系统调用此函数取得光标
//
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 生成随机6位数字
void CMainDlg::GenerateRandomNumber()
{
	// 生成100000到999999之间的随机数
	int nRandom = 100000 + rand() % 900000;
	m_strRandomNumber.Format(_T("%d"), nRandom);
}

// 更新统计信息显示
void CMainDlg::UpdateStatistics()
{
	CString strSuccess, strFailure;
	strSuccess.Format(_T("成功: %d"), m_nSuccessCount);
	strFailure.Format(_T("失败: %d"), m_nFailureCount);
	m_wndSuccessCount.SetWindowText(strSuccess);
	m_wndFailureCount.SetWindowText(strFailure);
}

// 定时器消息处理函数，每3秒更新一次随机数字
void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == m_nTimerID)
	{
		// 生成新的随机数字
		GenerateRandomNumber();
		m_wndRandomNumber.SetWindowText(m_strRandomNumber);

		// 清空输入框
		m_wndInputEdit.SetWindowText(_T(""));
	}

	CDialogEx::OnTimer(nIDEvent);
}

// 输入框内容变化处理函数
void CMainDlg::OnEnChangeInputEdit()
{
	// 获取输入框内容
	CString strInput;
	m_wndInputEdit.GetWindowText(strInput);

	// 只允许输入数字，过滤非数字字符
	CString strFiltered;
	for (int i = 0; i < strInput.GetLength(); i++)
	{
		TCHAR ch = strInput.GetAt(i);
		if (isdigit(ch))
		{
			strFiltered += ch;
		}
	}

	// 如果内容被过滤了，更新输入框
	if (strFiltered != strInput)
	{
		m_wndInputEdit.SetWindowText(strFiltered);
		// 将光标移到最后
		m_wndInputEdit.SetSel(strFiltered.GetLength(), strFiltered.GetLength());
	}

	// 如果输入了6位数字，自动进行验证
	if (strFiltered.GetLength() == 6)
	{
		// 比较输入的数字和随机数字
		if (strFiltered == m_strRandomNumber)
		{
			// 验证正确
			m_nSuccessCount++;
			AfxMessageBox(_T("校验正确！"), MB_ICONINFORMATION | MB_OK);
		}
		else
		{
			// 验证失败
			m_nFailureCount++;
			AfxMessageBox(_T("校验失败，请重新输入。"), MB_ICONWARNING | MB_OK);
		}

		// 更新统计信息
		UpdateStatistics();

		// 清空输入框
		m_wndInputEdit.SetWindowText(_T(""));
	}
}

// 登录按钮点击处理函数
void CMainDlg::OnBnClickedLoginButton()
{
	// 获取输入框内容
	CString strInput;
	m_wndInputEdit.GetWindowText(strInput);

	// 检查输入是否为6位数字
	if (strInput.GetLength() != 6)
	{
		AfxMessageBox(_T("请输入6位数字！"), MB_ICONWARNING | MB_OK);
		return;
	}

	// 比较输入的数字和随机数字
	if (strInput == m_strRandomNumber)
	{
		// 验证正确
		m_nSuccessCount++;
		AfxMessageBox(_T("校验正确！"), MB_ICONINFORMATION | MB_OK);
	}
	else
	{
		// 验证失败
		m_nFailureCount++;
		AfxMessageBox(_T("校验失败，请重新输入。"), MB_ICONWARNING | MB_OK);
	}

	// 更新统计信息
	UpdateStatistics();

	// 清空输入框
	m_wndInputEdit.SetWindowText(_T(""));
}
