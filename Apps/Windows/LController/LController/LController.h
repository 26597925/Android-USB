
// LController.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CLControllerApp:
// �� Ŭ������ ������ ���ؼ��� LController.cpp�� �����Ͻʽÿ�.
//

class CLControllerApp : public CWinApp
{
public:
	CLControllerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CLControllerApp theApp;