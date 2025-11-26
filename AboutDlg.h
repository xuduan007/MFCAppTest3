// AboutDlg.h: 头文件
//

#pragma once

// CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};
