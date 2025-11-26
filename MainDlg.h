// MainDlg.h: 头文件
//

#pragma once

// CMainDlg 对话框
class CMainDlg : public CDialogEx
{
// 构造
public:
	CMainDlg(CWnd* pParent = nullptr);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CStatic m_wndWelcomeImage; // 欢迎图片控件
	CStatic m_wndRandomNumber; // 随机数字显示控件
	CEdit m_wndInputEdit; // 输入框控件
	CButton m_wndLoginButton; // 登录按钮
	CStatic m_wndSuccessCount; // 成功次数显示控件
	CStatic m_wndFailureCount; // 失败次数显示控件

	UINT_PTR m_nTimerID; // 定时器ID
	CString m_strRandomNumber; // 随机生成的6位数字
	int m_nSuccessCount; // 成功次数
	int m_nFailureCount; // 失败次数

	// 生成随机6位数字
	void GenerateRandomNumber();
	// 更新统计信息显示
	void UpdateStatistics();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent); // 定时器消息处理
	afx_msg void OnEnChangeInputEdit(); // 输入框内容变化处理
	afx_msg void OnBnClickedLoginButton(); // 登录按钮点击处理
};
