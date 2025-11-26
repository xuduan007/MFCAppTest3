// MFCAppTest3.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"

// CMFCAppTest3App:
// 有关此类的实现，请参阅 MFCAppTest3.cpp
//

class CMFCAppTest3App : public CWinApp
{
public:
	CMFCAppTest3App() noexcept;

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CMFCAppTest3App theApp;
