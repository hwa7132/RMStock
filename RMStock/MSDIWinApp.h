#if !defined(AFX_MSDIWINAPP_H__F2F0253E_4AAB_419B_96BB_24C01824725B__INCLUDED_)
#define AFX_MSDIWINAPP_H__F2F0253E_4AAB_419B_96BB_24C01824725B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"

class CMainFrame;
class CMSDITemplate;

class CMSDIWinApp : public CWinAppEx
{
public:
	CMSDIWinApp();
	CMSDITemplate* GetDocTemplate(CRuntimeClass* pViewClass);
	CMSDITemplate* GetDocTemplate(CView* pView);
	CDocument* GetDocument();
	CView* GetView(CRuntimeClass* pViewClass);
	
#ifndef WIN32
public:
	POSITION GetFirstDocTemplatePosition() const;
	CDocTemplate* GetNextDocTemplate(POSITION& rPosition) const;
#endif

// Implementation
public:
	virtual BOOL CloseDocument();
	virtual CMDIChildWnd* CreateOrActivateFrame(CRuntimeClass* pViewClass, CDocument* pDoc);
	virtual CDocument* OpenDocumentFile(LPCTSTR pszPathName);

	int ExitInstance() override;

	//{{AFX_MSG(CMSDIWinApp)		
	afx_msg void OnFilePrintSetup();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CMSDITemplate : public CMultiDocTemplate
{
// Constructors
public:
	CMSDITemplate(UINT32 nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass) :
	CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass) {};

	void SetUntitleCount(UINT Count)
	{ m_nUntitledCount = Count; };

	CRuntimeClass* GetViewClass()	{ return m_pViewClass; }
	CRuntimeClass* GetDocClass()	{ return m_pDocClass; }
};

#endif // !defined(AFX_MSDIWINAPP_H__F2F0253E_4AAB_419B_96BB_24C01824725B__INCLUDED_)
