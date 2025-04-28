// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해
// 추가적으로 제공되는 내용입니다.
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// RMStock.h: RMStock 응용 프로그램의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"
#include "MSDIWinApp.h"
#include "khopenapictrl.h"

class CGridCtrl;
class CRMStockApp : public CMSDIWinApp
{
public:
	CRMStockApp() noexcept;

public:
	CString	m_sAppPath;		// 실행 파일 패스
	CKhopenapictrl m_khOpenApi;

// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	UINT  m_nAppLook;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	CString ConvDataFormat(int nType, LPCTSTR szData, LPCTSTR szBeforeData = "", LPCTSTR szAfterData = "");
	void SetSignData(CGridCtrl *pGrid, int nRow, int nCol, LPCTSTR szData);
	void SetDataFgColour(CGridCtrl *pGrid, int nRow, int nCol, LPCTSTR szData);		// 그리드 셀 문자색 변경
	BOOL IsError(long lErrCode);

};

extern CRMStockApp theApp;
