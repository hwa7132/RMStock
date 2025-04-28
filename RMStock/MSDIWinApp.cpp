#include "pch.h"
#include "MSDIWinApp.h"

BEGIN_MESSAGE_MAP(CMSDIWinApp, CWinAppEx)
  //{{AFX_MSG_MAP(CMSDIWinApp)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMSDIWinApp::CMSDIWinApp() : CWinAppEx()
{
	m_pRecentFileList = nullptr;
}

CDocument* CMSDIWinApp::OpenDocumentFile(LPCTSTR pszPathName)
{
	CDocument* pDoc = nullptr;
	POSITION pos = GetFirstDocTemplatePosition();
	ASSERT(NULL != pos);

	CFileFind cff;
	if ( (false == CString(pszPathName).IsEmpty()) && (FALSE == cff.FindFile(pszPathName)) )
	{
		AfxMessageBox(_T("파일을 찾을 수 없습니다."));
	}
	else
	{
		CDocTemplate* pTemplate = GetNextDocTemplate(pos);
		if (CloseDocument())
		{
			if (nullptr != pszPathName)
			{
				pTemplate->OpenDocumentFile(CString(pszPathName));
			}
			else
			{
				pTemplate->OpenDocumentFile(NULL);
			}
		}
	
		pos = pTemplate->GetFirstDocPosition();

		if (nullptr != pos)
		{
			pDoc = pTemplate->GetNextDoc(pos);
		}
	}

	return pDoc;
}

void CMSDIWinApp::OnFilePrintSetup()
{
	CWinAppEx::OnFilePrintSetup();
}

#ifndef WIN32
POSITION CMSDIWinApp::GetFirstDocTemplatePosition() const
{
  return m_templateList.GetHeadPosition();
}

CDocTemplate* CMSDIWinApp::GetNextDocTemplate(POSITION& rPosition) const
{
  return (CDocTemplate*)m_templateList.GetNext(rPosition);
}
#endif

BOOL CMSDIWinApp::CloseDocument()
{
	BOOL bResult = FALSE;
	if (CWinAppEx::SaveAllModified())
	{
		POSITION pos = GetFirstDocTemplatePosition();
		ASSERT(NULL != pos);
		CDocTemplate* pTemplate = GetNextDocTemplate(pos);

		pos = pTemplate->GetFirstDocPosition();
		if (nullptr != pos)
		{
			CDocument* pDoc = pTemplate->GetNextDoc(pos);
			if (nullptr != pDoc)
			{
				pDoc->OnCloseDocument();
			}
		}
		
		static_cast<CMSDITemplate*>(pTemplate)->SetUntitleCount(0);

		bResult = TRUE;
	}

	return bResult;
}

CMSDITemplate* CMSDIWinApp::GetDocTemplate(CRuntimeClass* pViewClass)
{
	CMSDITemplate *pResult = nullptr;
	POSITION pos = GetFirstDocTemplatePosition();

	while (NULL != pos)
	{
		CMSDITemplate* pTemplate = static_cast<CMSDITemplate*>(GetNextDocTemplate(pos));
		if (pTemplate->GetViewClass() == pViewClass)
		{
			pResult = pTemplate;
			break;
		}
	}

	return pResult;
}

CMSDITemplate* CMSDIWinApp::GetDocTemplate(CView* pView)
{
	CMSDITemplate *pResult = NULL;
	POSITION pos = GetFirstDocTemplatePosition();

	while (NULL != pos)
	{
		CMSDITemplate* pTemplate = static_cast<CMSDITemplate*>(GetNextDocTemplate(pos));
		if (pView->IsKindOf(pTemplate->GetViewClass()))
		{
			pResult = pTemplate;
			break;
		}
	}

	return pResult;
}

CDocument* CMSDIWinApp::GetDocument()
{
	CDocument *pResult = NULL;
	CMDIChildWnd* pMDIActive = dynamic_cast<CMDIFrameWnd*>(m_pMainWnd)->MDIGetActive();
	if (nullptr != pMDIActive)
	{
		pResult = pMDIActive->GetActiveDocument();
	}

	return pResult;
}

CView* CMSDIWinApp::GetView(CRuntimeClass* pViewClass)
{
	CView *pResult = nullptr;

	CDocument* pDoc = GetDocument();
	if (nullptr != pDoc)
	{
		POSITION pos = pDoc->GetFirstViewPosition();

		while (NULL != pos)
		{
			CView* pView = pDoc->GetNextView(pos);
			if (pView->IsKindOf(pViewClass))
			{
				pResult = pView;
				break;
			}
		}
	}

	return pResult;
}

CMDIChildWnd* CMSDIWinApp::CreateOrActivateFrame(CRuntimeClass* pViewClass, CDocument* pDoc)
{
	m_pMainWnd->LockWindowUpdate();

	CMDIChildWnd* pResult = nullptr;

	if (nullptr != pDoc)
	{
		CView* pView = GetView(pViewClass);
		if (nullptr != pView)
		{
			pView->GetParentFrame()->ActivateFrame(SW_SHOWMAXIMIZED);
			pResult = dynamic_cast<CMDIChildWnd*>(pView->GetParentFrame());
		}
	}
	
	if ( nullptr == pResult )
	{
		// find the doc template with this view
		CMSDITemplate* pTemplate = GetDocTemplate(pViewClass);
		if (nullptr != pTemplate)
		{
			CMDIChildWnd* pNewFrame = dynamic_cast<CMDIChildWnd*>(pTemplate->CreateNewFrame(pDoc, NULL));
			if (nullptr != pNewFrame)
			{
				pTemplate->InitialUpdateFrame(pNewFrame, pDoc);

				// use the fist string for window title
				CString strTitle;
				pTemplate->GetDocString(strTitle, CDocTemplate::windowTitle);
				pNewFrame->SetWindowText(strTitle);
				pNewFrame->ActivateFrame(SW_SHOWMAXIMIZED);

				pResult = pNewFrame;
			}
		}
	}

	m_pMainWnd->UnlockWindowUpdate();

	return pResult;
}

int CMSDIWinApp::ExitInstance() 
{
	return CWinAppEx::ExitInstance();
}
